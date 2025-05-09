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
 * @file mu_thunk.c
 * @brief Minimal thunk implementation.
 */

// *****************************************************************************
// Includes

#include "mu_thunk.h"

#include <stddef.h>
#include <stdint.h>

// *****************************************************************************
// Private types and definitions

// *****************************************************************************
// Private (static) storage

// *****************************************************************************
// Private (forward) declarations

// *****************************************************************************
// Public code

mu_thunk_t *mu_thunk_init(mu_thunk_t *thunk, mu_thunk_fn fn, void *context) {
    if (!thunk) return NULL;

    return _mu_thunk_init(thunk, fn, context);
}

void mu_thunk_call(mu_thunk_t *thunk, void *args) {
    if (thunk && thunk->fn) {
        _mu_thunk_call(thunk, args);
    }
}

// *****************************************************************************
// Private (static) code
