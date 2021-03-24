#include "../h/printer.h"

void print_summary(classfile *cf) {
    if (!cf) return;
    std::cout << "============== SUMMARY ==============" << "\n";

    std::cout << "magic: " << std::hex<<static_cast<int>(cf->magic) << "\n";

    std::cout << "major: " << std::hex<<static_cast<int>(cf->major_version) << "\n"; 
    std::cout << "minor: " << std::hex<<static_cast<int>(cf->minor_version) << "\n"; 

    std::cout << "cp_count: " << static_cast<int>(cf->cp_count) << "\n";

    std::cout << "access_flags: " << get_flags("class", cf->access_flags) << "\n";

    u4 class_name_index = cf->cp[cf->this_class].info.class_info.name_index;
    std::cout << "this_class: " << get_cp_string(cf->cp, class_name_index) << "\n";

    u4 superclass_name_index = cf->cp[cf->super_class].info.class_info.name_index;
    std::cout << "super_class: " << get_cp_string(cf->cp, superclass_name_index) << "\n";

    std::cout << "interfaces_count: " << static_cast<int>(cf->interfaces_count) << "\n";
    std::cout << "fields_count: " << static_cast<int>(cf->fields_count) << "\n";
    std::cout << "methods_count: " << static_cast<int>(cf->methods_count) << "\n";
    std::cout << "attributes_count: " << static_cast<int>(cf->attributes_count) << "\n";


    std::cout << "============== END OF SUMMARY ==============" << "\n";
}

void print_cp_info(classfile *cf) {
    for (int i = 1; i < cf->cp_count; i++) {
        print_cp_element(cf->cp, i);
    }
}

void print_cp_element(cp_info *cp, u2 i) {
    double d;
    u2 name_index, string_index, class_index, name_and_type_index, descriptor_index;
    u4 high, low;
    uint64_t lg;
    switch(cp[i].tag) {
        case CONSTANT_Utf8:
            std::cout << "Utf8:\t" << get_cp_string(cp, i) << "\n";
            break;
        case CONSTANT_Integer:
            std::cout << "Integer:\t" << static_cast<int>(cp[i].info.integer_info.bytes) << "\n";
            break;
        case CONSTANT_Float:
            std::cout << "Float:\t" << static_cast<float>(cp[i].info.integer_info.bytes) << "\n";
            //#TODO testar se funciona
            break;
        case CONSTANT_Long:
            printf("Long:\t");
            high = cp[i].info.long_info.high_bytes;
            low = cp[i].info.long_info.low_bytes;

            lg = ((uint64_t) high << 32) | ((uint64_t) low);
            printf("%ld\n", lg);
            break;
        case CONSTANT_Double:
            printf("Double:\t");
            high = cp[i].info.long_info.high_bytes;
            low = cp[i].info.long_info.low_bytes;

            lg = ((uint64_t) high << 32) | ((uint64_t) low);
            d = (double) lg;
            printf("%lf\n", d);
            break;
        case CONSTANT_Class:
            name_index = cp[i].info.class_info.name_index;
            std::cout << "Class:\t" <<  get_cp_string(cp, name_index) << "(" << name_index << ")\n";
            break;
        case CONSTANT_String:
            printf("String:\t");
            string_index = cp[i].info.string_info.string_index;
            std::cout << "String:\t" <<  get_cp_string(cp, string_index) << "(" << string_index << ")\n";
            break;
        case CONSTANT_Fieldref:
            printf("Fieldref:\t");
            class_index = cp[i].info.fieldref_info.class_index;
            name_and_type_index = cp[i].info.fieldref_info.name_and_type_index;
            printf("%s.%s:%s (#%d.#%d)\n", get_class_name_string(cp, class_index),
                get_name_and_type_string(cp, name_and_type_index, 1),
                get_name_and_type_string(cp, name_and_type_index, 0),
                class_index, name_and_type_index);
            break;
        case CONSTANT_Methodref:
            printf("Methodref:\t");
            class_index = cp[i].info.methodref_info.class_index;
            name_and_type_index = cp[i].info.methodref_info.name_and_type_index;
            printf("%s.%s:%s (#%d.#%d)\n", get_class_name_string(cp, class_index),
                get_name_and_type_string(cp, name_and_type_index, 1),
                get_name_and_type_string(cp, name_and_type_index, 0), 
                class_index, name_and_type_index);
            break;
        case CONSTANT_InterfaceMethodref:
            printf("InterfaceMethodref\t");
            class_index = cp[i].info.methodref_info.class_index;
            name_and_type_index = cp[i].info.methodref_info.name_and_type_index;
            printf("%s.%s:%s (#%d.#%d)\n", get_class_name_string(cp, class_index),
                get_name_and_type_string(cp, name_and_type_index, 1),
                get_name_and_type_string(cp, name_and_type_index, 0), 
                class_index, name_and_type_index);
            break;
        case CONSTANT_NameAndType:
            printf("NameAndType:\t");
            name_index = cp[i].info.nameandtype_info.name_index;
            descriptor_index = cp[i].info.nameandtype_info.descriptor_index;
            printf("%s:%s (#%d:#%d)\n", get_cp_string(cp, name_index),
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
            print_attribute_info(method->attributes, cf->cp);
        }

        std::cout << "\t}\n";
    }

    std::cout << "}\n";
}

void print_attribute_info(attribute_info *ptr, cp_info *cp) {
    std::cout << "undefined";
}