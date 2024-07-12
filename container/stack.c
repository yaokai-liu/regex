/**
 * Project Name: regex
 * Module Name:
 * Filename: stack.c
 * Creator: Yaokai Liu
 * Create Date: 2024-6-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "stack.h"
#include <malloc.h>
#include <string.h>
struct Stack {
  uint32_t allocated;
  uint32_t used;
  void *stack;
};

#define ALLOC_LEN (32 * sizeof(void *))
#define min(a, b) ((a) < (b) ? (a) : (b))

Stack *Stack_new() {
  Stack *stack = malloc(sizeof(Stack));
  stack->stack = malloc(ALLOC_LEN);
  stack->allocated = ALLOC_LEN;
  stack->used = 0;
  return stack;
}
void Stack_clear(Stack *stack) {
  free(stack->stack);
  stack->allocated = 0;
  stack->used = 0;
  stack->stack = nullptr;
}
uint32_t Stack_push(Stack *stack, const void *data, uint32_t size) {
  if (!data || !size) { return 0; }
  if (stack->used + size >= stack->allocated) {
    stack->allocated += ALLOC_LEN;
    void *p = realloc(stack->stack, stack->allocated);
    if (!p) { return -1; }
    stack->stack = p;
  }
  memcpy(stack->stack + stack->used, data, size);
  stack->used += size;
  return size;
}
uint32_t Stack_pop(Stack *stack, void *dest, uint32_t size) {
  size = min(stack->used, size);
  stack->used -= size;
  if (dest) { memcpy(dest, stack->stack + stack->used, size); }
  return size;
}

uint32_t Stack_top(Stack *stack, void *dest, uint32_t size) {
  size = min(stack->used, size);
  if (dest) { memcpy(dest, stack->stack + stack->used - size, size); }
  return size;
}