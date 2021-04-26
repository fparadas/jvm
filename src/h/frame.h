#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "dotclass.h"

/**
 * @brief Frame structure.
 *
 * Structure that stores the information that defines and is utilized by a frame from a JVM.
 */
typedef struct Frame {
  void *jvm;
  u4 n_locals;
  uint64_t *locals;
  u4 n_operands;
  uint64_t *operands;
  u4 i;
  cp_info *cp;
  u4 pc;
  int32_t class_index;
  int32_t method_index;
} Frame;

/**
 * Initializes a frame pointed by a jvm
 */
void init_frame(Frame *frame, void *jvm, u4 n_locals, u4 n_operands, cp_info *cp,
		int32_t class_index, int32_t method_index);

/**
 * Deinitializes frame memory area pointed to by jvm pointer.
 * Notably, locals, operands, and auxiliary structures are freed
 * @param frame pointer to a frame struct to be deinitialized
 */
void deinit_frame(Frame *frame);

/**
 * Push an integer to the top of the frame operand stack.
 * @param operand integer operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack(Frame *frame, uint64_t operand);

/**
 * Pop an integer of the top of the frame operand stack.
 * @param frame pointer to the current frame.
 */
uint64_t pop_stack(Frame *frame);

/**
 * Return de value of an integer of the top of the frame operand stack.
 * @param frame pointer to the current frame.
 */
uint64_t peek_stack(Frame *frame);


/**
 * Push a double to the top of the frame operand stack.
 * @param operand double operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack_double(Frame *frame, double d);

/**
 * Pop a double of the top of the frame operand stack.
 * @param frame pointer to the current frame.
 */
double pop_stack_double(Frame *frame);


/**
 * Push a long to the top of the frame operand stack.
 * @param operand long operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack_long(Frame *frame, int64_t x);

/**
 * Pop a long of the top of the frame operand stack.
 * @param frame pointer to the current frame.
 */
int64_t pop_stack_long(Frame *frame);


/**
 * Push a float to the top of the frame operand stack.
 * @param operand float operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack_float(Frame *frame, float x);

/**
 * Pop a float of the top of the frame operand stack.
 * @param frame pointer to the current frame.
 */
float pop_stack_float(Frame *frame);

/**
 * Push a 32 bits integer to the top of the frame operand stack.
 * @param operand integer operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack_int(Frame *frame, int32_t x);

/**
 * Pop a 32 bits integer of the top of the frame operand stack.
 * @param frame pointer to the current frame.
 */
int32_t pop_stack_int(Frame *frame);


/**
 * Push a void pointer to the top of the frame operand stack.
 * @param operand pointer operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack_pointer(Frame *frame, void *ptr);

/**
 * Pop a void pointer of the top of the frame operand stack.
 * @param frame pointer to the current frame.
 */
void *pop_stack_pointer(Frame *frame);


/**
 * Push a byte to the top of the frame operand stack.
 * @param operand byte operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack_byte(Frame *frame, int8_t x);

/**
 * Pop a byte of the top of the frame operand stack.
 * @param frame pointer to the current frame.
 */
int8_t pop_stack_byte(Frame *frame);

void frame_set_local(Frame *frame, u4 index, uint64_t value);
uint64_t frame_get_local(Frame *frame, u4 index);

void frame_set_local_int(Frame *frame, u4 index, int32_t value);
int32_t frame_get_local_int(Frame *frame, u4 index);

void frame_set_local_double(Frame *frame, u4 index, double value);
double frame_get_local_double(Frame *frame, u4 index);

void frame_set_local_float(Frame *frame, u4 index, float value);
float frame_get_local_float(Frame *frame, u4 index);

void frame_set_local_long(Frame *frame, u4 index, int64_t value);
int64_t frame_get_local_long(Frame *frame, u4 index);

void frame_set_local_pointer(Frame *frame, u4 index, void *value);
void* frame_get_local_pointer(Frame *frame, u4 index);