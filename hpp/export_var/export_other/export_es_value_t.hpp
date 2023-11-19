/*
 * Copyright (c) 2023 Ryota Sasaki.
 *
 * This source code is licensed under the MIT license found in the LICENSE file in the root
 * directory of this source tree.
 */

#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "../../escape_sequence.hpp"
#include "../../export_command/export_command.hpp"
#include "../../options.hpp"
#include "../../utility.hpp"
#include "../export_object_common.hpp"

namespace cpp_dump {

namespace _detail {

inline std::string _export_es_value_string(const std::string &es) {
  std::string escaped_es = es;
  replace_string(escaped_es, "\x1b", "\\e");

  return es::apply(es, R"(")" + escaped_es + R"(")");
}

inline std::string _export_es_value_vector(
    const std::vector<std::string> &es_vec,
    const std::string &indent,
    std::size_t last_line_length,
    std::size_t current_depth,
    bool fail_on_newline,
    const export_command &command
) {
  if (es_vec.empty()) return es::bracket("[ ]", current_depth);

  if (current_depth >= max_depth)
    return es::bracket("[ ", current_depth) + es::op("...") + es::bracket(" ]", current_depth);

  bool shift_indent = false;

  if (shift_indent && fail_on_newline) return "\n";

  std::string new_indent = indent + "  ";

  auto skipped = command.create_skip_container(es_vec);

rollback:
  std::string output = es::bracket("[ ", current_depth);
  bool is_first = true;

  for (const auto &[skip, it, index] : skipped) {
    const std::string &es = *it;

    if (is_first) {
      is_first = false;
    } else {
      output += es::op(", ");
    }

    if (shift_indent) {
      if (skip) {
        output += "\n" + new_indent + es::op("...");
        continue;
      }

      output += "\n" + new_indent;
      if (command.show_index()) output += es::member(std::to_string(index)) + es::op(": ");
      output += _export_es_value_string(es);
      continue;
    }

    if (skip) {
      output += es::op("...");

      if (last_line_length + get_length(output) + std::string_view(" ]").size() <= max_line_width)
        continue;

      shift_indent = true;
      goto rollback;
    }

    if (command.show_index()) output += es::member(std::to_string(index)) + es::op(": ");
    output += _export_es_value_string(es);

    if (last_line_length + get_length(output) + std::string_view(" ]").size() <= max_line_width)
      continue;

    if (fail_on_newline) return "\n";

    shift_indent = true;
    goto rollback;
  }

  if (shift_indent) {
    output += "\n" + indent + es::bracket("]", current_depth);
  } else {
    output += es::bracket(" ]", current_depth);
  }

  return output;
}

inline std::string export_es_value_t(
    const es_value_t &esv,
    const std::string &indent,
    std::size_t last_line_length,
    std::size_t current_depth,
    bool fail_on_newline,
    const export_command &command
) {
  std::string type_name = "cpp_dump::es_value_t";

  _p_CPP_DUMP_DEFINE_EXPORT_OBJECT_COMMON1_1;

  auto append_output = [&](const std::string &member_name, const auto &member) -> void {
    if (is_first) {
      is_first = false;
    } else {
      output += es::op(", ");
    }

    if (shift_indent) output += "\n" + new_indent;

    if constexpr (std::is_same_v<decltype(member), const std::string &>) {
      output += es::apply(member, member_name + "= ");
      output += _export_es_value_string(member);
    } else {
      output += es::member(member_name) + es::op("= ");
      output += _export_es_value_vector(
          member, new_indent, get_last_line_length(output), next_depth, false, command
      );
    }
  };

  _p_CPP_DUMP_DEFINE_EXPORT_OBJECT_COMMON1_3;

  append_output("log", esv.log);
  append_output("expression", esv.expression);
  append_output("reserved", esv.reserved);
  append_output("character", esv.character);
  append_output("op", esv.op);
  append_output("identifier", esv.identifier);
  append_output("member", esv.member);
  append_output("unsupported", esv.unsupported);
  append_output("bracket_by_depth", esv.bracket_by_depth);

  _p_CPP_DUMP_DEFINE_EXPORT_OBJECT_COMMON2;
}

}  // namespace _detail

}  // namespace cpp_dump
