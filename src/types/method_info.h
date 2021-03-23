#include "attribute_info.h"

/**
 * @brief Method.
 *
 * Structure that stores information about a Method
 */
typedef struct {
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  attribute_info *attributes; /*n=attributes_count */
} method_info;