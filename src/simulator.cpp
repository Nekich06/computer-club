#include "simulator.hpp"

#include "errors.hpp"

namespace
{
  void clientCame(const Event & event_info, Shift & shift)
  {
    std::string name = event_info.client_name;
    Time time = event_info.time;
    shift.recordClient(time, Client{ true, false, 0, name });
  }

  void clientTookTheTable(const Event & event_info, Shift & shift)
  {

  }
  void clientWaiting(const Event & event_info, Shift & shift)
  {

  }
  void clientWentAway(const Event & event_info, Shift & shift)
  {

  }
  void clientWentAwayByCause(const Event & event_info, Shift & shift)
  {

  }
  void clientTookTheTableAfterWaiting(const Event & event_info, Shift & shift)
  {

  }
}

void initEventHandlers(EventHandlers & event_handlers, Shift & shift, const Event & event_info)
{
  event_handlers.insert({ CLIENT_CAME, std::bind(clientCame, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_TOOK_THE_TABLE, std::bind(clientTookTheTable, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_WAITING, std::bind(clientWaiting, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_WENT_AWAY, std::bind(clientWentAway, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_WENT_AWAY_BY_CAUSE, std::bind(clientWentAwayByCause, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_TOOK_THE_TABLE_AFTER_WAITING, std::bind(clientTookTheTableAfterWaiting, std::cref(event_info), std::ref(shift)) });
}

void simulateShiftAndOutputInfo(std::ostream & out, Shift & shift, const EventHandlers & event_handlers, const Events & events, Event & event)
{
  out << shift.getShiftStartTime() << '\n';
  for (auto c_it = events.cbegin(); c_it != events.end(); ++c_it)
  {
    event = *c_it;
    out << event << '\n';
    try
    {
      event_handlers.at(event.id)();
    }
    catch (const ClientError & e)
    {
      out << e.what() << '\n';
    }
  }
  out << shift.getShiftEndTime() << '\n';
}

