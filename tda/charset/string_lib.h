#ifndef STRING_LIB_H
#define STRING_LIB_H

#include <stdint.h>
#include "charset.h"

char* string_get_common_chars(char strings[][MAX_CHARS], uint8_t num_strings);
void string_test();

#endif