# 24-bit BMP (Bitmap) ANSI C header library

This is an ANSI C header library for creating 24-bit BMP data. It does
not depend on the host's byte order, alignment requirements, or signed
integer represenation. It neither allocates memory nor accesses files,
which is instead left to the caller. As a result, it doesn't require the
C standard library.

This library can be compiled as if it were written in C++.

You cannot use this library to reliably manipulate bitmaps created by
other programs, even if they are 24-bit BMPs.

## API

```c
unsigned long
bmp_size(long width, long height)
```

Compute the total size in bytes required for a bitmap of the given size.
Returns 0 if the given dimensions are invalid, either due to being
non-positive or too large (overflow).

```c
#define BMP_SIZE(width, height) ...
```

This is the macro form of `bmp_size()`, suitable for use as a constant
so long as width and height are also constants. It's useful for
allocating static buffers. Unlike the function, this macro does *not* do
any sanity checks.

```c
void
bmp_init(void *buf, long width, long height)
```

Initialize the given memory buffer as a bitmap image. First use
`bmp_size()` to determine the necessary buffer size. This buffer has no
alignment requirements. At any point after the buffer is initialized it
may be written out to a file to create a BMP file (e.g. with
`fwrite()`).

No routine in this library writes to padding bytes. To avoid including
arbirary — and potentially sensitive — data in the unused bytes of your
BMP files, you should zero-initialize a buffer before initializing it as
a bitmap. Giving this function a zero-initialized buffer will create a
solid black image.

```c
void
bmp_set(void *buf, long x, long y, unsigned long color)
```

Set a specific pixel to a specific color. A color is a 24-bit integer
encoded 0xRRGGBB.

```c
unsigned long
bmp_get(const void *buf, long x, long y)
```

Retrieve a pixel color previously set with `bmp_set()`.

```c
unsigned long
bmp_encode(float r, float g, float b)
```

Encode a normalized (0.0f–1.0f) float color into a 24-bit integer color.

```c
void
bmp_decode(unsigned long c, float *r, float *g, float *b)
```

Decode a 24-bit integer color into normalized (0.0f–1.0f) floats.

## `BMP_COMPAT`

BMP files are normally written bottom-to-top. By default this library
creates BMP images that are "upside down," written top-to-bottom as is
typical in other image formats. `bmp_init()` indicates this by writing
the height as a negative value in the BMP data. However, not all BMP
readers support this feature and may not be able to open the BMP files.

To create "bottom-up" BMPs that are compatible with the most BMP
readers, define `BMP_COMPAT` before including the header. (Or with
`-DBMP_COMPAT` when compiling.)

```c
#define BMP_COMPAT
#include "bmp.h"
```

The accessor functions, `bmp_set()` and `bmp_get()`, will be *slightly*
slower when enabling this compile-time option.
