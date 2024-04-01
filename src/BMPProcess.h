#ifndef IMAGE_EDIT_BMPPROCESS_H
#define IMAGE_EDIT_BMPPROCESS_H

#include "bmp.h"
#include <cmath>
#include <map>

class BMPProcess {

private:
    BMP bmp;

public:

    explicit BMPProcess(const BMP &bmp_data);

    BMP bmp_red_channel();
    BMP bmp_green_channel();
    BMP bmp_blue_channel();
    std::vector<uint8_t> pixels_red_channel();
    std::vector<uint8_t> pixels_green_channel();
    std::vector<uint8_t> pixels_blue_channel();

    double correlation(const std::vector<uint8_t> &a, const std::vector<uint8_t> &b);
    double autocorrelation(const std::vector<uint8_t>& src, int x, int y);

    BMP RGB24_to_YCbCr();
    BMP YCbCr_to_RGB24();
    BMP get_Y_channel();
    BMP get_cb_channel();
    BMP get_cr_channel();
    std::vector<uint8_t> pixels_Y_channel();
    std::vector<uint8_t> pixels_cb_channel();
    std::vector<uint8_t> pixels_cr_channel();

    double PSNR(char channel, const std::string& original_path);

    void set_BMP(const BMP& bmpImage);

    BMP decimation_remove();
    BMP decimation_average();
};


#endif //IMAGE_EDIT_BMPPROCESS_H
