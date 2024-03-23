#include <validation.h>

void validate_command(int argc ,int argc_min, int argc_max){
    if(argc == argc_min){
        printf("[ERROR]: Not enough arguements for create_database!\n");
        exit(-1);
    }
    if(argc > argc_max){
        printf("[ERROR]: This command can't take this much arguements!\n");
        exit(-1);
    }
}

FILE* validate_prefix(char* prefix){
    char** pref = compile_prefix(prefix);
    char* db_name = *pref;
    char* table_name = *(pref + sizeof(char*));
    char path[256];
    strcpy(path, DBPATH);
    strncat(path, db_name, DBNAME_MAX_CHAR);
    strncat(path, "/", 2);
    strncat(path, table_name, TBNAME_MAX_CHAR);
    strncat(path, ".fd", 4);
    if(access(path, F_OK) != 0){
        printf("[ERROR]: Table %s.%s don't seem to exist!\n", db_name, table_name);
        free(pref);
        return NULL;
    }
    FILE* table = fopen(path, "a+");
    free(pref);
    return table;
}