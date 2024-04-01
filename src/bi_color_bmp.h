#ifndef IMAGE_EDIT_BI_COLOR_BMP_H
#define IMAGE_EDIT_BI_COLOR_BMP_H

#include "bmp.h"
#include "BMPProcess.h"

BMP bi_color_bmp_convert(const BMP& bmp, uint8_t thr)
{
    BMPProcess bmp_process = BMPProcess(bmp);
    BMP YCbCr_bmp = bmp_process.RGB24_to_YCbCr();
    for (auto & i : YCbCr_bmp.data)
    {
        if (i.red > thr) {
            i.red = 255;
            i.green = 255;
            i.blue = 255;
        } else {
            i.red = 0;
            i.green = 0;
            i.blue = 0;
        }

    }
    return YCbCr_bmp;
}


#endif //IMAGE_EDIT_BI_COLOR_BMP_H
