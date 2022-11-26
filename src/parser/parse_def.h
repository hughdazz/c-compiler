#ifndef PARSE_DEF_H
#define PARSE_DEF_H

#include "../../deps/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" int c_parse(const char *s, cJSON** syntax_tree);
#else
int c_parse(const char *s, cJSON** syntax_tree);
#endif
void parse(const char *s, cJSON **tree);
#endif