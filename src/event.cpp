#include "event.hpp"

std::ostream & operator<<(std::ostream & out, const Event & event)
{
  out << event.time << ' ' << event.id << ' ';
  out << event.client_name;
  if (event.table_num)
  {
    out << ' ' << event.table_num;
  }
  return out;
}
