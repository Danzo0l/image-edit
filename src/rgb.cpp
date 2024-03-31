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
    int step = sizeof(RGB);
    int size = data_rgb.size() * step;
    uint8_t *data = reinterpret_cast<uint8_t *>(data_rgb.data());

    std::vector<uint8_t> a(size);

    int offset = 0;
    if (channel == 'g') {
        offset = 1;
    } else if (channel == 'r') {
        offset = 2;
    }

    for (int i = offset; i < size; i+=step) {
        a[i] = data[i];
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
