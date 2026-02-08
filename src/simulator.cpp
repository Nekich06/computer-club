#include "simulator.hpp"

#include "errors.hpp"

namespace
{
  void clientCame(const Event & event_info, Shift & shift)
  {
    shift.recordClient(event_info.time, Client{ 0, event_info.client_name });
  }

  void clientTookTheTable(const Event & event_info, Shift & shift)
  {
    shift.toSeatClient(event_info.time, event_info.client_name, event_info.table_num);
  }

  void clientWaiting(const Event & event_info, Shift & shift)
  {
    shift.recordWaiting(event_info.time, event_info.client_name);
  }

  void clientWentAway(const Event & event_info, Shift & shift)
  {
    shift.unrecordClient(event_info.time, event_info.client_name);
  }

  void clientTookTheTableAfterWaiting(const Event & event_info, Shift & shift)
  {
    shift.toSeatClient(event_info.time, event_info.client_name, event_info.table_num);
  }

  std::ostream & endSimulationAndOutputInfo(std::ostream & out, Shift & shift)
  {
    std::list< std::string > clients_names = shift.getCurrentClientsNames();
    shift.endShift();
    for (auto it = clients_names.cbegin(); it != clients_names.cend(); ++it)
    {
      out << shift.getShiftEndTime() << ' ' << *it << '\n';
    }
    return out;
  }
}

void initEventHandlers(EventHandlers & event_handlers, Shift & shift, const Event & event_info)
{
  event_handlers.insert({ CLIENT_CAME, std::bind(clientCame, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_TOOK_THE_TABLE, std::bind(clientTookTheTable, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_WAITING, std::bind(clientWaiting, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_WENT_AWAY, std::bind(clientWentAway, std::cref(event_info), std::ref(shift)) });
  event_handlers.insert({ CLIENT_WENT_AWAY_BY_CAUSE, std::bind(clientWentAway, std::cref(event_info), std::ref(shift)) });
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
    catch (const OutgoingEvent & e)
    {
      out << e.what() << '\n';
      event = e.getEventInfo();
      event_handlers.at(event.id)();
    }
  }
  endSimulationAndOutputInfo(out, shift);
  out << shift.getShiftEndTime() << '\n';
  shift.outputTablesInfo(out);
}

