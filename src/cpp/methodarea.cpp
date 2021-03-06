#include "../h/methodarea.h"

void init_method_area(MethodArea *ma) {
  ma->n_classes = 0;
}

void deinit_method_area(MethodArea *ma) {
  int i;
  for (i = 0; i < ma->n_classes; i++) {
    deinit_class_file(ma->classes[i]);
    free(ma->classes[i]);
  }
}

void method_area_load_class(MethodArea *ma, char *class_name) {
  /* check if class is already loaded */
  if (method_area_class_lookup(ma, class_name) != -1) return;

  /* read classfile */

  char filename[BUFSIZE];
  strcpy(filename, class_name);
  strcat(filename, ".class");

  FILE *fp = fopen(filename, "rb");
  assert(fp);
  classfile *cf = (classfile *) calloc(sizeof(classfile), 1);
  read_class_file(cf, fp);

  method_area_load_classfile(ma, cf);
}

void method_area_load_classfile(MethodArea *ma, classfile *cf) {
  assert(ma->n_classes < MAX_CLASSES);
  ma->classes[ma->n_classes++] = cf;
}

int method_area_class_lookup(MethodArea *ma, char *class_name) {
  int i;
  for (i = 0; i < ma->n_classes; i++) {
    classfile *cf = ma->classes[i];
    uint32_t index = cf->this_class;
    CONSTANT_Class_info class_info = cf->cp[index].info.class_info;
    char *curr_name = get_cp_string(cf->cp, class_info.name_index);
    if (strcmp(class_name, curr_name) == 0) return i;
  }

  /* class not found */
  return -1;
}

int method_area_method_lookup(MethodArea *ma, int class_index, char *method_name, char *desc) {
  classfile *cf = ma->classes[class_index];
  method_info *methods = cf->methods;

  int i;
  for (i = 0; i < cf->methods_count; i++) {
    method_info *method = &methods[i];
    char *curr_name = get_cp_string(cf->cp, method->name_index);
    char *curr_desc = get_cp_string(cf->cp, method->description_index);

    if (strcmp(curr_name, method_name) == 0
	&& strcmp(curr_desc, desc) == 0) {
      return i;
    }
  }

  return -1;
}