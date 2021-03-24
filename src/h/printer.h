#pragma once
#include "attribute_info.h"
#include "utils.h"
#include "dotclass.h"
#include "access.h"
#include <stdio.h>
#include <stdlib.h>
#include "getter.h"
#include <string.h>
#include <iostream>
#include "opcodes.h"
#include <inttypes.h>
/**
 * @brief Prints classfile summary.
 * @param cf classfile
 */
void print_summary(classfile* cf);

/**
 * @brief Prints constant pool detail.
 * @param cf classfile
 */
void print_cp_info(classfile *cf);

/**
 * @brief Prints a constant pool element detail.
 * @param cp cp_info array
 * @param index index on cp_info array
 */
void print_cp_element(cp_info *cp, u2 index);

/**
 * @brief Prints interfaces detail.
 * @param cf classfile
 */
void print_interfaces_info(classfile *cf);


/**
 * @brief Prints a attribute detail.
 * @param ptr pointer to attribute info table
 * @param cp pointer to constant pool
 */
void print_attribute_info(attribute_info *ptr, cp_info *cp);

void print_attributes(attribute_info attr[], u2 attr_count, cp_info *cp);

/**
 * @brief Prints fields detail.
 * @param cf classfile
 */
void print_fields_info(classfile *cf);

/**
 * @brief Prints methods detail.
 * @param cf classfile
 */
void print_methods_info(classfile *cf);

void print_code_attribute(Code_attribute *attr, cp_info *cp);

void print_constantvalue_attribute(ConstantValue_attribute *attr);

void print_exception_attribute(Exceptions_attribute *ptr, cp_info *cp, ExcTable* excT);

void print_linenumber_attribute(LineNumberTable_attribute *ptr);

void print_sourcefile_attribute(SourceFile_attribute *attr);

void print_innerclasses_attribute(InnerClasses_attribute *ptr,cp_info *cp);

void print_stackmaptable_attribute(StackMapTable_attribute *attr);