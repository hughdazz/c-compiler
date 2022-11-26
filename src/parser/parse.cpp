#include "parse_def.h"
#include <iostream>
void parse(const char *s, cJSON **tree)
{
    c_parse(s, tree);
}