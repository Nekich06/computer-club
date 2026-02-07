#include "errors.hpp"

ClientError::ClientError(const std::string & msg):
  message(msg)
{}

const char * ClientError::what() const noexcept
{
  return message.c_str();
}

FormatError::FormatError(const std::string & msg):
  message(msg)
{}

const char * FormatError::what() const noexcept
{
  return message.c_str();
}

OutgoingEvent::OutgoingEvent(const Time & event_time, const std::string & client_name, EventID id, long long table):
  time(event_time),
  name(client_name),
  event_id(id),
  table_num(table)
{}

const char * OutgoingEvent::what() const noexcept
{
  if (table_num)
  {
    return (turnTimeToString(time) + ' ' + std::to_string(event_id) + ' ' + name + std::to_string(table_num)).c_str();
  }
  else
  {
    return (turnTimeToString(time) + ' ' + std::to_string(event_id) + ' ' + name).c_str();
  }
}

const Event OutgoingEvent::getEventInfo() const
{
  return Event{ time, event_id, name, table_num };
}
