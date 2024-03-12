#include <stdio.h>
#include <command.h>
int main(int argc, char* argv[]){
    if(argc ==  1){
        //No Command-Line Arguements passed
        return -1;
    }
    if(argc >= 2){
        //At least 1 Command-Line Arguement is passed
        if(strcmp(argv[1], "create_database") == 0){
            if (argc == 2){
                printf("[ERROR]: Not enough arguements for create_database!\n");
                return -1;
            }
            if(argc > 3){
                printf("[ERROR]: create_database can't take this much arguements!\n");
                return -1;
            }
            cmd_create_database(argv[2]);
            return 0;
        }
        else{
            printf("No such command is found!");
            return -1;
        }
    }
}