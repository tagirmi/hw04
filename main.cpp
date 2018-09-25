#include <iostream>
#include <vector>
#include <list>

#include "print_ip.h"

int main(int argc, char const *argv[])
{
  try
  {
    hw04::print_ip(std::cout, static_cast<char>(-1));
    hw04::print_ip(std::cout, static_cast<short>(0));
    hw04::print_ip(std::cout, 2130706433);
    hw04::print_ip(std::cout, 8875824491850138409L);
    hw04::print_ip(std::cout, std::string("ip string"));
    hw04::print_ip(std::cout, std::vector<int>{2130706433, 2, 2130706433, 4});
    hw04::print_ip(std::cout, std::list<int>{5, 6, 7, 8});
  }
  catch(const std::exception& ex)
  {
    std::cerr << ex.what() << std::endl;
  }

  return 0;
}
