#include "BMPProcess.h"

static uint32_t compute_BMP_size(BMP &bmp) {
    return bmp.data.size();
}

BMP BMPProcess::decimation_remove() {
    BMP bmp_dec = bmp;
    bmp_dec.map.bi_height = bmp_dec.map.bi_height / 2 + (bmp_dec.map.bi_height % 2);
    bmp_dec.map.bi_width = bmp_dec.map.bi_width / 2 + (bmp_dec.map.bi_width % 2);

    bmp_dec.data.clear();

    for (size_t i = 0; i < bmp.map.bi_height; i+=2) {
        for (size_t j = i * bmp.map.bi_width * 3; j < (i+1) * bmp.map.bi_width*3; j+=2) {
            bmp_dec.data.push_back(bmp.data[j]);
        }
    }

    bmp_dec.header.bf_size = compute_BMP_size(bmp_dec);

    return bmp_dec;
}

RGB average(RGB &rgb1, RGB &rgb2, RGB &rgb3, RGB &rgb4) {
    return {
            uint8_t ((rgb1.blue + rgb2.blue + rgb3.blue + rgb4.blue) / 4),
            uint8_t ((rgb1.green + rgb2.green + rgb3.green + rgb4.green) / 4),
            uint8_t ((rgb1.red + rgb2.red + rgb3.red + rgb4.red) / 4)
    };
}

BMP BMPProcess::decimation_average() {
    BMP bmp_dec = bmp;
    bmp_dec.map.bi_height = bmp_dec.map.bi_height / 2 + (bmp_dec.map.bi_height % 2);
    bmp_dec.map.bi_width = bmp_dec.map.bi_width / 2 + (bmp_dec.map.bi_width % 2);

    bmp_dec.data.clear();

    for (size_t i = 0; i < bmp.map.bi_height; i+=2) {
        for (size_t j = i * bmp.map.bi_width * 3; j < (i+1) * bmp.map.bi_width*3; j+=2) {
            size_t jrow = j - (i * bmp.map.bi_width * 3);
            bmp_dec.data.push_back(average(bmp.data[j], bmp.data[j+1], bmp.data[jrow], bmp.data[jrow+1]));
        }
    }

    bmp_dec.header.bf_size = compute_BMP_size(bmp_dec);

    return bmp_dec;
}