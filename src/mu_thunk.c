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

// *****************************************************************************
// Includes

#include "mu_thunk.h"
#include <stddef.h>

// *****************************************************************************
// Private types and definitions

// (none)

// *****************************************************************************
// Private (static) storage

// (none)

// *****************************************************************************
// Private (forward) declarations

// (none)

// *****************************************************************************
// Public code

mu_thunk_t *mu_thunk_init(mu_thunk_t *thunk, mu_thunk_fn fn) {
    if (thunk == NULL || fn == NULL) {
        return NULL;
    }
    // Use the inline initializer
    return _mu_thunk_init(thunk, fn);
}

void mu_thunk_call(mu_thunk_t *thunk, void *args) {
    if (thunk == NULL || thunk->fn == NULL) {
        return;
    }
    // Use the inline call
    _mu_thunk_call(thunk, args);
}

// *****************************************************************************
// Private (static) code

// (none)

// *****************************************************************************
// End of file
