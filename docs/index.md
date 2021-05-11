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

### `sar_bmat`
An unsigned byte matrix of len bytes. The type byte is a macro of unsigned char.
```C
struct saru_bytemat {
    byte  *buf;
    size_t len;
    size_t wid;
    size_t hgt;
    size_t col;
    size_t row;
};
```
#### Interface
`struct saru_bytemat *sbm_create(size_t wid, size_t hgt)`
Returns a pointer to a heap-allocated `saru_bytemat` with its buffer initialized to all zeros.

`struct saru_bytemat *sbm_wrap(byte *buf, size_t wid, size_t hgt)`
Returns a pointer to a heap-allocated 'saru_bytemat' withs its buffer set to the `buf` param.

`byte sbm_getxy(struct saru_bytemat *sbm, size_t x, size_t y)`
Returns the byte at column `x` and row `y`, if they are within bounds. Otherwise it returns `BYTE_MAX`.

`byte sbm_geti(struct saru_bytemat *sbm, size_t i)`
Returns the byte in the `i`th place, if it is within bounds. Otherwise it returns `BYTE_MAX`.

`void sbm_putxy(struct saru_bytemat *sbm, byte b, size_t x, size_t y)`
Puts byte `b` into column `x` and row `y`, if they are within bounds. 

`void sbm_sum(struct saru_bytemat *x, struct saru_bytemat *y, struct saru_bytemat *out)`
Sums two mxn matrices and stores the results in `out`.

`size_t sbm_gsum(struct saru_bytemat *sbm)`
Returns the grand sum of the elements in the matrix.

`void sbm_fill(struct saru_bytemat *sbm, byte c)`
Fills the matrix with byte `c`.

`size_t sbm_size(struct saru_bytemat *sbm)`
Returns the size of the matrix in bytes.

`int sbm_injective(struct saru_bytemat *x, struct saru_bytemat *y)`
Returns 1 if for every element in `x` there is a corresponding element in `y`. Otherwise 0.

`int sbm_subinjective(struct saru_bytemat *x, struct saru_bytemat *y)`
Returns 1 if for every element of the current submatrix ox `x` there is a corresponding element in `y`. Otherwise 0.

`size_t sbm_max(struct saru_bytemat *x)`
Returns the maximum value in the matrix. The `row` and `col` members are updated to the max's coordinates.

`void sbm_foreach(struct saru_bytemat *x, void (*func)(struct saru_bytemat *))`
Iterates through `x` calling the user-provided `func` on each element. The `row` and `col` members are update each iteration.

`void sbm_print(struct saru_bytemat *sbm)`
Prints the byte matrix.

`void sbm_destroy(struct saru_bytemat *sbm)`
Frees the byte matrix.

#### Example usage
```C
#include <string.h> /* for memcpy */

/* finds the number of ways for a 3x3 matrix to fit in a 5x3 frame */
SBM_CREATE(x, 3, 3);
SBM_CREATE(y, 5, 3);

int res = 0;
for (x->row = 0; x->row < x->hgt; x->row++)
    for (x->col = 0; x->col < x->wid; x->col++) {
        if (sbm_subinjective(x, y))
            res++;
    }

/* res is 3 */
sbm_destroy(x);
sbm_destroy(y);

/* wrap a native byte buffer and find the coordinates of the largest element */
byte *buf; /* byte is a macro for unsigned char */
buf = malloc(1024 * sizeof(byte)); /* NOTE: sizeof(byte) is optional here (it is always 1) */
memcpy(buf, (void*) memcpy, 1024 * sizeof(byte)); /* fill the buffer with random bytes just because */

SBM_WRAP(wb, buf, 32, 32); /* NOTE: 32 * 32 = 1024 */
size_t max = 0;
max = sbm_max(wb); /* wb->row and wb->col contain the max's coordinates */

sbm_destroy(wb);
```

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