#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <functional>
#include <iostream>
#include <map>

#include "shift.hpp"
#include "event.hpp"

using EventHandlers = std::map< EventID, std::function< void() > >;

void initEventHandlers(EventHandlers & event_handlers, Shift & shift, const Event & event);
void simulateShiftAndOutputInfo(std::ostream & out, Shift & shift, const EventHandlers & event_handlers, const Events & events, Event & event);

#endif
