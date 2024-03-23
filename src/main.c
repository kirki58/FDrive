#include <stdio.h>
#include <command.h>
#include <stdlib.h>
#include <string.h>
#include <tools.h>
#include <validation.h>

char* dtypes[] = {"int", "float", "str"};

int is_datatype(char* str){
    int res = -1;
    for (size_t i = 0; i < sizeof(dtypes) / sizeof(char*); i++){
        if(strcmp(dtypes[i], str) == 0){
            res = 0;
        }
    }
    return res;
}

int main(int argc, char* argv[]){
    if(argc ==  1){
        //No Command-Line Arguements passed
        return -1;
    }
    if(argc >= 2){
        //At least 1 Command-Line Arguement is passed

        //validate and run create_database command
        if(strcmp(argv[1], "create_database") == 0){
            validate_command(argc, 2, 3);
            cmd_create_database(argv[2]);
            return 0;
        }
        //validate and run create_table command
        if(strcmp(argv[1], "create_table") == 0){
            validate_command(argc, 2, 3);
            cmd_create_table(argv[2]);
            return 0;
        }

        //validate and run create_template command
        if(strcmp(argv[1], "create_template") == 0){
            validate_command(argc, 2, 4);
            cmd_create_template(argv[2], argv[3]);
            return 0;
        }
        else{
            printf("No such command is found!\n");
            return -1;
        }
    }
}