/**
 * Project Name: regex
 * Module Name:
 * Filename: stack.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "stack.h"
#include <malloc.h>
#include <string.h>
struct Stack {
  uint32_t alloc_len;
  uint32_t used_len;
  uint64_t *stack;
};

#define ALLOC_LEN 32
#define min(a, b) ((a) < (b) ? (a) : (b))

Stack *Stack_new() {
  Stack *stack = malloc(sizeof(Stack));
  stack->stack = malloc(ALLOC_LEN * sizeof(uint64_t));
  stack->alloc_len = ALLOC_LEN;
  stack->used_len = 0;
  return stack;
}
void Stack_release(Stack *stack) {
  free(stack->stack);
  free(stack);
}
int32_t Stack_push(Stack *stack, uint64_t *elements, int32_t n_ele) {
  uint32_t len = stack->alloc_len - 1 - stack->used_len;
  if (len < n_ele) {
    stack->alloc_len += ((n_ele - len - 1) / ALLOC_LEN + 1) * ALLOC_LEN;
    void *p = realloc(stack->stack, stack->alloc_len * sizeof(uint64_t));
    if (!p) { return -1; }
    stack->stack = p;
  }
  memcpy(&stack->stack[stack->used_len], elements, n_ele * sizeof(uint64_t));
  stack->used_len += n_ele;
  return n_ele;
}
int32_t Stack_pop(Stack *stack, uint64_t *dest, int32_t n_ele) {
  n_ele = min(stack->used_len, n_ele);
  stack->used_len -= n_ele;
  if (!dest) { return n_ele; }
  memcpy(dest, &stack->stack[stack->used_len], n_ele * sizeof(uint64_t));
  return n_ele;
}

void Stack_top(Stack *stack, uint64_t *dest) {
  if (stack->used_len) { *dest = stack->stack[stack->used_len - 1]; }
}