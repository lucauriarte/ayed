#ifndef CHARSET_H
#define CHARSET_H

#include "charset_lib2.h"

charset* charset_intersection(charset* cs_1, charset* cs_2);
char* charset_tostring(charset* ch);
void charset_test();

#endif