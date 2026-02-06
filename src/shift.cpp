#include "shift.hpp"

#include <limits>

#include "event.hpp"
#include "errors.hpp"

namespace
{
  enum ErrorID
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
    return turnTimeToString(time) + ' ' + std::to_string(ERROR) + ' ' + error;
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

size_t Shift::getShiftTablesNumber() const noexcept
{
  return tables_n;
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
