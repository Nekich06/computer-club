#ifndef SHIFT_HPP
#define SHIFT_HPP

#include "time.hpp"

#include <fstream>
#include <cstddef>
#include <queue>

struct Shift
{
  Shift(size_t tables_num, size_t price_per_hour, const Time & time_start, const Time & time_end);
  ~Shift();
private:
  struct Table
  {
    std::ostream & outputBusyTime(std::ostream & out);
  private:
    size_t profit = 0;
    Time busy_time;
  };
  size_t tables_n;
  size_t price;
  Time start;
  Time end;
  Table * tables;
};

Shift initShiftByFileData(std::ifstream & shift_record);
std::ostream & simulateShiftAndOutputInfo(std::ostream & out, std::ifstream & shift_record, Shift & shift);

#endif
