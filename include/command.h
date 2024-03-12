#ifndef COMMAND_H
#define COMMAND_H

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int cmd_create_database(char* name);
void initialize_commands();

#endif