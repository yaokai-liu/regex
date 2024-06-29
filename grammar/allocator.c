/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: allocator.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include <malloc.h>
const Allocator STDAllocator = {.malloc = malloc, .realloc = realloc, .calloc = calloc};