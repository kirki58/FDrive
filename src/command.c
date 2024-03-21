#include <command.h>

#define DBNAME_MAX_CHAR 64
#define TBNAME_MAX_CHAR 64
#define DBPATH "../database/"

char* datatypes[] = {"int", "float", "str"};

int cmd_create_database(char* name){
    //Check "name" parameter to prevent buffer overflows.
    if(strlen(name) > DBNAME_MAX_CHAR){
        printf("[ERROR]: Database name too long, it must be max. %d characters.\n", DBNAME_MAX_CHAR);
        return -1;
    }

    char path[76];
    strcpy(path, DBPATH);
    if(mkdir(strncat(path, name, DBNAME_MAX_CHAR), 0777) == -1){
        if(errno == EEXIST){
            printf("[ERROR]: Database already exists!\n");
            return -1;
        }
    }
    else{
        printf("[Success]: Database created.\n");
        return 0;
    }
}

int cmd_create_table(char* db_name, char* table_name){
    if(strlen(table_name) > TBNAME_MAX_CHAR || strlen(db_name) > DBNAME_MAX_CHAR){
        printf("[ERROR]: Too long table or database name passed in as input\n");
        return -1;
    }
    char path[76];
    strcpy(path, DBPATH);
    strncat(path, db_name, DBNAME_MAX_CHAR);

    if(access(path, F_OK) == 0){
        chdir(path);
        if(access(strncat(table_name, ".fd", 4), F_OK) == 0){
            printf("[ERROR]: Table %s.%s already exists!\n", db_name, table_name);
            chdir("../../src");
            return -1;
        }
        FILE* table = fopen(table_name, "w");
        if(table == NULL){
            printf("[ERROR]: Internal error while creating table, please try again\n");
            return -1;
        }
        fclose(table);
        printf("[SUCCESS]: Table %s.%s created!", db_name, table_name);
        return 0;
    }
    else{
        printf("[ERROR]: Database %s don't seem to exist!\n", db_name);
        return -1;
    }
}

int cmd_create_template(char* db_name, char* table_name, char* props){
    chdir(DBPATH);
    chdir(db_name);

    char filename[TBNAME_MAX_CHAR + 4];
    strcpy(filename, table_name);
    strncat(filename, ".fd", 4);

    FILE* table = fopen(filename, "w");
    if(table == NULL){
        printf("[ERROR]: Internal error while creating template!");
        return -1;
    }
    fprintf(table,"template=%s",props);
    fclose(table);
    printf("[SUCCESS]: Template written!\n");
    return 0;
}