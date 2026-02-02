#include <stdexcept>
#include <iostream>
#include <fstream>

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
  }
  catch (const std::logic_error & e)
  {
    std::cout << e.what() << '\n';
    return 1;
  }
}
