#ifndef IMAGE_EDIT_BMPPROCESS_H
#define IMAGE_EDIT_BMPPROCESS_H

#include "bmp.h"


class BMPProcess {

private:
    BMP bmp;

public:
    explicit BMPProcess(const BMP &bmp_data);

    BMP get_red_channel();
    BMP get_green_channel();
    BMP get_blue_channel();
};


#endif //IMAGE_EDIT_BMPPROCESS_H
