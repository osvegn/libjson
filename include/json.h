/*
 * Filename: json.h
 * Path: include
 * Created Date: Wednesday, October 09th 2024, 07:06 pm
 * Author: osvegn
 *
 * Copyright (c) 2023 Json
 */

#ifndef JSON_H_
#define JSON_H_

#include <stdbool.h>

typedef unsigned int u_int;

typedef enum j_type_e {
    STRING,
    NUMBER,
    OBJECT,
    ARRAY,
    BOOLEAN,
    JNULL
} j_type;

struct j_string_s {
    char *value;
};

struct j_number_s {
    // Improvement: Store the value as a void *, know the size, and store it as binary data.
    int value;
};

struct j_object_s {
    char **names;
    struct j_value_s *values;
    u_int capacity;
    u_int count;
};

struct j_array_s {
    struct j_value_s *values;
    u_int capacity;
    u_int count;
};

struct j_boolean_s {
    bool value;
};

struct j_value_s {
    j_type type;
    union
    {
        struct j_string_s string;
        struct j_number_s number;
        struct j_object_s object;
        struct j_array_s array;
        struct j_boolean_s boolean;
    } u;
};

struct j_value_s *from_int(struct j_value_s *value, int v);
struct j_value_s *from_string(struct j_value_s *value, char *v);
struct j_value_s *from_object(struct j_value_s *value, struct j_object_s *obj);
struct j_value_s *from_array(struct j_value_s *value, struct j_array_s *arr);
struct j_value_s *from_boolean(struct j_value_s *value, bool v);

int init_object(struct j_object_s *obj, u_int size);
void destroy_object(struct j_object_s *obj);
int init_array(struct j_array_s *arr, u_int size);
void destroy_array(struct j_array_s *arr);

struct j_object_s *add_named_value(struct j_object_s *obj, char *name, struct j_value_s *value);
struct j_object_s *add_named_bool(struct j_object_s *obj, char *name, bool value);
struct j_object_s *add_named_int(struct j_object_s *obj, char *name, int value);
struct j_object_s *add_named_object(struct j_object_s *obj, char *name, struct j_object_s *value);
struct j_object_s *add_named_array(struct j_object_s *obj, char *name, struct j_array_s *value);
struct j_object_s *add_named_string(struct j_object_s *obj, char *name, char *value);

#endif