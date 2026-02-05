#include "shift.hpp"

#include <limits>

#include "errors.hpp"

namespace
{
  std::string errors_id = "13";

  enum Errors
  {
    YOU_SHALL_NOT_PASS,
    NOT_OPEN_YET,
    PLACE_IS_BUSY,
    CLIENT_UNKNOWN,
    I_CAN_WAIT_NO_LONGER
  };

  std::string errors[] =
  {
    "YouShallNotPass",
    "NotOpenYet",
    "PlaceIsBusy",
    "ClientUknown",
    "ICanWaitNoLonger!"
  };

  std::string formatError(const Time & time, std::string & error)
  {
    return turnTimeToString(time) + ' ' + errors_id + ' ' + error;
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

Time Shift::getShiftStartTime() const
{
  return start;
}

Time Shift::getShiftEndTime() const
{
  return end;
}

void Shift::recordClient(const Time & time, const Client & client)
{
  if (time >= start && time < end)
  {
    if (!clients.insert({ client.name, client }).second)
    {
      throw ClientError(formatError(time, errors[YOU_SHALL_NOT_PASS]));
    }
  }
  else
  {
    throw ClientError(formatError(time, errors[NOT_OPEN_YET]));
  }
}

std::ostream & Shift::Table::outputBusyTime(std::ostream & out) const
{
  return out << busy_time;
}
