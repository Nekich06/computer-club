#ifndef SHIFT_HPP
#define SHIFT_HPP

#include "time.hpp"

#include <fstream>
#include <cstddef>

struct Shift
{
  Shift(size_t tables_num, size_t price_per_hour, const Time & time_start, const Time & time_end);
private:
  size_t tables;
  size_t price;
  Time start;
  Time end;
};

Shift initShiftByFileData(std::ifstream & shift_record);
void simulateShift(std::ifstream & shift_record, Shift & shift);

#endif
