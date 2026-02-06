#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <string>
#include <list>

#include "time.hpp"

enum EventID
{
  CLIENT_CAME = 1,
  CLIENT_TOOK_THE_TABLE,
  CLIENT_WAITING,
  CLIENT_WENT_AWAY,
  CLIENT_WENT_AWAY_BY_CAUSE = 11,
  CLIENT_TOOK_THE_TABLE_AFTER_WAITING,
  ERROR
};

struct Event
{
  Time time;
  EventID id;
  std::string client_name;
  long long table_num;
};

std::ostream & operator<<(std::ostream & out, const Event & event);

using Events = std::list< Event >;

#endif
