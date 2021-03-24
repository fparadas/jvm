#pragma once
#include "utils.h"
#include "dotclass.h"
#include <cstdio>
#include <typeinfo>
#include <string.h>
#include <string>

/**
 * @brief Return pointer to string in constant pool table.
 * Entry in constant pool must have tag CONSTANT_Utf8.
 * Indices start at 1.
 * @param cp constant pool array
 * @param index index in the cp
 */
char *get_cp_string(cp_info *cp, u2 index);

/**
 * @brief Return string containing this class's name
 * @param cf classfile
 */
char *get_class_name(classfile *cf);

/**
 * @brief Return string containing this class's name
 * @param cf classfile
 */
char *get_super_name(classfile *cf);

/**
 * @brief Return pointer to string in constant pool table.
 * Entry in constant pool must have tag CONSTANT_Class.
 * Indices start at 1.
 * @param cp constant pool array
 * @param class_index index in the cp
 */
char *get_class_name_string(cp_info *cp, u2 class_index);

/**
 * @brief Return pointer to string in constant pool table, choice betweem descriptor(0) and name(1).
 * Entry in constant pool must have tag CONSTANT_NameAndType.
 * Indices start at 1.
 * @param cp constant pool array
 * @param class_index index in the cp
 * @param flag choses between descriptor or name if (flag) name else descriptor
 */
char *get_name_and_type_string(cp_info *cp, u2 index, u1 flag);

/**
 * @brief Return string containing source file name
 * @param cf classfile
 */
char *get_source_file(classfile *cf);