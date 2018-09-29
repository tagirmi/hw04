#pragma once

#include <algorithm>
#include <list>
#include <vector>
#include <string>
#include <tuple>
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

template<typename T, typename U>
constexpr bool is_same_v = std::is_same<T, U>::value;


template<size_t I, typename... Args>
struct is_same_elements
{
  using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
  using type_next = typename is_same_elements<I - 1, Args...>::type;
  static constexpr bool value = is_same_v<type, type_next> &&
                                is_same_elements<I - 1, Args...>::value;
};

template<typename... Args>
struct is_same_elements<0, Args...>
{
  using type = typename std::tuple_element<0, std::tuple<Args...>>::type;
  static constexpr bool value = true;
};

template<typename...Args>
struct is_same_tuple_elements
{
  static constexpr auto size = std::tuple_size<std::tuple<Args...>>::value;
  static constexpr bool value = is_same_elements<size - 1, Args...>::value;
};

template<typename... Args>
constexpr bool is_same_tuple_elements_v = is_same_tuple_elements<Args...>::value;

static_assert(is_container_v<const std::vector<int>&>, "is_container<const std::vector<T>&>");
static_assert(is_container_v<const std::vector<int>>, "is_container<const std::vector<T>>");
static_assert(is_container_v<std::vector<int>>, "is_container<std::vector<T>>");

static_assert(is_container_v<const std::list<int>&>, "is_container<const std::vector<T>&>");
static_assert(is_container_v<const std::list<int>>, "is_container<const std::vector<T>>");
static_assert(is_container_v<std::list<int>>, "is_container<std::vector<T>>");

static_assert(is_same_tuple_elements_v<int, int, int>, "is_same_tuple_elements_v<Args...>");

template<typename T>
void container_print_helper(std::ostream& stream, const T& container)
{
  for (auto i = container.cbegin(); i != container.cend(); ++i) {
    if (i != container.cbegin())
      stream << '.';
    stream << *i;
  }
}

template<typename T>
void integral_print_helper(std::ostream& stream, const T& value)
{
  std::vector<int> vector;
  vector.reserve(sizeof(T));

  auto begin = reinterpret_cast<const unsigned char*>(&value);
  auto end = begin + sizeof(T);

  std::copy(begin, end, std::back_inserter(vector));
  std::reverse(vector.begin(), vector.end());

  container_print_helper(stream, vector);
}

template<typename T, size_t N>
struct TuplePrinter
{
  void operator()(std::ostream& stream, const T& t)
  {
    TuplePrinter<T, N-1> print;
    print(stream, t);
    stream << '.' << std::get<N-1>(t);
  }
};

template<typename T>
struct TuplePrinter<T, 1>
{
  void operator()(std::ostream& stream, const T& t)
  {
    stream << std::get<0>(t);
  }
};

template<typename...Args>
void tuple_print_helper(std::ostream& stream, const std::tuple<Args...>& tuple)
{
  TuplePrinter<decltype(tuple), sizeof...(Args)> print;
  print(stream, tuple);
}

} // details

/**
 * @brief Специализация шаблона функции для печати IP адреса для значений интрегральных типов.
 * Выводит побайтово начиная со старшего с символом '.' в качестве разделителя.
 *
 * @tparam T Интегральный тип.
 * @param stream Поток вывода.
 * @param value Значение интегрального типа.
 */
template<typename T>
std::enable_if_t<details::is_integral_v<T>, void>
print_ip(std::ostream& stream, const T& value)
{
  details::integral_print_helper(stream, value);
}

/**
 * @brief Специализация шаблона функции для печати IP адреса для строки.
 * Строку выводит как есть.
 *
 * @tparam T std::string.
 * @param stream Поток вывода.
 * @param string Строка.
 */
template<typename T>
std::enable_if_t<details::is_same_v<T, std::string>, void>
print_ip(std::ostream& stream, const T& string)
{
  stream << string;
}

/**
 * @brief Специализация шаблона функции для печати IP адреса для контейнеров std::vector и std::list.
 * Выводится содержимое контейнера поэлементно и разделяется '.'.
 *
 * @tparam T контейнер std::vector или std::list.
 * @param stream Поток вывода.
 * @param container Контейнер.
 */
template<typename T>
std::enable_if_t<details::is_container_v<T>, void>
print_ip(std::ostream& stream, const T& container)
{
  details::container_print_helper(stream, container);
}

/**
 * @brief Специализация шаблона функции для печати IP адреса для кортежа с элементами одинакового типа.
 * Выводится содержимое кортежа поэлементно и разделяется '.'.
 *
 * @tparam Args Элементы кортежа.
 * @param stream Поток вывода.
 * @param tuple Кортеж.
 */
template<typename... Args>
std::enable_if_t<details::is_same_tuple_elements_v<Args...>, void>
print_ip(std::ostream& stream, const std::tuple<Args...>& tuple)
{
  details::tuple_print_helper(stream, tuple);
}

} // hw04
