#include "printer.h"

void print_cp_info(classfile *cf) {
    char *str;
    float fl;
    double d;
    u2 name_index, string_index, class_index, name_and_type_index, descriptor_index;
    u4 x, f, high, low;
    uint64_t lg;
    for (int i = 1; i < cf->cp_count; i++) {
        switch(cf->cp[i].tag) {
            case CONSTANT_Utf8:
                printf("Utf8:\t");
                str = get_cp_string(cf->cp, i);
                printf("%s\n", str);
                break;
            case CONSTANT_Integer:
                printf("Integer:\t");
                x = cf->cp[i].info.integer_info.bytes;
                printf("%d\n", x);
                break;
            case CONSTANT_Float:
                printf("Float:\t");
                f = cf->cp[i].info.integer_info.bytes;

                memcpy(&fl, &f, sizeof(float));
                printf("%d\n", x);
                break;
            case CONSTANT_Long:
                printf("Long:\t");
                high = cf->cp[i].info.long_info.high_bytes;
                low = cf->cp[i].info.long_info.low_bytes;

                lg = ((uint64_t) high << 32) | ((uint64_t) low);
                printf("%ld\n", lg);
                break;
            case CONSTANT_Double:
                printf("Long:\t");
                high = cf->cp[i].info.long_info.high_bytes;
                low = cf->cp[i].info.long_info.low_bytes;

                lg = ((uint64_t) high << 32) | ((uint64_t) low);
                d = (double) lg;
                printf("%lf\n", d);
                break;
            case CONSTANT_Class:
                printf("Class\t");
                name_index = cf->cp[i].info.class_info.name_index;

                printf("%s (#%d)\n", get_cp_string(cf->cp, name_index), name_index);
                break;
            case CONSTANT_String:
                printf("String:\t");
                string_index = cf->cp[i].info.string_info.string_index;
                printf("%s (#%d)\n", get_cp_string(cf->cp, string_index), string_index);
                break;
            case CONSTANT_Fieldref:
                printf("Fieldref:\t");
                class_index = cf->cp[i].info.fieldref_info.class_index;
                name_and_type_index = cf->cp[i].info.fieldref_info.name_and_type_index;
                printf("%s.%s:%s (#%d.#%d)\n", get_class_name_string(cf->cp, class_index),
                    get_name_and_type_string(cf->cp, name_and_type_index, 1),
                    get_name_and_type_string(cf->cp, name_and_type_index, 0),
                    class_index, name_and_type_index);
                break;
            case CONSTANT_Methodref:
                printf("Methodref:\t");
                class_index = cf->cp[i].info.methodref_info.class_index;
                name_and_type_index = cf->cp[i].info.methodref_info.name_and_type_index;
                printf("%s.%s:%s (#%d.#%d)\n", get_class_name_string(cf->cp, class_index),
                    get_name_and_type_string(cf->cp, name_and_type_index, 1),
                    get_name_and_type_string(cf->cp, name_and_type_index, 0), 
                    class_index, name_and_type_index);
                break;
            case CONSTANT_InterfaceMethodref:
                printf("InterfaceMethodref\t");
                class_index = cf->cp[i].info.methodref_info.class_index;
                name_and_type_index = cf->cp[i].info.methodref_info.name_and_type_index;
                printf("%s.%s:%s (#%d.#%d)\n", get_class_name_string(cf->cp, class_index),
                    get_name_and_type_string(cf->cp, name_and_type_index, 1),
                    get_name_and_type_string(cf->cp, name_and_type_index, 0), 
                    class_index, name_and_type_index);
                break;
            case CONSTANT_NameAndType:
                printf("NameAndType:\t");
                name_index = cf->cp[i].info.nameandtype_info.name_index;
                descriptor_index = cf->cp[i].info.nameandtype_info.descriptor_index;
                printf("%s:%s (#%d:#%d)\n", get_cp_string(cf->cp, name_index),
                    get_cp_string(cf->cp, descriptor_index),
                    name_index, descriptor_index);
                break;
        }
    }
}
