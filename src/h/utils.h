#pragma once
#include <fstream>
#include <iostream>
#include <stdint.h>

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

/**
 * Returns the 16-bit input with switched endianness.
 */
u2 switch_endian(u2 x);

/**
 * Returns the 32-bit input with switched endianness.
 */
u4 switch_endian(u4 x);
/**
 * Reads a 8-bit value from fp.
 */
u1 read_u1(FILE *fp);

/**
 * Reads a big endian 16-bit value from fp and switches its endianness.
 */
u2 read_u2(FILE *fp);

/**
 * Reads a big endian 32-bit value from fp and switches its endianness.
 */
u4 read_u4(FILE *fp);