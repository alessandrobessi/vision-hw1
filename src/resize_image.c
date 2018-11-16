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
    int left = floorf(x);
    int right = ceilf(x);
    int top = floorf(y);
    int bottom = ceilf(y);

    float v1 = get_pixel(im, left, top, c);
    float v2 = get_pixel(im, right, top, c);
    float v3 = get_pixel(im, left, bottom, c);
    float v4 = get_pixel(im, right, bottom, c);

    float q1 = (bottom - y) * v1 + (y - top) * v3;
    float q2 = (bottom - y) * v2 + (y - top) * v4;

    float q = (x - left) * q2 + (right - x) * q1;

    return q;
}

image bilinear_resize(image im, int w, int h)
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
                float val = bilinear_interpolate(im, x, y, z);
                set_pixel(resize, col, row, z, val);
            }
        }
    }
    return resize;
}
