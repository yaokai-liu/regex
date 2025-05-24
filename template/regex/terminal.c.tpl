${license}

#include "token.h"
#include "generated/tokens.gen.h"
const char_t REGEX_TERMINALS[] = {
  ${terminals}
};

const char_t * REGEX_TERMINAL_STRINGS[] = {
  ${strings}
};

const uint32_t REGEX_TERMINAL_STRING_LENS[] = {
  ${string_lens}
};

const int32_t N_REGEX_TERMINAL = sizeof(REGEX_TERMINALS);
