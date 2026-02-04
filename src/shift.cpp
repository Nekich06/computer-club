#include "shift.hpp"

namespace
{
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
      minutes = std::stoi(str_hours);
    }

    return Time(hours, minutes);
  }

  std::pair< Time, Time > initShiftTime(std::ifstream & shift_record)
  {
    std::string time_start;
    shift_record >> time_start;
    Time start = parseTimeStringToObject(time_start);

    std::string time_end;
    shift_record >> time_end;
    Time end = parseTimeStringToObject(time_end);
    return std::make_pair(start, end);
  }
}

Shift::Shift(size_t tables_num, size_t price_per_hour, const Time & time_start, const Time & time_end):
  tables_n(tables_num),
  price(price_per_hour),
  start(time_start),
  end(time_end),
  tables(nullptr)
{
  tables = new Table[tables_n];
}

Shift::~Shift()
{
  delete[] tables;
}

std::ostream & Shift::Table::outputBusyTime(std::ostream & out)
{
  out << this->busy_time;
}

Shift initShiftByFileData(std::ifstream & shift_record)
{
  long long int tables = 0;
  shift_record >> tables;
  if (tables <= 0)
  {
    throw std::invalid_argument("Invalid value of tables number");
  }

  std::pair< Time, Time > work_time = initShiftTime(shift_record);

  long long int price = 0;
  shift_record >> price;
  if (price <= 0)
  {
    throw std::invalid_argument("Invalid value of price per hour");
  }

  return Shift(tables, price, work_time.first, work_time.second);
}
