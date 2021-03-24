#include "dotclass.h"
#include <string.h>
#include "getter.h"

void deinit_class_file(classfile *cf);

void deinit_cp(cp_info cp[], uint16_t cpsize);

void deinit_cp_entry(cp_info *ptr);

void deinit_interfaces(CONSTANT_Class_info *interfaces);

void deinit_fields(field_info fields[], uint16_t fields_count, cp_info *cp);

void deinit_field_entry(field_info *ptr, cp_info *cp);

void deinit_methods(method_info methods[], uint16_t method_count, cp_info *cp);

void deinit_method_entry(method_info *ptr, cp_info *cp);

void deinit_attributes(attribute_info attributes[], uint16_t attributes_count, cp_info *cp);

void deinit_attribute_info(attribute_info *ptr, cp_info *cp);

void deinit_code_attribute(Code_attribute *ptr, cp_info *cp);

void deinit_exceptions_attribute(Exceptions_attribute *ptr);

void deinit_linenumbertable_attribute(LineNumberTable_attribute *ptr);

void deinit_innerclasses_attribute(InnerClasses_attribute *ptr);