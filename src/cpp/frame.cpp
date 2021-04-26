#include "../h/frame.h"

void init_frame(Frame *frame, void *jvm, u4 n_locals, u4 n_operands, cp_info *cp,
		int32_t class_index, int32_t method_index) {
  frame->jvm = jvm;
  frame->n_locals = n_locals;
  frame->locals = (uint64_t*) calloc(sizeof(int64_t), n_locals);
  assert(frame->locals);
  frame->n_operands = n_operands;
  frame->operands = (uint64_t*) calloc(sizeof(int64_t), n_operands);
  assert(frame->operands);
  frame->i = 0;
  frame->cp = cp;

  frame->class_index = class_index;
  frame->method_index = method_index;
}

void deinit_frame(Frame *frame) {
  free(frame->locals);
  free(frame->operands);
}

void push_stack(Frame *frame, uint64_t operand) {
  assert(frame->i < frame->n_operands);
  frame->operands[frame->i++] = operand;
}

uint64_t pop_stack(Frame *frame) {
  assert(frame->i > 0);
  return frame->operands[--frame->i];
}

uint64_t peek_stack(Frame *frame) {
  return frame->operands[frame->i];
}

void push_stack_double(Frame *frame, double d) {
  uint64_t hex = *((uint64_t *) (& d));
  u4 hi = hex >> 32;
  u4 lo = hex;
  push_stack(frame, lo);
  push_stack(frame, hi);
}

double pop_stack_double(Frame *frame) {
  uint64_t hi = pop_stack(frame);
  uint64_t lo = pop_stack(frame);
  uint64_t hex = (hi << 32) | lo;
  return *((double *)(& hex));
}

void push_stack_long(Frame *frame, int64_t x) {
  uint64_t hex = *((uint64_t *) (& x));
  u4 hi = hex >> 32;
  u4 lo = hex;
  push_stack(frame, lo);
  push_stack(frame, hi);
}

int64_t pop_stack_long(Frame *frame) {
  uint64_t hi = pop_stack(frame);
  uint64_t lo = pop_stack(frame);
  uint64_t hex = (hi << 32) | lo;
  return *((int64_t *)(& hex));
}

void push_stack_float(Frame *frame, float x) {
  u4 hex = *((u4 *) (& x));
  push_stack(frame, hex);
}

float pop_stack_float(Frame *frame) {
  u4 hex = pop_stack(frame);
  return *((float *) (& hex));
}

void push_stack_int(Frame *frame, int32_t x) {
  uint64_t push = *((uint64_t *) (&x));
  push_stack(frame, push);
}

int32_t pop_stack_int(Frame *frame) {
  uint64_t pop = pop_stack(frame);
  int32_t int_value = *((int32_t *) (&pop));
  return int_value;
}

void push_stack_pointer(Frame *frame, void *ptr) {
  push_stack(frame, (uint64_t) ptr);
}

void *pop_stack_pointer(Frame *frame) {
  uint64_t pop = pop_stack(frame);
  return (void *) pop;
}

void push_stack_byte(Frame *frame, int8_t x) {
  uint64_t push = *((uint64_t *) (&x));
  push_stack(frame, push);
}

int8_t pop_stack_byte(Frame *frame) {
  uint64_t pop = pop_stack(frame);
  return *((int8_t *) &pop);
}

void frame_set_local(Frame *frame, u4 index, uint64_t value) {
  assert(index < frame->n_locals);
  frame->locals[index] = value;
}

uint64_t frame_get_local(Frame *frame, u4 index) {
  assert(index < frame->n_locals);
  return frame->locals[index];
}

void frame_set_local_int(Frame *frame, u4 index, int32_t value) {
  uint64_t x = *((uint64_t *) (& value));
  frame_set_local(frame, index, x);
}

int32_t frame_get_local_int(Frame *frame, u4 index) {
  uint64_t x = frame_get_local(frame, index);
  return *((int32_t *) (&x));
}

void frame_set_local_double(Frame *frame, u4 index, double value) {
  uint64_t x = *((uint64_t *) (& value));
  frame_set_local(frame, index, x);
}

double frame_get_local_double(Frame *frame, u4 index) {
  uint64_t x = frame_get_local(frame, index);
  return *((double *) (&x));
}

void frame_set_local_float(Frame *frame, u4 index, float value) {
  uint64_t x = *((uint64_t *) (& value));
  frame_set_local(frame, index, x);
}

float frame_get_local_float(Frame *frame, u4 index) {
  uint64_t x = frame_get_local(frame, index);
  return *((float *) (&x));
}

void frame_set_local_long(Frame *frame, u4 index, int64_t value) {
  uint64_t x = *((uint64_t *) (& value));
  frame_set_local(frame, index, x);
}

int64_t frame_get_local_long(Frame *frame, u4 index) {
  uint64_t x = frame_get_local(frame, index);
  return *((int64_t *) (&x));
}

void frame_set_local_pointer(Frame *frame, u4 index, void *value) {
  frame_set_local(frame, index, ((uint64_t) value));
}

void* frame_get_local_pointer(Frame *frame, u4 index) {
  uint64_t x = frame_get_local(frame, index);
  return *((void **) (&x));