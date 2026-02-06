#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>

#include "event.hpp"
#include "shift.hpp"

Shift parseInputFileIntoShiftAndEvents(std::ifstream & shift_record, Events & events_info);

#endif
