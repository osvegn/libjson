/*
 * Filename: json_add.c
 * Path: tests
 * Created Date: Thursday, October 10th 2024, 03:41 pm
 * Author: osvegn
 * 
 * Copyright (c) 2024 Json
*/

#include <criterion/criterion.h>
#include "json.h"

Test(json_add, json_add_boolean)
{
    struct j_object_s obj = {0};

    init_object(&obj, 0);
    add_named_bool(&obj, "boolean", true);
    cr_assert_eq(obj.capacity, 1);
    cr_assert_eq(obj.count, 1);
    cr_assert_eq(obj.values[0].type, BOOLEAN);
    cr_assert_eq(obj.values[0].u.boolean.value, true);
    cr_assert_str_eq(obj.names[0], "boolean");
    destroy_object(&obj);
}

Test(json_add, json_add_string)
{
    struct j_object_s obj = {0};

    init_object(&obj, 0);
    add_named_string(&obj, "string", "value");
    cr_assert_eq(obj.capacity, 1);
    cr_assert_eq(obj.count, 1);
    cr_assert_eq(obj.values[0].type, STRING);
    cr_assert_str_eq(obj.values[0].u.string.value, "value");
    cr_assert_str_eq(obj.names[0], "string");
    destroy_object(&obj);
}

Test(json_add, json_add_int)
{
    struct j_object_s obj = {0};

    init_object(&obj, 0);
    add_named_int(&obj, "int", 152);
    cr_assert_eq(obj.capacity, 1);
    cr_assert_eq(obj.count, 1);
    cr_assert_eq(obj.values[0].type, NUMBER);
    cr_assert_eq(obj.values[0].u.number.value, 152);
    cr_assert_str_eq(obj.names[0], "int");
    destroy_object(&obj);
}
