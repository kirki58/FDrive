#include <stdio.h>
#include <command.h>
#include <stdlib.h>
#include <string.h>
#include <tools.h>

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
            char** prefix = compile_prefix(argv[2]);
            cmd_create_table((*prefix), *(prefix+sizeof(char*) ) );
            free(prefix);
            return 0;
        }

        else{
            printf("No such command is found!\n");
            return -1;
        }
    }
}