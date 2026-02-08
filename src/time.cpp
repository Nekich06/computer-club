#include "time.hpp"

#include <cmath>

Time::Time():
  h(0),
  m(0)
{}

Time::Time(int hours, int minutes):
  h(hours),
  m(minutes)
{
  if (h < 0 || h > 23)
  {
    throw std::invalid_argument("Invalid hours format");
  }
  else if (m < 0 || m > 59)
  {
    throw std::invalid_argument("Invalid minutes format");
  }
}

bool Time::operator<(const Time & rhs) const noexcept
{
  if (getHours() < rhs.getHours())
  {
    return true;
  }
  else if (getHours() == rhs.getHours())
  {
    return getMinutes() < rhs.getMinutes();
  }
  else
  {
    return false;
  }
}

bool Time::operator>=(const Time & rhs) const noexcept
{
  return !(*this < rhs);
}

bool Time::operator==(const Time & rhs) const noexcept
{
  return h == rhs.h && m == rhs.m;
}

bool Time::operator!=(const Time & rhs) const noexcept
{
  return !(*this == rhs);
}

Time Time::operator+(const Time & rhs) const
{
  int this_minutes = h * 60 + m;
  int rhs_minutes = rhs.h * 60 + rhs.m;
  int result_minutes = this_minutes + rhs_minutes;
  int hours = result_minutes / 60;
  int minutes = result_minutes % 60;
  return Time(hours, minutes);
}

Time Time::operator-(const Time & rhs) const
{
  if (*this < rhs)
  {
    throw std::invalid_argument("Time is not consistent");
  }
  int this_minutes = h * 60 + m;
  int rhs_minutes = rhs.h * 60 + rhs.m;
  int result_minutes = this_minutes - rhs_minutes;
  int hours = result_minutes / 60;
  int minutes = result_minutes % 60;
  return Time(hours, minutes);
}

int Time::getHours() const noexcept
{
  return this->h;
}

int Time::getMinutes() const noexcept
{
  return this->m;
}

std::ostream & operator<<(std::ostream & out, const Time & time)
{
  std::string hours = std::to_string(time.getHours());
  if (hours.length() == 1)
  {
    out << '0' << hours;
  }
  else
  {
    out << hours;
  }

  out << ':';

  std::string minutes = std::to_string(time.getMinutes());
  if (minutes.length() == 1)
  {
    out << '0' << minutes;
  }
  else
  {
    out << minutes;
  }

  return out;
}

Time parseTimeStringToObject(const std::string & time)
{
  std::string str_hours = time.substr(0, 2);
  int hours = 0;
  if (str_hours[0] == '0')
  {
    hours = str_hours[1] - '0';
  }
  else
  {
    hours = std::stoi(str_hours);
  }

  std::string str_minutes = time.substr(3, 2);
  int minutes = 0;
  if (str_minutes[0] == '0')
  {
    minutes = str_minutes[1] - '0';
  }
  else
  {
    minutes = std::stoi(str_minutes);
  }

  return Time(hours, minutes);
}

std::string turnTimeToString(const Time & time)
{
  std::string hours = std::to_string(time.getHours());
  if (hours.length() == 1)
  {
    hours = '0' + hours;
  }

  std::string minutes = std::to_string(time.getMinutes());
  if (minutes.length() == 1)
  {
    minutes = '0' + minutes;
  }

  return hours + ':' + minutes;
}
