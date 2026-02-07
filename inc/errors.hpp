#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>
#include <string>

#include "event.hpp"
#include "time.hpp"

class ClientError : public std::exception
{
public:
  explicit ClientError(const std::string & msg);
  const char * what() const noexcept override;
private:
  const std::string message;
};

class FormatError : public std::exception
{
public:
  explicit FormatError(const std::string & msg);
  const char * what() const noexcept override;
private:
  const std::string message;
};

class OutgoingEvent : public std::exception
{
public:
  explicit OutgoingEvent(const Time & event_time, const std::string & client_name, EventID id, long long table);
  const char * what() const noexcept override;
  const Event getEventInfo() const;
private:
  const Time time;
  const std::string name;
  const EventID event_id;
  const long long table_num;
};

#endif
