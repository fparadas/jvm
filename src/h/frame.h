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
 * @brief Initializes a frame pointed by a jvm
 * 
 * @param frame reference to a frame
 * @param jvm reference to the jvm
 * @param n_locals size of the locals array
 * @param n_operands size of the operands stack
 * @param cp reference to the constant pool
 * @param class_index index of the class
 * @param method_index index of the current method
 */
void init_frame(Frame *frame, void *jvm, u4 n_locals, u4 n_operands, cp_info *cp,
		int32_t class_index, int32_t method_index);

/**
 * @brief Deinitializes frame memory area pointed to by jvm pointer.
 * 
 * @param frame pointer to a frame struct to be deinitialized
 */
void deinit_frame(Frame *frame);

/**
 * @brief Push an integer to the top of the frame operand stack.
 * 
 * @param operand integer operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack(Frame *frame, uint64_t operand);

/**
 * @brief Pop an integer of the top of the frame operand stack.
 * 
 * @param frame pointer to the current frame.
 */
uint64_t pop_stack(Frame *frame);

/**
 * @brief Return de value of an integer of the top of the frame operand stack.
 * 
 * @param frame pointer to the current frame.
 */
uint64_t peek_stack(Frame *frame);


/**
 * @brief Push a double to the top of the frame operand stack.
 * 
 * @param operand double operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack_double(Frame *frame, double d);

/**
 * @brief Pop a double of the top of the frame operand stack.
 * 
 * @param frame pointer to the current frame.
 */
double pop_stack_double(Frame *frame);


/**
 * @brief Push a long to the top of the frame operand stack.
 * 
 * @param x long operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack_long(Frame *frame, int64_t x);

/**
 * @brief Pop a long of the top of the frame operand stack.
 * 
 * @param frame pointer to the current frame.
 */
int64_t pop_stack_long(Frame *frame);


/**
 * @brief Push a float to the top of the frame operand stack.
 * 
 * @param x float operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack_float(Frame *frame, float x);

/**
 * @brief Pop a float of the top of the frame operand stack.
 * 
 * @param frame pointer to the current frame.
 */
float pop_stack_float(Frame *frame);

/**
 * @brief Push a 32 bits integer to the top of the frame operand stack.
 * 
 * @param x integer operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack_int(Frame *frame, int32_t x);

/**
 * @brief Pop a 32 bits integer of the top of the frame operand stack.
 * 
 * @param frame pointer to the current frame.
 */
int32_t pop_stack_int(Frame *frame);


/**
 * @brief Push a void pointer to the top of the frame operand stack.
 * 
 * @param operand pointer operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack_pointer(Frame *frame, void *ptr);

/**
 * @brief Pop a void pointer of the top of the frame operand stack.
 * 
 * @param frame pointer to the current frame.
 */
void *pop_stack_pointer(Frame *frame);


/**
 * @brief Push a byte to the top of the frame operand stack.
 * 
 * @param x byte operand to be added to the stack.
 * @param frame pointer to the current frame.
 */
void push_stack_byte(Frame *frame, int8_t x);

/**
 * @brief Pop a byte of the top of the frame operand stack.
 * 
 * @param frame pointer to the current frame.
 */
int8_t pop_stack_byte(Frame *frame);

/** 
 * @brief set local value at specific index
 * 
 * @param frame reference to the frame
 * @param index local array index
 * @param value value to be stored
 */
void frame_set_local(Frame *frame, u4 index, uint64_t value);

/**
 * @brief Gets value from locals array at specified index
 * 
 * @param frame reference to the frame
 * @param index index
 */
uint64_t frame_get_local(Frame *frame, u4 index);

/** 
 * @brief set local int value at specific index
 * 
 * @param frame reference to the frame
 * @param index local array index
 * @param value value to be stored
 */
void frame_set_local_int(Frame *frame, u4 index, int32_t value);

/**
 * @brief Gets int value from locals array at specified index
 * 
 * @param frame reference to the frame
 * @param index index
 */
int32_t frame_get_local_int(Frame *frame, u4 index);

/** 
 * @brief set local double value at specific index
 * 
 * @param frame reference to the frame
 * @param index local array index
 * @param value value to be stored
 */
void frame_set_local_double(Frame *frame, u4 index, double value);

/**
 * @brief Gets double value from locals array at specified index
 * 
 * @param frame reference to the frame
 * @param index index
 */
double frame_get_local_double(Frame *frame, u4 index);

/** 
 * @brief set local float value at specific index
 * 
 * @param frame reference to the frame
 * @param index local array index
 * @param value value to be stored
 */
void frame_set_local_float(Frame *frame, u4 index, float value);

/**
 * @brief Gets float value from locals array at specified index
 * 
 * @param frame reference to the frame
 * @param index index
 */
float frame_get_local_float(Frame *frame, u4 index);

/** 
 * @brief set local long value at specific index
 * 
 * @param frame reference to the frame
 * @param index local array index
 * @param value value to be stored
 */
void frame_set_local_long(Frame *frame, u4 index, int64_t value);

/**
 * @brief Gets (long) value from locals array at specified index
 * 
 * @param frame reference to the frame
 * @param index index
 */
int64_t frame_get_local_long(Frame *frame, u4 index);

/** 
 * @brief set local reference value at specific index
 * 
 * @param frame reference to the frame
 * @param index local array index
 * @param value reference to be stored
 */
void frame_set_local_pointer(Frame *frame, u4 index, void *value);

/**
 * @brief Gets reference from locals array at specified index
 * 
 * @param frame reference to the frame
 * @param index index
 */
void* frame_get_local_pointer(Frame *frame, u4 index);