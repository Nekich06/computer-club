#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

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
  OutgoingEvent(const Event & event);
  const Event getEventInfo() const;
private:
  const Event outgoing_event;
};

#endif
