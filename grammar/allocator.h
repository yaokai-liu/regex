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
} Allocator;

#include <malloc.h>
const Allocator STDAllocator = {
  .malloc = malloc, .realloc = realloc, .calloc = calloc
};

#endif  // REGEX_ALLOCATOR_H
