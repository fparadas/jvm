#include "../h/deinit.h"

void deinit_class_file(classfile *cf) {

  deinit_fields(cf->fields, cf->fields_count, cf->cp);
  free(cf->fields);

  deinit_methods(cf->methods, cf->methods_count, cf->cp);
  free(cf->methods);

  deinit_attributes(cf->attributes, cf->attributes_count, cf->cp);
  free(cf->attributes);

  deinit_cp(cf->cp, cf->cp_count);
  free(cf->cp);

  deinit_interfaces(cf->interfaces);

  /* TODO free interfaces */
}

void deinit_cp(cp_info cp[], u2 cp_count) {
  int i;
  for (i = 1; i < cp_count; i++) {
    deinit_cp_entry(&cp[i]);
  }
}

void deinit_cp_entry(cp_info *ptr) {
  assert(ptr);
  if (ptr->tag == CONSTANT_Utf8) {
    CONSTANT_Utf8_info *info = &ptr->info.utf8_info;
    free(info->bytes);
  }
}

void deinit_interfaces(CONSTANT_Class_info *interfaces) {
  if (!interfaces) return;
  free(interfaces);
}

void deinit_fields(field_info fields[], u2 fields_count, cp_info *cp) {
  int i;
  for (i = 0; i < fields_count; i++) {
    deinit_field_entry(&fields[i], cp);
  }
}
void deinit_field_entry(field_info *ptr, cp_info *cp) {
  int i;
  for (i = 0; i < ptr->attribute_count; i++) {
    deinit_attribute_info(&ptr->attributes[i], cp);
  }
  free(ptr->attributes);
}

void deinit_methods(method_info methods[], u2 method_count, cp_info *cp) {
  int i;
  for (i = 0; i < method_count; i++) {
    deinit_method_entry(&methods[i], cp);
  }
}

void deinit_method_entry(method_info *ptr, cp_info *cp) {
  deinit_field_entry((field_info *) ptr, cp);
}

void deinit_attributes(attribute_info attributes[], u2 attributes_count, cp_info *cp) {
  int i;
  for (i = 0; i < attributes_count; i++) {
    deinit_attribute_info(&attributes[i], cp);
  }
}

void deinit_attribute_info(attribute_info *ptr, cp_info *cp) {
  if (!ptr) return;
  assert(cp);

  char *str = get_cp_string(cp, ptr->attribute_name_index);

  if (strcmp("Code", str) == 0) {
    deinit_code_attribute(&ptr->info.code, cp);
  } else if (strcmp("Exceptions", str) == 0) {
    deinit_exceptions_attribute(&ptr->info.exceptions);
  } else if (strcmp("LineNumberTable", str) == 0) {
    deinit_linenumbertable_attribute(&ptr->info.linenumbertable);
  } else if (strcmp("InnerClasses", str) == 0) {
    deinit_innerclasses_attribute(&ptr->info.innerclasses);
  }
}

void deinit_code_attribute(Code_attribute *ptr, cp_info *cp) {
  free(ptr->code);
  free(ptr->exception_table);
  deinit_attributes(ptr->attributes, ptr->attributes_count, cp);
  free(ptr->attributes);
}

void deinit_exceptions_attribute(Exceptions_attribute *ptr) {
  free(ptr->exception_index_table);
}

void deinit_linenumbertable_attribute(LineNumberTable_attribute *ptr) {
  free(ptr->line_number_table);
}

void deinit_innerclasses_attribute(InnerClasses_attribute *ptr) {
  free(ptr->classes);
}