#pragma once
#include "constant_info.h"
#include "field_info.h"
#include "method_info.h"

typedef CONSTANT_Class_info interface_info;


/**
 * @brief Represents the Classfile format.
 *
 * Structure that stores the classfile
 */
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