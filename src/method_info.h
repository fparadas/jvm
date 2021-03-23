#pragma once
#include "utils.h";
#include "attribute_info.h"

/**
* @brief Method info.
*
* Describes each method, including instance initialization method or the 
* interface initialization method.
*/
typedef struct {
    u2 access_flags;
    u2 name_index;
    u2 description_index;
    u2 attributes_count;
    attribute_info* attributes; //size = attributes_count
} method_info;