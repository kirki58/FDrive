#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <command.h>
#include <regex.h>
#include <dirent.h>

void validate_command(int argc ,int argc_min, int argc_max);
char** compile_prefix(char* table_prefix);

#endif