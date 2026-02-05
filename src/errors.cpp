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

