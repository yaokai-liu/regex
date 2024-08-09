/**
 * Project Name: regex
 * Module Name: container
 * Filename: array.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-3
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "array.h"
#include "allocator.h"
#include <stdint.h>
#include <string.h>

struct Array {
  const Allocator *allocator;
  uint32_t alloc_len;
  uint32_t ele_size;
  uint32_t used_len;
  void *elements;
};

const size_t sizeof_array = sizeof(Array);

#define ALLOC_LEN 32

inline Array *Array_new(uint32_t ele_size, const Allocator * const allocator) {
  Array *array = allocator->calloc(1, sizeof(struct Array));
  array->allocator = allocator;
  if (ele_size == 0) { return nullptr; }
  Array_init(array, ele_size);
  return array;
}

uint32_t Array_init(struct Array *array, uint32_t ele_size) {
  array->ele_size = ele_size;
  array->elements = nullptr;
  array->alloc_len = 0;
  array->used_len = 0;
  return ele_size;
}

inline const Allocator *Array_allocator(struct Array *array) {
  return array->allocator;
}
inline uint32_t Array_length(struct Array *array) {
  return array->used_len;
}
inline void *Array_get(struct Array *array, uint32_t index) {
  if (index >= array->used_len) { return nullptr; }
  return array->elements + array->ele_size * index;
}
inline int32_t Array_append(struct Array *array, void *elements, int32_t count) {
  if (array->used_len + count >= array->alloc_len) {
    uint32_t length = array->alloc_len + ALLOC_LEN;
    void *p = array->allocator->realloc(array->elements, length * array->ele_size);
    if (!p) { return -1; }
    array->elements = p;
    array->alloc_len = length;
  }
  void *dest = array->elements + array->ele_size * array->used_len;
  memcpy(dest, elements, count * array->ele_size);
  array->used_len += count;
  return count;
}

inline bool Array_any(struct Array *array, bool (*fn_judgment)(void *)) {
  bool judge = false;
  for (uint32_t i = 0; i < array->used_len; i++) {
    void *element = array->elements + i * array->ele_size;
    if (fn_judgment(element)) { judge = true; }
  }
  return judge;
}

inline bool Array_all(struct Array *array, bool (*fn_judgment)(void *)) {
  bool judge = true;
  for (uint32_t i = 0; i < array->used_len; i++) {
    void *element = array->elements + i * array->ele_size;
    if (!fn_judgment(element)) { judge = false; }
  }
  return judge;
}

inline uint32_t Array_no_duplicated_concat(struct Array * restrict _to,
                                           struct Array * restrict _from) {
  if (_from->ele_size != _to->ele_size) { return 0; }
  return Array_no_duplicated_append(_to, _from->elements, _from->used_len);
}

inline uint32_t Array_no_duplicated_append(struct Array * restrict _to, void *elements,
                                           uint32_t count) {
  if (count == 0) { return 0; }
  void *temp = _to->allocator->malloc(count * sizeof(_to->ele_size));
  uint32_t len = 0;
  for (uint32_t i = 0; i < count; i++) {
    void *p1 = ((char *) elements) + i * _to->ele_size;
    for (uint32_t j = 0; j < _to->used_len; j++) {
      void *p2 = Array_get(_to, j);
      if (memcmp(p1, p2, _to->ele_size) == 0) { goto __Array_no_duplicated_concat_for_duplicated; }
    }
    memcpy(temp + len * _to->ele_size, p1, _to->ele_size);
    len++;
__Array_no_duplicated_concat_for_duplicated:;
  }
  if (len) { Array_append(_to, temp, (int32_t) len); }
  _to->allocator->free(temp);
  return len;
}

uint32_t Array_clear(struct Array *array, void (*fn_free)(void *, const Allocator *)) {
  if (fn_free) {
    for (uint32_t i = 0; i < array->used_len; i++) {
      void *ele = Array_get(array, i);
      fn_free(ele, array->allocator);
    }
  }
  uint32_t len = array->used_len;
  array->used_len = 0;
  return len;
}

uint32_t Array_reset(struct Array *array, void (*fn_free)(void *, const Allocator *)) {
  Array_clear(array, fn_free);
  uint32_t len = array->alloc_len;
  if (array->elements) { array->allocator->free(array->elements); }
  array->elements = nullptr;
  array->alloc_len = 0;
  array->used_len = 0;
  return len;
}

void Array_destroy(struct Array *array) {
  array->allocator->free(array);
}
