#include "../h/reader.h"
#include <iostream>
#include <ostream>

int read_class_file(classfile *file, FILE *fp) {
    // test pointers
    assert(file);
    assert(fp);

    file->magic = read_u4(fp);
    if(file->magic != 0xcafebabe) {
        std::cout << "This file is not a valid class file!" << std::endl;
        return 0;
    }

    file->minor_version = read_u2(fp);
    file->major_version = read_u2(fp);

    file->cp_count = read_u2(fp);

    file->cp = (cp_info*) calloc(file->cp_count, sizeof(cp_info));

    read_cp_info(file->cp, file->cp_count, fp);

    file->access_flags = read_u2(fp);
    

    file->this_class = read_u2(fp);

    file->super_class = read_u2(fp);

    file->interfaces_count = read_u2(fp);

    file->interfaces = (interface_info*) calloc(file->interfaces_count, sizeof(interface_info));
    if (file->interfaces_count > 0) {
        read_interfaces(fp, file->interfaces, file->interfaces_count);
    }

    file->fields_count = read_u2(fp);

    file->fields = (field_info*) calloc(file->fields_count, sizeof(field_info));
    if (file->fields_count > 0) {
        read_fields(fp, file->fields, file->fields_count, file->cp);
    }

    file->methods_count = read_u2(fp);

    file->methods = (method_info*) calloc(file->methods_count, sizeof(method_info));

    if(file->methods_count > 0) {
        read_methods(fp, file->methods, file->methods_count, file->cp);
    }

    file->attributes_count = read_u2(fp);

    file->attributes = (attribute_info*) calloc(file->attributes_count, sizeof(attribute_info));

    read_attributes(fp, file->attributes, file->attributes_count, file->cp);

    return 1;
}

void read_cp_info(cp_info cp[], int cp_count, FILE *fp) {
    for (int i=1; i < cp_count; i++) {
        cp_info *ptr = &cp[i];
        ptr->tag = read_u1(fp);
        
        read_constant_info(ptr->tag, &ptr->info, fp);

        if (static_cast<int>(ptr->tag) == CONSTANT_Double || static_cast<int>(ptr->tag) == CONSTANT_Long) {
            i++;
        }

    }
}

void read_constant_info(u1 tag, CONSTANT_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);

    switch(static_cast<int>(tag)) {
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
        read_code_attribute(&att_ptr->info.code, fp, cp);
    }
    else if (strcmp("ConstantValue", str) == 0)
    {
        read_constantvalue_attribute(&att_ptr->info.constantvalue, fp);
    }
    else if (strcmp("Exceptions", str) == 0)
    {
        read_exceptions_attribute(&att_ptr->info.exceptions, fp);
    }
    else if (strcmp("LineNumberTable", str) == 0)
    {
        read_linenumbertable_attribute(&att_ptr->info.linenumbertable, fp);
    }
    else if (strcmp("SourceFile", str) == 0)
    {
        read_sourcefile_attribute(&att_ptr->info.sourcefile, fp);
        assert(cp[att_ptr->info.sourcefile.sourcefile_index].tag == CONSTANT_Utf8);
    }
    else if (strcmp("InnerClasses", str) == 0)
    {
        read_innerclasses_attribute(&att_ptr->info.innerclasses, fp);
    }
    else if (strcmp("Synthetic", str) == 0)
    {
        read_synthetic_attribute(att_ptr, fp);
    }
    else if (strcmp("StackMapTable", str) == 0)
    {
        read_stackmaptable_attribute(&att_ptr->info.stackmaptable, fp);
    }
    else
    {
        std::cout << "Warning: unknown attribute type" << str << std::endl;
    }
}

void read_attributes(FILE *fp, attribute_info attributes[], u2 attributes_count, cp_info *cp)
{
    u2 i = 0;
    for (i = 0; i < attributes_count; i++)
    {
        read_attribute_info(fp, &attributes[i], cp);
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

    field->attributes = (attribute_info *) calloc(field->attribute_count, sizeof(attribute_info));
    if (field->attribute_count > 0) {
        read_attributes(fp, field->attributes, field->attribute_count, cp);
    }

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


void read_utf8(CONSTANT_Utf8_info *ptr, FILE *fp) {
    assert(ptr);
    assert(fp);
    ptr->length = read_u2(fp);
    ptr->bytes = (u1*) calloc(ptr->length+1, sizeof(u1));
    assert(ptr->bytes);
    fread(ptr->bytes, sizeof(u1), ptr->length, fp);
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

void read_code_attribute(Code_attribute* code_ptr, FILE* fp, cp_info* cp){
    // test pointers
    assert(code_ptr);
    assert(fp);
    assert(cp);

    code_ptr->max_stack = read_u2(fp);
    code_ptr->max_locals = read_u2(fp);
    code_ptr->code_length = read_u4(fp);

    code_ptr->code = (u1*) calloc(code_ptr->code_length, sizeof(u1));
    assert(code_ptr->code);
    int i;
    for(i = 0; i < code_ptr->code_length; i++) {
        code_ptr->code[i] = read_u1(fp);
    }

    code_ptr->exception_table_length = read_u2(fp);
    code_ptr->exception_table = (ExcTable*) calloc(code_ptr->exception_table_length, 4*sizeof(u2));
    for(i = 0; i < code_ptr->exception_table_length; i++) {
        code_ptr->exception_table[i].start_pc = read_u2(fp);
        code_ptr->exception_table[i].end_pc = read_u2(fp);
        code_ptr->exception_table[i].handler_pc = read_u2(fp);
        code_ptr->exception_table[i].catch_type = read_u2(fp);
    }

    code_ptr->attributes_count = read_u2(fp);
    code_ptr->attributes = (attribute_info*) calloc(code_ptr->attributes_count, sizeof(attribute_info));
    for(i = 0; i < code_ptr->attributes_count; i++) {
        read_attribute_info(fp, &code_ptr->attributes[i], cp);
    }
}

void read_constantvalue_attribute(ConstantValue_attribute *constValue_ptr, FILE *fp) {
    // test pointers
    assert(constValue_ptr);
    assert(fp);

    constValue_ptr->attribute_name_index = read_u2(fp);
    constValue_ptr->attribute_length = read_u4(fp);
    constValue_ptr->constantvalue_index = read_u2(fp);
}

void read_exceptions_attribute(Exceptions_attribute *excp_ptr, FILE *fp) {
    // test pointers
    assert(excp_ptr);
    assert(fp);

    excp_ptr->number_of_exceptions = read_u2(fp);
    excp_ptr->exception_index_table = (u2*) calloc(excp_ptr->number_of_exceptions, sizeof(u2));
    int i;
    for(i = 0; i < excp_ptr->number_of_exceptions; i++) {
        excp_ptr->exception_index_table[i] = read_u2(fp);
    }
}

void read_linenumbertable_attribute(LineNumberTable_attribute *lineNum_ptr, FILE *fp) {
    // test pointers
    assert(lineNum_ptr);
    assert(fp);

    lineNum_ptr->line_number_table_length = read_u2(fp);
    lineNum_ptr->line_number_table = (LineNTable*) calloc( lineNum_ptr->line_number_table_length, 2*sizeof(u2));

    int i;
    for (i = 0; i < lineNum_ptr->line_number_table_length; i++) {
        lineNum_ptr->line_number_table[i].start_pc = read_u2(fp);
        lineNum_ptr->line_number_table[i].line_number = read_u2(fp);
    }
}

void read_sourcefile_attribute(SourceFile_attribute *sourceFile_ptr, FILE *fp) {
    // test pointers
    assert(sourceFile_ptr);
    assert(fp);

    sourceFile_ptr->sourcefile_index = read_u2(fp);

}

void read_innerclasses_attribute(InnerClasses_attribute *innerClass_ptr, FILE *fp) {
    // test pointers
    assert(innerClass_ptr);
    assert(fp);

    innerClass_ptr->number_of_classes = read_u2(fp);
    innerClass_ptr->classes = (ClassesIn*) calloc(innerClass_ptr->number_of_classes, 4*sizeof(u2));

    int i;
    for (i = 0; i < innerClass_ptr->number_of_classes; i++) {
        innerClass_ptr->classes[i].inner_class_info_index = read_u2(fp);
        innerClass_ptr->classes[i].outer_class_info_index = read_u2(fp);
        innerClass_ptr->classes[i].inner_name_index = read_u2(fp);
        innerClass_ptr->classes[i].inner_class_access_flags = read_u2(fp);
    }
}

void read_synthetic_attribute(attribute_info *synthetic_ptr, FILE *fp){
  assert(synthetic_ptr);
  assert(fp);

  assert(!synthetic_ptr->attribute_length);
}

void read_stackmaptable_attribute(StackMapTable_attribute *smt_ptr, FILE *fp) {
    // test pointers
    assert(smt_ptr);
    assert(fp);

    smt_ptr->n_entries = read_u2(fp);
    smt_ptr->stack = (StackMapFrame*) calloc(smt_ptr->n_entries, sizeof(StackMapFrame));

    int n_entries = static_cast<int>(smt_ptr->n_entries);

    for (int i = 0; i < n_entries; i++) {
        read_stack_map_frame(fp, &smt_ptr->stack[i]);
    }
}

void read_interfaces(FILE *fp, CONSTANT_Class_info interfaces[], u2 interfaces_count) {
  int i;
  for (i = 0; i < interfaces_count; i++) {
    CONSTANT_Class_info *ptr = &interfaces[i];
    ptr->name_index = read_u2(fp);
  }
}

void read_methods(FILE *fp, method_info methods[], uint16_t methods_count, cp_info *cp) {
  int i;
  for (i = 0; i < methods_count; i++) {
    method_info *ptr = &methods[i];
    read_method_entry(fp, ptr, cp);
  }
}

void read_method_entry(FILE *fp, method_info *method, cp_info *cp) {
  read_single_field(fp, (field_info *) method, cp);
}


void read_stack_map_frame(FILE *fp, StackMapFrame *stack_map_frame) {
	stack_map_frame->frame_type = read_u1(fp);
    int type = static_cast<int>(stack_map_frame->frame_type);
     if (type >= 64 && type <= 127) {
		stack_map_frame->map_frame_type.same_locals_1_stack_item_frame.stack = (VerificationTypeInfo*) calloc(1, sizeof(VerificationTypeInfo));
        read_verification_type_info(fp, stack_map_frame->map_frame_type.same_locals_1_stack_item_frame.stack);

	} else if (type == 247) {
		stack_map_frame->map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta = read_u2(fp);

		stack_map_frame->map_frame_type.same_locals_1_stack_item_frame_extended.stack = (VerificationTypeInfo*)  calloc(1, sizeof(VerificationTypeInfo));
        read_verification_type_info(fp, stack_map_frame->map_frame_type.same_locals_1_stack_item_frame_extended.stack);

	} else if (type >= 248 && type <= 250) {
		stack_map_frame->map_frame_type.chop_frame.offset_delta = read_u2(fp);

	} else if (type == 251) {
		stack_map_frame->map_frame_type.same_frame_extended.offset_delta = read_u2(fp);

	} else if (type >= 252 && type <= 254) {
		stack_map_frame->map_frame_type.append_frame.offset_delta = read_u2(fp);
		u2 sizeMalloc = (type - 251);

		stack_map_frame->map_frame_type.append_frame.locals = (VerificationTypeInfo*)  calloc(type - 251, sizeof(VerificationTypeInfo));

		for (int posicao = 0; posicao < sizeMalloc; posicao++) {
            read_verification_type_info(fp, &stack_map_frame->map_frame_type.append_frame.locals[posicao]);
		}

	} else if (type == 255) {
        
		stack_map_frame->map_frame_type.full_frame.offset_delta = read_u2(fp);

		stack_map_frame->map_frame_type.full_frame.number_of_locals = read_u2(fp);


        int number_of_locals = static_cast<int>(stack_map_frame->map_frame_type.full_frame.number_of_locals);
		if (number_of_locals > 0) {
			stack_map_frame->map_frame_type.full_frame.locals = (VerificationTypeInfo*) calloc(number_of_locals, sizeof(VerificationTypeInfo));

			for (int posicao = 0; posicao < number_of_locals; posicao++) {
                read_verification_type_info(fp, &stack_map_frame->map_frame_type.full_frame.locals[posicao]);
			}
		}

		stack_map_frame->map_frame_type.full_frame.number_of_stack_items = read_u2(fp);
        int number_of_stack_items = static_cast<int>(stack_map_frame->map_frame_type.full_frame.number_of_stack_items);

		if (number_of_stack_items > 0) {
			stack_map_frame->map_frame_type.full_frame.stack = (VerificationTypeInfo*) calloc(number_of_stack_items , sizeof(VerificationTypeInfo));

            for (int posicao = 0; posicao < number_of_stack_items; posicao++) {
                read_verification_type_info(fp, &stack_map_frame->map_frame_type.full_frame.stack[posicao]);
			}
		}
	}
}

void read_verification_type_info (FILE* fp, VerificationTypeInfo *vtype) {
	vtype->tag = read_u1(fp);
    int tag = static_cast<int>(vtype->tag);

	switch (tag) {
		case 7:
			vtype->type_info.object_variable_info.cpool_index = read_u2(fp);
			break;
		case 8:
			vtype->type_info.uninitialized_variable_info.offset = read_u2(fp);
			break;
		default:
			break;
	}

}