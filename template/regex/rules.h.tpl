${license}

#ifndef REGEX_REDUCES_H
#define REGEX_REDUCES_H

#include "regex/target.h"
#include "regex/context.h"

typedef void *fn_regex_reduce(Token argv[], RegexContext *, ErrInfo *, const Allocator *);

enum REGEX_PRODUCT_RULE_ENUM {
  ${enum_reduces}
};

extern fn_regex_reduce * const REGEX_PRODUCTS[];

${reduces}

#endif  // REGEX_REDUCES_H
