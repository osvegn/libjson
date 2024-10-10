/*
 * Filename: json.c
 * Path: source
 * Created Date: Thursday, October 09th 2024, 10:34 am
 * Author: osvegn
 * 
 * Copyright (c) 2024 Json
*/

#include <criterion/criterion.h>
#include "json.h"

Test(json_init, json_init_empty)
{
    struct j_object_s obj = {0};

    init_object(&obj, 0);
    cr_assert_eq(obj.capacity, 0);
    cr_assert_eq(obj.count, 0);
    cr_assert_eq(obj.names, 0);
    cr_assert_eq(obj.values, 0);
    destroy_object(&obj);
}

Test(json_init, json_init_size_1)
{
    struct j_object_s obj = {0};

    init_object(&obj, 1);
    cr_assert_eq(obj.capacity, 1);
    cr_assert_eq(obj.count, 0);
    cr_assert_neq(obj.names, 0);
    cr_assert_neq(obj.values, 0);
    destroy_object(&obj);
}

Test(json_init, json_add_items)
{
    struct j_object_s obj = {0};

    init_object(&obj, 0);
    add_named_bool(&obj, "boolean", true);
    cr_assert_eq(obj.capacity, 1);
    cr_assert_eq(obj.count, 1);
    cr_assert_eq(obj.values[0].type, BOOLEAN);
    cr_assert_eq(obj.values[0].u.boolean.value, true);
    destroy_object(&obj);
}