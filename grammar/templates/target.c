/**
 * Project Name: regex
 * Module Name: grammar/templates
 * Filename: target.gen.c
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "reduce.gen.h"
#include "target.h"

fn_product * const PRODUCTS[] = {
  ${assign_reduces}
};
