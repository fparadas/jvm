#include "../h/getter.h"

char *get_cp_string(cp_info *cp, u2 index) {
    assert(cp);

    cp_info *entry = &cp[index];
    assert(entry->tag == CONSTANT_Utf8);

    return (char *) entry->info.utf8_info.bytes;
}

char *get_class_name(classfile *cf) {
    uint32_t index = cf->cp[cf->this_class].info.class_info.name_index;
    return get_cp_string(cf->cp, index);
}

char *get_super_name(classfile *cf) {
    uint32_t index = cf->cp[cf->super_class].info.class_info.name_index;
    return get_cp_string(cf->cp, index);
}


char *get_class_name_string(cp_info *cp, u2 class_index) {
    assert(cp);

    cp_info *entry = &cp[class_index];
    assert(entry->tag == CONSTANT_Class);

    return get_cp_string(cp, entry->info.methodref_info.class_index);
}

char *get_name_and_type_string(cp_info *cp, u2 index, u1 flag) {
    assert(cp);

    cp_info *entry = &cp[index];
    assert(entry->tag == CONSTANT_NameAndType);

    if (flag)
        return get_cp_string(cp, entry->info.nameandtype_info.name_index);
    else
        return get_cp_string(cp, entry->info.nameandtype_info.descriptor_index);
}