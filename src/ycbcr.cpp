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