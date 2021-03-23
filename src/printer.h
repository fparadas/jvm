#include "utils.h"
#include "types/dotclass.h"

/**
 * @brief Print constant pool detail.
 * @param cp_count size of the constant pool
 * @param cp array structure that stores cp_info
 */
void print_cp_info(u2 cp_count, cp_info cp[]);

/**
 * @brief Print constant pool detail.
 * @param tag tag to recognize witch constant type we're printing
 * @param info structure that stores cp_info value
 */
void print_constant_info(u1 tag, CONSTANT_info info);

/**
 * @brief Get data from file and store in a Utf8_info structure.
 * @param info value of the constant we're printing
 */
void print_utf8(CONSTANT_Utf8_info info);

/**
 * @brief Get data from file and store in a Integer_info structure.
 * @param info value of the constant we're printing
 */
void print_integer(CONSTANT_Integer_info info);

/**
 * @brief Get data from file and store in a Float_info structure.
 * @param info value of the constant we're printing
 */
void print_float(CONSTANT_Float_info info);

/**
 * @brief Get data from file and store in a Long_info structure.
 * @param info value of the constant we're printing
 */
void print_long(CONSTANT_Long_info info);

/**
 * @brief Get data from file and store in a Double_info structure.
 * @param info value of the constant we're printing
 */
void print_double(CONSTANT_Double_info info);

/**
 * @brief Get data from file and store in a Class_info structure.
 * @param info value of the constant we're printing
 */
void print_class(CONSTANT_Class_info info);

/**
 * @brief Get data from file and store in a String_info structure.
 * @param info value of the constant we're printing
 */
void print_string(CONSTANT_String_info info);

/**
 * @brief Get data from file and store in a Fieldref_info structure.
 * @param info value of the constant we're printing
 */
void print_fieldref(CONSTANT_Fieldref_info info);

/**
 * @brief Get data from file and store in a Methodref_info structure.
 * @param info value of the constant we're printing
 */
void print_methodref(CONSTANT_Methodref_info info);

/**
 * @brief Get data from file and store in a InterfaceMethodref_info structure.
 * @param info value of the constant we're printing
 */
void print_interfaceMethodref(CONSTANT_InterfaceMethodref_info info);

/**
 * @brief Get data from file and store in a NameAndType_info structure.
 * @param info value of the constant we're printing
 */
void print_nameAndType(CONSTANT_NameAndType_info info);