#pragma once

#include <bits/stdc++.h>

namespace cpp_dump {

using namespace std;

template <typename T>
string export_var(T, string = "");

}  // namespace cpp_dump

#include "export_container.hpp"
#include "export_map.hpp"
#include "export_set.hpp"
#include "export_tuple.hpp"
#include "export_xixo.hpp"

namespace cpp_dump {

using namespace std;

inline string export_var_real(bool value, string) {
  return value ? "true" : "false";
}

template <typename T>
inline auto export_var_real(T value, string) -> decltype(to_string(value)) {
  return to_string(value);
}

string export_var_real(string, string);

inline string export_var_real(const char* value, string indent) {
  return export_var_real((string)(value), indent);
}

inline string export_var_real(char value, string) {
  return "'" + string{value} + "'";
}

template <typename T>
inline auto export_var_real(T value, string indent)
    -> enable_if_t<is_set<T>, string> {
  return export_set(value, indent);
}

template <typename T>
inline auto export_var_real(T value, string indent)
    -> enable_if_t<is_map<T>, string> {
  return export_map(value, indent);
}

template <typename T>
inline auto export_var_real(T value, string indent)
    -> enable_if_t<is_tuple<T>, string> {
  return export_tuple(value, indent);
}

template <typename T>
inline auto export_var_real(T value, string indent)
    -> enable_if_t<is_container<T>, string> {
  return export_container(value, indent);
}

template <typename T>
inline auto export_var_real(T value, string indent)
    -> enable_if_t<is_xixo<T>, string> {
  return export_xixo(value, indent);
}

template <typename T>
inline string export_var(T value, string indent) {
  return export_var_real(value, indent);
}

}  // namespace cpp_dump
