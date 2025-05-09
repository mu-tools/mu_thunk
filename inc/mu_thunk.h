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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 */

/**
 * @file mu_thunk.h
 * @brief Minimal implementation for deferrable function execution.
 */

#ifndef _MU_THUNK_H_
#define _MU_THUNK_H_

// *****************************************************************************
// Includes

#include <stdint.h>
#include <stdbool.h>

// *****************************************************************************
// C++ Compatibility

#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************
// Public types and definitions

/**
 * @struct mu_thunk_t
 * @brief Represents a minimal deferred execution unit.
 *
 * Contains only a function pointer and a user-supplied context.
 */
typedef struct _mu_thunk mu_thunk_t;

/**
 * @brief Function signature for a thunk.
 *
 * The function is executed with its associated thunk instance and optional arguments.
 *
 * @param[in] thunk Pointer to the thunk instance.
 * @param[in] args  Optional arguments for execution.
 */
typedef void (*mu_thunk_fn)(mu_thunk_t *thunk, void *args);

/**
 * @struct mu_thunk_t
 * @brief Minimal thunk structure for deferred execution.
 */
struct _mu_thunk {
    mu_thunk_fn fn;   /**< Function to execute */
    void *context;    /**< User-defined execution context */
};

/**
 * @brief Initializes a thunk inline.
 *
 * This variant does not perform argument checking—call only from safe contexts.
 *
 * @param[in] thunk   Pointer to the thunk instance.
 * @param[in] fn      Function to associate with the thunk.
 * @param[in] context User-defined context for execution.
 * @return Pointer to the initialized thunk.
 */
static inline mu_thunk_t *_mu_thunk_init(mu_thunk_t *thunk, mu_thunk_fn fn, void *context) {
    thunk->fn = fn;
    thunk->context = context;
    return thunk;
}

/**
 * @brief Executes a thunk inline.
 *
 * This variant does not perform argument checking—call only from safe contexts.
 *
 * @param[in] thunk Pointer to the thunk instance.
 * @param[in] args  Optional arguments for execution.
 */
static inline void _mu_thunk_call(mu_thunk_t *thunk, void *args) {
    thunk->fn(thunk, args);
}

#define MU_THUNK_NULL ((mu_thunk_t){.fn=NULL, .context=NULL})

// *****************************************************************************
// Public declarations

/**
 * @brief Initializes a thunk.
 *
 * Assigns a function pointer and a context to the thunk instance, returning the initialized thunk.
 *
 * @param[in] thunk   Pointer to the thunk instance to initialize.
 * @param[in] fn      Function to associate with the thunk.
 * @param[in] context User-defined context for execution.
 * @return Pointer to the initialized thunk, or NULL if invalid.
 */
mu_thunk_t *mu_thunk_init(mu_thunk_t *thunk, mu_thunk_fn fn, void *context);

/**
 * @brief Executes a thunk.
 *
 * Calls the stored function pointer with its associated context and optional arguments.
 *
 * @param[in] thunk Pointer to the thunk instance.
 * @param[in] args  Optional arguments for execution.
 */
void mu_thunk_call(mu_thunk_t *thunk, void *args);

// *****************************************************************************
// End of file

#ifdef __cplusplus
}
#endif

#endif /* _MU_THUNK_H_ */
