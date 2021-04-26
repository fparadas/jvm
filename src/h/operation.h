/**
 * @file operation.h
 * @brief Operations defined
 * File containing the main implementation of the oiperations.
 *
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "frame.h"
#include "jvm.h"
#include "getter.h"
#include "utils.h"
#include "opcodes.h"

#define N_OPS 255

typedef void (*operation)(Frame *, u4, u4);

extern operation optable[N_OPS];

void nop(Frame *f, u4 a0, u4 a1);

void ldc(Frame *f, u4 a0, u4 a1);

void istore(Frame *f, u4 a0, u4 a1);
void istore_0(Frame *f, u4 a0, u4 a1);
void istore_1(Frame *f, u4 a0, u4 a1);
void istore_2(Frame *f, u4 a0, u4 a1);
void istore_3(Frame *f, u4 a0, u4 a1);

void iload(Frame *f, u4 a0, u4 a1);
void iload_0(Frame *f, u4 a0, u4 a1);
void iload_1(Frame *f, u4 a0, u4 a1);
void iload_2(Frame *f, u4 a0, u4 a1);
void iload_3(Frame *f, u4 a0, u4 a1);

void isub(Frame *f, u4 a0, u4 a1);
void iadd(Frame *f, u4 a0, u4 a1);
void idiv(Frame *f, u4 a0, u4 a1);
void imul(Frame *f, u4 a0, u4 a1);
void iand(Frame *f, u4 a0, u4 a1);
void ior(Frame *f, u4 a0, u4 a1);
void ishr(Frame *f, u4 a0, u4 a1);
void ishl(Frame *f, u4 a0, u4 a1);
void iushr(Frame *f, u4 a0, u4 a1);
void irem(Frame *f, u4 a0, u4 a1);
void ineg(Frame *f, u4 a0, u4 a1);

void return_func(Frame *f, u4 a0, u4 a1);
void ireturn(Frame *f, u4 a0, u4 a1);
void dreturn(Frame *f, u4 a0, u4 a1);
void lreturn(Frame *f, u4 a0, u4 a1);
void freturn(Frame *f, u4 a0, u4 a1);

void invokevirtual(Frame *f, u4 a0, u4 a1);
void invokestatic(Frame *f, u4 a0, u4 a1);

void invokespecial(Frame *f, u4 a0, u4 a1);

void getstatic(Frame *f, u4 a0, u4 a1);
void putstatic(Frame *f, u4 a0, u4 a1);

void ldc_w(Frame *f, u4 a0, u4 a1);
void ldc2_w(Frame *f, u4 a0, u4 a1);

void dstore(Frame *f, u4 a0, u4 a1);
void dstore_0(Frame *f, u4 a0, u4 a1);
void dstore_1(Frame *f, u4 a0, u4 a1);
void dstore_2(Frame *f, u4 a0, u4 a1);
void dstore_3(Frame *f, u4 a0, u4 a1);

void dload(Frame *f, u4 a0, u4 a1);
void dload_0(Frame *f, u4 a0, u4 a1);
void dload_1(Frame *f, u4 a0, u4 a1);
void dload_2(Frame *f, u4 a0, u4 a1);
void dload_3(Frame *f, u4 a0, u4 a1);

void dadd(Frame *f, u4 a0, u4 a1);
void dsub(Frame *f, u4 a0, u4 a1);
void ddiv(Frame *f, u4 a0, u4 a1);
void dmul(Frame *f, u4 a0, u4 a1);
void dneg(Frame *f, u4 a0, u4 a1);
void drem(Frame *f, u4 a0, u4 a1);

void bipush(Frame *f, u4 a0, u4 a1);

void iconst_0(Frame *f, u4 a0, u4 a1);
void iconst_1(Frame *f, u4 a0, u4 a1);
void iconst_2(Frame *f, u4 a0, u4 a1);
void iconst_3(Frame *f, u4 a0, u4 a1);
void iconst_4(Frame *f, u4 a0, u4 a1);
void iconst_5(Frame *f, u4 a0, u4 a1);
void iconst_m1(Frame *f, u4 a0, u4 a1);

void if_icmpeq(Frame *f, u4 a0, u4 a1);
void if_icmpne(Frame *f, u4 a0, u4 a1);
void if_icmplt(Frame *f, u4 a0, u4 a1);
void if_icmpge(Frame *f, u4 a0, u4 a1);
void if_icmpgt(Frame *f, u4 a0, u4 a1);
void if_icmple(Frame *f, u4 a0, u4 a1);

void lconst_0(Frame *f, u4 a0, u4 a1);
void lconst_1(Frame *f, u4 a0, u4 a1);

void lstore(Frame *f, u4 a0, u4 a1);
void lstore_0(Frame *f, u4 a0, u4 a1);
void lstore_1(Frame *f, u4 a0, u4 a1);
void lstore_2(Frame *f, u4 a0, u4 a1);
void lstore_3(Frame *f, u4 a0, u4 a1);

void lload(Frame *f, u4 a0, u4 a1);
void lload_0(Frame *f, u4 a0, u4 a1);
void lload_1(Frame *f, u4 a0, u4 a1);
void lload_2(Frame *f, u4 a0, u4 a1);
void lload_3(Frame *f, u4 a0, u4 a1);

void ladd(Frame *f, u4 a0, u4 a1);
void lsub(Frame *f, u4 a0, u4 a1);
void lmul(Frame *f, u4 a0, u4 a1);
void ldiv_(Frame *f, u4 a0, u4 a1);

void iinc(Frame *f, u4 a0, u4 a1);

void goto_func(Frame *f, u4 a0, u4 a1);

void fconst_0(Frame *f, u4 a0, u4 a1);
void fconst_1(Frame *f, u4 a0, u4 a1);
void fconst_2(Frame *f, u4 a0, u4 a1);

void fstore(Frame *f, u4 a0, u4 a1);
void fstore_0(Frame *f, u4 a0, u4 a1);
void fstore_1(Frame *f, u4 a0, u4 a1);
void fstore_2(Frame *f, u4 a0, u4 a1);
void fstore_3(Frame *f, u4 a0, u4 a1);

void fload(Frame *f, u4 a0, u4 a1);
void fload_0(Frame *f, u4 a0, u4 a1);
void fload_1(Frame *f, u4 a0, u4 a1);
void fload_2(Frame *f, u4 a0, u4 a1);
void fload_3(Frame *f, u4 a0, u4 a1);

void fsub(Frame *f, u4 a0, u4 a1);
void fadd(Frame *f, u4 a0, u4 a1);
void fdiv(Frame *f, u4 a0, u4 a1);
void fmul(Frame *f, u4 a0, u4 a1);
void fneg(Frame *f, u4 a0, u4 a1);
void frem(Frame *f, u4 a0, u4 a1);

void ifeq(Frame *f, u4 a0, u4 a1);
void ifne(Frame *f, u4 a0, u4 a1);
void iflt(Frame *f, u4 a0, u4 a1);
void ifge(Frame *f, u4 a0, u4 a1);
void ifgt(Frame *f, u4 a0, u4 a1);
void ifle(Frame *f, u4 a0, u4 a1);
void ifnull(Frame *f, u4 a0, u4 a1);
void ifnonnull(Frame *f, u4 a0, u4 a1);

void i2f(Frame *f, u4 a0, u4 a1);
void i2d(Frame *f, u4 a0, u4 a1);

void i2b(Frame *f, u4 a0, u4 a1);
void i2c(Frame *f, u4 a0, u4 a1);
void i2l(Frame *f, u4 a0, u4 a1);
void i2s(Frame *f, u4 a0, u4 a1);

void sipush(Frame *f, u4 a0, u4 a1);
void aconst_null(Frame *f, u4 a0, u4 a);
void aload(Frame *f, u4 a0, u4 a1);
void aload_0(Frame *f, u4 a0, u4 a1);
void aload_1(Frame *f, u4 a0, u4 a1);
void aload_2(Frame *f, u4 a0, u4 a1);
void aload_3(Frame *f, u4 a0, u4 a1);

void astore(Frame *f, u4 a0, u4 a1);
void astore_0(Frame *f, u4 a0, u4 a1);
void astore_1(Frame *f, u4 a0, u4 a1);
void astore_2(Frame *f, u4 a0, u4 a1);
void astore_3(Frame *f, u4 a0, u4 a1);

void newarray(Frame *f, u4 a0, u4 a1);

void aastore(Frame *f, u4 a0, u4 a1);
void aaload(Frame *f, u4 a0, u4 a1);

void iastore(Frame *f, u4 a0, u4 a1);
void iaload(Frame *f, u4 a0, u4 a1);

void fastore(Frame *f, u4 a0, u4 a1);
void faload(Frame *f, u4 a0, u4 a1);

void lastore(Frame *f, u4 a0, u4 a1);
void laload(Frame *f, u4 a0, u4 a1);

void dastore(Frame *f, u4 a0, u4 a1);
void daload(Frame *f, u4 a0, u4 a1);

void bastore(Frame *f, u4 a0, u4 a1);
void baload(Frame *f, u4 a0, u4 a1);

void d2f(Frame *f, u4 a0, u4 a1);
void d2i(Frame *f, u4 a0, u4 a1);
void d2l(Frame *f, u4 a0, u4 a1);

void f2d(Frame *f, u4 a0, u4 a1);
void f2i(Frame *f, u4 a0, u4 a1);
void f2l(Frame *f, u4 a0, u4 a1);

void l2d(Frame *f, u4 a0, u4 a1);
void l2f(Frame *f, u4 a0, u4 a1);
void l2i(Frame *f, u4 a0, u4 a1);

void athrow(Frame *f, u4 a0, u4 a1);

void multianewarray(Frame *f, u4 a0, u4 a1);

void anewarray(Frame *f, u4 a0, u4 a1);
void arraylength(Frame *f, u4 a0, u4 a1);

void dup(Frame *f, u4 a0, u4 a1);
void dup2(Frame *f, u4 a0, u4 a1);
void _new(Frame *f, u4 a0, u4 a1);
void getfield(Frame *f, u4 a0, u4 a1);
void putfield(Frame *f, u4 a0, u4 a1);

