#ifndef IMAGE_EDIT_BMPPROCESS_H
#define IMAGE_EDIT_BMPPROCESS_H

#include "bmp.h"
#include <cmath>

class BMPProcess {

private:
    BMP bmp;

public:
    explicit BMPProcess(const BMP &bmp_data);

    BMP get_red_channel();
    BMP get_green_channel();
    BMP get_blue_channel();

    double expected_payoff(char channel);
    double quadr_err(char channel);
    double correlation(char channel1, char channel2);

    BMP RGB24_to_YCbCr();
    BMP get_Y_channel();
    BMP get_cb_channel();
    BMP get_cr_channel();
};


#endif //IMAGE_EDIT_BMPPROCESS_H
