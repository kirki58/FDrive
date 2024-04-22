#include <stdio.h>
#include <command.h>
#include <stdlib.h>
#include <string.h>
#include <tools.h>
#include <validation.h>

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
            if(validate_template(argv[3]) != 0){
                return -1;
            }
            cmd_create_template(argv[2], argv[3]);
            return 0;
        }

        if(strcmp(argv[1], "test") == 0){
            struct object* obj = parse_props("prop1:16,prop2:12.0,prop3:\"string\"");
            printf("prop2: %f\n", *(obj_get_float(obj, "prop2")));
            printf("prop3: %s\n", obj_get_str(obj, "prop3"));
            printf("prop1: %d\n", *(obj_get_int(obj, "prop1")));
            free_object(obj);
            return 0;
        }

        else{
            printf("No such command is found!\n");
            return -1;
        }
    }
}