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
extern const size_t sizeof_array;

Array *Array_new(uint32_t ele_size, const Allocator *allocator);

uint32_t Array_init(struct Array * array, uint32_t ele_size);

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


// Suppose `_to` and `_from` both are not duplicated array.
uint32_t Array_no_duplicated_concat(struct Array * restrict _to, struct Array * restrict _from);

// Clear array and free all element with `fn_free`.
uint32_t Array_clear(struct Array * array, void (*fn_free)(void *));
// Release array and free all element with `fn_free`.
uint32_t Array_release(struct Array * array, void (*fn_free)(void *));
#endif  // REGEX_ARRAY_H