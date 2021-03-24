#include "access.h"

std::map<u4, std::string> ACC_FLAGS_FIELD;
std::map<u4, std::string> ACC_FLAGS_METHOD;
std::map<u4, std::string> ACC_FLAGS_CLASS;
std::vector<u4> acc_flags;

std::string get_flags(std::string access_map, u4 code) {
    std::string res = "";
    for (int i = 0; i < acc_flags.size(); i ++) {
        if (acc_flags[i] && code == acc_flags[i]) {
            if(access_map == "fields") {
                res = res + ", "  + ACC_FLAGS_FIELD[code];
            } else if(access_map == "methods") {
                res = res + ", "  + ACC_FLAGS_METHOD[code];
            } else if(access_map == "class") {
                res = res + ", "  + ACC_FLAGS_CLASS[code];
            }
        }
    }
    
    return res;
}

void populate_acc_maps() {
    populate_acc_class_map();
    populate_acc_fields_map();
    populate_acc_methods_map();
    acc_flags.push_back(ACC_PUBLIC);
    acc_flags.push_back(ACC_PROTECTED);
    acc_flags.push_back(ACC_STATIC);
    acc_flags.push_back(ACC_PRIVATE);
    acc_flags.push_back(ACC_FINAL);
    acc_flags.push_back(ACC_SUPER);
    acc_flags.push_back(ACC_VOLATILE);
    acc_flags.push_back(ACC_TRANSIENT);
    acc_flags.push_back(ACC_NATIVE);
    acc_flags.push_back(ACC_INTERFACE);
    acc_flags.push_back(ACC_ABSTRACT);
    acc_flags.push_back(ACC_STRICT);
    acc_flags.push_back(ACC_SYNTHETIC);
    acc_flags.push_back(ACC_ANNOTATION);
    acc_flags.push_back(ACC_ENUM);
}

void populate_acc_class_map() {
    ACC_FLAGS_CLASS[ACC_PUBLIC] = "ACC_PUBLIC";
    ACC_FLAGS_CLASS[ACC_FINAL] = "ACC_FINAL";
    ACC_FLAGS_CLASS[ACC_SUPER] = "ACC_SUPER";
    ACC_FLAGS_CLASS[ACC_INTERFACE] = "ACC_INTERFACE";
    ACC_FLAGS_CLASS[ACC_ABSTRACT] = "ACC_ABSTRACT";
    ACC_FLAGS_CLASS[ACC_SYNTHETIC] = "ACC_SYNTHETIC";
    ACC_FLAGS_CLASS[ACC_ANNOTATION] = "ACC_ANNOTATION";
    ACC_FLAGS_CLASS[ACC_ENUM] = "ACC_ENUM";
}

void populate_acc_fields_map() {
    ACC_FLAGS_CLASS[ACC_PUBLIC] = "ACC_PUBLIC";
    ACC_FLAGS_CLASS[ACC_PRIVATE] = "ACC_PRIVATE";
    ACC_FLAGS_CLASS[ACC_PROTECTED] = "ACC_PROTECTED";
    ACC_FLAGS_CLASS[ACC_STATIC] = "ACC_STATIC";
    ACC_FLAGS_CLASS[ACC_VOLATILE] = "ACC_VOLATILE";
    ACC_FLAGS_CLASS[ACC_TRANSIENT] = "ACC_TRANSIENT";
    ACC_FLAGS_CLASS[ACC_SYNTHETIC] = "ACC_SYNTHETIC";
    ACC_FLAGS_CLASS[ACC_ENUM] = "ACC_ENUM";
}

void populate_acc_methods_map() {
    ACC_FLAGS_CLASS[ACC_PUBLIC] = "ACC_PUBLIC";
    ACC_FLAGS_CLASS[ACC_PRIVATE] = "ACC_PRIVATE";
    ACC_FLAGS_CLASS[ACC_PROTECTED] = "ACC_PROTECTED";
    ACC_FLAGS_CLASS[ACC_STATIC] = "ACC_STATIC";
    ACC_FLAGS_CLASS[ACC_FINAL] = "ACC_FINAL";
    ACC_FLAGS_CLASS[ACC_SYNCHRONIZED] = "ACC_SYNCHRONIZED";
    ACC_FLAGS_CLASS[ACC_BRIDGE] = "ACC_BRIDGE";
    ACC_FLAGS_CLASS[ACC_VARARGS] = "ACC_VARARGS";
    ACC_FLAGS_CLASS[ACC_NATIVE] = "ACC_NATIVE";
    ACC_FLAGS_CLASS[ACC_ABSTRACT] = "ACC_ABSTRACT";
    ACC_FLAGS_CLASS[ACC_STRICT] = "ACC_STRICT";
    ACC_FLAGS_CLASS[ACC_SYNTHETIC] = "ACC_SYNTHETIC";
}