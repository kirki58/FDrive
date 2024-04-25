#ifndef VALIDATION_H
#define VALIDATION_H

#include <commondef.h>

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <tools.h>

int is_datatype(char* str);

void validate_command(int argc ,int argc_min, int argc_max);
FILE* validate_prefix(char* prefix, char* mode);
int validate_template(char* props);

#endif // VALIDATION_H