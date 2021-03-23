#include "reader.h"

void read_cp_info(cp_info cp[], int cp_count, FILE *fp) {
    for (int i=1; i < cp_count; i++) {
        cp_info *ptr = &cp[i];
        ptr->tag = read_u1(fp);

        read_constant_info(ptr->tag, &ptr->info, fp);

        if (ptr->tag == CONSTANT_Double || CONSTANT_Long) {
            i++;
        }
    }
}

void read_constant_info(u1 tag, CONSTANT_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);

    switch(tag) {
        case CONSTANT_Utf8:
            read_utf8(&ptr->utf8_info, fp);
            break;
        case CONSTANT_Integer:
            read_integer(&ptr->integer_info, fp);
            break;
        case CONSTANT_Float:
            read_float(&ptr->float_info, fp);
            break;
        case CONSTANT_Long:
            read_long(&ptr->long_info, fp);
            break;
        case CONSTANT_Double:
            read_double(&ptr->double_info, fp);
            break;
        case CONSTANT_Class:
            read_class(&ptr->class_info, fp);
            break;
        case CONSTANT_String:
            read_string(&ptr->string_info, fp);
            break;
        case CONSTANT_Fieldref:
            read_fieldref(&ptr->fieldref_info, fp);
            break;
        case CONSTANT_Methodref:
            read_methodref(&ptr->methodref_info, fp);
            break;
        case CONSTANT_InterfaceMethodref:
            read_interfaceMethodref(&ptr->interfacemethodref_info, fp);
            break;
        case CONSTANT_NameAndType:
            read_nameAndType(&ptr->nameandtype_info, fp);
            break;
        default:
            printf("Warning: wrong tag %x\n", tag);
            break;
    }

}


void read_utf8(CONSTANT_Utf8_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);
    ptr->length = read_u2(fp);
    ptr->bytes = (u1*) calloc(ptr->length+1, sizeof(u1));
    assert(ptr->bytes);
    fread(ptr->bytes, sizeof(u1), ptr->length, fp); //#TODO checar se não precisa trocar endian
}

void read_integer(CONSTANT_Integer_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);
    ptr->bytes = read_u4(fp);
}

void read_float(CONSTANT_Float_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);
    ptr->bytes = read_u4(fp);
}

void read_long(CONSTANT_Long_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);
    ptr->high_bytes = read_u4(fp);
    ptr->low_bytes = read_u4(fp);
}

void read_double(CONSTANT_Double_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);
    ptr->high_bytes = read_u4(fp);
    ptr->low_bytes = read_u4(fp);
}

void read_class(CONSTANT_Class_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);
    ptr->name_index = read_u2(fp);
}

void read_string(CONSTANT_String_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);
    ptr->string_index = read_u2(fp);
}

void read_fieldref(CONSTANT_Fieldref_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);
    ptr->class_index = read_u2(fp);
    ptr->name_and_type_index = read_u2(fp);
}

void read_methodref(CONSTANT_Methodref_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);
    ptr->class_index = read_u2(fp);
    ptr->name_and_type_index = read_u2(fp);
}

void read_interfaceMethodref(CONSTANT_InterfaceMethodref_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);
    ptr->class_index = read_u2(fp);
    ptr->name_and_type_index = read_u2(fp);
}

void read_nameAndType(CONSTANT_NameAndType_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);
    ptr->name_index = read_u2(fp);
    ptr->descriptor_index = read_u2(fp);
}