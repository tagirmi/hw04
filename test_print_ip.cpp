#include <gtest/gtest.h>
#include <sstream>

#include "print_ip.h"

TEST(TestPrintIp, PrintChar)
{
  std::stringstream ss;

  hw04::print_ip(ss, static_cast<char>(-1));

  EXPECT_EQ(ss.str(), "255");
}

TEST(TestPrintIp, PrintShort)
{
  std::stringstream ss;

  hw04::print_ip(ss, static_cast<short>(0));

  EXPECT_EQ(ss.str(), "0.0");
}

TEST(TestPrintIp, PrintInt)
{
  std::stringstream ss;

  hw04::print_ip(ss, 2130706433);

  EXPECT_EQ(ss.str(), "127.0.0.1");
}

TEST(TestPrintIp, PrintLongLong)
{
  std::stringstream ss;

  hw04::print_ip(ss, 8875824491850138409LL);

  EXPECT_EQ(ss.str(), "123.45.67.89.101.112.131.41");
}

TEST(TestPrintIp, PrintString)
{
  std::stringstream ss;

  hw04::print_ip(ss, std::string("some string"));

  EXPECT_EQ(ss.str(), "some string");
}

TEST(TestPrintIp, PrintVector)
{
  std::stringstream ss;

  hw04::print_ip(ss, std::vector<int>{1, 2, 3, 4});

  EXPECT_EQ(ss.str(), "1.2.3.4");
}

TEST(TestPrintIp, PrintList)
{
  std::stringstream ss;

  hw04::print_ip(ss, std::list<int>{1, 2, 3, 4});

  EXPECT_EQ(ss.str(), "1.2.3.4");
}
