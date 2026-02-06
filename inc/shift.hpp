#ifndef SHIFT_HPP
#define SHIFT_HPP

#include <iostream>
#include <cstddef>
#include <string>
#include <map>

#include "time.hpp"

struct Client
{
  bool is_inside;
  bool is_waiting;
  size_t table_num;
  std::string name;
};

struct Shift
{
  Shift(size_t tables_num, size_t price_per_hour, const Time & time_start, const Time & time_end);
  ~Shift();
  Time getShiftStartTime() const;
  Time getShiftEndTime() const;
  size_t getShiftTablesNumber() const noexcept;
  void recordClient(const Time & time, const Client & client);
  void toSeatClient(Client & client);
private:
  struct Table
  {
    std::ostream & outputBusyTime(std::ostream & out) const;
  private:
    size_t profit = 0;
    Time busy_time;
  };
  size_t tables_n;
  size_t price;
  Time start;
  Time end;
  Table * tables;
  std::map< std::string, Client > clients;
};

#endif
