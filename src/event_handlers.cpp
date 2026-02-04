#include "event_handlers.hpp"

namespace
{
  void clientCame(Shift & shift);
  void clientTookTheTable(Shift & shift);
  void clientWaiting(Shift & shift);
  void clientWentAway(Shift & shift);
  void clientWentAwayByCause(Shift & shift);
  void clientTookTheTableAfterWaiting(Shift & shift);
  void error(Shift & shift);
}

void initEventHandlers(EventHandlers & event_handlers, Shift & shift)
{
  event_handlers.insert({ CLIENT_CAME, std::bind(clientCame, std::ref(shift)) });
  event_handlers.insert({ CLIENT_TOOK_THE_TABLE, std::bind(clientTookTheTable, std::ref(shift)) });
  event_handlers.insert({ CLIENT_WAITING, std::bind(clientWaiting, std::ref(shift)) });
  event_handlers.insert({ CLIENT_WENT_AWAY, std::bind(clientWentAway, std::ref(shift)) });
  event_handlers.insert({ CLIENT_WENT_AWAY_BY_CAUSE, std::bind(clientWentAwayByCause, std::ref(shift)) });
  event_handlers.insert({ CLIENT_TOOK_THE_TABLE_AFTER_WAITING, std::bind(clientTookTheTableAfterWaiting, std::ref(shift)) });
  event_handlers.insert({ ERROR, std::bind(error, std::ref(shift)) });
}

