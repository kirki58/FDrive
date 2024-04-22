#include <tools.h>

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
int check_regex(char* str, const char* pattern){
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return -1; // Compilation failed
    }

    // Execute the regular expression
    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex); // Don't forget to free the regex
    if (!reti) {
        return 0; // Match found
    } else if (reti == REG_NOMATCH) {
        return 1; // No match
    } else {
        return -1; // Some error occurred
    }
}
int get_prop_dtype(char* prop){
    // this function takes in a prop in form of "prop1:16"
    // in this case it should return 0 since 16 is an integer
    // 0 represents integer , 1 represents float, 2 represents string -1 represents error
    char* propcpy = (char*) malloc(strlen(prop) + 1);
    strcpy(propcpy, prop);
    propcpy[strlen(prop)] = '\0';
    char *token = strchr(propcpy, ':');
    token++;
    
    if( token[0] != '0' && (check_regex(token, "^-?[0-9]+\\.[0-9]+$") == 0)){
        free(propcpy);
        return 1;
    }
    else if(token[0] != '0'&& (check_regex(token, "-?[0-9]+$") == 0)){
        free(propcpy);
        return 0;
    }
    else if(check_regex(token, "^\"[^\"]*\"$") == 0){
        free(propcpy);
        return 2;
    }
    else{
        return -1;
    }
}

struct object* parse_props(char* props){
    // this function takes in "props" string as parameter in form of "prop1:16,prop2:16.0,prop3:"string"
    // it should return a struct object* with the properties set as the input string
    char propscpy[strlen(props) + 1];
    strcpy(propscpy, props);
    propscpy[strlen(props)] = '\0';
    char* token = strtok(propscpy, ",");
    struct object* obj = init_object();
    while(token != NULL){
        char* value = strchr(token, ':');
        int pos = value - token;
        value++;
        char* key = malloc(pos + 1);
        strncpy(key, token, pos);
        key[pos] = '\0';

        int dtype = get_prop_dtype(token);
        switch(dtype){
            case -1:
                printf("[ERROR]: Invalid data type for property %s\n", key);
                exit(-1);
                break;
            case 0:
                obj_add_int(obj, key, atoi(value));
                break;
            case 1:
                obj_add_float(obj, key, atof(value));
                break;
            case 2:
                obj_add_str(obj, key, value);
                break;
            default:
                break;
        }
        token = strtok(NULL, ",");
    }
    return obj;
}