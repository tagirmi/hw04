#pragma once

#include <algorithm>
#include <list>
#include <vector>
#include <string>
#include <type_traits>

namespace hw04 {

namespace details {

template<typename T>
struct is_container
{
  static constexpr bool value = false;
};

template<typename T, typename Alloc>
struct is_container<std::vector<T, Alloc>>
{
  static constexpr bool value = true;
};

template<typename T, typename Alloc>
struct is_container<std::list<T, Alloc>>
{
  static constexpr bool value = true;
};

template<typename T>
constexpr bool is_container_v = is_container<
                                  std::remove_cv_t<
                                    std::remove_reference_t<T>
                                  >
                                >::value;

template<typename T>
constexpr bool is_integral_v = std::is_integral<T>::value;

static_assert(is_container_v<const std::vector<int>&>, "is_container<const std::vector<T>&>");
static_assert(is_container_v<const std::vector<int>>, "is_container<const std::vector<T>>");
static_assert(is_container_v<std::vector<int>>, "is_container<std::vector<T>>");

static_assert(is_container_v<const std::list<int>&>, "is_container<const std::vector<T>&>");
static_assert(is_container_v<const std::list<int>>, "is_container<const std::vector<T>>");
static_assert(is_container_v<std::list<int>>, "is_container<std::vector<T>>");

template<typename T>
void container_print_helper(std::ostream& stream, const T& container)
{
  for (auto i = container.cbegin(); i != container.cend(); ++i) {
    if (i != container.cbegin())
      stream << ".";
    stream << *i;
  }
  stream << std::endl;
}

}

template<typename T, typename std::enable_if_t<details::is_container_v<T>, int> = 0>
void print_ip(std::ostream& stream, const T& container)
{
  details::container_print_helper(stream, container);
}

template<typename T>
void print_ip(std::ostream& stream, const std::basic_string<T>& string)
{
  stream << string << std::endl;
}

template<typename T, typename std::enable_if_t<details::is_integral_v<T>, int> = 0>
void print_ip(std::ostream& stream, const T& value)
{
  std::vector<int> vector;
  vector.reserve(sizeof(T));

  auto begin = reinterpret_cast<const unsigned char*>(&value);
  auto end = begin + sizeof(T);

  std::copy(begin, end, std::back_inserter(vector));
  std::reverse(vector.begin(), vector.end());

  details::container_print_helper(stream, vector);
}

}
