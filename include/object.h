#ifndef OBJECT_H
#define OBJECT_H

#include <uthash.h>
#include <unistd.h>
#include <string.h>

struct inthash{
    char* key;
    int value;
    UT_hash_handle hh;
};
struct strhash{
    char* key;
    char* value;
    UT_hash_handle hh;
};
struct floathash{
    char* key;
    float value;
    UT_hash_handle hh;
};
struct object{
    struct inthash *ihash;
    struct strhash *shash;
    struct floathash *fhash;
};

struct object* init_object();

void obj_add_int(struct object* obj ,char* key, int value);
int* obj_get_int(struct object* obj, char* key);

void obj_add_str(struct object* obj, char* key, char* value);
char* obj_get_str(struct object* obj, char* key);

void obj_add_float(struct object* obj, char* key, float value);
float* obj_get_float(struct object* obj, char* key);

#endif