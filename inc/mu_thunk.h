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

/**
 * @file mu_thunk.h
 *
 * @brief Minimal deferrable execution unit: a thunk that carries only
 *        its function pointer.  User context must be embedded in your
 *        own struct as the first member.
 */

#ifndef _MU_THUNK_H_
#define _MU_THUNK_H_

// *****************************************************************************
// Includes

// *****************************************************************************
// C++ Compatibility

#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************
// Public types and definitions

/**
 * forward declaraton of struct _mu_thunk
 */
struct _mu_thunk;

/**
 * @brief Function signature for a thunk.
 *
 * The scheduler invokes `fn(thunk, args)`.  If you embed your `mu_thunk_t`
 * as the first field of your own struct, you can cast `thunk` back to that
 * enclosing type to access your context.
 *
 * @param thunk Pointer to the base `mu_thunk_t`, which must be at offset 0
 *              of your enclosing struct.
 * @param args  Optional arguments passed through `mu_thunk_call()`.
 */
typedef void (*mu_thunk_fn)(struct _mu_thunk *thunk, void *args);

/**
 * @brief Opaque handle for a deferrable function call.
 *
 * This struct holds only the function pointer.  User context must be stored
 * alongside in a containing struct where `mu_thunk_t` is the first member.
 */
typedef struct _mu_thunk {
    mu_thunk_fn fn; /**< Thunk function to execute */
} mu_thunk_t;

/**
 * @brief Inline initializer for a thunk.
 *
 * Does no parameter checking.  Use only when you know `thunk` and `fn`
 * are both non-NULL.
 *
 * @param thunk Pointer to the thunk instance.
 * @param fn    Function to associate with the thunk.
 * @return `thunk`
 */
static inline mu_thunk_t *_mu_thunk_init(mu_thunk_t *thunk, mu_thunk_fn fn) {
    thunk->fn = fn;
    return thunk;
}

/**
 * @brief Inline invocation of a thunk.
 *
 * Does no parameter checking.  Use only when you know `thunk` and
 * `thunk->fn` are valid.
 *
 * @param thunk Pointer to the thunk instance.
 * @param args  Optional arguments to pass through.
 */
static inline void _mu_thunk_call(mu_thunk_t *thunk, void *args) {
    thunk->fn(thunk, args);
}

/** A null thunk (fn set to NULL). */
#define MU_THUNK_NULL ((mu_thunk_t){.fn = NULL})

// *****************************************************************************
// Public declarations

/**
 * @brief Initialize a thunk.
 *
 * Must be called before scheduling or calling the thunk.
 *
 * @param thunk Pointer to your `mu_thunk_t` (must be non-NULL).
 * @param fn    Function to invoke when `mu_thunk_call()` runs.
 * @return `thunk` on success, or NULL if `thunk` or `fn` is NULL.
 */
mu_thunk_t *mu_thunk_init(mu_thunk_t *thunk, mu_thunk_fn fn);

/**
 * @brief Execute a thunk.
 *
 * Calls the stored function pointer with the thunk and provided `args`.
 * If `thunk` or `thunk->fn` is NULL, this is a no-op.
 *
 * @param thunk Pointer to the initialized `mu_thunk_t`.
 * @param args  Optional arguments to pass through.
 */
void mu_thunk_call(mu_thunk_t *thunk, void *args);

// *****************************************************************************
// End of file

#ifdef __cplusplus
}
#endif

#endif /* _MU_THUNK_H_ */
