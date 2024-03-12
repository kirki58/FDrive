#ifndef COMMAND_H
#define COMMAND_H

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int cmd_create_database(char* name);
int cmd_create_table(char* db_name, char* table_name);

#endif