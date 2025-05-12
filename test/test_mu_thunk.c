/**
 * MIT License
 *
 * Copyright (c) 2025 R. D. Poor & Assoc <rdpoor @ gmail.com>
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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "mu_thunk.h"
#include "unity.h"
#include <stddef.h>

// *****************************************************************************
// Private types and definitions

typedef struct {
    mu_thunk_t thunk; /**< Must be first member */
    int call_count;
} counting_thunk_t;

// Callback increments its enclosing struct’s call_count.
// Since thunk is at offset 0, we can cast directly.
static void counting_thunk_fn(mu_thunk_t *thunk, void *args) {
    (void)args;
    counting_thunk_t *counting_thunk = (counting_thunk_t *)thunk;
    counting_thunk->call_count++;
}

// Helper to initialize a counting_thunk_t
static void counting_thunk_init(counting_thunk_t *ct) {
    ct->call_count = 0;
    TEST_ASSERT_NOT_NULL(mu_thunk_init(&ct->thunk, counting_thunk_fn));
}

// thunk function to test the *args parameter
static void args_thunk_fn(mu_thunk_t *th, void *args) {
    (void)th;
    int *p = (int *)args;
    (*p)++;
}

// *****************************************************************************
// Unity boilerplate

void setUp(void) {}
void tearDown(void) {}

// *****************************************************************************
// Tests
// *****************************************************************************

// Parameter validation for mu_thunk_init()
void test_mu_thunk_init_param_validation(void) {
    counting_thunk_t ct;
    // NULL thunk pointer
    TEST_ASSERT_NULL(mu_thunk_init(NULL, counting_thunk_fn));
    // NULL function pointer
    TEST_ASSERT_NULL(mu_thunk_init(&ct.thunk, NULL));
    // Both NULL
    TEST_ASSERT_NULL(mu_thunk_init(NULL, NULL));
}

// Basic init + call behavior
void test_mu_thunk_call_executes_fn(void) {
    counting_thunk_t ct;
    counting_thunk_init(&ct);
    TEST_ASSERT_EQUAL_INT(0, ct.call_count);

    mu_thunk_call(&ct.thunk, NULL);
    TEST_ASSERT_EQUAL_INT(1, ct.call_count);

    mu_thunk_call(&ct.thunk, NULL);
    TEST_ASSERT_EQUAL_INT(2, ct.call_count);
}

// Passing an args pointer through mu_thunk_call()
void test_mu_thunk_call_with_args(void) {
    mu_thunk_t thunk;
    int arg = 0;

    TEST_ASSERT_NOT_NULL(mu_thunk_init(&thunk, args_thunk_fn));

    mu_thunk_call(&thunk, &arg);
    TEST_ASSERT_EQUAL_INT(1, arg);

    mu_thunk_call(&thunk, &arg);
    TEST_ASSERT_EQUAL_INT(2, arg);
}

// Safety: calling with NULL or uninitialized thunk does nothing
void test_mu_thunk_call_null_safety(void) {
    // No crash, no effect
    mu_thunk_call(NULL, NULL);

    mu_thunk_t t = {.fn = NULL};
    mu_thunk_call(&t, NULL);
}

// *****************************************************************************
// Test driver
// *****************************************************************************

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_mu_thunk_init_param_validation);
    RUN_TEST(test_mu_thunk_call_executes_fn);
    RUN_TEST(test_mu_thunk_call_with_args);
    RUN_TEST(test_mu_thunk_call_null_safety);

    return UNITY_END();
}
