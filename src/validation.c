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

int validate_prefix(char* db_name, char* tb_name){
    if(db_name == NULL || tb_name == NULL){
        printf("Error: Database or Table name is NULL\n");
        return -1;
    }
    chdir(DBPATH);
    DIR* db = opendir(db_name);
    if(db){
        chdir(db_name);
        closedir(db);
        FILE* tb = fopen(strncat(tb_name, ".fd", 4), "r");
        if(tb){
            fclose(tb);
            chdir("../../src");
            return 0;
        }
        else{
            printf("Error: Table %s.%s doesn't exist\n", db_name, tb_name);
            fclose(tb);
            chdir("../../src");
            return -1;
        }
    }
    else if(ENOENT == errno){
        printf("Error: Database %s doesn't exist\n", db_name);
        return -1;
    }
    else{
        printf("Error: Internal error while validating prefix\n");
        return -1;
    }
}