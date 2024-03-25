#include <command.h>

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

int cmd_create_table(char* prefix){
    char** pref = compile_prefix(prefix);
    char* db_name = *pref;
    char* table_name = *(pref + sizeof(char*));
    if(strlen(table_name) > TBNAME_MAX_CHAR || strlen(db_name) > DBNAME_MAX_CHAR){
        printf("[ERROR]: Too long table or database name passed in as input\n");
        free(pref);
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
            free(pref);
            return -1;
        }
        FILE* table = fopen(table_name, "w");
        if(table == NULL){
            printf("[ERROR]: Internal error while creating table, please try again\n");
            free(pref);
            return -1;
        }
        fclose(table);
        free(pref);
        printf("[SUCCESS]: Table %s.%s created!\n", db_name, table_name);
        return 0;
    }
    else{
        printf("[ERROR]: Database %s don't seem to exist!\n", db_name);
        return -1;
    }
}

int cmd_create_template(char* prefix, char* props){
    FILE* table = validate_prefix(prefix);
    if(table == NULL){
        printf("[ERROR]: Internal error. Most probably table %s doesn't exist\n", prefix);
        return -1;
    }
    //check if file is empty, it should be empty because template is the first thing you write to a table
    fseek(table, 0L, SEEK_END);
    unsigned int len = (unsigned int) ftell(table);
    fseek(table, 0L, SEEK_SET);
    if(len != 0){
        printf("[ERROR]: Table is not empty! Couldn't create template.\n", prefix);
        fclose(table);
        return -1;
    }

    fprintf(table,"template=%s\n",props);
    fclose(table);
    printf("[SUCCESS]: Template written!\n");
    return 0;
}