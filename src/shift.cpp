#include "shift.hpp"

#include <limits>

#include "errors.hpp"

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
