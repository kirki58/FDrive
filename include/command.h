#ifndef COMMAND_H
#define COMMAND_H

#include <commondef.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <tools.h>
#include <validation.h>
#include <object.h>

int cmd_create_database(char* name);
int cmd_create_table(char* prefix);
int cmd_create_template(char* prefix, char* props);
int cmd_insert(char* prefix, char* values);

#endif