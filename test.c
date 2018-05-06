#include <stdio.h>
#include <assert.h>
#include "bmp.h"

#define WIDTH   1024L
#define HEIGHT  1024L

int
main(void)
{
    FILE *f;
    long x, y;
    static char bmp[BMP_SIZE(WIDTH, HEIGHT)];

    /* Overflow test */
    assert(bmp_size(3, 178956966) == 0x7ffffffe);
    assert(bmp_size(3, 178956967) == 0);
    assert(bmp_size(0, 1) == 0);

    bmp_init(bmp, WIDTH, HEIGHT);

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            float r = y / (float)HEIGHT;
            float g = x / (float)WIDTH;
            float b = 1.0f;
            bmp_set(bmp, x, y, bmp_encode(r, g, b));
        }
    }

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            float r = y / (float)HEIGHT;
            float g = x / (float)WIDTH;
            float b = 1.0f;
            unsigned long e = bmp_encode(r, g, b);
            unsigned long c = bmp_get(bmp, x, y);
            float er, eg, eb;
            float cr, cg, cb;
            bmp_decode(c, &cr, &cg, &cb);
            bmp_decode(e, &er, &eg, &eb);
            assert(cr == er);
            assert(cg == eg);
            assert(cb == eb);
        }
    }

    f = fopen("test.bmp", "wb");
    fwrite(bmp, sizeof(bmp), 1, f);
    fclose(f);

    return 0;
}
