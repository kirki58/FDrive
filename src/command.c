#include <command.h>

#define DBNAME_MAX_CHAR 64

int cmd_create_database(char* name){
    //Check "name" parameter to prevent buffer overflows.
    if(strlen(name) > DBNAME_MAX_CHAR){
        printf("[ERROR]: Database name too long, it must be max. %d characters.\n", DBNAME_MAX_CHAR);
        return -1;
    }

    char path[76];
    strcpy(path, "../database/");
    if(mkdir(strncat(path, name, DBNAME_MAX_CHAR), 0777) == -1){
        if(errno == EEXIST){
            printf("[ERROR]: Database already exists!\n");
            return -1;
        }
    }
    else{
        printf("[Success]: Database created!\n");
        return 0;
    }
}