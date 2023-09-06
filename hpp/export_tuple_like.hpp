/*
 * Copyright (c) 2023 Ryota Sasaki.
 *
 * This source code is licensed under the MIT license found in the LICENSE file in the root
 * directory of this source tree.
 */

#pragma once

#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

#include "./type_check.hpp"
#include "./utility.hpp"

namespace cpp_dump {

extern inline size_t max_line_width;

extern inline size_t max_depth;

namespace _detail {

template <typename T>
std::string export_var(const T &, const std::string &, size_t, size_t, bool);

template <const size_t i, const size_t size, typename... Args>
inline std::string _export_tuple_like_in_one_line(const std::tuple<Args...> &tuple,
                                                  const std::string &indent,
                                                  size_t last_line_length, size_t next_depth) {
  std::string output = export_var(std::get<i>(tuple), indent, last_line_length, next_depth, true);
  if (has_newline(output)) return "\n";

  if constexpr (i < size - 1) {
    return output + ", " +
           _export_tuple_like_in_one_line<i + 1, size>(tuple, indent, output.length() + 2,
                                                       next_depth);
  } else {
    return output;
  }
}

template <const size_t i, const size_t size, typename... Args>
inline std::string _export_tuple_like_in_lines(const std::tuple<Args...> &tuple,
                                               const std::string &indent, size_t next_depth) {
  std::string output = export_var(std::get<i>(tuple), indent, indent.length(), next_depth, false);

  if constexpr (i < size - 1) {
    return output + ",\n" + indent +
           _export_tuple_like_in_lines<i + 1, size>(tuple, indent, next_depth);
  } else {
    return output;
  }
}

template <typename... Args>
inline std::string export_tuple_like(const std::tuple<Args...> &tuple, const std::string &indent,
                                     size_t last_line_length, size_t current_depth,
                                     bool fail_on_newline) {
  constexpr size_t tuple_size = std::tuple_size_v<std::tuple<Args...>>;

  if constexpr (tuple_size == 0) {
    return "( )";
  } else {
    if (current_depth >= max_depth) return "( ... )";

    size_t next_depth = current_depth + 1;

    std::string output = "( " +
                         _export_tuple_like_in_one_line<0, tuple_size>(
                             tuple, indent, last_line_length + 2, next_depth) +
                         " )";

    if (!has_newline(output) && output.length() <= max_line_width) return output;

    if (fail_on_newline) return "\n";

    std::string new_indent = indent + "  ";
    return "(\n" + new_indent +
           _export_tuple_like_in_lines<0, tuple_size>(tuple, new_indent, next_depth) + "\n" +
           indent + ")";
  }
}

template <typename T1, typename T2>
inline std::string export_tuple_like(const std::pair<T1, T2> &pair, const std::string &indent,
                                     size_t last_line_length, size_t current_depth,
                                     bool fail_on_newline) {
  return export_tuple_like(std::tie(pair.first, pair.second), indent, last_line_length,
                           current_depth, fail_on_newline);
}

}  // namespace _detail

}  // namespace cpp_dump
