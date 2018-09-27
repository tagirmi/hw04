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

template<typename T, typename U>
constexpr bool is_same_v = std::is_same<T, U>::value;

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

} // hw04
