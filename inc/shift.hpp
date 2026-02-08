#ifndef SHIFT_HPP
#define SHIFT_HPP

#include <iostream>
#include <cstddef>
#include <string>
#include <queue>
#include <list>
#include <map>

#include "time.hpp"

struct Client
{
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
  size_t getShiftPrice() const noexcept;
  size_t getShiftClientsNumber() const;
  std::list< std::string > getCurrentClientsNames() const;
  void recordClient(const Time & time, const Client & client);
  void toSeatClient(const Time & time, const std::string & client_name, size_t table_number);
  void recordWaiting(const Time & time, const std::string & client_name);
  void unrecordClient(const Time & time, const std::string & client_name);
  void endShift();
  std::ostream & outputTablesInfo(std::ostream & out) const;
private:
  struct Table
  {
    std::ostream & outputInfo(std::ostream & out) const;
    void takeClient(const Time & time);
    void getBillsAndLetGoClient(const Time & time, size_t price);
    bool isBusy();
  private:
    bool is_busy_now = false;
    size_t profit = 0;
    Time last_not_busy_time;
    Time total_busy_time;
  };
  size_t tables_n;
  size_t price;
  Time start;
  Time end;
  Table * tables;
  std::map< std::string, Client > clients;
  std::queue< Client > waiting_queue;
};

#endif
