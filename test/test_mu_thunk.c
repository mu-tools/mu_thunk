/**
 * MIT License
 *
 * Copyright (c) 2021-2025 R. D. Poor <rdpoor@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 */

/**
 * @file test_mu_thunk.c
 * @brief Unit tests for mu_thunk using Unity and FFF.
 */

// *****************************************************************************
// Includes

#include "mu_thunk.h"
#include "unity.h"
#include "fff.h"

#include <stddef.h>
#include <stdint.h>

DEFINE_FFF_GLOBALS

// *****************************************************************************
// FFF Fake Functions

FAKE_VOID_FUNC(mock_thunk_fn, mu_thunk_t *, void *);

// *****************************************************************************
// Setup & Teardown

void setUp(void) {
    RESET_FAKE(mock_thunk_fn);
}

void tearDown(void) {
}

// *****************************************************************************
// Unit Tests

/**
 * @brief Test that mu_thunk_init properly initializes a thunk.
 */
void test_mu_thunk_init_valid(void) {
    mu_thunk_t thunk;
    void *expected_context = (void*)1234;

    mu_thunk_t *result = mu_thunk_init(&thunk, mock_thunk_fn, expected_context);

    TEST_ASSERT_EQUAL_PTR(&thunk, result);
    TEST_ASSERT_EQUAL_PTR(mock_thunk_fn, thunk.fn);
    TEST_ASSERT_EQUAL_PTR(expected_context, thunk.context);
}

/**
 * @brief Test that mu_thunk_init returns NULL when given a NULL thunk pointer.
 */
void test_mu_thunk_init_null_thunk(void) {
    mu_thunk_t *result = mu_thunk_init(NULL, mock_thunk_fn, (void*)5678);

    TEST_ASSERT_NULL(result);
}

/**
 * @brief Test that mu_thunk_call calls the assigned function.
 */
void test_mu_thunk_call_calls_fn(void) {
    mu_thunk_t thunk;
    mu_thunk_init(&thunk, mock_thunk_fn, (void*)1234);

    mu_thunk_call(&thunk, (void*)5678);

    TEST_ASSERT_EQUAL(1, mock_thunk_fn_fake.call_count);
    TEST_ASSERT_EQUAL_PTR(&thunk, mock_thunk_fn_fake.arg0_val);
    TEST_ASSERT_EQUAL_PTR((void*)5678, mock_thunk_fn_fake.arg1_val);
}

/**
 * @brief Test that mu_thunk_call gracefully handles a NULL thunk pointer.
 */
void test_mu_thunk_call_null_thunk(void) {
    mu_thunk_call(NULL, NULL);

    TEST_ASSERT_EQUAL(0, mock_thunk_fn_fake.call_count);
}

/**
 * @brief Test that mu_thunk_call gracefully handles a NULL function pointer.
 */
void test_mu_thunk_call_null_fn(void) {
    mu_thunk_t thunk;
    mu_thunk_init(&thunk, NULL, (void*)1234);

    mu_thunk_call(&thunk, (void*)5678);

    TEST_ASSERT_EQUAL(0, mock_thunk_fn_fake.call_count);
}

// *****************************************************************************
// Test Runner

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_mu_thunk_init_valid);
    RUN_TEST(test_mu_thunk_init_null_thunk);
    RUN_TEST(test_mu_thunk_call_calls_fn);
    RUN_TEST(test_mu_thunk_call_null_thunk);
    RUN_TEST(test_mu_thunk_call_null_fn);

    return UNITY_END();
}
    