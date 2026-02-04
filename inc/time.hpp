#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>

struct Time
{
  Time();
  Time(int hours, int minutes);
  bool operator<(const Time & rhs) const noexcept;
  bool operator>=(const Time & rhs) const noexcept;
  int getHours() const noexcept;
  int getMinutes() const noexcept;
private:
  int h;
  int m;
};

std::ostream & operator<<(std::ostream & out, const Time & time);
Time parseTimeStringToObject(const std::string & time);

#endif
