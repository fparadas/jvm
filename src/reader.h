#pragma once
#include "types/dotclass.h"
#include "utils.h"

/**
 * @brief Reads the class file's constant pool.
 * @param cp array to where the pool will be stored.
 * @param cp_count size of the constant pool.
 * @param fp file pointer situated at the first byte of the constant pool.
 */
void read_cp_info(cp_info cp[], int cp_count, FILE *fp);

/**
 * @brief Reads the constant pool info.
 * @param tag constant pool info tag to know what are we reading
 * @param ptr pointer to the constant pool info value structure that will receive the value.
 * @param fp file pointer situated at the first byte of the constant pool value.
 */
void read_constant_info(u1 tag, CONSTANT_info *ptr, FILE *fp);


/**
 * @brief Get data from file and store in a Utf8_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_UTF8_info
 * @param ptr non-null pointer to a CONSTANT_Utf8_info structure that will receive the value.
 */
void read_utf8(CONSTANT_Utf8_info *ptr, FILE *fp);

/**
 * @brief Get data from file and store in a Integer_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Integer_info
 * @param ptr non-null pointer to a CONSTANT_Integer_info structure that will receive the value.
 */
void read_integer(CONSTANT_Integer_info *ptr, FILE *fp);

/**
 * @brief Get data from file and store in a Float_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Float_info
 * @param ptr non-null pointer to a CONSTANT_Float_info structure that will receive the value.
 */
void read_float(CONSTANT_Float_info *ptr, FILE *fp);

/**
 * @brief Get data from file and store in a Long_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Long_info
 * @param ptr non-null pointer to a CONSTANT_Long_info structure that will receive the value.
 */
void read_long(CONSTANT_Long_info *ptr, FILE *fp);

/**
 * @brief Get data from file and store in a Double_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Double_info
 * @param ptr non-null pointer to a CONSTANT_Double_info structure that will receive the value.
 */
void read_double(CONSTANT_Double_info *ptr, FILE *fp);

/**
 * @brief Get data from file and store in a Class_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Class_info
 * @param ptr non-null pointer to a CONSTANT_Class_info structure that will receive the value.
 */
void read_class(CONSTANT_Class_info *ptr, FILE *fp);

/**
 * @brief Get data from file and store in a String_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_String_info
 * @param ptr non-null pointer to a CONSTANT_String_info structure that will receive the value.
 */
void read_string(CONSTANT_String_info *ptr, FILE *fp);

/**
 * @brief Get data from file and store in a Fieldref_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Fieldref_info
 * @param ptr non-null pointer to a CONSTANT_Fieldref_info structure that will receive the value.
 */
void read_fieldref(CONSTANT_Fieldref_info *ptr, FILE *fp);

/**
 * @brief Get data from file and store in a Methodref_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_Methodref_info
 * @param ptr non-null pointer to a CONSTANT_Methodref_info structure that will receive the value.
 */
void read_methodref(CONSTANT_Methodref_info *ptr, FILE *fp);

/**
 * @brief Get data from file and store in a InterfaceMethodref_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_InterfaceMethodref_info
 * @param ptr non-null pointer to a CONSTANT_InterfaceMethodref_info structure that will receive the value.
 */
void read_interfaceMethodref(CONSTANT_InterfaceMethodref_info *ptr, FILE *fp);

/**
 * @brief Get data from file and store in a NameAndType_info structure.
 * @param fp non-null pointer to .class file situated at the CONSTANT_NameAndType_info
 * @param ptr non-null pointer to a CONSTANT_NameAndType_info structure that will receive the value.
 */
void read_nameAndType(CONSTANT_NameAndType_info *ptr, FILE *fp);
