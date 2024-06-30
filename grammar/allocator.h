/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: allocator.h
 * Creator: Yaokai Liu
 * Create Date: 24-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_ALLOCATOR_H
#define REGEX_ALLOCATOR_H

#include "stddef.h"

typedef struct {
  void *(*malloc)(size_t size);
  void *(*realloc)(void *ptr, size_t size);
  void *(*calloc)(size_t count, size_t size);
  void (*free)(void *ptr);
} Allocator;

extern const Allocator STDAllocator;

#endif  // REGEX_ALLOCATOR_H
