#include "../h/jvm.h"


void init_jvm(JVM *jvm) {
  jvm->pc = 0;
  jvm->frame_index = 0;
  jvm->method_area = (MethodArea *) calloc(sizeof(MethodArea), 1);
  init_method_area(jvm->method_area);
  jvm->current_class_index = -1;
  jvm->current_method_index = -1;
  jvm->jmp = false;
  jvm->ret = false;
  jvm->heap_index = -1;
  jvm->static_index = -1;
}

void deinit_jvm(JVM *jvm) {
  deinit_method_area(jvm->method_area);
  free(jvm->method_area);
  while (jvm_peek_frame(jvm)) {
    jvm_pop_frame(jvm);
  }

  while (jvm->heap_index >= 0) {
    free(jvm->heap[(jvm->heap_index)--]);
  }

  while (jvm->static_index >= 0) {
    free(jvm->statics[(jvm->static_index)--]);
  }
}

void jvm_load_classfile(JVM *jvm, classfile *cf) {
  method_area_load_classfile(jvm->method_area, cf);
}

void jvm_load_class(JVM *jvm, char *class_name) {
  method_area_load_class(jvm->method_area, class_name);
}

void jvm_set_current_class(JVM *jvm, char *class_name) {
  int index = method_area_class_lookup(jvm->method_area, class_name);
  jvm->current_class_index = index;
}

void jvm_set_current_method(JVM *jvm, char *method_name) {
  classfile *_class = jvm_get_current_class(jvm);
  int i;
  for (i = 0; i < _class->methods_count; i++) {
    method_info *method = &_class->methods[i];
    char *curr_method_name = get_cp_string(_class->cp, method->name_index);
    if (strcmp(curr_method_name, method_name) == 0) {
      jvm->current_method_index = i;
      return;
    }
  }
}

void jvm_exec_clinit(JVM *jvm) {
  classfile *_class = jvm_get_current_class(jvm);
  int flag = 0;
  int i;
  for (i = 0; i < _class->methods_count; i++) {
    method_info *method = &_class->methods[i];
    char *curr_method_name = get_cp_string(_class->cp, method->name_index);
    if (strcmp(curr_method_name, "<clinit>") == 0) {
      flag = 1;
      jvm->current_method_index = i;
    }
  }

  if (flag) {
    jvm_push_frame(jvm);
    jvm_run(jvm);
  }
}


void jvm_load_method(JVM *jvm, u4 class_index, u4 method_index) {
  jvm->current_class_index = class_index;
  jvm->current_method_index = method_index;
}

classfile *jvm_get_current_class(JVM *jvm) {
  classfile *_class = jvm->method_area->classes[jvm->current_class_index];
  return _class;
}

char *jvm_get_current_class_name(JVM *jvm) {
  Frame *f = jvm_peek_frame(jvm);
  classfile *_class = jvm_get_current_class(jvm);
  CONSTANT_Class_info class_info = f->cp[_class->this_class].info.class_info;
  return get_cp_string(f->cp, class_info.name_index);
}

method_info *jvm_get_current_method(JVM *jvm) {
  classfile *_class = jvm_get_current_class(jvm);
  method_info *method = &_class->methods[jvm->current_method_index];
  return method;
}

char *jvm_get_current_method_name(JVM *jvm) {
  Frame *f = jvm_peek_frame(jvm);
  method_info *method = jvm_get_current_method(jvm);
  char *str = get_cp_string(f->cp, method->name_index);
  return str;
}

void jvm_push_frame(JVM *jvm) {
  classfile *_class = jvm_get_current_class(jvm);
  method_info *method = jvm_get_current_method(jvm);
  Code_attribute *code = &method->attributes[0].info.code;
  Frame *f = (Frame *) calloc(sizeof(Frame), 1);
  init_frame(f, jvm, code->max_locals, code->max_stack, _class->cp,
	     jvm->current_class_index, jvm->current_method_index);
  jvm->frames[jvm->frame_index++] = f;
  jvm->pc = 0;
}

void jvm_pop_frame(JVM *jvm) {
  Frame *f = jvm->frames[--jvm->frame_index];
  deinit_frame(f);
  free(f);
}

Frame *jvm_peek_frame(JVM *jvm) {
  if (jvm->frame_index == 0) return NULL;
  return jvm->frames[jvm->frame_index-1];
}

int jvm_cycle(JVM *jvm) {
  int flag = 1;                  /* will be set to 0 if returns from main in this cycle */
  Frame *f = jvm_peek_frame(jvm);
  method_info *method = jvm_get_current_method(jvm);
  Code_attribute *code = &method->attributes[0].info.code;

  u4 opcode = code->code[jvm->pc];
  jvm->jmp = false;

  if (opcode == OP_tableswitch) {
    return tableswitch(jvm);
  }

  u4 a[3];
  int i;
  for (i = 0; i < opargs[opcode]; i++) {
    a[i] = code->code[jvm->pc+i+1];
  #ifdef DEBUG
      printf("load a%d: %d\n", i, a[i]);
  #endif
  }
  if (opcode == OP_multianewarray) {
    u4 index = (a[0] << 8) | a[1];
    multianewarray(f, index, a[2]);
  } else {
  #ifdef DEBUG
        std::cout << "operation " << strings_opcodes[opcode];
      printf(": %d, %d\n", strings_opcodes[opcode], a[0], a[1]);
  #endif
    optable[opcode](f, a[0], a[1]);
  }
  if (opcode == OP_return && jvm_in_main(jvm)) {
      #ifdef DEBUG
      printf("frame->i: %d\n", f->i);
      if (f->i > 0) printf("Final value in stack: %d (0x%x)\n", peek_stack(f), peek_stack(f));
      #endif
    flag = 0;
  } else if (opcode == OP_return && jvm_in_clinit(jvm)) {
    #ifdef DEBUG
    printf("Return from '%s' <clinit>\n", jvm_get_current_class(jvm));
    #endif
    flag = 0;
  }

  if (jvm->ret && !jvm_in_main(jvm) && !jvm_in_clinit(jvm)) {
    /* free called method's frame */
    jvm_pop_frame(jvm);
    jvm_restore_context(jvm);
    Frame *f = jvm_peek_frame(jvm);
    /* Push return value to callee's operand stack */
    if (opcode == OP_dreturn) {
      double d = *((double *) (&jvm->retval));
      push_stack_double(f, d);
    } else if (opcode == OP_lreturn) {
      int64_t l = *((int64_t *) (&jvm->retval));
      push_stack_long(f, l);
    } else if (opcode != OP_return) {
      push_stack(f, jvm->retval);
    }

    /* reset return flag */
    jvm->ret = false;
  }

  if (!jvm->jmp && opcode != OP_invokestatic
		&& opcode != OP_invokespecial) {
    jvm->pc += opargs[opcode] + 1;
  }
  return flag;
}

void jvm_run(JVM *jvm) {
  while (jvm_cycle(jvm));
}

void jvm_run_method(JVM *jvm) {
  classfile *_class = jvm->method_area->classes[jvm->current_class_index];
  method_info *method = &_class->methods[jvm->current_method_index];
  Code_attribute *code = &method->attributes[0].info.code;
  Frame *f = (Frame *) calloc(sizeof(Frame), 1);
  init_frame(f, jvm, code->max_locals, code->max_stack, _class->cp, jvm->current_class_index,
	     jvm->current_method_index);

#ifdef DEBUG
  printf("Current class: %s\n", get_class_name(jvm->method_area->classes[0]));
  printf("Current method: %s\n", get_cp_string(_class->cp, method->name_index));
  printf("Current method descriptor: %s\n", get_cp_string(_class->cp, method->description_index));
  printf("Max locals:%d\nMax stack: %d\n", code->max_locals, code->max_stack);
#endif

  while (1) {
    u4 opcode = code->code[jvm->pc];

#ifdef DEBUG
    printf("%d: 0x%x (%d)\n", jvm->pc, opcode, opargs[opcode]);
#endif

    uint8_t a[2];
    int i;
    for (i = 0; i < opargs[opcode]; i++) {
      a[i] = code->code[jvm->pc+i+1];

#ifdef DEBUG
      printf("load a%d: %d\n", i, a[i]);
#endif
    }
    optable[opcode](f, a[0], a[1]);
    if (opcode == OP_return) {
#ifdef DEBUG
      printf("frame->i: %d\n", f->i);
      if (f->i > 0) printf("Final value in stack: %d (0x%x)\n", peek_stack(f), peek_stack(f));
#endif
      break;
    }
    jvm->pc += opargs[opcode] + 1;
  }

  deinit_frame(f);
  free(f);
}

int jvm_in_main(JVM *jvm) {
  char *str = jvm_get_current_method_name(jvm);
  return strcmp(str, "main") == 0;
}

bool jvm_in_clinit(JVM *jvm) {
  char *str = jvm_get_current_method_name(jvm);
  return strcmp(str, "<clinit>") == 0;
}

void jvm_save_context(JVM *jvm) {
  Frame *f = jvm_peek_frame(jvm);
  f->pc = jvm->pc + 2;
  f->class_index = jvm->current_class_index;
  f->method_index = jvm->current_method_index;
}

void jvm_restore_context(JVM *jvm) {
  Frame *f = jvm_peek_frame(jvm);
  jvm->pc = f->pc;
  jvm->current_class_index = f->class_index;
  jvm->current_method_index = f->method_index;
}

void jvm_add_to_heap(JVM *jvm, void *ptr) {
  jvm->heap[++(jvm->heap_index)] = ptr;
}

void jvm_parse_types(char *type, char parsed[], int *count) {
  char buf[BUFSIZE];
  int i = 1;
  int j = 0;
  int k = 0;
  while (type[i] != ')') {
    switch (type[i]) {
    case 'I':
      parsed[j] = 'I';
      break;
    case 'J':
      parsed[j] = 'J';
      break;
    case 'F':
      parsed[j] = 'F';
      break;
    case 'D':
      parsed[j] = 'D';
      break;
    default:
      while (type[i] != ';') buf[k++] = type[i++];
      buf[k] = 0;
      if (strcmp(buf, "Ljava/lang/String;")) {
	parsed[j] = 'A';
      } else {
	#ifdef DEBUG
	printf("jvm_set_args: Unknown arg type %s\n", buf);
	#endif
      }
      break;
    }
    j++;
    i++;
  }
  *count = j;
}

void jvm_set_args(JVM *jvm, Frame *caller, char *type) {
  Frame *f1 = jvm_peek_frame(jvm);

  int32_t intarg;
  int64_t longarg;
  float floatarg;
  double doublearg;
  void *ptrarg;

  char parsed[BUFSIZE] = {0};
  int count = 0;
  jvm_parse_types(type, parsed, &count);
  #ifdef DEBUG
  printf("jvm_set_args: parsed types: %s\n", parsed);
  #endif


  int i, j;

  /* compute last arg's position in locals array (j) */
  for (i = j = 0; i < count; i++) {
    switch (parsed[i]) {
    case 'D':
    case 'J':
      j++;
    default:
      j++;
      break;
    }
  }
  j-=1;

  /* loop backwards over args to pop in correct order */
  for (i = count-1; i >= 0; i--, j--) {
    switch (parsed[i]) {
    case 'I':
      intarg = pop_stack_int(caller);
      frame_set_local_int(f1, j, intarg);
      break;
    case 'J':
      longarg = pop_stack_long(caller);
      frame_set_local_long(f1, --j, longarg);
      break;
    case 'F':
      floatarg = pop_stack_float(caller);
      frame_set_local_float(f1, j, floatarg);
      break;
    case 'D':
      doublearg = pop_stack_double(caller);
      printf("Placing arg %f in local %d\n", doublearg, j-1);
      frame_set_local_double(f1, --j, doublearg);
      break;
    case 'A':
	ptrarg = pop_stack_pointer(caller);
	frame_set_local_pointer(f1, j, ptrarg);
	break;
    default:
      #ifdef DEBUG
      printf("jvm_set_args: Unknown type %c\n", parsed[i]);
      #endif
      break;
    }
  }
}

Static *jvm_get_static(JVM *jvm, char *classname, char *name) {
  int i;
  for (i = 0; i <= jvm->static_index; i++) {
    if (strcmp(classname, jvm->statics[i]->_class) == 0
	&& strcmp(name, jvm->statics[i]->name) == 0) {
      return jvm->statics[i];
    }
  }
  return NULL;
}

Static *jvm_push_static(JVM *jvm) {
  Static *s = (Static *) calloc(sizeof(Static), 1);
  assert(s);
  jvm->statics[++(jvm->static_index)] = s;
  return s;
}

int tableswitch(JVM *jvm) {
  Frame *f = jvm_peek_frame(jvm);
  method_info *method = jvm_get_current_method(jvm);
  Code_attribute *code = &method->attributes[0].info.code;

  u4 opcode = code->code[jvm->pc];
    u4 start = jvm->pc-1;
    /* skip padding */
    while ((jvm->pc - start) % 4 != 0) jvm->pc++;
    u4 default_bytes = 0;
    int i;
    for (i = 0; i < 4; i++) {
      default_bytes = (default_bytes << 4) | code->code[jvm->pc];
      jvm->pc++;
    }

    u4 low_bytes = 0;
    for (i = 0; i < 4; i++) {
      low_bytes = (low_bytes << 4) | code->code[jvm->pc];
      jvm->pc++;
    }

    u4 high_bytes = 0;
    for (i = 0; i < 4; i++) {
      high_bytes = (high_bytes << 4) | code->code[jvm->pc];
      jvm->pc++;
    }

    int32_t def = *((int32_t *) (&default_bytes));
    int32_t lo = *((int32_t *) (&low_bytes));
    int32_t hi = *((int32_t *) (&high_bytes));

    #ifdef DEBUG
    printf("tableswitch: def=%d(0x%x), lo=%d(0x%x), hi=%d(0x%x)\n",
	   def, def,
	   lo, lo,
	   hi, hi);
    #endif

    int32_t offsets[hi-lo+1];
    for (i = 0; i < hi-lo+1; i++) {
      u4 bytes = 0;
      int j;
      for (j = 0; j < 4; j++) {
	bytes = (bytes << 4) | code->code[jvm->pc];
	jvm->pc++;
      }
      offsets[i] = *((int32_t *) (&bytes));
      #ifdef DEBUG
      printf("\t%d (0x%x)\n", offsets[i], offsets[i]);
      #endif
    }

    int32_t value = pop_stack_int(f);
    if (value < lo || value > hi) {
      jvm->pc = start + def + 1;
    } else {
      jvm->pc = start + offsets[value - lo] + 1;
    }
    #ifdef DEBUG
    printf("\tpc=%d (0x%x)\n", jvm->pc, jvm->pc);
    #endif
    return 1;
}

void jvm_alloc_array_2d(JVM *jvm, int32_t counts[], u4 size) {
  Frame *f = jvm_peek_frame(jvm);
  int32_t **ptr = (int32_t **) calloc(sizeof(void *), counts[0]);
  int32_t i;
  for (i = 0; i < counts[0]; i++) {
    ptr[i] = (int32_t *) calloc(size, counts[1]);
    jvm_add_to_heap(jvm, ptr[i]);
  }
  push_stack_pointer(f, ptr);
  jvm_add_to_heap(jvm, ptr);
}

void jvm_alloc_array_3d(JVM *jvm, int32_t counts[], u4 size) {
  Frame *f = jvm_peek_frame(jvm);
  int32_t ***ptr = (int32_t ***) calloc(sizeof(void *), counts[0]);
  int32_t i, j;
  for (i = 0; i < counts[0]; i++) {
    ptr[i] = (int32_t **)calloc(sizeof(void *), counts[1]);
    for (j = 0; j < counts[1]; j++) {
      ptr[i][j] = (int32_t *) calloc(size, counts[2]);
      jvm_add_to_heap(jvm, ptr[i][j]);
    }
    jvm_add_to_heap(jvm, ptr[i]);
  }
  push_stack_pointer(f, ptr);
  jvm_add_to_heap(jvm, ptr);
}

int32_t jvm_get_field_index(JVM *jvm, char *classname, char *fieldname) {
  int32_t class_index = method_area_class_lookup(jvm->method_area, classname);
  classfile *cf = jvm->method_area->classes[class_index];
  field_info *fields = cf->fields;
  int i;
  for (i = 0; i < cf->fields_count; i++) {
    char *curr_field = get_cp_string(cf->cp, fields[i].name_index);
    char *desc = get_cp_string(cf->cp, fields[i].description_index);
    if (strcmp(curr_field, fieldname) == 0) {
      /* found desired field */
      return i;
    }
  }
  return -1;
}

char *jvm_get_field_descriptor(JVM *jvm, char *classname, char *fieldname) {
  int32_t class_index = method_area_class_lookup(jvm->method_area, classname);
  classfile *cf = jvm->method_area->classes[class_index];
  field_info *fields = cf->fields;
  int i;
  for (i = 0; i < cf->fields_count; i++) {
    char *curr_field = get_cp_string(cf->cp, fields[i].name_index);
    char *desc = get_cp_string(cf->cp, fields[i].description_index);
    if (strcmp(curr_field, fieldname) == 0) {
      /* found desired field */
      return desc;
    }
  }
  return NULL;
}

void jvm_alloc_object(JVM *jvm, char *classname) {
  classfile *cf = jvm->method_area->classes[method_area_class_lookup(jvm->method_area, classname)];
  field_info *fields = cf->fields;

  Object *obj = (Object *) calloc(sizeof(Object), 1);
  obj->size = cf->fields_count;
  obj->fields = (ObjectField *) calloc(sizeof(ObjectField), obj->size);
  jvm_add_to_heap(jvm, obj);
  jvm_add_to_heap(jvm, obj->fields);
  push_stack_pointer(jvm_peek_frame(jvm), obj);
}