#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

class ClientError : public std::exception
{
public:
  explicit ClientError(const char * msg);
  const char * what() const noexcept override;
private:
  const char * message;
};

class FormatError : public std::exception
{
public:
  explicit FormatError(const char * msg);
  const char * what() const noexcept override;
private:
  const char * message;
};

#endif
