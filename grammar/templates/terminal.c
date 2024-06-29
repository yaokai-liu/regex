/**
 * Project Name: regex
 * Module Name: grammar/templates
 * Filename: terminals.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/
#include "terminal.h"
#include "tokens.gen.h"
const int32_t N_TERMINAL = ${n_terminal};
const char TERMINALS[] = {
  ${terminals}
};