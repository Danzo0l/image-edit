#include "BMPProcess.h"

BMPProcess::BMPProcess(const BMP& bmp_data) : bmp(bmp_data) {
    this->bmp = bmp_data;
}

BMP BMPProcess::get_blue_channel() {
    BMP blue_channel_bmp = bmp;
    for (size_t i = 0; i < bmp.data.size(); i+=3) {
        bmp.data[i] = 0;
    }
    return blue_channel_bmp;
}

BMP BMPProcess::get_green_channel() {
    BMP blue_channel_bmp = bmp;
    for (size_t i = 1; i < bmp.data.size(); i+=3) {
        bmp.data[i] = 0;
    }
    return blue_channel_bmp;
}

BMP BMPProcess::get_red_channel() {
    BMP blue_channel_bmp = bmp;
    for (size_t i = 3; i < bmp.data.size(); i+=3) {
        bmp.data[i] = 0;
    }
    return blue_channel_bmp;
}
