/**
 * Project Name: regex
 * Module Name: container
 * Filename: utils.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-16
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "utils.h"

#define max(a, b) ((a) >= (b) ? (a) : (b))
#define min(a, b) ((a) <= (b) ? (a) : (b))

void Range_set_update(Set *range_set, const Range *range) {
  uint32_t n_ranges = Set_count(range_set);
  uint64_t *ranges = Set_data(range_set);
  for (uint32_t i = 0; i < n_ranges; i++) {
    Range _range = {.max = ranges[i] >> 32, .min = ranges[i] & 0xFFFFFFFF};
    if (_range.min <= range->min && range->min <= _range.max) {
      _range.max = max(_range.max, range->max);
      ranges[i] = (((uint64_t) _range.max) << 32) | ((uint64_t) _range.min);
      return;
    } else if (range->min <= _range.min && _range.min <= range->max) {
      _range.min = min(_range.min, range->min);
      ranges[i] = (((uint64_t) _range.max) << 32) | ((uint64_t) _range.min);
      return;
    }
  }
  uint64_t val = (((uint64_t) range->max) << 32) | ((uint64_t) range->min);
  Set_add(range_set, (void *) val);
}