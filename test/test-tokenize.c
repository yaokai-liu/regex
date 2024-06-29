/**
 * Project Name: regex
 * Module Name: test
 * Filename: test-tokenize.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-25
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "grammar/token.h"
#include <malloc.h>
#include <stdio.h>

#define len(a) ((sizeof a) / sizeof(a[0]))

int main() {
    const char * string = "+-*^,12345{123,45}()[]<>";
    const uint8_t type_list[21] = {
            PLUS, MINUS, TIMES, NOT, COMMA,
            CHAR, CHAR, CHAR, CHAR, CHAR,
            BEGIN_QUANTIFIER, NUMBER, COMMA,
            NUMBER, END_QUANTIFIER, BEGIN_GROUP,
            END_GROUP, BEGIN_CHARSET, END_CHARSET,
            BEGIN_RANGE, END_RANGE
    };
    uint32_t cost = 0, n_tokens = 0;
    Terminal * tokens = tokenize(string, &cost, &n_tokens);
    if (n_tokens != len(type_list)) { return -1; }
    for (int i = 0; i < n_tokens; i ++) {
        if (tokens[i].type != type_list[i]) { return -1; }
        printf("%s ", get_token_name(tokens[i]));
        if (i % 5 == 4) { printf("\n"); }
    }
    free(tokens);
    return 0;
}


