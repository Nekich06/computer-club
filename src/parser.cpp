#include "parser.hpp"

#include <string>

#include "exceptions.hpp"

namespace
{
  std::string getWord(const std::string & event_info, size_t & start_pos)
  {
    size_t temp = start_pos;
    start_pos = event_info.find(' ', start_pos);
    if (start_pos == std::string::npos)
    {
      return event_info.substr(temp);
    }
    return event_info.substr(temp, start_pos++ - temp);
  }

  std::pair< Time, Time > initShiftTime(std::ifstream & shift_record)
  {
    std::string timeline;
    Time start;
    Time end;
    std::getline(shift_record, timeline, '\n');
    try
    {
      size_t pos = 0;
      std::string time_start = getWord(timeline, pos);
      start = parseTimeStringToObject(time_start);
      std::string time_end = getWord(timeline, pos);
      end = parseTimeStringToObject(time_end);
    }
    catch (const std::invalid_argument &)
    {
      throw FormatError(timeline);
    }

    if (end < start)
    {
      throw FormatError(timeline);
    }

    return std::make_pair(start, end);
  }

  Shift getInitializedShift(std::ifstream & shift_record)
  {
    std::string tables_str;
    std::getline(shift_record, tables_str, '\n');
    long long int tables = std::stoll(tables_str);
    if (tables <= 0)
    {
      throw FormatError(tables_str);
    }

    std::pair< Time, Time > work_time = initShiftTime(shift_record);

    std::string price_str;
    std::getline(shift_record, price_str, '\n');
    long long int price = std::stoll(price_str);
    if (price <= 0)
    {
      throw FormatError(price_str);
    }
    return Shift(tables, price, work_time.first, work_time.second);
  }

  void fillEventsInfo(std::ifstream & shift_record, Events & events, size_t tables, Time shift_end)
  {
    std::string event_info;
    Time recent_event_time;
    while (std::getline(shift_record, event_info, '\n'))
    {
      try
      {
        size_t pos = 0;
        std::string time_str = getWord(event_info, pos);
        Time time = parseTimeStringToObject(time_str);
        if (time < recent_event_time)
        {
          throw std::invalid_argument("Events are not consistent in time");
        }
        else if (time >= shift_end)
        {
          throw std::invalid_argument("Event can not be handled after closing the shift");
        }

        int id = std::stoi(getWord(event_info, pos));
        if (id < CLIENT_CAME || id > CLIENT_WENT_AWAY)
        {
          throw std::invalid_argument("Invalid event id");
        }
        EventID event_id = static_cast< EventID >(id);

        std::string client_name = getWord(event_info, pos);
        if (event_info[pos] != '\0')
        {
          std::string table_num_str = getWord(event_info, pos);
          long long int table_num = std::stoll(table_num_str);
          if (table_num <= 0 || table_num > tables)
          {
            throw std::invalid_argument("Invalid table ordinal number");
          }
          events.push_back(Event{ time, event_id, client_name, table_num });
        }
        else
        {
          events.push_back(Event{ time, event_id, client_name, 0 });
        }
        recent_event_time = time;
      }
      catch (const std::invalid_argument & e)
      {
        throw FormatError(event_info);
      }
    }
  }
}

Shift parseInputFileIntoShiftAndEvents(std::ifstream & shift_record, Events & events)
{
  Shift shift = getInitializedShift(shift_record);
  fillEventsInfo(shift_record, events, shift.getShiftTablesNumber(), shift.getShiftEndTime());
  return shift;
}
