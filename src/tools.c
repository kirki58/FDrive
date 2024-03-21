#include <tools.h>

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

char** compile_prefix(char* table_prefix){
    //input should be passed as "database.table"
    //there must be exactly 1 dot in the name string.
    //this means that the first and last occurances of "." in the string should be the same
    char** table_data = (char**) malloc(sizeof(char*) * 2);
    char* occ = strchr(table_prefix, '.');
    if(occ == NULL){
        printf("[ERROR]: table %s is not valid. Table names should be passed in as 'database.table'\n", table_prefix);
        exit(-1);
    }
    if(occ != strrchr(table_prefix, '.')){
        printf("[ERROR]: table %s is not valid. Table names can't contain dots\n", table_prefix);
        exit(-1);
    }

    //we validated the input, now we can tokenize and pass as parameters each token.
    char* delim = ".";
    char* dbname = strtok(table_prefix, delim);
    char* table_name = strtok(NULL, delim);
    *(table_data) = dbname;
    *(table_data + sizeof(char*)) = table_name;
    return table_data;
}