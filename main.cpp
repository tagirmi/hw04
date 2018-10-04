#include <iostream>
#include <vector>
#include <list>
#include <tuple>

#include "print_ip.h"

int main(int argc, char const *argv[])
{
  try
  {
    hw04::print_ip(std::cout, static_cast<char>(-1));
    std::cout << std::endl;

    hw04::print_ip(std::cout, static_cast<short>(0));
    std::cout << std::endl;

    hw04::print_ip(std::cout, 2130706433);
    std::cout << std::endl;

    hw04::print_ip(std::cout, 8875824491850138409LL);
    std::cout << std::endl;

    hw04::print_ip(std::cout, std::string("ip string"));
    std::cout << std::endl;

    hw04::print_ip(std::cout, std::vector<int>{1, 2, 3, 4});
    std::cout << std::endl;

    hw04::print_ip(std::cout, std::list<int>{5, 6, 7, 8});
    std::cout << std::endl;

    hw04::print_ip(std::cout, std::make_tuple(9, 10, 11, 12));
    std::cout << std::endl;

  }
  catch(const std::exception& ex)
  {
    std::cerr << ex.what() << std::endl;
  }

  return 0;
}
