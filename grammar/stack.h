/**
 * Project Name: regex
 * Module Name:
 * Filename: stack.h
 * Creator: Yaokai Liu
 * Create Date: 24-6-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_STACK_H
#define REGEX_STACK_H

#include <stdint.h>

typedef struct Stack Stack;

Stack *Stack_new();
void Stack_release(Stack *stack);
int32_t Stack_push(Stack *stack, uint64_t *elements, int32_t n_ele);
int32_t Stack_pop(Stack *stack, uint64_t *dest, int32_t n_ele);
void Stack_top(Stack *stack, uint64_t *dest);
#endif  // REGEX_STACK_H
