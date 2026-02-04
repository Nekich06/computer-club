#include "time.hpp"

#include <string>

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

std::ostream & operator<<(std::ostream & out, const Time & time)
{
  std::string hours = std::to_string(time.h);
  if (hours.length() == 1)
  {
    out << '0' << hours;
  }
  else
  {
    out << hours;
  }

  out << ':';

  std::string minutes = std::to_string(time.m);
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
