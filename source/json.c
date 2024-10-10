/*
 * Filename: json.c
 * Path: source
 * Created Date: Wednesday, October 09th 2024, 07:04 pm
 * Author: osvegn
 * 
 * Copyright (c) 2024 Json
*/

#include "json.h"
#include <stdlib.h>

struct j_value_s *from_int(struct j_value_s *value, int v)
{
    value->type = NUMBER;
    value->u.number = (struct j_number_s){
        .value = v
    };
    return value;
}

struct j_value_s *from_string(struct j_value_s *value, char *v)
{
    value->type = STRING;
    value->u.string = (struct j_string_s){
        .value = v
    };
    return value;
}

struct j_value_s *from_object(struct j_value_s *value, struct j_object_s *obj)
{
    value->type = OBJECT;
    value->u.object = *obj;
    return value;
}

struct j_value_s *from_array(struct j_value_s *value, struct j_array_s *arr)
{
    value->type = ARRAY;
    value->u.array = *arr;
    return value;
}

struct j_value_s *from_boolean(struct j_value_s *value, bool v)
{
    value->type = BOOLEAN;
    value->u.boolean = (struct j_boolean_s){
        .value = v
    };
    return value;
}


int init_object(struct j_object_s *obj, u_int size)
{
    obj->capacity = size;
    obj->count = 0;
    if (size == 0) {
        obj->names = 0;
        obj->values = 0;
    } else {
        obj->names = malloc(sizeof(char *) * size);
        if (obj->names == 0)
            return -1;
        obj->values = malloc(sizeof(void *) * size);
        if (obj->values == 0)
            return -1;
    }
    return 0;
}

void destroy_object(struct j_object_s *obj)
{
    if (obj->capacity) {
        free(obj->names);
        free(obj->values);
    }
}

int init_array(struct j_array_s *arr, u_int size)
{
    arr->capacity = size;
    arr->count = 0;
    if (size == 0) {
        arr->values = 0;
    } else {
        arr->values = malloc(sizeof(char *) * size);
        if (arr->values == 0)
            return -1;
    }
    return 0;
}

void destroy_array(struct j_array_s *arr)
{
    if (arr->capacity) {
        free(arr->values);
    }
}

static int realloc_object(struct j_object_s *obj)
{
    obj->capacity++;
    obj->names = realloc(obj->names, sizeof(char *) * obj->capacity);
    if (obj->names == 0)
        return -1;
    obj->values = realloc(obj->values, sizeof(struct j_value_s) * obj->capacity);
    if (obj->values == 0)
        return -1;
    return 0;
}

static int realloc_array(struct j_array_s *arr)
{
    arr->capacity++;
    arr->values = realloc(arr->values, sizeof(struct j_value_s) * arr->capacity);
    if (arr->values == 0)
        return -1;
    return 0;
}

struct j_object_s *add_named_value(struct j_object_s *obj, char *name, struct j_value_s *value)
{
    if (obj->count >= obj->capacity) {
        if (realloc_object(obj) < 0)
            return 0;
    }
    obj->names[obj->count] = name;
    obj->values[obj->count] = *value;
    obj->count++;
    return obj;
}

struct j_object_s *add_named_bool(struct j_object_s *obj, char *name, bool value)
{
    struct j_value_s v = {0};

    from_boolean(&v, value);
    return add_named_value(obj, name, &v);
}

struct j_object_s *add_named_int(struct j_object_s *obj, char *name, int value)
{
    struct j_value_s v = {0};

    from_int(&v, value);
    return add_named_value(obj, name, &v);
}

struct j_object_s *add_named_object(struct j_object_s *obj, char *name, struct j_object_s *value)
{
    struct j_value_s v = {0};

    from_object(&v, value);
    return add_named_value(obj, name, &v);
}

struct j_object_s *add_named_array(struct j_object_s *obj, char *name, struct j_array_s *value)
{
    struct j_value_s v = {0};

    from_array(&v, value);
    return add_named_value(obj, name, &v);
}

struct j_object_s *add_named_string(struct j_object_s *obj, char *name, char *value)
{
    struct j_value_s v = {0};

    from_string(&v, value);
    return add_named_value(obj, name, &v);
}