#include "BMPProcess.h"

BMPProcess::BMPProcess(const BMP& bmp_data) : bmp(bmp_data) {
    this->bmp = bmp_data;
}

BMP BMPProcess::bmp_blue_channel() {
    BMP blue_channel_bmp = bmp;
    for (auto & pixel : blue_channel_bmp.data) {
        pixel.green = 0;
        pixel.red = 0;
    }
    return blue_channel_bmp;
}

BMP BMPProcess::bmp_green_channel() {
    BMP green_channel_bmp = bmp;
    for (auto & pixel : green_channel_bmp.data) {
        pixel.red = 0;
        pixel.blue = 0;
    }
    return green_channel_bmp;
}

BMP BMPProcess::bmp_red_channel() {
    BMP red_channel_bmp = bmp;
    for (auto & pixel : red_channel_bmp.data) {
        pixel.green = 0;
        pixel.blue = 0;
    }
    return red_channel_bmp;
}

std::vector<uint8_t> RGB_pixels_channel(std::vector<RGB> &data_rgb, char channel) {
    int size = data_rgb.size();

    std::vector<uint8_t> a(size);

    for (int i = 0; i < size; ++i) {
        if (channel == 'r') {
            a[i] = data_rgb[i].red;
        } else if (channel == 'g') {
            a[i] = data_rgb[i].green;
        } else if (channel == 'b') {
            a[i] = data_rgb[i].blue;
        }
    }
    return a;
}

std::vector<uint8_t> BMPProcess::pixels_red_channel() {
    return RGB_pixels_channel(bmp.data, 'r');
}

std::vector<uint8_t> BMPProcess::pixels_green_channel() {
    return RGB_pixels_channel(bmp.data, 'g');
}

std::vector<uint8_t> BMPProcess::pixels_blue_channel() {
    return RGB_pixels_channel(bmp.data, 'b');
}
