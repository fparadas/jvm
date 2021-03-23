#include "printer.h"

void print_cp_info(u2 cp_count, cp_info cp[]) {
    for (int i = 1; i < cp_count; i++) {
        print_constant_info(cp[i].tag, cp[i].info);
    }
}

void print_constant_info(u1 tag, CONSTANT_info info) {
    switch(tag) {
        case CONSTANT_Utf8:
            print_utf8(info.utf8_info);
            break;
        case CONSTANT_Integer:
            print_integer(info.integer_info);
            break;
        case CONSTANT_Float:
            print_float(info.float_info);
            break;
        case CONSTANT_Long:
            print_long(info.long_info);
            break;
        case CONSTANT_Double:
            print_double(info.double_info);
            break;
        case CONSTANT_Class:
            print_class(info.class_info);
            break;
        case CONSTANT_String:
            print_string(info.string_info);
            break;
        case CONSTANT_Fieldref:
            print_fieldref(info.fieldref_info);
            break;
        case CONSTANT_Methodref:
            print_methodref(info.methodref_info);
            break;
        case CONSTANT_InterfaceMethodref:
            print_interfaceMethodref(info.interfacemethodref_info);
            break;
        case CONSTANT_NameAndType:
            print_nameAndType(info.nameandtype_info);
            break;
        default:
            printf("Warning: wrong tag %x\n", tag);
            break;
    }

}

void print_utf8(CONSTANT_Utf8_info info) {

}

void print_integer(CONSTANT_Integer_info info);

void print_float(CONSTANT_Float_info info);

void print_long(CONSTANT_Long_info info);

void print_double(CONSTANT_Double_info info);

void print_class(CONSTANT_Class_info info);

void print_string(CONSTANT_String_info info);

void print_fieldref(CONSTANT_Fieldref_info info);

void print_methodref(CONSTANT_Methodref_info info);

void print_interfaceMethodref(CONSTANT_InterfaceMethodref_info info);

void print_nameAndType(CONSTANT_NameAndType_info info);