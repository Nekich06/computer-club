#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>

struct Time
{
  Time();
  Time(int hours, int minutes);
  int h;
  int m;
};

std::ostream & operator<<(std::ostream & out, const Time & time);

#endif
