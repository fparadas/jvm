/**
 * @file jvm.h
 * @brief Interpreter
 * File containing the main implementation of the interpreter.
 *
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "dotclass.h"
#include "frame.h"
#include "methodarea.h"
#include "object.h"
#include "operation.h"

#define MAX_FRAMES  32
#define MAXHEAP     256
#define MAXSTATICS  256

/**
 * @brief Static attribute.
 *
 * Structure to store a static attribute of a class.
 */
typedef struct Static {
  char *_class; /**< Class name */
  char *name; /**< Attribute name */
  char *type; /**< Attribute type name */
  ObjectField value; /**< Attribute value */
} Static;

/**
 * @brief Interpreter structure.
 *
 * Structure that stores the information utilized by the JVM interpreter and defines it.
 */
typedef struct JVM {
  u4 pc; /**< Program counter */
  Frame *frames[MAX_FRAMES]; /**< Pointer to frame stack */
  int32_t frame_index;    /**< Top index of frame stack */
  /* uint8_t *heap; */
  MethodArea *method_area; /**< Pointer to method area */
  /* NativeMethodArea nma; */
  int32_t current_class_index; 
  int32_t current_method_index;
  bool jmp; /**< If will ocurr a jump */
  bool ret; /**< If will return */
  uint64_t retval; /**< Value that will be returned */

  void *heap[MAXHEAP]; /**< Pointer to heap area */
  int32_t heap_index; /**< Top index of heap */

  Static *statics[MAXSTATICS]; /**< Pointer to static objects stack*/
  int32_t static_index; /**< Top index of static stack*/
} JVM;

/**
 * Initializes JVM memory area pointed to by jvm pointer.
 * @param jvm non-null pointer to jvm struct to be initialized
 */
void init_jvm(JVM *jvm);

/**
 * Deinitializes JVM memory area pointed to by jvm pointer.
 * Notably, heap, frames, and auxiliary structures are freed
 * @param jvm non-null pointer to jvm struct to be deinitialized
 */
void deinit_jvm(JVM *jvm);

/**
 * Load the classfile into the jvm's MethodArea
 * Classfile reference is directly assigned (will not be copied in any way).
 * Therefore the allocated memory must be persitent and is maintained by the user.
 * @param jvm non-null pointer to jvm to which cf will be loaded
 * @param cf classfile to be loaded
 */
void jvm_load_classfile(JVM *jvm, classfile *cf);

/**
 * Load the class with class_name into the jvm's MethodArea
 * File will be read from disk. An assertion will check whether the file can be read.
 * @param jvm non-null pointer to jvm to which class will be loaded
 * @param class_name name of the class to be loaded (without .class extension)
 */
void jvm_load_class(JVM *jvm, char *class_name);

/**
 * Set class which owns current method being run
 * Assumes class is already loaded
 * @param jvm non-null pointer to jvm to which class will be set
 * @param class_name name of the class to be set as current
 */
void jvm_set_current_class(JVM *jvm, char *class_name);

/**
 * Set current method to run
 * Assumes method belongs to class set as current.
 * @param jvm non-null pointer to jvm to which method will be set
 * @param method_name name of the method to be set as current
 */
void jvm_set_current_method(JVM *jvm, char *method_name);

void jvm_exec_clinit(JVM *jvm);

/**
 * Set the current class and current method members with index in MethodArea.
 * Assumes that the current class does contain the method required
 * @param jvm non-null pointer to jvm to which method will be set
 * @param class_index index to classfile in JVM's MethodArea
 * @param method_index index to the desired method in the classfile
 */
void jvm_load_method(JVM *jvm, u4 class_index, u4 method_index);

/**
 * Returns a reference to the class which runs the method being run
 * @param jvm pointer to jvm
 */
classfile *jvm_get_current_class(JVM *jvm);

/**
 * Returns the name of the class which runs the method being run
 * @param jvm pointer to jvm
 */
char *jvm_get_current_class_name(JVM *jvm);

/**
 * Returns a reference to the method being run
 * @param jvm pointer to jvm
 */
method_info *jvm_get_current_method(JVM *jvm);

/**
 * Returns the name of the method being run
 * @param jvm pointer to jvm
 */
char *jvm_get_current_method_name(JVM *jvm);

/**
 * Creates a frame for a call to the current method and pushes it onto the frame stack of jvm
 * @param jvm pointer to jvm
 */
void jvm_push_frame(JVM *jvm);

/**
 * Pop the current frame off the stack and free all its resources
 * @param jvm pointer to jvm
 */
void jvm_pop_frame(JVM *jvm);

/**
 * Returns a pointer to the frame on top of the stack
 * @param jvm pointer to jvm
 */
Frame *jvm_peek_frame(JVM *jvm);

/** Run one jvm cycle
 * Returns 0 when return from main or clinit is called, 1 otherwise
 * @param jvm pointer to jvm
 */
int jvm_cycle(JVM *jvm);

/**
 * Runs until return from main or clinit is reached.
 * @param jvm pointer to jvm
 */
void jvm_run(JVM *jvm);

/**
 * Load current method into frame stack and run it
 * @param jvm pointer to jvm
 */
void jvm_run_method(JVM *jvm);

/**
 * Returns whether jvm is currently running a main method
 * @param jvm pointer to jvm
 */
int jvm_in_main(JVM *jvm);

/**
 * Returns whether jvm is currently running <clinit> method
 * @param jvm pointer to jvm
 */
bool jvm_in_clinit(JVM *jvm);

/**
 * Save current frame context
 * PC, current class and current method's indexes are saved to frame (typically the callee).
 * @param jvm pointer to jvm
 */
void jvm_save_context(JVM *jvm);

/**
 * Restore context to previous frame (callee)
 * PC and previous class' and method's indexes are restored.
 * @param jvm pointer to jvm
 */
void jvm_restore_context(JVM *jvm);

/**
 * Add new pointer to jvm's heap table
 * The heap space is for memory allocated during runtime.
 * When an object is allocated, it persists until the JVM is deinitialized.
 * Upon deinitialization, all heap memory is freed.
 * The heap uses a stack structure, where the latest placed pointers are freed first.
 * Therefore, nested structures must have their 'leafs' placed after the 'parents' (i.e. 2d,3d arrays)
 * @param jvm pointer to jvm
 * @param ptr pointer to be added to the heap
 */
void jvm_add_to_heap(JVM *jvm, void *ptr);

/**
 * Passes the arguments from the caller to the callee's local variables array
 * @param jvm pointer to jvm
 * @param caller pointer to caller's frame
 * @param type callee's type descriptor
 */
void jvm_set_args(JVM *jvm, Frame *caller, char *type);

/**
 * Returns reference to static variable with name belonging to classname
 * A null pointer is returned if not such static variable is found.
 * @param jvm pointer to jvm containing static variable
 * @param classname name of the class to which the variable belongs
 * @param name name of the static variable
 */
Static *jvm_get_static(JVM *jvm, char *classname, char *name);

/**
 * Returns reference to a newly allocted static variable.
 * The newly allocated static variable is placed in the jvm's static variables stats.
 * It persists until the jvm is deallocated.
 * @param jvm pointer to jvm containing static variable
 */
Static *jvm_push_static(JVM *jvm);

int tableswitch(JVM *jvm);

/**
 * Allocates 2d array and places it in jvm's heap.
 * @param jvm pointer to jvm
 * @param counts array of length 2 containig length of each of the 2 dimensions
 * @param size size of each of the array's elements
 */
void jvm_alloc_array_2d(JVM *jvm, int32_t counts[], u4 size);

/**
 * Allocates 3d array and places it in jvm's heap.
 * @param jvm pointer to jvm
 * @param counts array of length 3 containig length of each of the 3 dimensions
 * @param size size of each of the array's elements
 */
void jvm_alloc_array_3d(JVM *jvm, int32_t counts[], u4 size);

/**
 * Returns a index to the field 'fieldname' in class 'classname' if found in jvm's MethodArea.
 * -1 is returned if the field is not found.
 * @param jvm pointer to jvm
 * @param classname name of the class to which the field belongs
 * @param fieldname name of the field
 */
int32_t jvm_get_field_index(JVM *jvm, char *classname, char *fieldname);

/**
 * Returns a reference to the field 'fieldname' in class 'classname' descriptor string.
 * NULL is returned if the field is not found.
 * @param jvm pointer to jvm
 * @param classname name of the class to which the field belongs
 * @param fieldname name of the field
 */
char *jvm_get_field_descriptor(JVM *jvm, char *classname, char *fieldname);

/**
 * Allocates new object of class 'classname' and places it onto the jvm's heap.
 * The object persists until the jvm is deinitialized.
 * The newly allocated object contains the number of fields corresponding to
 * instances of the class.
 * Each field is a union that can contain one of the primitive values or a reference.
 * @param jvm pointer to jvm
 * @param classname name of the class
 */
void jvm_alloc_object(JVM *jvm, char *classname);