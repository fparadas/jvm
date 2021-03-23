#include "attribute_info.h"

/**
* @brief Fields.
*
* Describes the structure of a field
*/
typedef struct field_info
{
    u2 access_flags;
    u2 name_index;
    u2 description_index;
    u2 attribute_count;
    attribute_info *attributes;
};