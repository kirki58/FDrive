#include <object.h>

struct object* init_object(){
    struct object *obj = (struct object*) malloc(sizeof(struct object)); // DON'T FORGET TO FREE OBJ;
    obj->fhash = NULL;
    obj->ihash = NULL;
    obj->shash = NULL;
    return obj;
}

void free_object(struct object* obj){
    if (obj->ihash != NULL){
        struct inthash *current_entry, *tmp;
        HASH_ITER(hh, obj->ihash, current_entry, tmp){
            free(obj->ihash->key);
            HASH_DEL(obj->ihash, current_entry);
            free(current_entry);
        }
    }
    if(obj->fhash != NULL){
        struct floathash *current_entry, *tmp;
        HASH_ITER(hh, obj->fhash, current_entry, tmp){
            free(obj->fhash->key);
            HASH_DEL(obj->fhash, current_entry);
            free(current_entry);
        }
    }
    if(obj->shash != NULL){
        struct strhash *current_entry, *tmp;
        HASH_ITER(hh, obj->shash, current_entry, tmp){
            free(obj->shash->key);
            free(obj->shash->value);
            HASH_DEL(obj->shash, current_entry);
            free(current_entry);
        }
    }
    free(obj->ihash);
    free(obj->fhash);
    free(obj->shash);
    free(obj);
    return;
}

void obj_add_int(struct object* obj, char* key, int value){
    struct inthash *kv = (struct inthash*) malloc(sizeof(struct inthash));
    kv->key = key;
    kv->value = value;
    HASH_ADD_KEYPTR(hh, obj->ihash, kv->key, strlen(kv->key), kv);
}
int* obj_get_int(struct object* obj, char* key){
    struct inthash *kv = NULL;
    HASH_FIND_STR(obj->ihash, key, kv);
    if (kv == NULL){
        return NULL;
    }
    return &(kv->value);
}

void obj_add_str(struct object* obj, char* key, char* value){
    struct strhash *kv = (struct strhash*) malloc(sizeof(struct strhash));
    kv->key = key;
    kv->value = value;
    HASH_ADD_KEYPTR(hh, obj->shash, kv->key, strlen(kv->key), kv);
}
char* obj_get_str(struct object* obj, char* key){
    struct strhash *kv = NULL;
    HASH_FIND_STR(obj->shash, key, kv);
    if (kv == NULL){
        return NULL;
    }
    return kv->value;
}

void obj_add_float(struct object* obj, char* key, float value){
    struct floathash *kv = (struct floathash*) malloc(sizeof(struct floathash));
    kv->key = key;
    kv->value = value;
    HASH_ADD_KEYPTR(hh, obj->fhash, kv->key, strlen(kv->key), kv);
}
float* obj_get_float(struct object* obj, char* key){
    struct floathash *kv = NULL;
    HASH_FIND_STR(obj->fhash, key, kv);
    if (kv == NULL){
        return NULL;
    }
    return &(kv->value);
}