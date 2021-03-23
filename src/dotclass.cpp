#include "dotclass.h"
#include "utils.h"
#include <iostream>

void read_attribute_info(FILE *fp, attribute_info *att_ptr, cp_info *cp)
{
    // test pointers
    assert(fp);
    assert(att_ptr);
    assert(cp);

    att_ptr->attribute_name_index = read_u2(fp);
    att_ptr->attribute_length = read_u4(fp);

    char *str = get_cp_string(cp, att_ptr->attribute_name_index);

    if (strcmp("Code", str) == 0)
    {
        // read_code_attribute(&att_ptr->info.code, fp, cp);
    }
    else if (strcmp("ConstantValue", str) == 0)
    {
        // read_constantvalue_attribute(&att_ptr->info.constantvalue, fp);
    }
    else if (strcmp("Exceptions", str) == 0)
    {
        // read_exceptions_attribute(&att_ptr->info.exceptions, fp);
        // fseek(fp, att_ptr->attribute_length, SEEK_CUR);
    }
    else if (strcmp("LineNumberTable", str) == 0)
    {
        // read_linenumbertable_attribute(&att_ptr->info.linenumbertable, fp);
    }
    else if (strcmp("SourceFile", str) == 0)
    {
        // read_sourcefile_attribute(&att_ptr->info.sourcefile, fp);
        // assert(cp[att_ptr->info.sourcefile.index].tag == CONSTANT_Utf8);
    }
    else if (strcmp("InnerClasses", str) == 0)
    {
        // read_innerclasses_attribute(&att_ptr->info.innerclasses, fp);
    }
    else if (strcmp("Synthetic", str) == 0)
    {
        // read_synthetic_attribute(att_ptr, fp);
    }
    else if (strcmp("StackMapTable", str) == 0)
    {
        /*fseek(fp, att_ptr->attribute_length, SEEK_CUR);*/
        // read_stackmaptable_attribute(&att_ptr->info.stackmaptable, fp);
        // fseek(fp, att_ptr->attribute_length - 2, SEEK_CUR); /*WARN Talvez o bug esteja aqui*/
    }
    else
    {
        std::cout << "Warning: unknown attribute type" << str << std::endl;
    }
}

void read_attributes(FILE *fp, attribute_info attributes[], u2 attributes_count, cp_info *cp)
{
    int i = 0;
    for (i = 0; i < attributes_count; i++)
    {
        attribute_info *attr = &attributes[i];
        read_attribute_info(fp, attr, cp);
    }
}

void read_single_field(FILE *fp, field_info *field, cp_info *cp)
{
    // test pointers
    assert(fp);
    assert(field);
    assert(cp);

    field->access_flags = read_u2(fp);
    field->name_index = read_u2(fp);
    field->description_index = read_u2(fp);
    field->attribute_count = read_u2(fp);

    field->attributes = (attribute_info *)calloc(sizeof(attribute_info), field->attribute_count);
    read_attributes(fp, field->attributes, field->attribute_count, cp);
}

void read_fields(FILE *fp, field_info fields[], u2 fields_count, cp_info *cp)
{
    int i = 0;
    for (i = 0; i < fields_count; i++)
    {
        field_info *field_ptr = &fields[i];
        read_single_field(fp, field_ptr, cp);
    }
}

char *get_cp_string(cp_info *cp, u2 index)
{
    // test pointers
    assert(cp);

    cp_info *entry = &cp[index];
    assert(entry->tag == CONSTANT_Utf8);

    return (char *)entry->info.utf8_info.bytes;
}
