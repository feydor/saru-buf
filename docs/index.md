# libsaru-buf API Documentation

## Overview
Libsaru-buf is a library of static buffer data structures and their accompanying functions. It is a part of the "saru-" family of C libraries written to provide well-tested data structures for use in my own projects.

## Overview of the folder structure
- `src` - The implementation, there is one C file for each data structure.
- `inc` - The interface, the header files which document the structures and public functions.
- `docs` - The documentation.
- `subprojects` - The dependencies, there is one Meson wrap file for each dependency.
- `test` - The unit tests, uses Unity testing framework.

## Structure reference
When feasible structures are directly copied from their relevant header file in `inc`.

### `saru_buf`
```C
struct saru_buf {
    void  **buf; /* a buffer of void pointers */
    size_t len;  /* the number of elements in buf */
};
```
#### Interface

`struct saru_buf *sb_create(size_t len)`
Returns a pointer to a new `saru_buf` structure initialized with a `buf` of `len` void pointers.
Note: Must be freed with `sb_destroy(struct saru_buf *sb)`.

`void sb_destroy(struct saru_buf *sb)`
Frees the allocated memory pointed to by `sb`.

`void sb_fill(struct saru_buf *sb, int c)`
Fills the buffer with pointers to ints containing `c`.

`void sb_memcpy(struct saru_buf *sb, void *src, size_t n, size_t typesize)`
Copies `n` elements from `src` of `typesize` bytes into the buffer.

`void sb_strcpy(struct saru_buf *sb, char *str, size_t n)`
Copies `n` characters from `str` into the buffer.

`size_t sb_len(struct saru_buf *sb)`
Returns the number of elements in the buffer.

`void sb_put(struct saru_buf *sb, void *elem, size_t i)`
Puts the `elem` pointer in the `i`th spot of the buffer.

`void *sb_get(struct saru_buf *sb, size_t i)`
Gets the pointer in the `i`th spot of the buffer.

`void sb_print(struct saru_buf *sb, void (*print)(void *))`
Runs the passed in `print` function for each element in the buffer.
Note: The `print` function recieves a pointer to an element, it must be cast to a proper datatype before use.

#### Example usage
```C
SB_CREATE(sb, 100); /* sb is a pointer to a buffer of len 100 */
char *str = "hello world";
sb_strcpy(sb, str, 12);

/* change from 'hello world' to 'jello world' */
char j = 'j';
sb_put(sb, (void *)&j, 0);
sb_print(sb, printchar); /* where printchar is a user-defined function
                          * that gets a void * to each iterative element */

sb_destroy(sb);
```
