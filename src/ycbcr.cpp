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

static inline double pixel_Y(uint8_t r, uint8_t g, uint8_t b) {
    return (0.299 * r) + (0.587 * b) + (0.114 * g);
}

static inline double pixel_cb(uint8_t blue, double Y) {
    return 0.5643 * (blue - Y) + 128;
}

static inline double pixel_cr(uint8_t red, double Y) {
    return 0.7132 * (red - Y) + 128;
}

BMP BMPProcess::RGB24_to_YCbCr()
{
    BMP YCbCr_image;
    YCbCr_image.header = bmp.header;
    YCbCr_image.map = bmp.map;

    for (auto & pixel : bmp.data)
    {
        double Y = pixel_Y(pixel.red, pixel.green, pixel.blue);

        pixel.red = uint8_t(Y);
        pixel.green = uint8_t(pixel_cb(pixel.blue, Y));
        pixel.blue = uint8_t(pixel_cr(pixel.red, Y));
    }

    return bmp;
}

BMP BMPProcess::YCbCr_to_RGB24()
{
    BMP YCbCr_image;
    YCbCr_image.header = bmp.header;
    YCbCr_image.map = bmp.map;

    for (auto & pixel : bmp.data)
    {
        double R = pixel.red - 0.714 * (pixel.blue - 128) - 0.334 * (pixel.green - 128);
        double G = pixel.red + 1.402 * (pixel.blue - 128);
        double B = pixel.red + 1.772 * (pixel.green - 128);

        pixel.green = uint8_t(R);
        pixel.red = uint8_t(G);
        pixel.blue = uint8_t(B);
    }

    return bmp;
}

double BMPProcess::PSNR(char channel, const std::string& original_path)
{
    BMP original_image = load_bmp_image(original_path);
    double summ = 0;

    for (int i = 0; i < bmp.map.bi_height; ++i) {
        for (int j = 0; j < bmp.map.bi_width; ++j) {
            if (channel == 'r') {
                summ += pow((original_image.data[i * bmp.map.bi_width + j].red - bmp.data[i * bmp.map.bi_width + j].red), 2);
            } else if (channel == 'g') {
                summ += pow((original_image.data[i * bmp.map.bi_width + j].green - bmp.data[i * bmp.map.bi_width + j].green), 2);
            } else if (channel == 'b') {
                summ += pow((original_image.data[i * bmp.map.bi_width + j].blue - bmp.data[i * bmp.map.bi_width + j].blue), 2);
            }

        }
    }
    double PSNR_value = 10 * log10((bmp.map.bi_width * bmp.map.bi_height * pow(2, 24)) / summ);

    return PSNR_value;
}

static std::vector<uint8_t> YCbCr_pixels_channel(std::vector<RGB> &data_rgb, char channel) {
    int size = data_rgb.size();

    std::vector<uint8_t> a(size);

    for (int i = 0; i < size; ++i) {
        if (channel == 'Y') {
            a[i] = data_rgb[i].red;
        } else if (channel == 'Cb') {
            a[i] = data_rgb[i].green;
        } else if (channel == 'b') {
            a[i] = data_rgb[i].blue;
        }
    }
    return a;
}

std::vector<uint8_t> BMPProcess::pixels_Y_channel() {
    size_t size = bmp.data.size();
    std::vector<uint8_t> a(size);

    for (size_t i = 0; i < size; ++i) {
        auto &rgb = bmp.data[i];
        a[i] = (uint8_t) pixel_Y(rgb.red, rgb.green, rgb.blue);
    }
    return a;
}

std::vector<uint8_t> BMPProcess::pixels_cb_channel() {
    size_t size = bmp.data.size();
    std::vector<uint8_t> a(size);

    for (size_t i = 0; i < size; ++i) {
        auto &rgb = bmp.data[i];
        double y = pixel_Y(rgb.red, rgb.green, rgb.blue);
        a[i] = (uint8_t) pixel_cb(rgb.blue, y);
    }
    return a;
}

std::vector<uint8_t> BMPProcess::pixels_cr_channel() {
    size_t size = bmp.data.size();
    std::vector<uint8_t> a(size);

    for (size_t i = 0; i < size; ++i) {
        auto &rgb = bmp.data[i];
        double y = pixel_Y(rgb.red, rgb.green, rgb.blue);
        a[i] = (uint8_t) pixel_cr(rgb.red, y);
    }
    return a;
}
