#include "event_handlers.hpp"

namespace
{
  std::string getWord(const std::string & event_info, size_t & start_pos)
  {
    size_t temp = start_pos;
    start_pos = event_info.find(' ', start_pos);
    return event_info.substr(temp, start_pos - temp);
  }

  void clientCame(const std::string & event_info, Shift & shift)
  {
    size_t pos = 0;
    std::string time_str = getWord(event_info, pos);
    pos += 3;
    std::string name = getWord(event_info, pos);
    Time time = parseTimeStringToObject(time_str);
    shift.recordClient(time, Client{ true, false, 0, name });
  }

  void clientTookTheTable(const std::string & event_info, Shift & shift)
  {

  }
  void clientWaiting(const std::string & event_info, Shift & shift)
  {

  }
  void clientWentAway(const std::string & event_info, Shift & shift)
  {

  }
  void clientWentAwayByCause(const std::string & event_info, Shift & shift)
  {

  }
  void clientTookTheTableAfterWaiting(const std::string & event_info, Shift & shift)
  {

  }
  void error(Shift & shift)
  {

  }

  std::string getEventID(const std::string & event_info)
  {
    size_t start_pos = event_info.find(' ');
    size_t end_pos = event_info.find(' ', start_pos + 1);
    return event_info.substr(start_pos + 1, end_pos - start_pos - 1);
  }
}

void initEventHandlers(EventHandlers & event_handlers, std::string & event_info, Shift & shift)
{
  event_handlers.insert({ CLIENT_CAME, std::bind(clientCame, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_TOOK_THE_TABLE, std::bind(clientTookTheTable, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_WAITING, std::bind(clientWaiting, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_WENT_AWAY, std::bind(clientWentAway, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_WENT_AWAY_BY_CAUSE, std::bind(clientWentAwayByCause, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_TOOK_THE_TABLE_AFTER_WAITING, std::bind(clientTookTheTableAfterWaiting, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ ERROR, std::bind(error, std::ref(shift)) });
}

void simulateShiftAndOutputInfo(std::ostream & out, std::ifstream & shift_record, Shift & shift, const EventHandlers & event_handlers, std::string & event_info)
{
  while (!shift_record.eof())
  {
    std::getline(shift_record, event_info, '\n');
    std::string ID = getEventID(event_info);
    try
    {
      event_handlers.at(static_cast< Event >(std::stoi(ID)))();
    }
    catch (const std::out_of_range & e)
    {
      throw std::invalid_argument(event_info);
    }
  }
}
