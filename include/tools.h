#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <command.h>
#include <object.h>
#include <commondef.h>
#include <regex.h>

char** compile_prefix(char* table_prefix);
int check_regex(char* str, const char* pattern);
int get_prop_dtype(char* prop);
struct object* parse_props(char* props);
int write_buffer(char* prefix,void* buffer, size_t size);

#endif