#pragma once
#include "constant_info.h"

typedef union {
  CONSTANT_Class_info               class_info;
  CONSTANT_Fieldref_info            fieldref_info;
  CONSTANT_Methodref_info           methodref_info;
  CONSTANT_InterfaceMethodref_info  interfacemethodref_info;
  CONSTANT_String_info              string_info;
  CONSTANT_Integer_info             integer_info;
  CONSTANT_Float_info               float_info;
  CONSTANT_Long_info                long_info;
  CONSTANT_Double_info              double_info;
  CONSTANT_NameAndType_info         nameandtype_info;
  CONSTANT_Utf8_info                utf8_info;
} CONSTANT_info;

typedef struct cp_info {}; //#TODO
typedef struct interface_info {}; //#TODO
typedef struct field_info {}; //#TODO
typedef struct method_info {}; //#TODO
typedef struct attribute_info {}; //#TODO