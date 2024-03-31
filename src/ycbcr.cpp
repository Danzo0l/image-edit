#include "BMPProcess.h"

BMP BMPProcess::get_cr_channel() {
    BMP blue_channel_bmp = bmp;
    for (auto & pixel : blue_channel_bmp.data) {
        pixel.green = pixel.blue;
        pixel.red = pixel.blue;
    }
    return blue_channel_bmp;
}

BMP BMPProcess::get_cb_channel() {
    BMP green_channel_bmp = bmp;
    for (auto & pixel : green_channel_bmp.data) {
        pixel.red = pixel.green;
        pixel.blue = pixel.green;
    }
    return green_channel_bmp;
}

BMP BMPProcess::get_Y_channel() {
    BMP red_channel_bmp = bmp;
    for (auto & pixel : red_channel_bmp.data) {
        pixel.green = pixel.red;
        pixel.blue = pixel.red;
    }
    return red_channel_bmp;
}


BMP BMPProcess::RGB24_to_YCbCr()
{
    BMP YCbCr_image;
    YCbCr_image.header = bmp.header;
    YCbCr_image.map = bmp.map;

    for (auto & pixel : bmp.data)
    {
        double Y = (0.299 * pixel.red) + (0.587 * pixel.blue) + (0.114 * pixel.green);
        double C_b = 0.5643 * (pixel.blue - Y) + 128;
        double C_r = 0.7132 * (pixel.red - Y) + 128;

        pixel.red = uint8_t(Y);
        pixel.green = uint8_t(C_b);
        pixel.blue = uint8_t(C_r);
    }

    return bmp;
}