#ifndef VALIDATION_H
#define VALIDATION_H

#define DBPATH "../database/"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void validate_command(int argc ,int argc_min, int argc_max);
int validate_prefix(char* db_name, char* tb_name);

#endif // VALIDATION_H