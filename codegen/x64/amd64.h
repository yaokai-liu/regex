/**
 * Project Name: regex
 * Module Name: codegen/x64
 * Filename: amd64.h
 * Creator: Yaokai Liu
 * Create Date: 2024-08-03
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_X64_AMD64_H
#define REGEX_X64_AMD64_H

#include <stdbool.h>
#include <stdint.h>

enum LEGACY_PREFIX : uint8_t {
  // prefix group 1
  LEGACY_LOCK   = 0xf0,
  LEGACY_REP_NZ = 0xf2,
  LEGACY_REP_Z  = 0xf3,

  // prefix group 2
  LEGACY_CS    = 0x2E,
  LEGACY_SS    = 0x36,
  LEGACY_DS    = 0x3E,
  LEGACY_ES    = 0x26,
  LEGACY_FS    = 0x64,
  LEGACY_GS    = 0x65,
  LEGACY_BR_NT = 0x2E,
  LEGACY_BR_T  = 0x3E,

  // prefix group 3
  LEGACY_SIZE_OD = 0x66,

  // prefix group 4
  LEGACY_ADDR_OD = 0x67,
};

struct LegacyPrefix {
  uint8_t prefix;
};

enum REX_PREFIX : uint8_t {
  REX_WB = 0b00001000,
  REX_RB = 0b00000100,
  REX_XB = 0b00000010,
  REX_BB = 0b00000001,
};

struct RexPrefix {
  uint8_t prefix;
};

enum VEX_XOP_PREFIX : uint8_t {
  VEX_XOP_3VEX = 0xc4,
  VEX_XOP_2VEX = 0xc5,
  VEX_XOP_3XOP = 0x8f
};

struct VexXopPrefix {
  uint8_t prefix;
  bool invR         : 1;
  bool invX         : 1;
  bool invB         : 1;
  uint8_t mapSelect : 5;
  uint8_t WE        : 1;
  uint8_t inv4V     : 4;
  bool L            : 1;
  uint8_t pp        : 2;
};

struct ModRMSuffix {
  uint8_t mod : 2;
  uint8_t reg : 3;
  uint8_t rm  : 3;
};

struct SibSuffix {
  uint8_t scale : 2;
  uint8_t index : 3;
  uint8_t base  : 3;
};

#endif  // REGEX_X64_AMD64_H
