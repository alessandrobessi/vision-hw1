#include <stdio.h>
#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    return get_pixel(im, round(x), round(y), c);
}

image nn_resize(image im, int w, int h)
{
    image resize = make_image(w, h, im.c);

    float a_x = (float)im.w / (float)w;
    float b_x = -0.5 + 0.5 * a_x;

    float a_y = (float)im.h / (float)h;
    float b_y = -0.5 + 0.5 * a_y;

    int z, row, col;

    for (row = 0; row < resize.h; row++)
    {
        for (col = 0; col < resize.w; col++)
        {
            float x = a_x * col + b_x;
            float y = a_y * row + b_y;
            for (z = 0; z < resize.c; z++)
            {
                float val = nn_interpolate(im, x, y, z);
                set_pixel(resize, col, row, z, val);
            }
        }
    }
    return resize;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    return 0;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    return make_image(1, 1, 1);
}
