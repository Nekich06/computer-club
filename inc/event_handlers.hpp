#ifndef EVENT_HANDLERS_HPP
#define EVENT_HANDLERS_HPP

#include <functional>
#include <string>
#include <map>

#include "shift.hpp"

enum Event
{
  CLIENT_CAME = 1,
  CLIENT_TOOK_THE_TABLE,
  CLIENT_WAITING,
  CLIENT_WENT_AWAY,
  CLIENT_WENT_AWAY_BY_CAUSE = 11,
  CLIENT_TOOK_THE_TABLE_AFTER_WAITING,
  ERROR
};

using EventHandlers = std::map< Event, std::function< void() > >;

void initEventHandlers(EventHandlers & event_handlers, std::string & event_info, Shift & shift);
void simulateShiftAndOutputInfo(std::ostream & out, std::ifstream & shift_record, Shift & shift, const EventHandlers & event_handlers, std::string & event_info);

#endif
