/**
 * Project Name: regex
 * Module Name: container
 * Filename: array.h
 * Creator: Yaokai Liu
 * Create Date: 24-7-3
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_ARRAY_H
#define REGEX_ARRAY_H

#include "allocator.h"
#include <stddef.h>
#include <stdint.h>

typedef struct Array Array;

Array *Array_new(size_t ele_size, const Allocator *allocator);

uint32_t Array_length(struct Array *array);

// Note: append may change elements' address, 
// so it is not promised that two `Array_get` of one same `index` will return a same address.
void *Array_get(struct Array *array, uint32_t index);
int32_t Array_append(struct Array *array, void *elements, int32_t count);

// Promised that every element would be detacted with `fn_judgment`.
// So that for traversing elements.
bool Array_any(struct Array * array, bool (*fn_judgment)(void *));
// Promised that every element would be detacted with `fn_judgment`.
// So that for traversing elements.
bool Array_all(struct Array * array, bool (*fn_judgment)(void *));

#endif  // REGEX_ARRAY_H