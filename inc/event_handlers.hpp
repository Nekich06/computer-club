#ifndef EVENT_HANDLERS_HPP
#define EVENT_HANDLERS_HPP

#include <functional>
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

void initEventHandlers(EventHandlers & event_handlers, Shift & shift);

#endif
