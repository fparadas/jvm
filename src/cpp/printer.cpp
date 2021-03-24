#include "../h/printer.h"
#include <iterator>
#include <ostream>

void print_summary(classfile *cf) {
    if (!cf) return;
    std::cout << "============== SUMMARY ==============" << "\n";

    std::cout << "magic: " << std::hex<<static_cast<int>(cf->magic) << "\n";

    std::cout << "major: " << std::dec<< cf->major_version << "\n"; 
    std::cout << "minor: " << std::dec<< cf->minor_version << "\n"; 

    std::cout << "cp_count: " << static_cast<int>(cf->cp_count) << "\n";

    std::cout << "access_flags: " << get_flags("class", cf->access_flags) << "\n";

    u2 class_name_index = cf->cp[cf->this_class].info.class_info.name_index;
    std::cout << "this_class: " << get_cp_string(cf->cp, class_name_index) << "\n";

    u2 superclass_name_index = cf->cp[cf->super_class].info.class_info.name_index;
    std::cout << "super_class: " << get_cp_string(cf->cp, superclass_name_index) << "\n";

    std::cout << "interfaces_count: " << static_cast<int>(cf->interfaces_count) << "\n";
    std::cout << "fields_count: " << static_cast<int>(cf->fields_count) << "\n";
    std::cout << "methods_count: " << static_cast<int>(cf->methods_count) << "\n";
    std::cout << "attributes_count: " << static_cast<int>(cf->attributes_count) << "\n";


    std::cout << "============== END OF SUMMARY ==============" << "\n";
}

void print_all(classfile *cf) {
        if (!cf) return;
    std::cout << "============== FILE DESCRIPTION ==============" << "\n";

    std::cout << "magic: " << std::hex<<static_cast<int>(cf->magic) << "\n";

    std::cout << "major: " << std::dec<<static_cast<int>(cf->major_version) << "\n"; 
    std::cout << "minor: " << std::dec<<static_cast<int>(cf->minor_version) << "\n"; 
    print_java_version(cf->major_version, cf->minor_version);
    std::cout << "cp_count: " << static_cast<int>(cf->cp_count) << "\n";
    print_cp_info(cf);

    std::cout << "access_flags: " << get_flags("class", cf->access_flags) << "\n";

    u2 class_name_index = cf->cp[cf->this_class].info.class_info.name_index;
    std::cout << "this_class: " << get_cp_string(cf->cp, class_name_index) << "\n";

    u2 superclass_name_index = cf->cp[cf->super_class].info.class_info.name_index;
    std::cout << "super_class: " << get_cp_string(cf->cp, superclass_name_index) << "\n";

    std::cout << "interfaces_count: " << static_cast<int>(cf->interfaces_count) << "\n";
    print_interfaces_info(cf);

    std::cout << "fields_count: " << static_cast<int>(cf->fields_count) << "\n";
    print_fields_info(cf);

    std::cout << "methods_count: " << static_cast<int>(cf->methods_count) << "\n";
    print_methods_info(cf);

    std::cout << "attributes_count: " << static_cast<int>(cf->attributes_count) << "\n";
    print_attributes(cf->attributes, cf->attributes_count, cf->cp);


    std::cout << "============== END OF FILE DESCRIPTION ==============" << "\n";
}

void print_cp_info(classfile *cf) {
    for (int i = 1; i < cf->cp_count; i++) {
        std::cout << "\t[" << i <<"]:";
        print_cp_tag(cf->cp[i].tag);
        print_cp_element(cf->cp, i);
        std::cout <<std::endl;
        if (cf->cp[i].tag == CONSTANT_Double || cf->cp[i].tag == CONSTANT_Long ){
            i++;
        }
    }
}

void print_cp_tag(u1 tag) {
    switch(tag) {
        case CONSTANT_Utf8:
            std::cout << "Utf8:\t";
            break;
        case CONSTANT_Integer:
            std::cout << "Integer:\t" ;
            break;
        case CONSTANT_Float:
            std::cout << "Float:\t";
            break;
        case CONSTANT_Long:
            std::cout <<  "Long:\t";
            break;
        case CONSTANT_Double:
            std::cout <<  "Double:\t";
            break;
        case CONSTANT_Class:
            std::cout <<  "Class:\t";
            break;
        case CONSTANT_String:
            std::cout <<  "String:\t";
            break;
        case CONSTANT_Fieldref:
            std::cout <<  "Fieldref:\t";
            break;
        case CONSTANT_Methodref:
            std::cout <<  "Methodref:\t";
            break;
        case CONSTANT_InterfaceMethodref:
            std::cout <<  "InterfaceMethodref:\t";
            break;
        case CONSTANT_NameAndType:
            std::cout <<  "NameAndType:\t";
            break;
    }
}

void print_cp_element(cp_info *cp, u2 i) {
    double d;
    float f;
    u2 name_index, string_index, class_index, name_and_type_index, descriptor_index;
    u4 high;
    uint64_t low, lg, conc;
    switch(cp[i].tag) {
        case CONSTANT_Utf8:
            std::cout << get_cp_string(cp, i);
            break;
        case CONSTANT_Integer:
            std::cout << std::dec <<static_cast<int>(cp[i].info.integer_info.bytes);
            break;
        case CONSTANT_Float:
            memcpy(&f, &cp[i].info.integer_info.bytes, sizeof(float));
            std::cout << f;
            break;
        case CONSTANT_Long:
            high = cp[i].info.long_info.high_bytes;
            low = cp[i].info.long_info.low_bytes;

            lg = ((uint64_t) high << 32) | ((uint64_t) low);
            printf("%ld", lg);
            break;
        case CONSTANT_Double:
            high = cp[i].info.long_info.high_bytes;
            low = cp[i].info.long_info.low_bytes;

            conc = ((uint64_t) high << 32) + ((uint64_t) low);
            d = *((double *) (&conc));
            printf("%lf", d);
            break;
        case CONSTANT_Class:
            name_index = cp[i].info.class_info.name_index;
            std::cout << get_cp_string(cp, name_index) << "(" << name_index << ")";
            break;
        case CONSTANT_String:
            string_index = cp[i].info.string_info.string_index;
            std::cout << "String:\t" <<  get_cp_string(cp, string_index) << "(" << string_index << ")";
            break;
        case CONSTANT_Fieldref:
            class_index = cp[i].info.fieldref_info.class_index;
            name_and_type_index = cp[i].info.fieldref_info.name_and_type_index;
            printf("%s.%s:%s (#%d.#%d)", get_class_name_string(cp, class_index),
                get_name_and_type_string(cp, name_and_type_index, 1),
                get_name_and_type_string(cp, name_and_type_index, 0),
                class_index, name_and_type_index);
            break;
        case CONSTANT_Methodref:
            class_index = cp[i].info.methodref_info.class_index;
            name_and_type_index = cp[i].info.methodref_info.name_and_type_index;
            printf("%s.%s:%s (#%d.#%d)", get_class_name_string(cp, class_index),
                get_name_and_type_string(cp, name_and_type_index, 1),
                get_name_and_type_string(cp, name_and_type_index, 0), 
                class_index, name_and_type_index);
            break;
        case CONSTANT_InterfaceMethodref:
            class_index = cp[i].info.methodref_info.class_index;
            name_and_type_index = cp[i].info.methodref_info.name_and_type_index;
            printf("%s.%s:%s (#%d.#%d)", get_class_name_string(cp, class_index),
                get_name_and_type_string(cp, name_and_type_index, 1),
                get_name_and_type_string(cp, name_and_type_index, 0), 
                class_index, name_and_type_index);
            break;
        case CONSTANT_NameAndType:
            name_index = cp[i].info.nameandtype_info.name_index;
            descriptor_index = cp[i].info.nameandtype_info.descriptor_index;
            printf("%s:%s (#%d:#%d)", get_cp_string(cp, name_index),
                get_cp_string(cp, descriptor_index),
                name_index, descriptor_index);
            break;
    }
}

void print_interfaces_info(classfile *cf) {
    int interfaces_size = static_cast<int>(cf->interfaces_count);
    u2 name_index;

    std::cout << "Interfaces: (Count: " << interfaces_size <<") {\n";

    for (int i = 0; i < interfaces_size; i++) {
        interface_info *interface = &cf->interfaces[i];

        name_index = cf->cp[interface->name_index].info.class_info.name_index;

        std::cout << "\tClass:\t" <<  get_cp_string(cf->cp, name_index) << "(" << name_index << "),\n";
    }

    std::cout << "}\n";
}

void print_fields_info(classfile *cf) {
    int fields_size = static_cast<int>(cf->fields_count);

    std::cout << "Fields: (Count: " << fields_size <<") {\n";

    for (int i = 0; i < fields_size; i++) {
        field_info *field = &cf->fields[i];

        std::cout << "\tName:\t" << get_cp_string(cf->cp, field->name_index) << "\n";
        std::cout << "\tDescriptor:\t" << get_cp_string(cf->cp, field->description_index) << "\n";

        std::cout << "\tFlags:\t" << get_flags("fields", field->access_flags) << "\n";

        std::cout <<"\tAttributes: (Count: " << static_cast<int>(field->attribute_count) << "){\n";
        for (int j = 0; j < static_cast<int>(field->attribute_count); j++) {
            std::cout << "\t\t" <<j <<": ";
            print_attribute_info(&field->attributes[j], cf->cp);
        }

        std::cout << "\t}\n";
    }

    std::cout << "}\n";
}

void print_methods_info(classfile *cf) {
    int methods_size = static_cast<int>(cf->methods_count);

    std::cout << "Methods: (Count: " << methods_size <<") {\n";

    for (int i = 0; i < methods_size; i++) {
        method_info *method = &cf->methods[i];

        std::cout << "\tName:\t" << get_cp_string(cf->cp, method->name_index) << "\n";
        std::cout << "\tDescriptor:\t" << get_cp_string(cf->cp, method->description_index) << "\n";

        std::cout << "\tFlags:\t" << get_flags("methods", method->access_flags) << "\n";

        std::cout <<"\tAttributes: (Count: " << static_cast<int>(method->attributes_count) << "){\n";
        for (int j = 0; j < static_cast<int>(method->attributes_count); j++) {
            std::cout << "\t\t" <<j <<": ";
            print_attribute_info(&method->attributes[j], cf->cp);
        }

        std::cout << "\t}\n";
    }

    std::cout << "}\n";
}

void print_attributes(attribute_info attr[], u2 attr_count, cp_info *cp) {
    assert(attr);
    for (u2 i = 0; i < attr_count; i++) {
        print_attribute_info(&attr[i], cp);
    }
}

void print_attribute_info(attribute_info *att_ptr, cp_info *cp)
{
    
    char *str = get_cp_string(cp, att_ptr->attribute_name_index);
    if (strcmp("Code", str) == 0)
    {
       print_code_attribute(&att_ptr->info.code, cp);
    }
    else if (strcmp("ConstantValue", str) == 0)
    {
       print_constantvalue_attribute(&att_ptr->info.constantvalue);
    }
    else if (strcmp("Exceptions", str) == 0)
    {
       print_exception_attribute(&att_ptr->info.exceptions, cp, att_ptr->info.code.exception_table);
    }
    else if (strcmp("LineNumberTable", str) == 0)
    {
       print_linenumber_attribute(&att_ptr->info.linenumbertable);
    }
    else if (strcmp("SourceFile", str) == 0)
    {
        print_sourcefile_attribute(&att_ptr->info.sourcefile, cp);
    }
    else if (strcmp("InnerClasses", str) == 0)
    {
       print_innerclasses_attribute(&att_ptr->info.innerclasses, cp);
    }
    else if (strcmp("Synthetic", str) == 0)
    {
    //    print_synthetic_attribute(att_ptr);
    }
    else if (strcmp("StackMapTable", str) == 0)
    {
       print_stackmaptable_attribute(&att_ptr->info.stackmaptable, cp);
    }
    else
    {
        std::cout << "Warning: unknown attribute type" << str << std::endl;
    }
}

void print_sourcefile_attribute(SourceFile_attribute *attr, cp_info *cp) {
    std::cout << "SouceFile: " << get_cp_string(cp, attr->sourcefile_index) << std::endl;
}

void print_stackmaptable_attribute(StackMapTable_attribute *attr, cp_info *cp) {
    std::cout << "\t\t StackMapTable: { " << std::endl;
    int n_entries = static_cast<int>(attr->n_entries);
    std::cout << "\t\t\tN Entries: " << n_entries << std::endl;

    for (int i=0; i < n_entries; i++) {
        std::cout << "\t\t\t" << i <<": ";
        print_stack_map_frame(&attr->stack[i], cp);
    }
    std::cout << "\t\t }" << std::endl;

}

void print_stack_map_frame(StackMapFrame *frame, cp_info *cp) {
    int type = static_cast<int>(frame->frame_type);
    if (type <= 67) {
        std::cout << "SAME" <<std::endl;
    } else if (type >=64 && type <= 127) {
        std::cout << "SAME_LOCALS_1_STACK_ITEM" <<std::endl;
        std::cout << "Local verifications: " <<std::endl;
        print_verification_type_info(frame->map_frame_type.same_locals_1_stack_item_frame.stack, cp);

    } else if (type == 247) {
        std::cout << "SAME_LOCALS_1_STACK_ITEM_EXTENDED, Offset: " << std::dec << frame->map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta <<std::endl;
        std::cout << "\t\t\t" << "Local verifications: " <<std::endl;
        print_verification_type_info(frame->map_frame_type.same_locals_1_stack_item_frame_extended.stack, cp);
    } else if (type >= 248 && type <= 250) {
        std::cout << "CHOP, Offset: " << std::dec << frame->map_frame_type.chop_frame.offset_delta <<std::endl;
    } else if (type == 251) {
        std::cout << "SAME_FRAME_EXTENDED, Offset: " << std::dec << frame->map_frame_type.same_frame_extended.offset_delta <<std::endl;
    } else if (type >= 252 && type <= 254) {
        std::cout << "APPEND, Offset: "  << std::dec << frame->map_frame_type.append_frame.offset_delta<<std::endl;
        std::cout << "\t\t\t" << "Local verifications: " <<std::endl;
        for (int i = 0; i < type - 251; i++) {
            print_verification_type_info(&frame->map_frame_type.append_frame.locals[i], cp);
        }
    } else if (type == 255) {
        std::cout << "FULL_FRAME, Offset: " << std::dec << frame->map_frame_type.full_frame.offset_delta <<std::endl;

        int number_of_locals = static_cast<int>(frame->map_frame_type.full_frame.number_of_locals);
        std::cout << "\t\t\t" << "Local verifications: " <<std::endl;
        for (int i = 0; i < number_of_locals; i++) {
            print_verification_type_info(&frame->map_frame_type.full_frame.locals[i], cp);
        }

        int number_of_stack_items = static_cast<int>(frame->map_frame_type.full_frame.number_of_stack_items);
        std::cout << "\t\t\t" << "Stack verifications: " <<std::endl;
        for (int i = 0; i < number_of_stack_items; i++) {
            print_verification_type_info(&frame->map_frame_type.full_frame.stack[i], cp);
        }
    }
}

void print_verification_type_info(VerificationTypeInfo *info, cp_info *cp) {
    int tag = static_cast<int>(info->tag);

    switch(tag) {
        case 0:
            std::cout << "\t\t\t" << "\tTOP" << std::endl;
            break;
        case 1:
            std::cout << "\t\t\t" << "\tInteger" << std::endl;
            break;
        case 2:
            std::cout << "\t\t\t" << "\tFloat" << std::endl;
            break;
        case 3:
            std::cout << "\t\t\t" << "\tLong" << std::endl;
            break;
        case 4:
            std::cout << "\t\t\t" << "\tDouble" << std::endl;
            break;
        case 5:
            std::cout << "\t\t\t" << "\tNull" << std::endl;
            break;
        case 6:
            std::cout << "\t\t\t" << "\tUninitializedThis" << std::endl;
            break;
        case 7:
            std::cout << "\t\t\t" << "\tObject:  " << get_cp_string(cp, cp[info->type_info.object_variable_info.cpool_index].info.class_info.name_index)<< std::endl;
            break;
        case 8:
            std::cout << "\t\t\t" << "\tUninitialized, Offset: " << info->type_info.uninitialized_variable_info.offset << std::endl;
            break;
    }

}

void print_exception_attribute(Exceptions_attribute *ptr, cp_info *cp, ExcTable* excT) {
  int i = 0;
  u2 index_table;

  printf("\t\tfrom\tto\ttarget\ttype\n");

  for (;i < ptr->number_of_exceptions;i++) {
    index_table = ptr->exception_index_table[i];

    u2 from = (excT + index_table)->start_pc;
    u2 to = (excT + index_table)->end_pc;
    u2 target = (excT + index_table)->handler_pc;
    u2 handler_index = (excT + index_table)->handler_pc;

    char* handler = get_cp_string(cp, handler_index);

    printf("%" PRIu16 "\t%" PRIu16 "\t%" PRIu16 "\t%s\n", from, to, target, handler);
  }
}

void print_linenumber_attribute(LineNumberTable_attribute *ptr) {
  int i = 0;

  LineNTable* ptr_crawler = ptr->line_number_table;
  std::cout << "\t\t LineNumberTable: {\n";

  for (; i < ptr->line_number_table_length;i++) {
    printf("\t\t\t line %d: %d\n", ptr_crawler->line_number, ptr_crawler->start_pc);
    ptr_crawler += 1;
  }
  std::cout << "\t\t}\n";
}

void print_code_attribute(Code_attribute *ptr, cp_info *cp) {
    printf("\t\t stack=%d, locals=%d\n",
	   ptr->max_stack,
	   ptr->max_locals);
    u4 f, param1, param2, param3, param4;
    u4 result;
    for (u4 i = 0; i < ptr->code_length; i++) {
      f = i;
      std::cout << "\t\t " << i << "\t" << strings_opcodes[ptr->code[i]];
      switch (opargs[ptr->code[i]]){
        case 1:
        if ((ptr->code[i] >= OP_iload && ptr->code[i] >= OP_aload) || ptr->code[i] == OP_ret)
            printf (" %d", ptr->code[++i]);
        else if (ptr->code[i] == OP_ldc){
            printf (" #%u ", ptr->code[++i]);
            print_cp_element (cp, ptr->code[i]);
        }
        else
            printf (" %d", ptr->code[++i]);
        break;
        case 2:
        param1 = ptr->code[++i];
        param2 = ptr->code[++i];
        if ((ptr->code[f] >= OP_ifeq && ptr->code[f] <= OP_jsr) ||
            ptr->code[f] == OP_ifnull || ptr->code[f] == OP_ifnonnull ||
            ptr->code[f] == OP_sipush) {

            result = (param1 << 8) + param2;
            printf (" %d", (int16_t) result);
        }
        else if (ptr->code[f] == OP_iinc){
            printf (" %u by %d", param1, (int8_t) param2);
        }
        else if (ptr->code[f] == OP_ldc_w || ptr->code[f] == OP_ldc2_w ||
            (ptr->code[f] >= OP_getstatic && ptr->code[f] <= OP_invokestatic) ||
            ptr->code[f] == OP_new || ptr->code[f] == OP_anewarray ||
            ptr->code[f] == OP_checkcast || ptr->code[f] == OP_instanceof) {

            result = (param1 << 8) + param2;
            printf (" #%u ", result);
            print_cp_element (cp, (u2) result);
        }
        else {
            printf (" %d", param1);
            printf (" %d", param2);
        }
        break;
        case 3:
        param1 = ptr->code[++i];
        param2 = ptr->code[++i];
        param3 = ptr->code[++i];
        if (ptr->code[f] == OP_multianewarray) {
            result = (param1 << 8) + param2;
            printf (" #%u", result);
            print_cp_element (cp, (u2) result);
            printf (" Dimensão: %u", param3);
        }
        else {
            printf (" %d", param1);
            printf (" %d", param2);
            printf (" %d", param3);
        }
        break;
        case 4:
        param1 = ptr->code[++i];
        param2 = ptr->code[++i];
        param3 = ptr->code[++i];
        param4 = ptr->code[++i];
        if (ptr->code[f] == OP_goto_w || ptr->code[f] == OP_jsr_w) {
            result = (param1 << 24) + (param2 << 16) + (param3 << 8) + param4;
            printf (" %d", (int32_t) result);
        }
        else if (ptr->code[f] == OP_invokedynamic || ptr->code[f] == OP_invokeinterface){
            result = (param1 << 8) + param2;
            printf (" #%u", result);
            print_cp_element (cp, (u2) result);
            printf (" %d", param3);
            printf (" %d", param4);
        }
        else {
            printf (" %d", param1);
            printf (" %d", param2);
            printf (" %d", param3);
            printf (" %d", param4);
        }
        break;
        case 0:
        break;
        default:
        break;
        }

      printf("\t(0x%x)\n", ptr->code[f]);
    }

    for (u4 i = 0; i < ptr->attributes_count; i++) {
      print_attribute_info(&ptr->attributes[i], cp);
    }
}

void print_innerclasses_attribute(InnerClasses_attribute *ptr,cp_info *cp) {
    u2 innerclass;
    u2 outerclass;
    u2 innername;
    u2 access_flags;
    u2 innerclass_name;
    u2 outerclass_name;

    char *s_innername, *s_outerclass_name;

    printf("\t\t Number of classes: %d\n",
        ptr->number_of_classes);

    for (u4 i = 0; i < ptr->number_of_classes; i++) {
    /* Indexes to constant pool elements*/
        innerclass = ptr->classes[i].inner_class_info_index;
        outerclass = ptr->classes[i].outer_class_info_index;
        innername = ptr->classes[i].inner_name_index;
        access_flags = ptr->classes[i].inner_class_access_flags;
        innerclass_name = cp[innerclass].info.class_info.name_index;
        outerclass_name = cp[outerclass].info.class_info.name_index;
        
        if(outerclass_name) {
            s_outerclass_name = get_cp_string(cp, outerclass_name);
        } else {
            strcpy(s_outerclass_name, "Invalid constant pool reference.");
        }

        if(innername) {
            s_innername = get_cp_string(cp, innername);
        } else {
            strcpy(s_innername, "Invalid constant pool reference.");
        }

        printf("\n\t\t  %d) InnerClass- %s (#%d);\n\t\t     OuterClass- %s (#%d);\n\t\t     InnerName- %s (#%d);\n\t\t     AccessFlags- (0x%04x) ",
            i, get_cp_string(cp, innerclass_name), innerclass,
            s_outerclass_name, outerclass,
            s_innername, innername, access_flags);

        std::cout << "access_flags: " << get_flags("class", access_flags) << "\n";
    }
}

void print_constantvalue_attribute(ConstantValue_attribute *attr) {
    std::cout << "ConstantValue: { ";

    std::cout << "Attribute Name Index: " << static_cast<int>(attr->attribute_name_index) << ", ";
    std::cout << "Attribute Length: " << static_cast<int>(attr->attribute_length) << ", ";
    std::cout << "Constant Value Index: " << static_cast<int>(attr->constantvalue_index) << "}\n";
}

void print_java_version (u2 major,  u2 minor) {
  std::string  major_version = "";
  switch (major){
    case 52:
      major_version = "J2SE 8";
    break;
    case 51:
      major_version = "J2SE 7";
    break;
    case 50:
      major_version = "J2SE 6.0";
    break;
    case 49:
      major_version = "J2SE 5.0";
    break;
    case 48:
      major_version = "JDK 1.4";
    break;
    case 47:
      major_version = "JDK 1.3";
    break;
    case 46:
      major_version = "JDK 1.2";
    break;
    case 45:
      major_version = "JDK 1.1";
    break;
    default:
      major_version = "0";
    break;
  }
  std::cout << "Java Version: " << major_version << "." << minor << std::endl;
}