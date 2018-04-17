#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "bmp.h"

int
main(void)
{
    FILE *f;
    size_t z;
    void *bmp;
    long w = 1024;
    long h = 1024;
    long x, y;

    z = bmp_size(w, h);
    bmp = calloc(z, 1);
    bmp_init(bmp, w, h);

    /* Overflow test */
    assert(bmp_size(3, 178956966) == 0x7ffffffe);
    assert(bmp_size(3, 178956967) == 0);
    assert(bmp_size(0, 1) == 0);

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            float r = y / (float)h;
            float g = x / (float)w;
            float b = 1.0f;
            bmp_set(bmp, x, y, bmp_encode(r, g, b));
        }
    }

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            float r = y / (float)h;
            float g = x / (float)w;
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
    fwrite(bmp, z, 1, f);
    fclose(f);

    free(bmp);
    return 0;
}
