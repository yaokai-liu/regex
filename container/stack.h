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
void Stack_clear(Stack *stack);
int32_t Stack_push(Stack *stack, const void *data, int32_t size);
int32_t Stack_pop(Stack *stack, void *dest, int32_t size);
int32_t Stack_top(Stack *stack, void *dest, int32_t size);
#endif  // REGEX_STACK_H
