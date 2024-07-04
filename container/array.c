/**
 * Project Name: regex
 * Module Name: container
 * Filename: array.c
 * Creator: Yaokai Liu
 * Create Date: 24-7-3
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "array.h"
#include "allocator.h"
#include <stdint.h>
#include <string.h>

struct Array {
  const Allocator * allocator;
  uint32_t alloc_len;
  uint32_t ele_size;
  uint32_t used_len;
  void *elements;
};

#define ALLOC_LEN 32

Array *Array_new(size_t ele_size, const Allocator *allocator) {
  Array *array = allocator->calloc(1, sizeof(struct Array));
  array->allocator = allocator;
  array->ele_size = ele_size;
  array->elements = nullptr;
  array->alloc_len = 0;
  array->used_len = 0;
  return array;
}

inline uint32_t Array_length(struct Array *array) {
    return array->used_len;
}
inline void *Array_get(struct Array *array, uint32_t index) {
    if (index >= array->used_len) { return nullptr; }
    return array->elements + array->ele_size * index;
}
int32_t Array_append(struct Array *array, void *elements, int32_t count) {
    if (array->used_len + count >= array->alloc_len) {
        uint32_t size = array->alloc_len + ALLOC_LEN;
        void * p = array->allocator->realloc(array->elements, array->alloc_len);
        if (!p) { return -1; }
        array->elements = p;
        array->alloc_len = size;
    }
    void * dest = Array_get(array, array->used_len);
    memcpy(dest, elements, count * array->ele_size);
    array->used_len ++;
    return count;
}

bool Array_any(struct Array * array, bool (*fn_judgment)(void *)) {
  bool judge = false;
  for (uint32_t i = 0; i < array->used_len; i++) {
    void * element = array->elements + i * array->ele_size;
    if (fn_judgment(element)) { judge = true; }
  }
  return judge;
}

bool Array_all(struct Array * array, bool (*fn_judgment)(void *)) {
  bool judge = true;
  for (uint32_t i = 0; i < array->used_len; i++) {
    void * element = array->elements + i * array->ele_size;
    if (!fn_judgment(element)) { judge = false; }
  }
  return judge;
}
