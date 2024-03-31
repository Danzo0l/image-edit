#include "BMPProcess.h"

BMPProcess::BMPProcess(const BMP& bmp_data) : bmp(bmp_data) {
    this->bmp = bmp_data;
}

BMP BMPProcess::get_blue_channel() {
    BMP blue_channel_bmp = bmp;
    for (auto & pixel : blue_channel_bmp.data) {
        pixel.green = 0;
        pixel.red = 0;
    }
    return blue_channel_bmp;
}

BMP BMPProcess::get_green_channel() {
    BMP green_channel_bmp = bmp;
    for (auto & pixel : green_channel_bmp.data) {
        pixel.red = 0;
        pixel.blue = 0;
    }
    return green_channel_bmp;
}

BMP BMPProcess::get_red_channel() {
    BMP red_channel_bmp = bmp;
    for (auto & pixel : red_channel_bmp.data) {
        pixel.green = 0;
        pixel.blue = 0;
    }
    return red_channel_bmp;
}