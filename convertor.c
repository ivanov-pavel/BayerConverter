#include "convertor.h"

uint8_t *BayerRg8ToRgb(uint16_t width, uint16_t height, uint8_t *data, bool flipped)
{
    if (data == NULL)
        return NULL;

    uint32_t size = width * height * 3;
    uint8_t *rgb = (uint8_t *)calloc(size, 1);
    uint8_t *ptr = &rgb[0];
    uint8_t *src = data;
    uint8_t *dst = !flipped ? ptr : ptr + size - 3;
    for (uint16_t h = 0; h < height; h++)
    {
        bool rg = h % 2 == 0;
        bool sh = h == 0;
        bool eh = h == height - 1;
        for (uint16_t w = 0; w < width; w++)
        {
            bool sw = w == 0;
            bool ew = w == width - 1;
            bool ev = w % 2 == 0;
            // rg
            if (rg)
            {
                // r
                if (ev)
                {
                    // r
                    *dst = *src;
                    dst++;

                    // g
                    if (sw)
                    {
                        if (sh)
                            *dst = (uint8_t)((*(src + 1) + *(src + width)) / 2);
                        else if (eh)
                            *dst = (uint8_t)((*(src + 1) + *(src - width)) / 2);
                        else
                            *dst = (uint8_t)((*(src + 1) + *(src - width) + *(src + width)) / 3);
                    }
                    else if (ew)
                    {
                        if (sh)
                            *dst = (uint8_t)((*(src - 1) + *(src + width)) / 2);
                        else if (eh)
                            *dst = (uint8_t)((*(src - 1) + *(src - width)) / 2);
                        else
                            *dst = (uint8_t)((*(src - 1) + *(src - width) + *(src + width)) / 3);
                    }
                    else
                    {
                        if (sh)
                            *dst = (uint8_t)((*(src - 1) + *(src + 1) + *(src + width)) / 3);
                        else if (eh)
                            *dst = (uint8_t)((*(src - 1) + *(src + 1) + *(src - width)) / 3);
                        else
                            *dst = (uint8_t)((*(src - 1) + *(src + 1) + *(src - width) + *(src + width)) / 4);
                    }

                    dst++;

                    // b
                    if (sw)
                    {
                        if (sh)
                            *dst = *(src + 1 + width);
                        else if (eh)
                            *dst = *(src + 1 - width);
                        else
                            *dst = (uint8_t)((*(src + 1 - width) + *(src + 1 + width)) / 2);
                    }
                    else if (ew)
                    {
                        if (sh)
                            *dst = *(src - 1 + width);
                        else if (eh)
                            *dst = *(src - 1 - width);
                        else
                            *dst = (uint8_t)((*(src - 1 - width) + *(src - 1 + width)) / 2);
                    }
                    else
                    {
                        if (sh)
                            *dst = (uint8_t)((*(src - 1 + width) + *(src + 1 + width)) / 2);
                        else if (eh)
                            *dst = (uint8_t)((*(src - 1 - width) + *(src + 1 - width)) / 2);
                        else
                            *dst = (uint8_t)((*(src - 1 - width) + *(src + 1 - width) + *(src - 1 + width) + *(src + 1 + width)) / 4);
                    }

                    dst++;
                }
                // g
                else
                {
                    // r
                    if (sw)
                        *dst = *(src + 1);
                    else if (ew)
                        *dst = *(src - 1);
                    else
                        *dst = (uint8_t)((*(src - 1) + *(src + 1)) / 2);
                    dst++;

                    // g
                    *dst = *src;
                    dst++;

                    // b
                    if (sh)
                        *dst = *(src + width);
                    else if (eh)
                        *dst = *(src - width);
                    else
                        *dst = (uint8_t)((*(src - width) + *(src + width)) / 2);
                    dst++;
                }
            }
            // gb
            else
            {
                // g
                if (ev)
                {
                    // r
                    if (sh)
                        *dst = *(src + width);
                    else if (eh)
                        *dst = *(src - width);
                    else
                        *dst = (uint8_t)((*(src - width) + *(src + width)) / 2);
                    dst++;

                    // g
                    *dst = *src;
                    dst++;

                    // b
                    if (sw)
                        *dst = *(src + 1);
                    else if (ew)
                        *dst = *(src - 1);
                    else
                        *dst = (uint8_t)((*(src - 1) + *(src + 1)) / 2);
                    dst++;
                }
                // b
                else
                {
                    // r
                    if (sw)
                    {
                        if (sh)
                            *dst = *(src + 1 + width);
                        else if (eh)
                            *dst = *(src + 1 - width);
                        else
                            *dst = (uint8_t)((*(src + 1 - width) + *(src + 1 + width)) / 2);
                    }
                    else if (ew)
                    {
                        if (sh)
                            *dst = *(src - 1 + width);
                        else if (eh)
                            *dst = *(src - 1 - width);
                        else
                            *dst = (uint8_t)((*(src - 1 - width) + *(src - 1 + width)) / 2);
                    }
                    else
                    {
                        if (sh)
                            *dst = (uint8_t)((*(src - 1 + width) + *(src + 1 + width)) / 2);
                        else if (eh)
                            *dst = (uint8_t)((*(src - 1 - width) + *(src + 1 - width)) / 2);
                        else
                            *dst = (uint8_t)((*(src - 1 - width) + *(src + 1 - width) + *(src - 1 + width) + *(src + 1 + width)) / 4);
                    }

                    dst++;

                    // g
                    if (sw)
                    {
                        if (sh)
                            *dst = (uint8_t)((*(src + 1) + *(src + width)) / 2);
                        else if (eh)
                            *dst = (uint8_t)((*(src + 1) + *(src - width)) / 2);
                        else
                            *dst = (uint8_t)((*(src + 1) + *(src - width) + *(src + width)) / 3);
                    }
                    else if (ew)
                    {
                        if (sh)
                            *dst = (uint8_t)((*(src - 1) + *(src + width)) / 2);
                        else if (eh)
                            *dst = (uint8_t)((*(src - 1) + *(src - width)) / 2);
                        else
                            *dst = (uint8_t)((*(src - 1) + *(src - width) + *(src + width)) / 3);
                    }
                    else
                    {
                        if (sh)
                            *dst = (uint8_t)((*(src - 1) + *(src + 1) + *(src + width)) / 3);
                        else if (eh)
                            *dst = (uint8_t)((*(src - 1) + *(src + 1) + *(src - width)) / 3);
                        else
                            *dst = (uint8_t)((*(src - 1) + *(src + 1) + *(src - width) + *(src + width)) / 4);
                    }

                    dst++;

                    // b.
                    *dst = *src;
                    dst++;
                }
            }

            src++;
            if (flipped)
                dst -= 6;
        }
    }

    return rgb;
}

void FreeRgbMemory(uint8_t *data)
{
    free(data);
}
