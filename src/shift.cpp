#include "shift.hpp"

#include <limits>
#include <string>

#include "simulation_errors.hpp"

namespace
{
  enum Errors
  {
    YOU_SHALL_NOT_PASS,
    NOT_OPEN_YET,
    PLACE_IS_BUSY,
    CLIENT_UNKNOWN,
    I_CAN_WAIT_NO_LONGER
  };

  const char * errors[] =
  {
    "YouShallNotPass",
    "NotOpenYet",
    "PlaceIsBusy",
    "ClientUknown",
    "ICanWaitNoLonger!"
  };

  std::string getWord(const std::string & event_info, size_t & start_pos)
  {
    size_t temp = start_pos;
    start_pos = event_info.find(' ', start_pos);
    return event_info.substr(temp, start_pos++ - temp);
  }

  std::pair< Time, Time > initShiftTime(std::ifstream & shift_record)
  {
    std::string timeline;
    Time start;
    Time end;
    std::getline(shift_record, timeline, '\n');
    try
    {
      size_t pos = 0;
      std::string time_start = getWord(timeline, pos);
      start = parseTimeStringToObject(time_start);
      std::string time_end = getWord(timeline, pos);
      end = parseTimeStringToObject(time_end);
    }
    catch (const std::invalid_argument & e)
    {
      throw FormatError(timeline.c_str());
    }
    return std::make_pair(start, end);
  }
}

Shift::Shift(size_t tables_num, size_t price_per_hour, const Time & time_start, const Time & time_end):
  tables_n(tables_num),
  price(price_per_hour),
  start(time_start),
  end(time_end),
  tables(nullptr)
{
  tables = new Table[tables_n];
}

Shift::~Shift()
{
  delete[] tables;
}

void Shift::recordClient(const Time & time, const Client & client)
{
  if (time < start)
  {
    if (!clients.insert({ client.name, client }).second)
    {
      throw ClientError(errors[YOU_SHALL_NOT_PASS]);
    }
  }
  else
  {
    throw ClientError(errors[NOT_OPEN_YET]);
  }
}

std::ostream & Shift::Table::outputBusyTime(std::ostream & out) const
{
  return out << busy_time;
}

Shift initShiftByFileData(std::ifstream & shift_record)
{
  std::string tables_str;
  std::getline(shift_record, tables_str, '\n');
  long long int tables = std::stoll(tables_str);
  if (tables <= 0)
  {
    throw FormatError(tables_str.c_str());
  }

  std::pair< Time, Time > work_time = initShiftTime(shift_record);

  std::string price_str;
  std::getline(shift_record, price_str, '\n');
  long long int price = std::stoll(price_str);
  if (price <= 0)
  {
    throw FormatError(price_str.c_str());
  }
  return Shift(tables, price, work_time.first, work_time.second);
}

