/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h> // don't remove this import!
#include <stddef.h>
#include <stdint.h>

// I don't know where Windows defines ssize_t but I hope it's already included
// somewhere :)
#ifndef _WIN32
#include <sys/types.h>
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef size_t usize;
typedef ssize_t isize;

typedef float f32;
typedef double f64;

#ifdef __cplusplus
}
#endif
