/*
 * Copyright (c) 2023 Ryota Sasaki.
 *
 * This source code is licensed under the MIT license found in the LICENSE file in the root
 * directory of this source tree.
 */

#pragma once

// This is for MSVC.
// See https://stackoverflow.com/questions/5134523/msvc-doesnt-expand-va-args-correctly
#define _p_CPP_DUMP_BUFFER(x) x

#define _p_CPP_DUMP_EXPAND_VA1(func, arg1) _p_CPP_DUMP_BUFFER(func(arg1))
#define _p_CPP_DUMP_EXPAND_VA2(func, arg1, ...)                                                    \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA1(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA3(func, arg1, ...)                                                    \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA2(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA4(func, arg1, ...)                                                    \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA3(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA5(func, arg1, ...)                                                    \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA4(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA6(func, arg1, ...)                                                    \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA5(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA7(func, arg1, ...)                                                    \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA6(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA8(func, arg1, ...)                                                    \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA7(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA9(func, arg1, ...)                                                    \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA8(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA10(func, arg1, ...)                                                   \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA9(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA11(func, arg1, ...)                                                   \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA10(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA12(func, arg1, ...)                                                   \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA11(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA13(func, arg1, ...)                                                   \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA12(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA14(func, arg1, ...)                                                   \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA13(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA15(func, arg1, ...)                                                   \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA14(func, __VA_ARGS__))
#define _p_CPP_DUMP_EXPAND_VA16(func, arg1, ...)                                                   \
  func(arg1), _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_EXPAND_VA15(func, __VA_ARGS__))

#define _p_CPP_DUMP_VA_SIZE_AUX(                                                                   \
    arg1,                                                                                          \
    arg2,                                                                                          \
    arg3,                                                                                          \
    arg4,                                                                                          \
    arg5,                                                                                          \
    arg6,                                                                                          \
    arg7,                                                                                          \
    arg8,                                                                                          \
    arg9,                                                                                          \
    arg10,                                                                                         \
    arg11,                                                                                         \
    arg12,                                                                                         \
    arg13,                                                                                         \
    arg14,                                                                                         \
    arg15,                                                                                         \
    arg16,                                                                                         \
    size,                                                                                          \
    ...                                                                                            \
)                                                                                                  \
  size
#define _p_CPP_DUMP_VA_SIZE(...)                                                                   \
  _p_CPP_DUMP_BUFFER(                                                                              \
      _p_CPP_DUMP_VA_SIZE_AUX(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)  \
  )

#define _p_CPP_DUMP_GET_EXPAND_VA_MACRO(size) _p_CPP_DUMP_EXPAND_VA##size
#define _p_CPP_DUMP_EXPAND_VA_AUX(func, size, ...)                                                 \
  _p_CPP_DUMP_BUFFER(_p_CPP_DUMP_GET_EXPAND_VA_MACRO(size)(func, __VA_ARGS__))

#define _p_CPP_DUMP_EXPAND_VA(func, ...)                                                           \
  _p_CPP_DUMP_EXPAND_VA_AUX(func, _p_CPP_DUMP_VA_SIZE(__VA_ARGS__), __VA_ARGS__)
