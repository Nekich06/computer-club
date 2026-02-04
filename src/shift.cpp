#include "shift.hpp"

#include <limits>

namespace
{
  enum Errors {
    YOU_SHALL_NOT_PASS,
    NOT_OPEN_YET,
    PLACE_IS_BUSY,
    CLIENT_UNKNOWN,
    I_CAN_WAIT_NO_LONGER
  };

  std::string err_msgs[] = {
    "YouShallNotPass",
    "NotOpenYet",
    "PlaceIsBusy",
    "ClientUknown",
    "ICanWaitNoLonger!"
  };

  std::pair< Time, Time > initShiftTime(std::ifstream & shift_record)
  {
    std::string time_start;
    shift_record >> time_start;
    Time start = parseTimeStringToObject(time_start);

    std::string time_end;
    shift_record >> time_end;
    Time end = parseTimeStringToObject(time_end);
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
      throw std::invalid_argument(err_msgs[YOU_SHALL_NOT_PASS]);
    }
  }
  else
  {
    throw std::invalid_argument(err_msgs[NOT_OPEN_YET]);
  }
}

std::ostream & Shift::Table::outputBusyTime(std::ostream & out) const
{
  return out << busy_time;
}

Shift initShiftByFileData(std::ifstream & shift_record)
{
  long long int tables = 0;
  shift_record >> tables;
  if (tables <= 0)
  {
    throw std::invalid_argument(std::to_string(tables));
  }

  std::pair< Time, Time > work_time = initShiftTime(shift_record);

  long long int price = 0;
  shift_record >> price;
  if (price <= 0)
  {
    throw std::invalid_argument(std::to_string(price));
  }

  shift_record.ignore(std::numeric_limits< std::streamsize >::max(), '\n');

  return Shift(tables, price, work_time.first, work_time.second);
}

