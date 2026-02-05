#include "simulation_errors.hpp"

ClientError::ClientError(const char * msg):
  message(msg)
{}

const char * ClientError::what() const noexcept
{
  return message;
}

FormatError::FormatError(const char * msg):
  message(msg)
{}

const char * FormatError::what() const noexcept
{
  return message;
}

