/**
 * Project Name: regex
 * Module Name: codegen/x64
 * Filename: registers.h
 * Creator: Yaokai Liu
 * Create Date: 2024-07-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_REGISTERS_H
#define REGEX_REGISTERS_H

#include <stdint.h>

enum RealRegister : uint8_t {
  // 8-bit GPR
  REG_AL   = 0x00,
  REG_CL   = 0x01,
  REG_DL   = 0x02,
  REG_BL   = 0x03,
  REG_SPL  = 0x04,
  REG_BPL  = 0x05,
  REG_SIL  = 0x06,
  REG_DIL  = 0x07,
  REG_R8L  = 0x08,
  REG_R9L  = 0x09,
  REG_R10L = 0x0a,
  REG_R11L = 0x0b,
  REG_R12L = 0x0c,
  REG_R13L = 0x0d,
  REG_R14L = 0x0e,
  REG_R15L = 0x0f,

  // 16-bit GPR
  REG_AX   = 0x00,
  REG_CX   = 0x01,
  REG_DX   = 0x02,
  REG_BX   = 0x03,
  REG_SP   = 0x04,
  REG_BP   = 0x05,
  REG_SI   = 0x06,
  REG_DI   = 0x07,
  REG_R8W  = 0x08,
  REG_R9W  = 0x09,
  REG_R10W = 0x0a,
  REG_R11W = 0x0b,
  REG_R12W = 0x0c,
  REG_R13W = 0x0d,
  REG_R14W = 0x0e,
  REG_R15W = 0x0f,

  // 32-bit GPR
  REG_EAX  = 0x00,
  REG_ECX  = 0x01,
  REG_EDX  = 0x02,
  REG_EBX  = 0x03,
  REG_ESP  = 0x04,
  REG_EBP  = 0x05,
  REG_ESI  = 0x06,
  REG_EDI  = 0x07,
  REG_R8D  = 0x08,
  REG_R9D  = 0x09,
  REG_R10D = 0x0a,
  REG_R11D = 0x0b,
  REG_R12D = 0x0c,
  REG_R13D = 0x0d,
  REG_R14D = 0x0e,
  REG_R15D = 0x0f,

  // 64-bit GPR
  REG_RAX = 0x00,
  REG_RCX = 0x01,
  REG_RDX = 0x02,
  REG_RBX = 0x03,
  REG_RSP = 0x04,
  REG_RBP = 0x05,
  REG_RSI = 0x06,
  REG_RDI = 0x07,
  REG_R8  = 0x08,
  REG_R9  = 0x09,
  REG_R10 = 0x0a,
  REG_R11 = 0x0b,
  REG_R12 = 0x0c,
  REG_R13 = 0x0d,
  REG_R14 = 0x0e,
  REG_R15 = 0x0f,

  // 80-bit x87 Register
  REG_ST0 = 0x00,
  REG_ST1 = 0x01,
  REG_ST2 = 0x02,
  REG_ST3 = 0x03,
  REG_ST4 = 0x04,
  REG_ST5 = 0x05,
  REG_ST6 = 0x06,
  REG_ST7 = 0x07,

  // 64-bit MMX
  REG_MMX0 = 0x00,
  REG_MMX1 = 0x01,
  REG_MMX2 = 0x02,
  REG_MMX3 = 0x03,
  REG_MMX4 = 0x04,
  REG_MMX5 = 0x05,
  REG_MMX6 = 0x06,
  REG_MMX7 = 0x07,
  REG_MMX8 = 0x08,
  REG_MMX9 = 0x09,
  REG_MMXa = 0x0a,
  REG_MMXb = 0x0b,
  REG_MMXc = 0x0c,
  REG_MMXd = 0x0d,
  REG_MMXe = 0x0e,
  REG_MMXf = 0x0f,

  // 128-bit XMM Register
  REG_XMM0 = 0x00,
  REG_XMM1 = 0x01,
  REG_XMM2 = 0x02,
  REG_XMM3 = 0x03,
  REG_XMM4 = 0x04,
  REG_XMM5 = 0x05,
  REG_XMM6 = 0x06,
  REG_XMM7 = 0x07,
  REG_XMM8 = 0x08,
  REG_XMM9 = 0x09,
  REG_XMMa = 0x0a,
  REG_XMMb = 0x0b,
  REG_XMMc = 0x0c,
  REG_XMMd = 0x0d,
  REG_XMMe = 0x0e,
  REG_XMMf = 0x0f,

  // 256-bit YMM Register
  REG_YMM0 = 0x00,
  REG_YMM1 = 0x01,
  REG_YMM2 = 0x02,
  REG_YMM3 = 0x03,
  REG_YMM4 = 0x04,
  REG_YMM5 = 0x05,
  REG_YMM6 = 0x06,
  REG_YMM7 = 0x07,
  REG_YMM8 = 0x08,
  REG_YMM9 = 0x09,
  REG_YMMa = 0x0a,
  REG_YMMb = 0x0b,
  REG_YMMc = 0x0c,
  REG_YMMd = 0x0d,
  REG_YMMe = 0x0e,
  REG_YMMf = 0x0f,

  // 16-bit Segment Register
  REG_ES0 = 0x00,
  REG_CS0 = 0x01,
  REG_SS0 = 0x02,
  REG_DS0 = 0x03,
  REG_FS0 = 0x04,
  REG_GS0 = 0x05,
  REG_ES1 = 0x08,
  REG_CS1 = 0x09,
  REG_SS1 = 0x0a,
  REG_DS1 = 0x0b,
  REG_FS1 = 0x0c,
  REG_GS1 = 0x0d,

  // 32-bit Control Register
  REG_CR0 = 0x00,
  REG_CR1 = 0x01,
  REG_CR2 = 0x02,
  REG_CR3 = 0x03,
  REG_CR4 = 0x04,
  REG_CR5 = 0x05,
  REG_CR6 = 0x06,
  REG_CR7 = 0x07,
  REG_CR8 = 0x08,
  REG_CR9 = 0x09,
  REG_CRa = 0x0a,
  REG_CRb = 0x0b,
  REG_CRc = 0x0c,
  REG_CRd = 0x0d,
  REG_CRe = 0x0e,
  REG_CRf = 0x0f,

  // 32-bit Debug Register
  REG_DR0 = 0x00,
  REG_DR1 = 0x01,
  REG_DR2 = 0x02,
  REG_DR3 = 0x03,
  REG_DR4 = 0x04,
  REG_DR5 = 0x05,
  REG_DR6 = 0x06,
  REG_DR7 = 0x07,
  REG_DR8 = 0x08,
  REG_DR9 = 0x09,
  REG_DRa = 0x0a,
  REG_DRb = 0x0b,
  REG_DRc = 0x0c,
  REG_DRd = 0x0d,
  REG_DRe = 0x0e,
  REG_DRf = 0x0f,
};

enum ReRegister : uint32_t {
#ifdef WIN64
  REREG_STR_BASE = REG_RCX,
  REREG_STR_PTR  = REG_RDX,
  REREG_PATTERN  = REG_R8,
  REREG_REPEAT   = REG_R9,
#elifdef UNIX64
  REREG_STR_BASE = REG_RDI,
  REREG_STR_PTR  = REG_RSI,
  REREG_PATTERN  = REG_RCX,
  REREG_REPEAT   = REG_RDX,
#else
  #error "Unknown operating system."
#endif
};

#endif  // REGEX_REGISTERS_H
