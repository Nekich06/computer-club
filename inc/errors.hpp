#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>

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

#endif
