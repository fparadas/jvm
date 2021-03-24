#pragma once
#include "dotclass.h"
#include "utils.h"
#include "access.h"
#include "getter.h"
#include <string.h>
#include <cstdlib>

/**
 * @brief Reads the class file's content
 * @param file pointer to the structure where the content will be stored
 * @param fp pointer to the .class file.
 */
int read_class_file(classfile *file, FILE *fp);

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

/**
* Reads attribute_info structure.
*
* @param fp pointer to the .class file
* @param att_ptr pointer to the attribute info Structure
* @param cp pointer to the constant info structure
*/
void read_attribute_info(FILE *fp, attribute_info *att_ptr, cp_info *cp);

/**
* Reads attributes.
*
* @param fp pointer to the .class file
* @param attributes array of attributes
* @param attributes_count size of the array attributes
* @param cp pointer to the constant info structure
*/
void read_attributes(FILE *fp, attribute_info attributes[], u2 attributes_count, cp_info *cp);

/**
* Reads single field entry.
*
* @param fp pointer to the .class file
* @param field pointer to the field_info structure
* @param cp pointer to the constant info structure
*/
void read_single_field(FILE *fp, field_info *field, cp_info *cp);

/**
* Reads fields table.
*
* @param fp pointer to the .class file
* @param fields array of fields
* @param fields_count size of the fields array
* @param cp pointer to the constant info structure
*/
void read_fields(FILE *fp, field_info fields[], u2 fields_count, cp_info *cp);

/**
* Reads Code attribute table.
*
* @param code_ptr pointer to the Code attribute structure
* @param fp pointer the to .class file
* @param cp pointer to the constant info structure
*/
void read_code_attribute(Code_attribute* code_ptr, FILE* fp, cp_info* cp);

/**
* Reads Constant value attribute table.
*
* @param constValue_ptr pointer to the constant value attribute structure
* @param fp pointer the to .class file
*/
void read_constantvalue_attribute(ConstantValue_attribute *constValue_ptr, FILE *fp);

/**
* Reads Exceptions attribute table.
*
* @param excp_ptr pointer to the exceptions attribute structure
* @param fp pointer the to .class file
*/
void read_exceptions_attribute(Exceptions_attribute *excp_ptr, FILE *fp);

/**
* Reads Line number table.
*
* @param lineNum_ptr pointer to the line number table
* @param fp pointer the to .class file
*/
void read_linenumbertable_attribute(LineNumberTable_attribute *lineNum_ptr, FILE *fp);

/**
* Reads source file table.
*
* @param sourceFile_ptr pointer to the source file attribute table
* @param fp pointer the to .class file
*/
void read_sourcefile_attribute(SourceFile_attribute *sourceFile_ptr, FILE *fp);

/**
* Reads inner classes table.
*
* @param innerClass_ptr pointer to the inner classes table
* @param fp pointer the to .class file
*/
void read_innerclasses_attribute(InnerClasses_attribute *innerClass_ptr, FILE *fp);

/**
* Reads synthetic attribute table.
*
* @param synthetic_ptr pointer to the synthetic attribute table
* @param fp pointer the to .class file
*/
void read_synthetic_attribute(attribute_info *synthetic_ptr, FILE *fp);

/**
* Reads stack map table.
*
* @param smt_ptr pointer to the stack map table
* @param fp pointer the to .class file
*/
void read_stackmaptable_attribute(StackMapTable_attribute *smt_ptr, FILE *fp);

/**
* Reads interfaces
*
* @param fp pointer the to .class file
* @param interfaces array of interfaces
* @param interfaces_count number of interfaces
*/
void read_interfaces(FILE *fp, CONSTANT_Class_info interfaces[], u2 interfaces_count);

/**
* Reads interfaces
*
* @param fp pointer the to .class file
* @param methods array of methods
* @param methods_count number of methods
* @param cp pointer to the constant info structure
*/
void read_methods(FILE *fp, method_info methods[], u2 methods_count, cp_info *cp);

/**
* Reads interfaces
*
* @param fp pointer the to .class file
* @param method pointer to a method_info structure
* @param cp pointer to the constant info structure
*/
void read_method_entry(FILE *fp, method_info *method, cp_info *cp);






