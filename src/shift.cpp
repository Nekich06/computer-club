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

  std::string formatEventInfo(const Time & time, const std::string & client_name, EventID id, long long table_num)
  {
    if (table_num)
    {
      return (turnTimeToString(time) + ' ' + std::to_string(id) + ' ' + client_name + ' ' + std::to_string(table_num));
    }
    else
    {
      return (turnTimeToString(time) + ' ' + std::to_string(id) + ' ' + client_name);
    }
  }
}

Shift::Shift(size_t tables_num, size_t price_per_hour, const Time & time_start, const Time & time_end):
  tables_n(tables_num),
  price(price_per_hour),
  start(time_start),
  end(time_end),
  tables(nullptr),
  clients(),
  waiting_queue()
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

size_t Shift::getShiftPrice() const noexcept
{
  return price;
}

size_t Shift::getShiftClientsNumber() const
{
  return clients.size();
}

std::list< std::string > Shift::getCurrentClientsNames() const
{
  std::list< std::string > clients_names;
  for (auto it = clients.cbegin(); it != clients.cend(); ++it)
  {
    clients_names.push_back(it->first);
  }
  return std::move(clients_names);
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

void Shift::toSeatClient(const Time & time, const std::string & client_name, size_t table_number)
{
  try
  {
    Client & client = clients.at(client_name);
    if (tables[table_number - 1].isBusy())
    {
      throw ClientError(formatError(time, errors[PLACE_IS_BUSY]));
    }
    client.table_num = table_number;
    tables[table_number - 1].takeClient(time);
  }
  catch (const std::out_of_range & e)
  {
    throw ClientError(formatError(time, errors[CLIENT_UNKNOWN]));
  }
}

void Shift::recordWaiting(const Time & time, const std::string & client_name)
{
  try
  {
    Client & client = clients.at(client_name);
    bool is_worth = true;
    for (size_t i = 0; i < tables_n; ++i)
    {
      if (!tables[i].isBusy())
      {
        is_worth = false;
      }
    }
    if (!is_worth)
    {
      throw ClientError(formatError(time, errors[I_CAN_WAIT_NO_LONGER]));
    }
    if (waiting_queue.size() != tables_n)
    {
      waiting_queue.push(client);
    }
    else
    {
      std::string msg = formatEventInfo(time, client_name, CLIENT_WENT_AWAY_BY_CAUSE, 0LL);
      throw OutgoingEvent(time, client_name, CLIENT_WENT_AWAY_BY_CAUSE, 0LL, msg);
    }
  }
  catch (const std::out_of_range & e)
  {
    throw ClientError(formatError(time, errors[CLIENT_UNKNOWN]));
  }
}

void Shift::unrecordClient(const Time & time, const std::string & client_name)
{
  try
  {
    Client & client = clients.at(client_name);
    size_t table_number = client.table_num;
    if (!table_number)
    {
      clients.erase(client_name);
    }
    else
    {
      tables[table_number - 1].getBillsAndLetGoClient(time, price);
      clients.erase(client_name);
      if (!waiting_queue.empty())
      {
        std::string waiting_client_name = waiting_queue.back().name;
        waiting_queue.pop();
        std::string msg = formatEventInfo(time, waiting_client_name, CLIENT_TOOK_THE_TABLE_AFTER_WAITING, table_number);
        throw OutgoingEvent(time, waiting_client_name, CLIENT_TOOK_THE_TABLE_AFTER_WAITING, table_number, msg);
      }
    }
  }
  catch (const std::out_of_range & e)
  {
    throw ClientError(formatError(time, errors[CLIENT_UNKNOWN]));
  }
}

void Shift::endShift()
{
  for (auto it = clients.cbegin(); it != clients.cend(); ++it)
  {
    unrecordClient(end, it->first);
  }
}

std::ostream & Shift::outputTablesInfo(std::ostream & out) const
{
  for (size_t i = 0; i < tables_n; ++i)
  {
    out << i << ' ';
    tables[i].outputInfo(out);
    out << '\n';
  }
  return out;
}

std::ostream & Shift::Table::outputInfo(std::ostream & out) const
{
  return out << profit << ' ' << total_busy_time;
}

void Shift::Table::takeClient(const Time & time)
{
  is_busy_now = true;
  last_not_busy_time = time;
}

void Shift::Table::getBillsAndLetGoClient(const Time & time, size_t price)
{
  Time client_busy_time = time - last_not_busy_time;
  profit = (client_busy_time.getHours() + 1) * price;
  total_busy_time = total_busy_time + client_busy_time;
  is_busy_now = false;
}

bool Shift::Table::isBusy()
{
  return is_busy_now;
}
