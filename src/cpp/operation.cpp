#include "../h/operation.h"

operation optable[] = {
    nop,
    aconst_null,
    iconst_m1,
    iconst_0,
    iconst_1,
    iconst_2,
    iconst_3,
    iconst_4,
    iconst_5,
    lconst_0,
    lconst_1,
    fconst_0,
    fconst_1,
    fconst_2,
    nop, //dconst_0,
    nop, //dconst_1,
    bipush,
    sipush,
    ldc,
    ldc_w,
    ldc2_w,
    iload,
    lload,
    fload,
    dload,
    aload,
    iload_0,
    iload_1,
    iload_2,
    iload_3,
    lload_0,
    lload_1,
    lload_2,
    lload_3,
    fload_0,
    fload_1,
    fload_2,
    fload_3,
    dload_0,
    dload_1,
    dload_2,
    dload_3,
    aload_0,
    aload_1,
    aload_2,
    aload_3,
    iaload,
    laload,
    faload,
    daload,
    aaload,
    baload,
    nop, //caload,
    nop, //saload,
    istore,
    lstore,
    fstore,
    dstore,
    astore,
    istore_0,
    istore_1,
    istore_2,
    istore_3,
    lstore_0,
    lstore_1,
    lstore_2,
    lstore_3,
    fstore_0,
    fstore_1,
    fstore_2,
    fstore_3,
    dstore_0,
    dstore_1,
    dstore_2,
    dstore_3,
    astore_0,
    astore_1,
    astore_2,
    astore_3,
    iastore,
    lastore,
    fastore,
    dastore,
    aastore,
    bastore,
    iastore, //castore,
    iastore, //sastore,
    nop, //pop,
    nop, //pop2,
    dup,
    nop, //dup_x1,
    nop, //dup_x2,
    dup2, //dup2,
    nop, //dup2_x1,
    nop, //dup2_x2,
    nop, //swap,
    iadd,
    ladd,
    fadd,
    dadd,
    isub,
    lsub,
    fsub,
    dsub,
    imul,
    lmul,
    fmul,
    dmul,
    idiv,
    ldiv_,
    fdiv,
    ddiv,
    irem,
    nop, //lrem,
    frem,
    drem,
    ineg,
    nop, //lneg,
    fneg,
    dneg,
    ishl,
    nop, //lshl,
    ishr,
    nop, //lshr,
    iushr,
    nop, //lushr,
    iand,
    nop, //land,
    ior,
    nop, //lor,
    nop, //ixor,
    nop, //lxor,
    iinc,
    i2l,
    i2f,
    i2d,
    l2i,
    l2f,
    l2d,
    f2i,
    f2l,
    f2d,
    d2i,
    d2l,
    d2f,
    i2b,
    i2c,
    i2s,
    nop, //nop, //lcmp,
    nop, //nop, //fcmpl,
    nop, //nop, //fcmpg,
    nop, //nop, //dcmpl,
    nop, //nop, //dcmpg,
    ifeq,
    ifne,
    iflt,
    ifge,
    ifgt,
    ifle,
    if_icmpeq,
    if_icmpne,
    if_icmplt,
    if_icmpge,
    if_icmpgt,
    if_icmple,
    nop, //if_acmpeq,
    nop, //if_acmpne,
    goto_func, //goto,
    nop, //jsr,
    nop, //ret,
    nop, //tableswitch,
    nop, //lookupswitch,
    ireturn,
    lreturn,
    freturn,
    dreturn,
    nop, //areturn,
    return_func,
    getstatic,
    putstatic,
    getfield,
    putfield,
    invokevirtual,
    invokespecial,
    invokestatic,
    nop, //invokeinterface,
    nop, //invokedynamic,
    _new,
    newarray,
    anewarray,
    arraylength, //arraylength,
    athrow,
    nop, //checkcast,
    nop, //instanceof,
    nop, //monitorenter,
    nop, //monitorexit,
    nop, //wide,
    multianewarray,
    ifnull,
    ifnonnull,
    nop, //goto_w,
    nop, //jsr_w,
    nop, //breakpoint
};

void nop(Frame *f, u4 a0, u4 a1)
{
  /* do nothing */
  return;
}

void ldc(Frame *f, u4 a0, u4 a1)
{
  u2 index;
  char *str;
  /* push item from runtime constant pool */
  uint8_t tag = f->cp[a0].tag;
  switch (tag)
  {
  case CONSTANT_Integer:
#ifdef DEBUG
    printf("Push %d from cp\n", f->cp[a0].info.integer_info.bytes);
#endif

    push_stack(f, f->cp[a0].info.integer_info.bytes);
    break;
  case CONSTANT_Float:
#ifdef DEBUG
    printf("Push %f from cp\n", f->cp[a0].info.float_info.bytes);
#endif

    push_stack(f, f->cp[a0].info.float_info.bytes);
    break;
  case CONSTANT_String:
    index = f->cp[a0].info.string_info.string_index;
    str = get_cp_string(f->cp, index);

#ifdef DEBUG
    printf("Push \'%s\' from cp\n", str);
#endif

    push_stack_pointer(f, str);
  default:
    break;
  }
}

void istore(Frame *f, u4 a0, u4 a1)
{
  /* store int into local variable a0 */
  int32_t op = pop_stack(f);
  frame_set_local_int(f, a0, op);
}

void istore_0(Frame *f, u4 a0, u4 a1)
{
  /* store int into local variable 0 */
  istore(f, 0, 0);
}

void istore_1(Frame *f, u4 a0, u4 a1)
{
  /* store int into local variable 1 */
  istore(f, 1, 0);
}

void istore_2(Frame *f, u4 a0, u4 a1)
{
  /* store int into local variable 2 */
  istore(f, 2, 0);
}

void istore_3(Frame *f, u4 a0, u4 a1)
{
  /* store int into local variable 3 */
  istore(f, 3, 0);
}

void iload(Frame *f, u4 a0, u4 a1)
{
  /* Load int from local variable a0 */
  int32_t op = frame_get_local_int(f, a0);
  push_stack(f, op);
}

void iload_0(Frame *f, u4 a0, u4 a1)
{
  /* Load int from local variable 0 */
  iload(f, 0, 0);
}

void iload_1(Frame *f, u4 a0, u4 a1)
{
  /* Load int from local variable 1 */
  iload(f, 1, 0);
}

void iload_2(Frame *f, u4 a0, u4 a1)
{
  /* Load int from local variable 2 */
  iload(f, 2, 0);
}

void iload_3(Frame *f, u4 a0, u4 a1)
{
  /* Load int from local variable 3 */
  iload(f, 3, 0);
}

void iadd(Frame *f, u4 a0, u4 a1)
{
  push_stack(f, pop_stack(f) + pop_stack(f));
}

void isub(Frame *f, u4 a0, u4 a1)
{
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  push_stack(f, v2 - v1);
}

void imul(Frame *f, u4 a0, u4 a1)
{
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  push_stack(f, v1 * v2);
}
void idiv(Frame *f, u4 a0, u4 a1)
{
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);

  if (v1 == 0)
  {
    printf("ArithmeticException: Can't be divided by Zero\n");
    exit(1);
  }

  push_stack(f, v2 / v1);
}

void iand(Frame *f, u4 a0, u4 a1)
{
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  push_stack(f, (v2) & (v1));
}

void ior(Frame *f, u4 a0, u4 a1)
{
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  push_stack(f, (v2) | (v1));
}

void ineg(Frame *f, u4 a0, u4 a1)
{
  int32_t d1 = pop_stack(f);
  int32_t result = -d1;
  push_stack(f, result);
}

void irem(Frame *f, u4 a0, u4 a1)
{
  int32_t d1 = pop_stack(f);
  int32_t d2 = pop_stack(f);
  int q = d2 / d1;
  int32_t result = d2 - (d1 * q);
  push_stack(f, result);
}

void ishr(Frame *f, u4 a0, u4 a1)
{
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  int32_t result_ishr = (v2 >> (v1 & 0x1F));
  push_stack(f, result_ishr);
}

void ishl(Frame *f, u4 a0, u4 a1)
{
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  int32_t result_ishl = (v2 << (v1 & 0x1F));
  push_stack(f, result_ishl);
}

void iushr(Frame *f, u4 a0, u4 a1)
{
  int32_t v1 = pop_stack(f);
  int32_t v2 = pop_stack(f);
  int32_t result_ishr = (v2 >> (v1 & 0x1F)) + (2 << ~(v1 & 0x1F));
  push_stack(f, result_ishr);
}

void return_func(Frame *f, u4 a0, u4 a1)
{
#ifdef DEBUG
  printf("return\n");
#endif

  JVM *jvm = (JVM *)f->jvm;
  if (!jvm_in_main(jvm))
  {
    jvm->ret = true;
  }
}

void ireturn(Frame *f, u4 a0, u4 a1)
{
  /* get value to be returned */
  int32_t retval = pop_stack_int(f);
  JVM *jvm = (JVM *)f->jvm;
  jvm->ret = true;
  jvm->retval = *((uint64_t *)(&retval));
#ifdef DEBUG
  printf("ireturn (%d 0x%x)\n", retval, retval);
#endif
}

void dreturn(Frame *f, u4 a0, u4 a1)
{
  /* get value to be returned */
  double retval = pop_stack_double(f);
  JVM *jvm = (JVM *)f->jvm;
  jvm->ret = true;
  jvm->retval = *((uint64_t *)(&retval));
#ifdef DEBUG
  printf("dreturn (%f 0x%x)\n", retval, retval);
#endif
}

void lreturn(Frame *f, u4 a0, u4 a1)
{
  /* get value to be returned */
  int64_t retval = pop_stack_long(f);
  JVM *jvm = (JVM *)f->jvm;
  jvm->ret = true;
  jvm->retval = *((uint64_t *)(&retval));
#ifdef DEBUG
  printf("lreturn (%ld 0x%x)\n", retval, retval);
#endif
}

void freturn(Frame *f, u4 a0, u4 a1)
{
  /* get value to be returned */
  float retval = pop_stack_float(f);
  JVM *jvm = (JVM *)f->jvm;
  jvm->ret = true;
  jvm->retval = *((uint64_t *)(&retval));
#ifdef DEBUG
  printf("freturn (%f 0x%x)\n", retval, retval);
#endif
}

void invokevirtual(Frame *f, u4 a0, u4 a1)
{
  u4 index = (a0 << 8) | a1;
  CONSTANT_Methodref_info methodref_info = f->cp[index].info.methodref_info;
  u2 class_index = methodref_info.class_index;
  u2 name_and_type_index = methodref_info.name_and_type_index;
  char *name = get_name_and_type_string(f->cp, name_and_type_index, 1);
  char *type = get_name_and_type_string(f->cp, name_and_type_index, 0);

#ifdef DEBUG
  printf("invokevirtual: Methodref\t");
  printf("class: %s, name: %s, type: %s\n", get_class_name_string(f->cp, class_index),
         name, type);
#endif

  if (strcmp(name, "println") == 0)
  {
    if (strcmp(type, "(Ljava/lang/String;)V") == 0)
    {
      /* print string */
      char *str = (char *)pop_stack_pointer(f);
#ifdef DEBUG
      printf("println(String): \'%s\'\n", str);
#else
      printf("%s\n", str);
#endif
    }
    else if (strcmp(type, "(I)V") == 0)
    {
      /* print int */
      uint64_t value = pop_stack(f);
      int32_t integer = *((int32_t *)(&value));

#ifdef DEBUG
      printf("println(Int): %d\n", integer);
#else
      printf("%d\n", integer);
#endif
    }
    else if (strcmp(type, "(D)V") == 0)
    {
      /* print double */
      double db = pop_stack_double(f);
#ifdef DEBUG
      printf("println(double): %f\n", db);
#else
      printf("%f\n", db);
#endif
    }
    else if (strcmp(type, "(J)V") == 0)
    {
      /* print long */
      int64_t x = pop_stack_long(f);
#ifdef DEBUG
      printf("println(long): %ld\n", x);
#else
      printf("%ld\n", x);
#endif
    }
    else if (strcmp(type, "(F)V") == 0)
    {
      /* print float */
      float x = pop_stack_float(f);
#ifdef DEBUG
      printf("println(float): %f\n", x);
#else
      printf("%f\n", x);
#endif
    }
    else if (strcmp(type, "(C)V") == 0)
    {
      /* print char */
      u2 ch = pop_stack(f);
#ifdef DEBUG
      printf("println(char): %c\n", ch);
#else
      printf("%c\n", ch);
#endif
    }
    else if (strcmp(type, "(Z)V") == 0)
    {
      /* print bool */
      int32_t boolean = pop_stack_int(f);
#ifdef DEBUG
      printf("println(bool): %d\n", boolean);
#else
      if (boolean)
      {
        printf("true\n");
      }
      else
      {
        printf("false\n");
      }
#endif
    }

    /* pop getstatic dummy value (view getstatic definition) */
    u4 dummy = pop_stack(f);
#ifdef DEBUG
    printf("dummy: 0x%x\n", dummy);
#endif
  }
  else if (strcmp(name, "print") == 0)
  {
    if (strcmp(type, "(Ljava/lang/String;)V") == 0)
    {
      /* print string */
      char *str = (char *)pop_stack_pointer(f);
#ifdef DEBUG
      printf("print(String): \'%s\'\n", str);
#else
      printf("%s", str);
#endif
    }
    else if (strcmp(type, "(I)V") == 0)
    {
      /* print int */
      uint64_t value = pop_stack(f);
      int32_t integer = *((int32_t *)(&value));

#ifdef DEBUG
      printf("print(Int): %d\n", integer);
#else
      printf("%d", integer);
#endif
    }
    else if (strcmp(type, "(D)V") == 0)
    {
      /* print double */
      double db = pop_stack_double(f);
#ifdef DEBUG
      printf("print(double): %f\n", db);
#else
      printf("%f", db);
#endif
    }
    else if (strcmp(type, "(J)V") == 0)
    {
      /* print long */
      int64_t x = pop_stack_long(f);
#ifdef DEBUG
      printf("print(long): %ld\n", x);
#else
      printf("%ld", x);
#endif
    }
    else if (strcmp(type, "(F)V") == 0)
    {
      /* print float */
      float x = pop_stack_float(f);
#ifdef DEBUG
      printf("print(float): %f\n", x);
#else
      printf("%f", x);
#endif
    }
    else if (strcmp(type, "(C)V") == 0)
    {
      /* print char */
      u2 ch = pop_stack(f);
#ifdef DEBUG
      printf("print(char): %c\n", ch);
#else
      printf("%c", ch);
#endif
    }
    else if (strcmp(type, "(Z)V") == 0)
    {
      /* print bool */
      int32_t boolean = pop_stack_int(f);
#ifdef DEBUG
      printf("print(bool): %d\n", boolean);
#else
      if (boolean)
      {
        printf("true");
      }
      else
      {
        printf("false");
      }
#endif
    }
    /* pop getstatic dummy value (view getstatic definition) */
    u4 dummy = pop_stack(f);
#ifdef DEBUG
    printf("dummy: 0x%x\n", dummy);
#endif
  }

  return;
}

void invokestatic(Frame *f, u4 a0, u4 a1)
{
  u4 index = (a0 << 8) | a1;
  CONSTANT_Methodref_info methodref_info = f->cp[index].info.methodref_info;
  u2 class_index = methodref_info.class_index;
  char *class_name = get_class_name_string(f->cp, class_index);
  u2 name_and_type_index = methodref_info.name_and_type_index;
  char *method_name = get_name_and_type_string(f->cp, name_and_type_index, 1);
  char *type = get_name_and_type_string(f->cp, name_and_type_index, 0);
#ifdef DEBUG
  printf("invokestatic: Methodref\t");
  printf("class: %s, name: %s, type: %s\n", class_name,
         method_name, type);
#endif
  JVM *jvm = (JVM *)f->jvm;

  jvm_save_context(jvm);
  jvm_load_class(jvm, class_name);
  jvm_set_current_class(jvm, class_name);
  jvm_set_current_method(jvm, method_name);
  jvm_push_frame(jvm);

  jvm_set_args(jvm, f, type);
}

void invokespecial(Frame *f, u4 a0, u4 a1)
{
  u4 index = (a0 << 8) | a1;
  CONSTANT_Methodref_info methodref_info = f->cp[index].info.methodref_info;
  u2 class_index = methodref_info.class_index;
  char *class_name = get_class_name_string(f->cp, class_index);
  u2 name_and_type_index = methodref_info.name_and_type_index;
  char *method_name = get_name_and_type_string(f->cp, name_and_type_index, 1);
  char *type = get_name_and_type_string(f->cp, name_and_type_index, 0);
#ifdef DEBUG
  printf("invokespecial: Methodref\t");
  printf("class: %s, name: %s, type: %s\n", class_name,
         method_name, type);
#endif

  if (strcmp(class_name, "java/lang/Object") == 0)
  {
    /* ignore base object init */
    JVM *jvm = (JVM *)f->jvm;
    pop_stack_pointer(f);
    jvm->pc += opargs[OP_invokespecial] + 1;
  }
  else if (strcmp(method_name, "<init>") == 0)
  {
    JVM *jvm = (JVM *)f->jvm;
    jvm_save_context(jvm);
    jvm_load_class(jvm, class_name);
    jvm_set_current_class(jvm, class_name);
    jvm_set_current_method(jvm, method_name);
    jvm_push_frame(jvm);
    void *ref = pop_stack_pointer(f);
    frame_set_local_pointer(jvm_peek_frame(jvm), 0, ref);
  }
}

void getstatic(Frame *f, u4 a0, u4 a1)
{
  u4 index = (a0 << 8) | a1;
  JVM *jvm = (JVM *)f->jvm;
  CONSTANT_Fieldref_info fieldref_info = f->cp[index].info.fieldref_info;
  u2 class_index = fieldref_info.class_index;
  u2 name_and_type_index = fieldref_info.name_and_type_index;

  char *classname = get_class_name_string(f->cp, class_index);
  char *name = get_name_and_type_string(f->cp, name_and_type_index, 1);
  char *type = get_name_and_type_string(f->cp, name_and_type_index, 0);

#ifdef DEBUG
  printf("getstatic: classname=%s, name=%s, type=%s\n", classname, name, type);
#endif

  if ((strcmp(classname, "java/lang/System") == 0) && (strcmp(name, "out") == 0))
  {
    /* io operations will be handled by c code */
    /* push a dummy value onto the stack */
    push_stack(f, 0xcc0de);
  }
  else
  {
    Static *st = jvm_get_static(jvm, classname, name);

    assert(st);

    /* TODO: Add remaining types */
    if (strcmp(type, "I") == 0)
    {
      push_stack_int(f, st->value.intfield);
    }
    else if (strcmp(type, "J") == 0)
    {
      push_stack_long(f, st->value.longfield);
    }
    else if (strcmp(type, "F") == 0)
    {
      push_stack_float(f, st->value.floatfield);
    }
    else if (strcmp(type, "D") == 0)
    {
      push_stack_double(f, st->value.doublefield);
    }
    else if (strcmp(type, "Z") == 0)
    {
      push_stack(f, st->value.boolfield);
    }
    else if (strcmp(type, "S") == 0)
    {
      push_stack(f, st->value.shortfield);
    }
    else if (strcmp(type, "C") == 0)
    {
      push_stack(f, st->value.charfield);
    }
    else if (strcmp(type, "B") == 0)
    {
      push_stack(f, st->value.bytefield);
    }
    else
    {
      push_stack_pointer(f, st->value.ptrfield);
    }
  }
  return;
}

void putstatic(Frame *f, u4 a0, u4 a1)
{
  u4 index = (a0 << 8) | a1;
  JVM *jvm = (JVM *)f->jvm;
  CONSTANT_Fieldref_info fieldref_info = f->cp[index].info.fieldref_info;
  u2 class_index = fieldref_info.class_index;
  u2 name_and_type_index = fieldref_info.name_and_type_index;

  char *classname = get_class_name_string(f->cp, class_index);
  char *name = get_name_and_type_string(f->cp, name_and_type_index, 1);
  char *type = get_name_and_type_string(f->cp, name_and_type_index, 0);

#ifdef DEBUG
  printf("putstatic: classname=%s, name=%s, type=%s\n", classname, name, type);
#endif

  Static *st = jvm_get_static(jvm, classname, name);

  if (!st)
  {
    st = jvm_push_static(jvm);
    st->_class = classname;
    st->name = name;
    st->type = type;
  }

  if (strcmp(type, "I") == 0)
  {
    int32_t value = pop_stack_int(f);
    st->value.intfield = value;
  }
  else if (strcmp(type, "J") == 0)
  {
    int64_t value = pop_stack_long(f);
    st->value.longfield = value;
  }
  else if (strcmp(type, "F") == 0)
  {
    float value = pop_stack_float(f);
    st->value.floatfield = value;
  }
  else if (strcmp(type, "D") == 0)
  {
    double value = pop_stack_double(f);
    st->value.doublefield = value;
  }
  else if (strcmp(type, "S") == 0)
  {
    uint64_t pop = pop_stack(f);
    int16_t value = *((int16_t *)(&pop));
    st->value.shortfield = value;
  }
  else if (strcmp(type, "Z") == 0)
  {
    uint64_t pop = pop_stack(f);
    uint8_t value = *((uint8_t *)(&pop));
    st->value.boolfield = value;
  }
  else if (strcmp(type, "C") == 0)
  {
    uint64_t pop = pop_stack(f);
    u2 value = *((u2 *)(&pop));
    st->value.charfield = value;
  }
  else
  {
    void *value = pop_stack_pointer(f);
    st->value.ptrfield = value;
  }
}

void ldc_w(Frame *f, u4 a0, u4 a1)
{
  uint16_t index, cp_index;
  char *str;

  index = (a0 << 8) + a1;
  /* push item from runtime constant pool */
  uint8_t tag = f->cp[index].tag;
  switch (tag)
  {
  case CONSTANT_Integer:
#ifdef DEBUG
    printf("ldc_w: Push %d from cp\n", f->cp[index].info.integer_info.bytes);
#endif
    push_stack(f, f->cp[index].info.integer_info.bytes);
    break;
  case CONSTANT_Float:
#ifdef DEBUG
    printf("ldc_w: Push %f from cp\n", f->cp[index].info.float_info.bytes);
#endif
    push_stack(f, f->cp[index].info.float_info.bytes);
    break;
  case CONSTANT_String:
    cp_index = f->cp[index].info.string_info.string_index;
    str = get_cp_string(f->cp, cp_index);

#ifdef DEBUG
    printf("ldc_w: Push \'%s\' from cp\n", str);
#endif

    push_stack_pointer(f, str);
  default:
    break;
  }
  return;
}

void ldc2_w(Frame *f, u4 a0, u4 a1) {
  uint16_t index, cp_index;
  char *str;
  u4 high_bytes;
  u4 low_bytes;
  uint64_t cat;
  int64_t l;
  double d;

  index = (a0 << 8) + a1;
  /* push item from runtime constant pool */
  uint8_t tag = f->cp[index].tag;
  switch (tag) {
  case CONSTANT_Long:
    low_bytes = f->cp[index].info.long_info.low_bytes;
    high_bytes = f->cp[index].info.long_info.high_bytes;
    cat = (((uint64_t) high_bytes) << 32) | low_bytes;
    l = *((uint64_t *) (&cat));
    push_stack_long(f, l);
#ifdef DEBUG
    printf("ldc2_w: Push %ld from cp\n", l);
#endif
    break;
  case CONSTANT_Double:
    low_bytes = f->cp[index].info.double_info.low_bytes;
    high_bytes = f->cp[index].info.double_info.high_bytes;

    cat = (((uint64_t) high_bytes) << 32) | low_bytes;
    d = *((double *) (&cat));
    push_stack_double(f, d);
#ifdef DEBUG
    printf("ldc2_w: Push %lf from cp\n", d);
#endif
    break;
  default:
    break;
  }
  return;
}

void dstore(Frame *f, u4 a0, u4 a1)
{
  /* store a double into local variable a0 and a0 + 1 */
  double d = pop_stack_double(f);
  frame_set_local_double(f, a0, d);
  /* placeholder (doubles don't need 2 slots in this implementation */
  frame_set_local_double(f, a0 + 1, d);
}

void dstore_0(Frame *f, u4 a0, u4 a1)
{
  /* store a double into local variable 0 and 1 */
  dstore(f, 0, 0);
}

void dstore_1(Frame *f, u4 a0, u4 a1)
{
  /* store a double into local variable 1 and 2 */
  dstore(f, 1, 0);
}

void dstore_2(Frame *f, u4 a0, u4 a1)
{
  /* store a double into local variable 2 and 3 */
  dstore(f, 2, 0);
}

void dstore_3(Frame *f, u4 a0, u4 a1)
{
  /* store a double into local variable 3 and 4 */
  dstore(f, 3, 0);
}

void dload(Frame *f, u4 a0, u4 a1)
{
  /* load double from local variable a0 and a0 + 1*/
  double d = frame_get_local_double(f, a0);
  push_stack_double(f, d);
}

void dload_0(Frame *f, u4 a0, u4 a1)
{
  /* load double from local variable 0 and 1*/
  dload(f, 0, 0);
}

void dload_1(Frame *f, u4 a0, u4 a1)
{
  /* load double from local variable 1 and 2*/
  dload(f, 1, 0);
}

void dload_2(Frame *f, u4 a0, u4 a1)
{
  /* load double from local variable 2 and 3*/
  dload(f, 2, 0);
}

void dload_3(Frame *f, u4 a0, u4 a1)
{
  /* load double from local variable 3 and 4*/
  dload(f, 3, 0);
}

void dadd(Frame *f, u4 a0, u4 a1)
{
  double d1 = pop_stack_double(f);
  double d2 = pop_stack_double(f);
  double result = d1 + d2;
  push_stack_double(f, result);
}

void dsub(Frame *f, u4 a0, u4 a1)
{
  double d1 = pop_stack_double(f);
  double d2 = pop_stack_double(f);
  double result = d2 - d1;
  push_stack_double(f, result);
}

void ddiv(Frame *f, u4 a0, u4 a1)
{
  double d1 = pop_stack_double(f);
  double d2 = pop_stack_double(f);
  double result = d2 / d1;
  push_stack_double(f, result);
}

void dmul(Frame *f, u4 a0, u4 a1)
{
  double d1 = pop_stack_double(f);
  double d2 = pop_stack_double(f);
  double result = d1 * d2;
  push_stack_double(f, result);
}
void dneg(Frame *f, u4 a0, u4 a1)
{
  double d1 = pop_stack_double(f);
  double result = -d1;
  push_stack_double(f, result);
}

void drem(Frame *f, u4 a0, u4 a1)
{
  double d1 = pop_stack_double(f);
  double d2 = pop_stack_double(f);
  int q = d2 / d1;
  double result = d2 - (d1 * q);
  push_stack_double(f, result);
}

void bipush(Frame *f, u4 a0, u4 a1)
{
  /* TODO */
  char byte = a0;
  int32_t sign_ext = byte;
  uint64_t value = *((uint64_t *)(&sign_ext));
  push_stack(f, value);
}

void iconst_0(Frame *f, u4 a0, u4 a1)
{
  push_stack_int(f, 0);
}

void iconst_1(Frame *f, u4 a0, u4 a1)
{
  push_stack_int(f, 1);
}

void iconst_2(Frame *f, u4 a0, u4 a1)
{
  push_stack_int(f, 2);
}

void iconst_3(Frame *f, u4 a0, u4 a1)
{
  push_stack_int(f, 3);
}

void iconst_4(Frame *f, u4 a0, u4 a1)
{
  push_stack_int(f, 4);
}

void iconst_5(Frame *f, u4 a0, u4 a1)
{
  push_stack_int(f, 5);
}

void iconst_m1(Frame *f, u4 a0, u4 a1)
{
  push_stack_int(f, -1);
}

void if_icmpeq(Frame *f, u4 a0, u4 a1)
{
  u4 pop1 = pop_stack(f);
  u4 pop2 = pop_stack(f);

  int32_t value2 = *((int32_t *)(&pop1));
  int32_t value1 = *((int32_t *)(&pop2));

  if (value1 == value2)
  {
    uint16_t offset = (a0 << 8) | a1;
    JVM *jvm = (JVM *)f->jvm;
    uint16_t new_addr = jvm->pc + offset;
#ifdef DEBUG
    printf("if_icmpeq: set pc to 0x%x (%u)\n", new_addr, new_addr);
#endif
    jvm->pc = new_addr;
    jvm->jmp = true;
  }
}

void if_icmpne(Frame *f, u4 a0, u4 a1)
{
  u4 pop1 = pop_stack(f);
  u4 pop2 = pop_stack(f);

  int32_t value2 = *((int32_t *)(&pop1));
  int32_t value1 = *((int32_t *)(&pop2));

  if (value1 != value2)
  {
    uint16_t offset = (a0 << 8) | a1;
    JVM *jvm = (JVM *)f->jvm;
    uint16_t new_addr = jvm->pc + offset;
#ifdef DEBUG
    printf("if_icmpeq: set pc to 0x%x (%u)\n", new_addr, new_addr);
#endif
    jvm->pc = new_addr;
    jvm->jmp = true;
  }
}

void if_icmplt(Frame *f, u4 a0, u4 a1)
{
  u4 pop1 = pop_stack(f);
  u4 pop2 = pop_stack(f);

  int32_t value2 = *((int32_t *)(&pop1));
  int32_t value1 = *((int32_t *)(&pop2));

  if (value1 < value2)
  {
    uint16_t offset = (a0 << 8) | a1;
    JVM *jvm = (JVM *)f->jvm;
    uint16_t new_addr = jvm->pc + offset;
#ifdef DEBUG
    printf("if_icmpeq: set pc to 0x%x (%u)\n", new_addr, new_addr);
#endif
    jvm->pc = new_addr;
    jvm->jmp = true;
  }
}

void if_icmpge(Frame *f, u4 a0, u4 a1)
{
  u4 pop1 = pop_stack(f);
  u4 pop2 = pop_stack(f);

  int32_t value2 = *((int32_t *)(&pop1));
  int32_t value1 = *((int32_t *)(&pop2));

  if (value1 >= value2)
  {
    uint16_t offset = (a0 << 8) | a1;
    JVM *jvm = (JVM *)f->jvm;
    uint16_t new_addr = jvm->pc + offset;
#ifdef DEBUG
    printf("if_icmpge: set pc to 0x%x (%u)\n", new_addr, new_addr);
#endif
    jvm->pc = new_addr;
    jvm->jmp = true;
  }
}

void if_icmpgt(Frame *f, u4 a0, u4 a1)
{
  u4 pop1 = pop_stack(f);
  u4 pop2 = pop_stack(f);

  int32_t value2 = *((int32_t *)(&pop1));
  int32_t value1 = *((int32_t *)(&pop2));

  if (value1 > value2)
  {
    uint16_t offset = (a0 << 8) | a1;
    JVM *jvm = (JVM *)f->jvm;
    uint16_t new_addr = jvm->pc + offset;
#ifdef DEBUG
    printf("if_icmpeq: set pc to 0x%x (%u)\n", new_addr, new_addr);
#endif
    jvm->pc = new_addr;
    jvm->jmp = true;
  }
}

void if_icmple(Frame *f, u4 a0, u4 a1)
{
  u4 pop1 = pop_stack(f);
  u4 pop2 = pop_stack(f);

  int32_t value2 = *((int32_t *)(&pop1));
  int32_t value1 = *((int32_t *)(&pop2));

  if (value1 <= value2)
  {
    uint16_t offset = (a0 << 8) | a1;
    JVM *jvm = (JVM *)f->jvm;
    uint16_t new_addr = jvm->pc + offset;
#ifdef DEBUG
    printf("if_icmpeq: set pc to 0x%x (%u)\n", new_addr, new_addr);
#endif
    jvm->pc = new_addr;
    jvm->jmp = true;
  }
}

void lconst_0(Frame *f, u4 a0, u4 a1)
{
  push_stack_long(f, 0);
}

void lconst_1(Frame *f, u4 a0, u4 a1)
{
  push_stack_long(f, 1);
}

void lstore(Frame *f, u4 a0, u4 a1)
{
  int64_t x = pop_stack_long(f);
  frame_set_local_long(f, a0, x);
  /* placeholder (longs don't need 2 slots in this implementation */
  frame_set_local_long(f, a0 + 1, x);
}

void lstore_0(Frame *f, u4 a0, u4 a1)
{
  lstore(f, 0, 0);
}

void lstore_1(Frame *f, u4 a0, u4 a1)
{
  lstore(f, 1, 0);
}

void lstore_2(Frame *f, u4 a0, u4 a1)
{
  lstore(f, 2, 0);
}

void lstore_3(Frame *f, u4 a0, u4 a1)
{
  lstore(f, 3, 0);
}

void lload(Frame *f, u4 a0, u4 a1)
{
  int64_t x = frame_get_local_long(f, a0);
  push_stack_long(f, x);
}

void lload_0(Frame *f, u4 a0, u4 a1)
{
  lload(f, 0, 0);
}

void lload_1(Frame *f, u4 a0, u4 a1)
{
  lload(f, 1, 0);
}

void lload_2(Frame *f, u4 a0, u4 a1)
{
  lload(f, 2, 0);
}

void lload_3(Frame *f, u4 a0, u4 a1)
{
  lload(f, 3, 0);
}

void ladd(Frame *f, u4 a0, u4 a1)
{
  int64_t long_1 = pop_stack_long(f);
  int64_t long_2 = pop_stack_long(f);
  int64_t result = (int64_t)(long_1 + long_2);
  push_stack_long(f, result);
}

void lsub(Frame *f, u4 a0, u4 a1)
{
  int64_t long_2 = pop_stack_long(f);
  int64_t long_1 = pop_stack_long(f);
  int64_t result = long_1 - long_2;
  push_stack_long(f, result);
}

void lmul(Frame *f, u4 a0, u4 a1)
{
  int64_t long_1 = pop_stack_long(f);
  int64_t long_2 = pop_stack_long(f);
  int64_t result = long_1 * long_2;
  push_stack_long(f, result);
}

void ldiv_(Frame *f, u4 a0, u4 a1)
{
  int64_t long_2 = pop_stack_long(f);
  int64_t long_1 = pop_stack_long(f);
  int64_t result = long_1 / long_2;
  push_stack_long(f, result);
}

void iinc(Frame *f, u4 a0, u4 a1)
{
  int32_t index = a0;
  int32_t c = ((int8_t)a1);
  f->locals[index] += c;
}

void goto_func(Frame *f, u4 a0, u4 a1)
{
  int16_t branchoffset = (a0 << 8) | a1;
#ifdef DEBUG
  printf("goto: %d (0x%x)\n", branchoffset, branchoffset);
#endif

  JVM *jvm = (JVM *) f->jvm;
  jvm->pc += branchoffset;
  jvm->jmp = true;
}

void fconst_0(Frame *f, u4 a0, u4 a1)
{
  push_stack_float(f, 0.0f);
}

void fconst_1(Frame *f, u4 a0, u4 a1)
{
  push_stack_float(f, 1.0f);
}

void fconst_2(Frame *f, u4 a0, u4 a1)
{
  push_stack_float(f, 2.0f);
}

void fstore(Frame *f, u4 a0, u4 a1)
{
  float x = pop_stack_float(f);
  frame_set_local_float(f, a0, x);
}

void fstore_0(Frame *f, u4 a0, u4 a1)
{
  fstore(f, 0, 0);
}

void fstore_1(Frame *f, u4 a0, u4 a1)
{
  fstore(f, 1, 0);
}

void fstore_2(Frame *f, u4 a0, u4 a1)
{
  fstore(f, 2, 0);
}

void fstore_3(Frame *f, u4 a0, u4 a1)
{
  fstore(f, 3, 0);
}

void fload(Frame *f, u4 a0, u4 a1)
{
  float x = frame_get_local_float(f, a0);
  push_stack_float(f, x);
}

void fload_0(Frame *f, u4 a0, u4 a1)
{
  fload(f, 0, 0);
}

void fload_1(Frame *f, u4 a0, u4 a1)
{
  fload(f, 1, 0);
}

void fload_2(Frame *f, u4 a0, u4 a1)
{
  fload(f, 2, 0);
}

void fload_3(Frame *f, u4 a0, u4 a1)
{
  fload(f, 3, 0);
}

void fsub(Frame *f, u4 a0, u4 a1)
{
  float v1 = pop_stack_float(f);
  float v2 = pop_stack_float(f);
  push_stack_float(f, v2 - v1);
}

void fadd(Frame *f, u4 a0, u4 a1)
{
  float v1 = pop_stack_float(f);
  float v2 = pop_stack_float(f);
  push_stack_float(f, v2 + v1);
}

void fdiv(Frame *f, u4 a0, u4 a1)
{
  float v1 = pop_stack_float(f);
  float v2 = pop_stack_float(f);
  float div = v2 / v1;
  push_stack_float(f, div);
}

void fmul(Frame *f, u4 a0, u4 a1)
{
  float v1 = pop_stack_float(f);
  float v2 = pop_stack_float(f);
  float mul = v2 * v1;
  push_stack_float(f, mul);
}

void fneg(Frame *f, u4 a0, u4 a1)
{
  float v1 = pop_stack_float(f);
  float result = -v1;
  push_stack_float(f, result);
}

void frem(Frame *f, u4 a0, u4 a1)
{
  float v1 = pop_stack_float(f);
  float v2 = pop_stack_float(f);
  int q = v2 / v1;
  float result = v2 - (v1 * q);
  push_stack_float(f, result);
}

void ifeq(Frame *f, u4 a0, u4 a1)
{
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  int32_t value = (int32_t)((u4)pop);
  if (value == 0)
  {
    JVM *jvm = (JVM *)f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void ifne(Frame *f, u4 a0, u4 a1)
{
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  int32_t value = (int32_t)((u4)pop);
  if (value != 0)
  {
    JVM *jvm = (JVM *)f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void iflt(Frame *f, u4 a0, u4 a1)
{
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  int32_t value = (int32_t)((u4)pop);
  if (value < 0)
  {
    JVM *jvm = (JVM *)f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void ifge(Frame *f, u4 a0, u4 a1)
{
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  int32_t value = (int32_t)((u4)pop);
  if (value >= 0)
  {
    JVM *jvm = (JVM *)f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void ifgt(Frame *f, u4 a0, u4 a1)
{
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  int32_t value = (int32_t)((u4)pop);
  if (value > 0)
  {
    JVM *jvm = (JVM *)f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void ifle(Frame *f, u4 a0, u4 a1)
{
  int16_t branchoffset = (a0 << 8) | a1;
  void *value = pop_stack_pointer(f);
  if (value <= 0)
  {
    JVM *jvm = (JVM *)f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void ifnonnull(Frame *f, u4 a0, u4 a1)
{
  int16_t branchoffset = (a0 << 8) | a1;
  void *value = pop_stack_pointer(f);
  if (value != NULL)
  {
    JVM *jvm = (JVM *)f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void ifnull(Frame *f, u4 a0, u4 a1)
{
  int16_t branchoffset = (a0 << 8) | a1;
  uint64_t pop = pop_stack(f);
  void *value = (void *)((u4)pop);
  if (value == NULL)
  {
    JVM *jvm = (JVM *)f->jvm;
    jvm->pc += branchoffset;
    jvm->jmp = true;
  }
}

void i2f(Frame *f, u4 a0, u4 a1)
{
  uint64_t pop = pop_stack(f);
  int32_t int_value = (int32_t)((u4)pop);
  float float_value = (float)int_value;
  push_stack_float(f, float_value);
}

void i2d(Frame *f, u4 a0, u4 a1)
{
  int32_t int_value = pop_stack_int(f);
  double double_value = (double)int_value;
  push_stack_double(f, double_value);
}

void i2b(Frame *f, u4 a0, u4 a1)
{
  int32_t intval = pop_stack_int(f);
  int8_t truncated = intval;
  int32_t result = truncated;
  push_stack_int(f, result);
}

void i2c(Frame *f, u4 a0, u4 a1)
{
  int32_t intval = pop_stack_int(f);
  uint16_t truncated = intval;
  int32_t result = truncated;
  push_stack_int(f, result);
}

void i2l(Frame *f, u4 a0, u4 a1)
{
  int32_t intval = pop_stack_int(f);
  int64_t longval = (int64_t)intval;
  push_stack_long(f, longval);
}

void i2s(Frame *f, u4 a0, u4 a1)
{
  int32_t intval = pop_stack_int(f);
  int16_t truncated = intval;
  int32_t result = truncated;
  push_stack_int(f, result);
}

void sipush(Frame *f, u4 a0, u4 a1)
{
  int16_t sh = (a0 << 8) | a1;
  push_stack_int(f, sh);
}

void aconst_null(Frame *f, u4 a0, u4 a1)
{
  push_stack_pointer(f, NULL);
}

void aload(Frame *f, u4 a0, u4 a1)
{
  void *ref = frame_get_local_pointer(f, a0);
  push_stack_pointer(f, ref);
}

void aload_0(Frame *f, u4 a0, u4 a1)
{
  aload(f, 0, 0);
}

void aload_1(Frame *f, u4 a0, u4 a1)
{
  aload(f, 1, 0);
}

void aload_2(Frame *f, u4 a0, u4 a1)
{
  aload(f, 2, 0);
}

void aload_3(Frame *f, u4 a0, u4 a1)
{
  aload(f, 3, 0);
}

void astore(Frame *f, u4 a0, u4 a1)
{
  /* TODO */
  void *ref = pop_stack_pointer(f);
  frame_set_local_pointer(f, a0, ref);
}

void astore_0(Frame *f, u4 a0, u4 a1)
{
  astore(f, 0, 0);
}

void astore_1(Frame *f, u4 a0, u4 a1)
{
  astore(f, 1, 0);
}

void astore_2(Frame *f, u4 a0, u4 a1)
{
  astore(f, 2, 0);
}

void astore_3(Frame *f, u4 a0, u4 a1)
{
  astore(f, 3, 0);
}

void newarray(Frame *f, u4 a0, u4 a1)
{
  /* TODO */
  int32_t count = pop_stack_int(f);
  size_t size = 0;
  switch (a0)
  {
  case T_BOOLEAN:
    size = sizeof(uint8_t);
    break;
  case T_CHAR:
    size = sizeof(uint16_t);
    break;
  case T_FLOAT:
    size = sizeof(float);
    break;
  case T_DOUBLE:
    size = sizeof(double);
    break;
  case T_BYTE:
    size = sizeof(int8_t);
    break;
  case T_SHORT:
    size = sizeof(int16_t);
    break;
  case T_INT:
    size = sizeof(u4);
    break;
  case T_LONG:
    size = sizeof(int64_t);
    break;
  default:
    break;
  }

  void *mem = calloc(size, count);
  JVM *jvm = (JVM *)f->jvm;
  jvm_add_to_heap(jvm, mem);

  push_stack_pointer(f, mem);
}

void aastore(Frame *f, u4 a0, u4 a1)
{
  void *value = pop_stack_pointer(f);
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);

  memcpy(arrayref + index * sizeof(void *), &value, sizeof(void *));
}

void aaload(Frame *f, u4 a0, u4 a1)
{
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);
  void *value = 0;

  memcpy(&value, arrayref + index * sizeof(void *), sizeof(void *));
  push_stack_pointer(f, value);
}

void iastore(Frame *f, u4 a0, u4 a1)
{
  int32_t value = pop_stack_int(f);
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);

  memcpy(arrayref + index * sizeof(int32_t), &value, sizeof(int32_t));
}

void iaload(Frame *f, u4 a0, u4 a1)
{
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);
  int32_t value = 0;

  memcpy(&value, arrayref + index * sizeof(int32_t), sizeof(int32_t));
  push_stack_int(f, value);
}

void fastore(Frame *f, u4 a0, u4 a1)
{
  float value = pop_stack_float(f);
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);

  memcpy(arrayref + index * sizeof(float), &value, sizeof(float));
}

void faload(Frame *f, u4 a0, u4 a1)
{
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);
  float value = 0;

  memcpy(&value, arrayref + index * sizeof(float), sizeof(float));
  push_stack_float(f, value);
}

void lastore(Frame *f, u4 a0, u4 a1)
{
  int64_t value = pop_stack_long(f);
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);

  memcpy(arrayref + index * sizeof(int64_t), &value, sizeof(int64_t));
}

void laload(Frame *f, u4 a0, u4 a1)
{
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);
  int64_t value = 0;

  memcpy(&value, arrayref + index * sizeof(int64_t), sizeof(int64_t));
  push_stack_long(f, value);
}

void dastore(Frame *f, u4 a0, u4 a1)
{
  double value = pop_stack_double(f);
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);

  memcpy(arrayref + index * sizeof(double), &value, sizeof(double));
}

void daload(Frame *f, u4 a0, u4 a1)
{
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);
  double value = 0;

  memcpy(&value, arrayref + index * sizeof(double), sizeof(double));
  push_stack_double(f, value);
}

void bastore(Frame *f, u4 a0, u4 a1)
{
  int8_t value = pop_stack_byte(f);
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);

  memcpy(arrayref + index * sizeof(int8_t), &value, sizeof(int8_t));
}

void baload(Frame *f, u4 a0, u4 a1)
{
  int32_t index = pop_stack_int(f);
  void *arrayref = pop_stack_pointer(f);
  int8_t value = 0;

  memcpy(&value, arrayref + index * sizeof(int8_t), sizeof(int8_t));
  push_stack_byte(f, value);
}

void d2f(Frame *f, u4 a0, u4 a1)
{
  double dval = pop_stack_double(f);
  float fval = dval;
  push_stack_float(f, fval);
}

void d2i(Frame *f, u4 a0, u4 a1)
{
  double dval = pop_stack_double(f);
  int32_t ival = dval;
  push_stack_int(f, ival);
}

void d2l(Frame *f, u4 a0, u4 a1)
{
  double dval = pop_stack_double(f);
  int64_t lval = dval;
  push_stack_long(f, lval);
}

void f2d(Frame *f, u4 a0, u4 a1)
{
  float fval = pop_stack_float(f);
  double dval = fval;
  push_stack_double(f, dval);
}

void f2i(Frame *f, u4 a0, u4 a1)
{
  float fval = pop_stack_float(f);
  int32_t ival = fval;
  push_stack_int(f, ival);
}

void f2l(Frame *f, u4 a0, u4 a1)
{
  float fval = pop_stack_float(f);
  int64_t lval = fval;
  push_stack_long(f, lval);
}

void l2d(Frame *f, u4 a0, u4 a1)
{
  int64_t lval = pop_stack_long(f);
  double dval = lval;
  push_stack_double(f, dval);
}

void l2f(Frame *f, u4 a0, u4 a1)
{
  int64_t lval = pop_stack_long(f);
  float fval = lval;
  push_stack_float(f, fval);
}

void l2i(Frame *f, u4 a0, u4 a1)
{
  int64_t lval = pop_stack_long(f);
  int32_t ival = lval;
  push_stack_int(f, ival);
}

void multianewarray(Frame *f, u4 a0, u4 a1)
{
  u4 index = a0;
  u4 dims = a1;
  int32_t counts[dims];
  u4 i;
  JVM *jvm = (JVM *)f->jvm;
  cp_info *entry = &f->cp[index];

  for (i = 0; i < dims; i++)
  {
    counts[i] = pop_stack_int(f);
  }

  /* assume 2d array */
  u4 size = 0;
  if (entry->tag == CONSTANT_Class)
  {
    CONSTANT_Class_info ci = entry->info.class_info;
    uint16_t name_index = ci.name_index;
    char *name = get_cp_string(f->cp, name_index);
    if (strcmp(name, "[[[I") == 0 || strcmp(name, "[[I") == 0)
    {
      /* int array */
      size = sizeof(int32_t);
    }
    else if (strcmp(name, "[[[J") == 0 || strcmp(name, "[[J") == 0)
    {
      /* long array */
      size = sizeof(int64_t);
    }
    else if (strcmp(name, "[[[F") == 0 || strcmp(name, "[[F") == 0)
    {
      /* float array */
      size = sizeof(float);
    }
    else if (strcmp(name, "[[[D") == 0 || strcmp(name, "[[D") == 0)
    {
      /* double array */
      size = sizeof(double);
    }
  }

  if (dims == 2)
    jvm_alloc_array_2d(jvm, counts, size);
  else if (dims == 3)
    jvm_alloc_array_3d(jvm, counts, size);
}

void anewarray(Frame *f, u4 a0, u4 a1)
{
  int32_t index = (a0 << 8) | a1;
  int32_t count = pop_stack_int(f);
  JArray *j = (JArray *) calloc(sizeof(JArray *), 1);
  /* TODO Resolve cp entry */
  j->ptr = calloc(sizeof(void *), count);
  j->size = count;
  JVM *jvm = (JVM *)f->jvm;
  jvm_add_to_heap(jvm, j->ptr);
  push_stack_pointer(f, j);
}

void arraylength(Frame *f, u4 a0, u4 a1)
{
  uint64_t *ref =  (uint64_t *) pop_stack_pointer(f);
  int count = (int) sizeof(ref)/sizeof(ref[0]);

  push_stack_int(f, count);
}

void dup2(Frame *f, u4 a0, u4 a1)
{
  uint64_t pop = pop_stack(f);
  uint64_t pop1 = pop_stack(f);
  push_stack(f, pop1);
  push_stack(f, pop);
  push_stack(f, pop1);
  push_stack(f, pop);
}

void dup(Frame *f, u4 a0, u4 a1)
{
  uint64_t pop = pop_stack(f);
  push_stack(f, pop);
  push_stack(f, pop);
}

void _new(Frame *f, u4 a0, u4 a1)
{
  u4 index = (a0 << 8) | a1;
  CONSTANT_Class_info *ci = &f->cp[index].info.class_info;
  char *name = get_cp_string(f->cp, ci->name_index);
  jvm_load_class((JVM *)f->jvm, name);
  jvm_alloc_object((JVM *)f->jvm, name);
}

void athrow(Frame *f, u4 a0, u4 a1)
{
  uint64_t objref = pop_stack(f);

  if (!objref)
  {
    printf("NullPointerException\n");
    exit(1);
  }

  else
  {
    printf("UnimplementedException\n");
    exit(1);
  }
}

void getfield(Frame *f, u4 a0, u4 a1)
{
  u4 index = (a0 << 8) | a1;

  Object *objectref = (Object *)pop_stack_pointer(f);
  JVM *jvm = (JVM *)f->jvm;

  CONSTANT_Fieldref_info fieldref_info = f->cp[index].info.fieldref_info;
  u4 class_index = fieldref_info.class_index;
  u4 nameandtype_index = fieldref_info.name_and_type_index;

  CONSTANT_Class_info *class_info = &f->cp[class_index].info.class_info;
  CONSTANT_NameAndType_info *nameandtype_info = &f->cp[nameandtype_index].info.nameandtype_info;

  char *classname = get_cp_string(f->cp, class_info->name_index);
  char *fieldname = get_cp_string(f->cp, nameandtype_info->name_index);
  char *class_desc = get_cp_string(f->cp, nameandtype_info->descriptor_index);

  u4 field_index = jvm_get_field_index(jvm, classname, fieldname);
  char *field_desc = jvm_get_field_descriptor(jvm, classname, fieldname);

  if (strcmp(field_desc, "I") == 0)
  {
    /* field is int */
    int32_t value = objectref->fields[field_index].intfield;
    push_stack_int(f, value);
  }
  else if (strcmp(field_desc, "J") == 0)
  {
    int64_t value = objectref->fields[field_index].longfield;
    push_stack_long(f, value);
  }
  else if (strcmp(field_desc, "D") == 0)
  {
    double value = objectref->fields[field_index].doublefield;
    push_stack_double(f, value);
  }
  else if (strcmp(field_desc, "F") == 0)
  {
    float value = objectref->fields[field_index].floatfield;
    push_stack_float(f, value);
  }
  else if (strcmp(field_desc, "Z") == 0)
  {
    uint8_t value = objectref->fields[field_index].boolfield;
    push_stack(f, value);
  }
  else if (strcmp(field_desc, "S") == 0)
  {
    int16_t value = objectref->fields[field_index].shortfield;
    push_stack(f, *((uint64_t *)(&value)));
  }
  else if (strcmp(field_desc, "B") == 0)
  {
    int8_t value = objectref->fields[field_index].bytefield;
    push_stack(f, *((uint64_t *)(&value)));
  }
  else if (strcmp(field_desc, "C") == 0)
  {
    uint16_t value = objectref->fields[field_index].charfield;
    push_stack(f, value);
  }
  else
  {
    void *value = objectref->fields[field_index].ptrfield;
    push_stack_pointer(f, value);
  }
}

void putfield(Frame *f, u4 a0, u4 a1)
{
  JVM *jvm = (JVM *)f->jvm;
  u4 index = (a0 << 8) | a1;

  CONSTANT_Fieldref_info fieldref_info = f->cp[index].info.fieldref_info;
  u4 class_index = fieldref_info.class_index;
  u4 nameandtype_index = fieldref_info.name_and_type_index;

  CONSTANT_Class_info *class_info = &f->cp[class_index].info.class_info;
  CONSTANT_NameAndType_info *nameandtype_info = &f->cp[nameandtype_index].info.nameandtype_info;

  char *classname = get_cp_string(f->cp, class_info->name_index);
  char *fieldname = get_cp_string(f->cp, nameandtype_info->name_index);
  char *class_desc = get_cp_string(f->cp, nameandtype_info->descriptor_index);

  u4 field_index = jvm_get_field_index(jvm, classname, fieldname);
  char *field_desc = jvm_get_field_descriptor(jvm, classname, fieldname);

  if (strcmp(field_desc, "I") == 0)
  {
    int32_t value = pop_stack_int(f);
    Object *obj = (Object *)pop_stack_pointer(f);
    obj->fields[field_index].intfield = value;
  }
  else if (strcmp(field_desc, "J") == 0)
  {
    int64_t value = pop_stack_long(f);
    Object *obj = (Object *)pop_stack_pointer(f);
    obj->fields[field_index].longfield = value;
  }
  else if (strcmp(field_desc, "D") == 0)
  {
    double value = pop_stack_double(f);
    Object *obj = (Object *)pop_stack_pointer(f);
    obj->fields[field_index].doublefield = value;
  }
  else if (strcmp(field_desc, "F") == 0)
  {
    float value = pop_stack_float(f);
    Object *obj = (Object *)pop_stack_pointer(f);
    obj->fields[field_index].floatfield = value;
  }
  else if (strcmp(field_desc, "Z") == 0)
  {
    uint8_t value = pop_stack(f);
    Object *obj = (Object *)pop_stack_pointer(f);
    obj->fields[field_index].boolfield = value;
  }
  else if (strcmp(field_desc, "S") == 0)
  {
    uint64_t value = pop_stack(f);
    Object *obj = (Object *)pop_stack_pointer(f);
    obj->fields[field_index].shortfield = *((int16_t *)(&value));
  }
  else if (strcmp(field_desc, "C") == 0)
  {
    uint16_t value = pop_stack(f);
    Object *obj = (Object *)pop_stack_pointer(f);
    obj->fields[field_index].shortfield = value;
  }
  else if (strcmp(field_desc, "B") == 0)
  {
    uint64_t value = pop_stack(f);
    Object *obj = (Object *)pop_stack_pointer(f);
    obj->fields[field_index].bytefield = *((int8_t *)(&value));
  }
  else
  {
    void *value = pop_stack_pointer(f);
    Object *obj = (Object *)pop_stack_pointer(f);
    obj->fields[field_index].ptrfield = value;
  }
}