/* License
 *
 * xRegex - a Kind of Regular Expression
 * Copyright (C) 2025 Yaokai Liu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
 * Project Name: regex
 * Module Name: grammar
 * Filename: reduce.c
 * Creator: Yaokai Liu
 * Create Date: 2024-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "array.h"
#include "enum.h"
#include "generated/regex/rules.gen.h"
#include "generated/tokens.gen.h"
#include "stack.h"
#include "target.h"
#include "terminal.h"
#include <stdint.h>
#include <string.h>

#define ALLOC_LEN 32
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

Affixed *Regex_Affixed_0(Token argv[], RegexContext *, ErrInfo *, const Allocator * const) {
  Object *_arg1 = argv[1].value;
  _arg1->inverse = true;
  return _arg1;
}

Assertion *Regex_Assertion_0(Token argv[], RegexContext *, ErrInfo *, const Allocator * const) {
  Quantified *_arg1 = argv[1].value;
  _arg1->assertion = true;
  return _arg1;
}

Assertion *Regex_Assertion_1(Token argv[], RegexContext *, ErrInfo *, const Allocator * const) {
  Affixed *_arg1 = argv[1].value;
  _arg1->assertion = true;
  return _arg1;
}

Assertion *Regex_Assertion_2(Token argv[], RegexContext *, ErrInfo *, const Allocator * const) {
  Element *_arg1 = argv[1].value;
  _arg1->assertion = true;
  return _arg1;
}

Branch *Regex_Branch_0(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  Branch *_arg0 = argv[0].value;
  Object *_arg1 = argv[1].value;
  Array_append(_arg0, _arg1, 1);
  allocator->free(_arg1);
  return _arg0;
}

Branch *Regex_Branch_1(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  Object *_arg0 = argv[0].value;
  Branch *br = Array_new(sizeof(Object), enum_Object, allocator);
  Array_append(br, _arg0, 1);
  allocator->free(_arg0);
  return br;
}

Charset *Regex_Charset_0(Token argv[], RegexContext *, ErrInfo *,
                         const Allocator * const allocator) {
  UnitArray *_arg1 = argv[1].value;

  Charset *charset = allocator->calloc(1, sizeof(Charset));
  // create parts
  charset->parts[CT_NORMAL ].plains = Array_new(sizeof(uint32_t), enum_CHAR, allocator);
  charset->parts[CT_NORMAL ].ranges = Array_new(sizeof(Range), enum_Range, allocator);
  charset->parts[CT_INVERSE].plains = Array_new(sizeof(uint32_t), enum_CHAR, allocator);
  charset->parts[CT_INVERSE].ranges = Array_new(sizeof(Range), enum_Range, allocator);

  uint32_t length = Array_length(_arg1);
  Unit *units = Array_first_real(_arg1);
  for (uint32_t i = 0; i < length; i++) {
    Unit *unit = &units[i];
    if (unit->type == enum_Charset) {
      // select part
      // copy without duplicate
      Charset *target = unit->target;
      Charset_update(charset, target, unit->inverse);
    } else if (unit->type == enum_CHAR) {
      // select part
      struct CharsetPart *part = &charset->parts[unit->inverse];
      // update plains
      uint32_t chr = (uint64_t) unit->target;
      Plain_set_update(part->plains, chr);
    } else if (unit->type == enum_Range) {
      // select part
      struct CharsetPart *part = &charset->parts[unit->inverse];
      // update range
      Range *range = unit->target;
      Range_set_update(part->ranges, *range);
    } else {
      // never be touched
    }
  }
  releaseUnitArray(_arg1, allocator);
  Array_destroy(_arg1);
  return charset;
}

Charset *Regex_Charset_1(Token argv[], RegexContext *, ErrInfo *,
                         const Allocator * const allocator) {
  uint32_t escape_id = (uint32_t) (uint64_t) argv[0].value;

  Charset *charset = allocator->calloc(1, sizeof(Charset));
  // create parts
  charset->parts[CT_NORMAL ].plains = Array_new(sizeof(uint32_t), enum_CHAR, allocator);
  charset->parts[CT_NORMAL ].ranges = Array_new(sizeof(Range), enum_Range, allocator);
  charset->parts[CT_INVERSE].plains = Array_new(sizeof(uint32_t), enum_CHAR, allocator);
  charset->parts[CT_INVERSE].ranges = Array_new(sizeof(Range), enum_Range, allocator);

  switch (escape_id) {
    case CHARSET_HEX_DIGITAL: {
      Range hex_ranges[3] = {
          { .min = '0', .max = '9' }, { .min = 'a', .max = 'f' }, { .min = 'A', .max = 'F' }
      };
      Array_append(charset->parts[CT_NORMAL].ranges, hex_ranges, 3);
      break;
    }
    case CHARSET_DEC_DIGITAL: {
      Range dec_range = {.min = '0', .max = '9'};
      Array_append(charset->parts[CT_NORMAL].ranges, &dec_range, 1);
      break;
    }
    case CHARSET_IDENT: {
      char_t *ident_plains = "_";
      Array_append(charset->parts[CT_NORMAL].plains, ident_plains, 1);
      Range ident_ranges[2] = { { .min = 'a', .max = 'z' }, { .min = 'A', .max = 'Z' } };
      Array_append(charset->parts[CT_NORMAL].ranges, ident_ranges, 2);
      break;
    }
    case CHARSET_LETTER: {
      Range ident_ranges[2] = { { .min = 'a', .max = 'z' }, { .min = 'A', .max = 'Z' } };
      Array_append(charset->parts[CT_NORMAL].ranges, ident_ranges, 2);
      break;
    }
    case CHARSET_LOWER_LETTER: {
      Range ident_ranges[1] = { { .min = 'a', .max = 'z' }};
      Array_append(charset->parts[CT_NORMAL].ranges, ident_ranges, 1);
      break;
    }
    case CHARSET_UPPER_LETTER: {
      Range ident_ranges[1] = { { .min = 'A', .max = 'Z' } };
      Array_append(charset->parts[CT_NORMAL].ranges, ident_ranges, 1);
      break;
    }
    default: { releaseCharset(charset, allocator); return nullptr; }
  }
  return charset;
}

Unit *Regex_Unit_0(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  void *chr = argv[0].value;
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_CHAR;
  unit->inverse = false;
  unit->target = chr;
  return unit;
}

Unit *Regex_Unit_1(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  void *_arg0 = argv[0].value;
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_Range;
  unit->inverse = false;
  unit->target = _arg0;
  return unit;
}

Unit *Regex_Unit_2(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  void *_arg0 = argv[0].value;
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_Charset;
  unit->inverse = false;
  unit->target = _arg0;
  return unit;
}

Unit *Regex_Unit_3(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  void *chr = argv[1].value;
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_CHAR;
  unit->inverse = true;
  unit->target = chr;
  return unit;
}

Unit *Regex_Unit_4(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  void *_arg1 = argv[1].value;
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_Charset;
  unit->inverse = true;
  unit->target = _arg1;
  return unit;
}

UnitArray *Regex_UnitArray_0(Token argv[], RegexContext *, ErrInfo *,
                             const Allocator * const allocator) {
  UnitArray *_arg0 = argv[0].value;
  Unit *_arg1 = argv[1].value;
  Array_append(_arg0, _arg1, 1);
  allocator->free(_arg1);
  return _arg0;
}

UnitArray *Regex_UnitArray_1(Token argv[], RegexContext *, ErrInfo *,
                             const Allocator * const allocator) {
  Unit *_arg0 = argv[0].value;
  UnitArray *array = Array_new(sizeof(Unit), enum_Unit, allocator);
  Array_append(array, _arg0, 1);
  allocator->free(_arg0);
  return array;
}

Group *Regex_Group_0(Token argv[], RegexContext *, ErrInfo *, const Allocator *allocator) {
  Regex *regexp = argv[1].value;
  Group *group = allocator->calloc(1, sizeof(Group));
  group->regexp = (enum_Regex == (uint64_t) regexp) ? nullptr : regexp;
  return group;
}

Element *Regex_Element_0(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  void *chr = argv[0].value;
  Element *ele = allocator->calloc(1, sizeof(Element));
  ele->type = enum_CHAR;
  ele->assertion = false;
  ele->inverse = false;
  ele->min_times = 1;
  ele->max_times = 1;
  ele->target = chr;
  return ele;
}

Object *Regex_Element_1(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  Charset *_arg0 = argv[0].value;
  Element *ele = allocator->calloc(1, sizeof(Element));
  ele->type = enum_Charset;
  ele->assertion = false;
  ele->inverse = false;
  ele->min_times = 1;
  ele->max_times = 1;
  ele->target = (void *) _arg0;
  return ele;
}

Object *Regex_Element_2(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  Group *_arg0 = argv[0].value;
  Element *ele = allocator->calloc(1, sizeof(Element));
  ele->type = enum_Group;
  ele->assertion = false;
  ele->inverse = false;
  ele->min_times = 1;
  ele->max_times = 1;
  ele->target = (void *) _arg0;
  return ele;
}

Object *Regex_Object_0(Token argv[], RegexContext *, ErrInfo *, const Allocator * const) {
  return (Object *) argv[0].value;
}

Object *Regex_Object_1(Token argv[], RegexContext *, ErrInfo *, const Allocator * const) {
  return (Object *) argv[0].value;
}

Object *Regex_Object_2(Token argv[], RegexContext *, ErrInfo *, const Allocator * const) {
  return (Object *) argv[0].value;
}

Object *Regex_Object_3(Token argv[], RegexContext *, ErrInfo *, const Allocator * const) {
  return (Object *) argv[0].value;
}

Quantified *Regex_Quantified_0(Token argv[], RegexContext *, ErrInfo *, const Allocator * const) {
  Affixed *_arg1 = argv[0].value;
  Quantifier quant = Quantifier_fromUint64((uint64_t) argv[1].value);
  _arg1->min_times = quant.min;
  _arg1->max_times = quant.max;
  return _arg1;
}

Quantified *Regex_Quantified_1(Token argv[], RegexContext *, ErrInfo *, const Allocator * const) {
  Element *_arg1 = argv[0].value;
  Quantifier quant = Quantifier_fromUint64((uint64_t) argv[1].value);
  _arg1->min_times = quant.min;
  _arg1->max_times = quant.max;
  return _arg1;
}

Range *Regex_Range_0(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  char_t chr1 = (uint64_t) argv[0].value;
  char_t chr2 = (uint64_t) argv[2].value;

  Range *rng = allocator->calloc(1, sizeof(Range));
  rng->min = min(chr1, chr2);
  rng->max = max(chr1, chr2);
  return rng;
}

Regex *Regex_Regex_0(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  Regex *_arg0 = argv[0].value;
  Branch *_arg2 = argv[2].value;
  Array_append(_arg0, _arg2, 1);
  allocator->free(_arg2);
  return _arg0;
}

Regex *Regex_Regex_1(Token argv[], RegexContext *, ErrInfo *, const Allocator * const allocator) {
  Branch *_arg0 = argv[0].value;
  Regex *regex = Array_new(sizeof_array, enum_Branch, allocator);
  Array_append(regex, _arg0, 1);
  allocator->free(_arg0);
  return regex;
}

Regex *Regex_Regex_2(Token[], RegexContext *, ErrInfo *, const Allocator * const) {
  return (Regex *) enum_Regex;
}

Regex *Regex_Regex_EXT(Token argv[], RegexContext *, ErrInfo *, const Allocator *) {
  return (Regex *) argv[0].value;
}

Regex *failed_to_get_next_state(Stack *state_stack, Stack *token_stack, void *result,
                                 uint32_t result_type, const Allocator *allocator);
Regex *failed_to_parse(Stack *state_stack, Stack *token_stack, Token *, uint32_t,
                        const Allocator *allocator);
Regex *failed_to_get_action(Stack *state_stack, Stack *token_stack, const Allocator *allocator);

Regex *failed_to_get_next_state(Stack *state_stack, Stack *token_stack, void *result,
                                 uint32_t result_type, const Allocator *allocator) {
  int32_t state = 0;
  Stack_top(state_stack, (int32_t *) &state, sizeof(int32_t));
  switch (result_type) {
    case enum_Regex: {
      if (((uint64_t) result) > enum_Regex) { Array_destroy(result); }
      break;
    }
    case enum_Branch: {
      releaseBranch(result, allocator);
      break;
    }
    case enum_Group: {
      releaseGroup(result, allocator);
      break;
    }
    case enum_Object: {
      releaseObject(result, allocator);
      break;
    }
    case enum_Charset: {
      releaseCharset(result, allocator);
      break;
    }
    case enum_Sequence: {
      releaseSequence(result, allocator);
      break;
    }
    case enum_UnitArray: {
      releaseUnitArray(result, allocator);
      break;
    }
    case enum_Unit: {
      releaseUnit(result, allocator);
      break;
    }
    default: {
    }
  }
  allocator->free(result);
  return failed_to_get_action(state_stack, token_stack, allocator);
}

Regex *failed_to_parse(Stack *state_stack, Stack *token_stack, Token *, uint32_t,
                        const Allocator *allocator) {
  // TODO： release memory allocated.
  return failed_to_get_action(state_stack, token_stack, allocator);
}

Regex *failed_to_get_action(Stack *state_stack, Stack *token_stack, const Allocator *allocator) {
  // TODO： release memory allocated.
  Stack_clear(token_stack);
  Stack_clear(state_stack);
  allocator->free(token_stack);
  allocator->free(state_stack);
  return nullptr;
}
