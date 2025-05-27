${license}

#ifndef REGEX_TOKENS_H
#define REGEX_TOKENS_H

#include "regex/char_t.h"
#include <stdint.h>

enum TOKEN_TYPE_ENUM: uint32_t {
  ${enums},
  enum_PLACE_HOLDER,
  MAX_TOTAL_TOKEN,
  enum_BAD_TOKEN = UINT32_MAX
};
extern const char_t *TOKEN_NAMES[];
#endif  // REGEX_TOKENS_H
