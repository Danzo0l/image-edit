#include "BMPProcess.h"

static uint8_t clipping(uint32_t value){
    if (value < 0) return 0;
    if (value > UCHAR_MAX) return UCHAR_MAX;
    return (uint8_t) value;
}

BMP BMPProcess::decimation_remove2() {
    BMP bmp_dec = BMPProcess(bmp).BMP_RGB24_to_YCbCr();

    int32_t H = bmp_dec.map.bi_height, W = bmp_dec.map.bi_width;
    auto &data = bmp_dec.data;
    int32_t size = data.size();
    std::vector<RGB> res = data;

    // red - Y, green - Cb, blue - Cr

    for (int i = H - 1; i >= 0; i--){
        for (int j = W - 1; j >= 0; j--){
            // Берем всю нижнюю строчку
            if (i % 2 == 0){
                res[(i * W + j) % size] = data[((i + 1) * W + j) % size];
                res[i].red = data[i].red;
                continue;
            }
            // Берем слева
            if (j % 2 == 0){
                res[(i * W + j) % size] = data[(i * W + j + 1) % size];
                res[i].red = data[i].red;
                continue;
            }
            res[(i * W + j) % size] = data[(i * W + j) % size];
            res[i].red = data[i].red;
        }
    }

    bmp_dec.data.swap(res);

    return BMPProcess(bmp_dec).BMP_YCbCr_to_RGB24();
}

BMP BMPProcess::decimation_average2() {
    BMP bmp_dec = BMPProcess(bmp).BMP_RGB24_to_YCbCr();

    int32_t H = bmp_dec.map.bi_height, W = bmp_dec.map.bi_width;
    auto &data = bmp_dec.data;

    // red - Y, green - Cb, blue - Cr

    for (int i = H - 1; i >= 0; i = i - 2){
        for (int j = W - 1; j >= 0; j = j - 2){
            uint32_t tmpCb = data[i * W + j].green + data[i * W + j - 1].green + data[(i - 1) * W + j].green + data[(i - 1) * W + j - 1].green;
            tmpCb /= 4;
            uint32_t tmpCr = data[i * W + j].blue + data[i * W + j - 1].blue + data[(i - 1) * W + j].blue + data[(i - 1) * W + j - 1].blue;
            tmpCr /= 4;
            data[i * W + j].green = uint8_t (tmpCb);
            data[i * W + j].blue = uint8_t (tmpCr);

            data[i * W + j - 1].green = uint8_t (tmpCb);
            data[i * W + j - 1].blue = uint8_t (tmpCr);

            data[(i - 1) * W + j].green = uint8_t (tmpCb);
            data[(i - 1) * W + j].blue = uint8_t (tmpCr);

            data[(i - 1) * W + j - 1].green = uint8_t (tmpCb);
            data[(i - 1) * W + j - 1].blue = uint8_t (tmpCr);
        }
    }

    return BMPProcess(bmp_dec).BMP_YCbCr_to_RGB24();

}

BMP BMPProcess::decimation_remove4() {
    BMP bmp_dec = BMPProcess(bmp).BMP_RGB24_to_YCbCr();

    int32_t H = bmp_dec.map.bi_height, W = bmp_dec.map.bi_width;
    auto &data = bmp_dec.data;
    std::vector<RGB> res = data;

    // red - Y, green - Cb, blue - Cr

    for (int i = 0; i < H; i++){
        for (int j = 0; j < W; j++){
            // Берем верхние строчки
            if (i % 4 != 0){
                res[i * W + j] = data[(i - (i % 4)) * W + j];
                res[i].red = data[i].red;
                continue;
            }
            // Берем слева
            if (j % 4 != 0){
                res[i * W + j] = data[i * W - (j % 4)];
                res[i].red = data[i].red;
                continue;
            }
            res[i * W + j] = data[i * W + j];
        }
    }


    bmp_dec.data.swap(res);

    return BMPProcess(bmp_dec).BMP_YCbCr_to_RGB24();
}

BMP BMPProcess::decimation_average4() {
    BMP bmp_dec = BMPProcess(bmp).BMP_RGB24_to_YCbCr();

    int32_t H = bmp_dec.map.bi_height, W = bmp_dec.map.bi_width;
    auto &data = bmp_dec.data;

    // red - Y, green - Cb, blue - Cr

    for (int i = 0; i < H; i = i + 4){
        for (int j = 0; j < W; j = j + 4){
            int tmpCb = 0;
            int tmpCr = 0;
            for (int k = 0; k < 4; k++){
                for (int l = 0; l < 4; l++){
                    tmpCb += data[(i + k) * W + (j + l)].green;
                    tmpCr += data[(i + k) * W + (j + l)].blue;
                }
            }
            tmpCb /= 16;
            tmpCr /= 16;
            for (int k = 0; k < 4; k++){
                for (int l = 0; l < 4; l++){
                    data[(i + k) * W + (j + l)].green = uint8_t (tmpCb);
                    data[(i + k) * W + (j + l)].blue = uint8_t (tmpCr);
                }
            }
        }
    }

    return BMPProcess(bmp_dec).BMP_YCbCr_to_RGB24();
}