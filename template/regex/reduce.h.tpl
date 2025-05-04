${license}

#ifndef REGEX_REDUCES_H
#define REGEX_REDUCES_H

#include "regex/target.h"
#include "regex/context.h"

typedef void *fn_reduce(Token argv[], RegexContext *, const Allocator *);

enum REGEX_PRODUCT_RULE_ENUM {
  ${enum_reduces}
};

${reduces}

#endif  // REGEX_REDUCES_H
