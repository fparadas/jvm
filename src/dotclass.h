// #include "types.h"
#include <string.h>
#include "utils.h"
#include "constant_info.h"
#include "attribute_info.h"
#include "field_info.h"

typedef struct classfile{
    u4 magic;
    u2 minor_version;
    u2 major_version;
    
    u2 cp_count;
    cp_info* cp;

    u2 access_flags;
    u2 this_class;
    u2 super_class;
    
    u2 interfaces_count;
    interface_info* interfaces;

    u2 fields_count;
    field_info* fields;

    u2 methods_count;
    method_info* methods;

    u2 attributes_count;
    attribute_info* attributes;
}classfile;

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
* Returns a pointer to a string in the constant pool
*
* @param cp pointer to the constant pool
* @param index index where the string is located at the constant pool array
*/
char *get_cp_string(cp_info *cp, u2 index);

