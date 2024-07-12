/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: target.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "target.h"
#include "allocator.h"
#include "tokens.gen.h"

void releaseSequence(Sequence *sequence, const Allocator *) {
  Array_reset(sequence, nullptr);
  Array_destroy(sequence);
}

void releaseCharset(Charset *charset, const Allocator *allocator) {
  Array_reset(charset->taps[0].plains, nullptr);
  Array_reset(charset->taps[0].ranges, nullptr);
  Array_reset(charset->taps[1].plains, nullptr);
  Array_reset(charset->taps[1].ranges, nullptr);
  Array_destroy(charset->taps[0].plains);
  Array_destroy(charset->taps[0].ranges);
  Array_destroy(charset->taps[1].plains);
  Array_destroy(charset->taps[1].ranges);
  allocator->free(charset);
}

void releaseGroup(Group *group, const Allocator *allocator) {
  releaseRegexp(group->regexp, allocator);
  allocator->free(group);
}

void releaseRegexp(Regexp *regexp, const Allocator *) {
  Array_reset(regexp, (void (*)(void *, const Allocator *)) releaseBranch);
  Array_destroy(regexp);
}

void releaseBranch(Branch *branch, const Allocator *) {
  Array_reset(branch, (void (*)(void *, const Allocator *)) releaseObject);
}

void releaseQuantified(Quantified *quantified, const Allocator *allocator) {
  releaseObject(&quantified->object, allocator);
  allocator->free(quantified);
}

void releaseObject(Object *object, const Allocator *allocator) {
  switch (object->type) {
    case enum_CHAR: {
      return;
    }
    case enum_Sequence: {
      releaseSequence(object->target, allocator);
      return;
    }
    case enum_Charset: {
      releaseCharset(object->target, allocator);
      break;
    }
    case enum_Group: {
      releaseGroup(object->target, allocator);
      break;
    }
    case enum_Quantified: {
      releaseQuantified(object->target, allocator);
      break;
    }
  }
}
