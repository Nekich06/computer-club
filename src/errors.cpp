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

OutgoingEvent::OutgoingEvent(const Time & event_time, const std::string & client_name, EventID id, long long table, std::string & msg):
  time(event_time),
  name(client_name),
  event_id(id),
  table_num(table),
  message(msg)
{}

const char * OutgoingEvent::what() const noexcept
{
  return message.c_str();
}

const Event OutgoingEvent::getEventInfo() const
{
  return Event{ time, event_id, name, table_num };
}
