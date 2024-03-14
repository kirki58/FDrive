#include <stdio.h>
#include <command.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char* argv[]){
    if(argc ==  1){
        //No Command-Line Arguements passed
        return -1;
    }
    if(argc >= 2){
        //At least 1 Command-Line Arguement is passed

        //validate create_database command
        if(strcmp(argv[1], "create_database") == 0){
            validate_command(argc, 2, 3);
            cmd_create_database(argv[2]);
            return 0;
        }

        //validate create_table command
        if(strcmp(argv[1], "create_table") == 0){
            validate_command(argc, 2, 3);
            //input should be passed as "database.table"
            //there must be exactly 1 dot in the name string.
            //this means that the first and last occurances of "." in the string should be the same
            char* occ = strchr(argv[2], '.');
            if(occ == NULL){
                printf("[ERROR]: table %s not found. Table names should be passed in as 'database.table'\n", argv[2]);
                return -1;
            }
            if(occ != strrchr(argv[2], '.')){
                printf("[ERROR]: table %s not found. Table names can't contain dots\n", argv[2]);
                return -1;
            }

            //we validated the input, now we can tokenize and pass as parameters each token.
            char* delim = ".";
            char* dbname = strtok(argv[2], delim);
            char* table_name = strtok(NULL, delim);
            cmd_create_table(dbname, table_name);
            return 0;
        }

        else{
            printf("No such command is found!\n");
            return -1;
        }
    }
}