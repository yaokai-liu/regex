/**
 * Project Name: regex
 * Module Name: grammar/templates
 * Filename: terminals.gen.c
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/
#include "terminal.h"
#include "tokens.gen.h"
const char TERMINALS[] = {
  ${terminals}
};
const int32_t N_TERMINAL = sizeof(TERMINALS);