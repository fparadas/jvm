#pragma once
#include "utils.h"
#include "types/dotclass.h"
#include <stdio.h>
#include <stdlib.h>
#include "getter.h"
#include <string.h>

/**
 * @brief Print constant pool detail.
 * @param cp_count size of the constant pool
 * @param cp array structure that stores cp_info
 */
void print_cp_info(u2 cp_count, cp_info cp[]);
