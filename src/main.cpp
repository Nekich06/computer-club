#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cstring>

#include "shift.hpp"
#include "parser.hpp"
#include "simulator.hpp"
#include "exceptions.hpp"

namespace
{
  std::ifstream createFileStream(const int argc, const char * const * argv)
  {
    if (argc != 2)
    {
      throw std::logic_error("Invalid number of command line arguments");
    }
    std::ifstream file_stream(argv[1]);
    if (!file_stream.is_open())
    {
      throw std::logic_error("Can't open file");
    }
    return file_stream;
  }
}

int main(const int argc, const char * const * argv)
{
  try
  {
    std::ifstream shift_record(createFileStream(argc, argv));

    Events events;
    Shift shift = parseInputFileIntoShiftAndEvents(shift_record, events);

    Event event_info;
    EventHandlers event_handlers;
    initEventHandlers(event_handlers, shift, event_info);

    simulateShiftAndOutputInfo(std::cout, shift, event_handlers, events, event_info);
  }
  catch (const std::logic_error & e)
  {
    std::cout << e.what() << '\n';
    return 1;
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  catch (const FormatError & e)
  {
    std::cout << e.what() << '\n';
    return 3;
  }
}
