#include <validation.h>

int is_datatype(char* str){
    char* dtypes[] = DTYPES;
    int res = -1;
    for (size_t i = 0; i < sizeof(dtypes) / sizeof(char*); i++){
        if(strcmp(dtypes[i], str) == 0){
            res = 0;
        }
    }
    return res;
}

void validate_command(int argc ,int argc_min, int argc_max){
    if(argc == argc_min){
        printf("[ERROR]: Not enough arguements for this command!\n");
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

int validate_template(char* props){
    char* propscopy = strdup(props);
    char* prop = strtok(propscopy, ",");
    while(prop != NULL){
        char* datatype = strstr(prop, ":"); // finds the first occurance of ':' in prop and returns the pointer to it
        datatype += sizeof(char); // moves the pointer to the next character after ':' so "datatype" doesn't actually include ':'
        if(is_datatype(datatype) != 0){
            printf("[ERROR]: Invalid datatype %s found in template!\n", datatype);
            free(propscopy);
            return -1;
        }
        prop = strtok(NULL, ","); // moves to the next property
    }
    free(propscopy);
    return 0;
}