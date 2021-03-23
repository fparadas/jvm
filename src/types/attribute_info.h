#pragma once
#include "../utils.h"

struct attribute_info;

/**
* @brief Constant value attribute.
*
* Represents the value of a constant expression
*/
typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 constantvalue_index;
} ConstantValue_attribute;

/**
* @brief Code attribute.
*
* Contains the JVM instructions and auxiliary information for a method.
*/
typedef struct
{
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code; /* n=code_length */
    u2 exception_table_length;

    struct ExcTable
    {
        u2 start_pc;
        u2 end_pc;
        u2 handler_pc;
        u2 catch_type;
    } * exception_table; /* n=exception_table_length */

    u2 attributes_count;
    attribute_info *attributes; /* n=attributes_count */
} Code_attribute;

/**
* @brief Exceptions Attribute.
*
* Indicates which checked exceptions a method may throw
*/
typedef struct
{
    u2 number_of_exceptions;
    u2 *exception_index_table; /* n=number_of_exceptions */
} Exceptions_attribute;

/**
* @brief LineNumberTable Attribute.
*
* Determines which line part of the code corresponds to a given line number.
*/
typedef struct
{
    u2 line_number_table_length;
    struct LineNTable
    {
        u2 start_pc;
        u2 line_number;
    } * line_number_table;
} LineNumberTable_attribute;

/**
* @brief Sourcefile Attribute.
*
* There may be at most one SourceFile attribute in the attributes table of a
* ClassFile structure.
*/
typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 sourcefile_index;
} SourceFile_attribute;

/**
* @brief Synthetic Attribute.
*
* A class member that does not appear in the source code must be marked using a 
* Synthetic Attribute
*/
typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
} Synthetic_attribute;

/**
* @brief InnerClasses Attribute.
*
* Structure that stores information about an InnerClasses attribute
*/
typedef struct
{
    u2 number_of_classes;
    struct
    {
        u2 inner_class_info_index;
        u2 outer_class_info_index;
        u2 inner_name_index;
        u2 inner_class_access_flags;
    } *classes; /* n=number_of_classes */
} InnerClasses_attribute;


/**
* @brief StackMapTable Attribute.
*
* A StackMapTable attribute is used during the process of verification by 
* type checking
*/
typedef struct
{
    u2 index;
    u4 length;
    u2 n_entries;
} StackMapTable_attribute;

/**
* @brief Attribute info.
*
* Stores information about an attribute
*/
typedef struct attribute_info
{
    u2 attribute_name_index;
    u4 attribute_length;
    union
    {
        ConstantValue_attribute constantvalue;
        Code_attribute code;
        Exceptions_attribute exceptions;
        LineNumberTable_attribute linenumbertable;
        SourceFile_attribute sourcefile;
        Synthetic_attribute synthetic;
        InnerClasses_attribute innerclasses;
        StackMapTable_attribute stackmaptable;
    } info;
}attribute_info;