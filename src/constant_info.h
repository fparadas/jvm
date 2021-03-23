#pragma once
#include "utils.h"
#include <assert.h>

#define CONSTANT_Utf8                 1
#define CONSTANT_Integer              3
#define CONSTANT_Float                4
#define CONSTANT_Long                 5
#define CONSTANT_Double               6
#define CONSTANT_Class                7
#define CONSTANT_String               8
#define CONSTANT_Fieldref             9
#define CONSTANT_Methodref           10
#define CONSTANT_InterfaceMethodref  11
#define CONSTANT_NameAndType         12


/**
 * @brief Info of type Class.
 *
 * Structure that stores specific information about a constant of type Class (id 7)
 */
/* id 7 */
typedef struct {
  u2 name_index;
} CONSTANT_Class_info;

/**
 * @brief Info of type Fieldref.
 *
 * Structure that stores specific information about a constant of type Fieldref (id 9)
 */
/* id 9 */
typedef struct {
  u2 class_index;
  u2 name_and_type_index;
} CONSTANT_Fieldref_info;

/**
 * @brief Info of type Methodref.
 *
 * Structure that stores specific information about a constant of type Methodref (id 10)
 */
/* id 10 */
typedef struct {
  u2 class_index;
  u2 name_and_type_index;
} CONSTANT_Methodref_info;

/**
 * @brief Info of type InterfaceMethodref.
 *
 * Structure that stores specific information about a constant of type InterfaceMethodref (id 11)
 */
/* id 11 */
typedef struct {
  u2 class_index;
  u2 name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

/**
 * @brief Info of type String.
 *
 * Structure that stores specific information about a constant of type String (id 8)
 */
/* id 8 */
typedef struct {
  u2 string_index;
} CONSTANT_String_info;

/**
 * @brief Info of type Integer.
 *
 * Structure that stores specific information about a constant of type Integer (id 3)
 */
/* id 3 */
typedef struct {
  u4 bytes;
} CONSTANT_Integer_info;

/**
 * @brief Info of type Float.
 *
 * Structure that stores specific information about a constant of type Float (id 4)
 */
/* id 4 */
typedef struct {
  u4 bytes;
} CONSTANT_Float_info;

/**
 * @brief Info of type Long.
 *
 * Structure that stores specific information about a constant of type Long (id 5)
 */
/* id 5 */
typedef struct {
  u4 high_bytes;
  u4 low_bytes;
} CONSTANT_Long_info;

/**
 * @brief Info of type Double.
 *
 * Structure that stores specific information about a constant of type Double (id 6)
 */
/* id 6 */
typedef struct {
  u4 high_bytes;
  u4 low_bytes;
} CONSTANT_Double_info;

/**
 * @brief Info of type NameAndType.
 *
 * Structure that stores specific information about a constant of type Class (id 12)
 */
/* id 12 */
typedef struct {
  u2 name_index;
  u2 descriptor_index;
} CONSTANT_NameAndType_info;

/**
 * @brief Info of type Utf8.
 *
 * Structure that stores specific information about a constant of type Utf8 (id 1)
 */
/* id 1 */
typedef struct {
  u2 length;
  u1 *bytes;
} CONSTANT_Utf8_info;

/**
 * @brief Constant.
 *
 * Union to store generically a constant information value.
 */
typedef union {
  CONSTANT_Class_info               class_info;
  CONSTANT_Fieldref_info            fieldref_info;
  CONSTANT_Methodref_info           methodref_info;
  CONSTANT_InterfaceMethodref_info  interfacemethodref_info;
  CONSTANT_String_info              string_info;
  CONSTANT_Integer_info             integer_info;
  CONSTANT_Float_info               float_info;
  CONSTANT_Long_info                long_info;
  CONSTANT_Double_info              double_info;
  CONSTANT_NameAndType_info         nameandtype_info;
  CONSTANT_Utf8_info                utf8_info;
} CONSTANT_info;

/**
 * @brief Info of a constant pool element.
 *
 * Structure that stores the tag and the info of a constant
 */
typedef struct  {
  u1 tag;
  CONSTANT_info info;
} cp_info;


/**
 * Reads the class file's constant pool.
 * @param cp array to where the pool will be stored.
 * @param size size of the constant pool.
 * @param fp file pointer situated at the first byte of the constant pool.
 */
void read_cp_info(cp_info cp[], int size, FILE *fp);

/**
 * Reads the constant pool info.
 * @param tag constant pool info tag to know what are we reading
 * @param ptr pointer to the constant pool info value structure that will receive the value.
 * @param fp file pointer situated at the first byte of the constant pool value.
 */
void read_constant_info(u1 tag, CONSTANT_info *ptr, FILE *fp);


/**
 * Get data from file and store in a Utf8_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_UTF8_info
 * @param ptr non-null pointer to a CONSTANT_Utf8_info structure that will receive the value.
 */
void read_utf8(CONSTANT_Utf8_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Integer_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Integer_info
 * @param ptr non-null pointer to a CONSTANT_Integer_info structure that will receive the value.
 */
void read_integer(CONSTANT_Integer_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Float_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Float_info
 * @param ptr non-null pointer to a CONSTANT_Float_info structure that will receive the value.
 */
void read_float(CONSTANT_Float_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Long_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Long_info
 * @param ptr non-null pointer to a CONSTANT_Long_info structure that will receive the value.
 */
void read_long(CONSTANT_Long_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Double_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Double_info
 * @param ptr non-null pointer to a CONSTANT_Double_info structure that will receive the value.
 */
void read_double(CONSTANT_Double_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Class_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Class_info
 * @param ptr non-null pointer to a CONSTANT_Class_info structure that will receive the value.
 */
void read_class(CONSTANT_Class_info *ptr, FILE *fp);

/**
 * Get data from file and store in a String_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_String_info
 * @param ptr non-null pointer to a CONSTANT_String_info structure that will receive the value.
 */
void read_string(CONSTANT_String_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Fieldref_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Fieldref_info
 * @param ptr non-null pointer to a CONSTANT_Fieldref_info structure that will receive the value.
 */
void read_fieldref(CONSTANT_Fieldref_info *ptr, FILE *fp);

/**
 * Get data from file and store in a Methodref_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Methodref_info
 * @param ptr non-null pointer to a CONSTANT_Methodref_info structure that will receive the value.
 */
void read_methodref(CONSTANT_Methodref_info *ptr, FILE *fp);

/**
 * Get data from file and store in a InterfaceMethodref_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_InterfaceMethodref_info
 * @param ptr non-null pointer to a CONSTANT_InterfaceMethodref_info structure that will receive the value.
 */
void read_interfaceMethodref(CONSTANT_InterfaceMethodref_info *ptr, FILE *fp);

/**
 * Get data from file and store in a NameAndType_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_NameAndType_info
 * @param ptr non-null pointer to a CONSTANT_NameAndType_info structure that will receive the value.
 */
void read_nameAndType(CONSTANT_NameAndType_info *ptr, FILE *fp);