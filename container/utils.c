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

void Range_array_update(Array *range_array, Range *range) {
  for (uint32_t i = 0; i < Array_length(range_array); i++) {
    Range *_range = (Range *) Array_get(range_array, i);
    if (_range->min < range->min && range->min < _range->max) {
      _range->max = max(_range->max, range->max);
      return;
    } else if (range->min < _range->min && _range->min < range->max) {
      _range->min = min(_range->min, range->min);
      return;
    }
  }
  Array_append(range_array, range, 1);
}