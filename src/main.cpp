#include "bmp.h"
#include "BMPProcess.h"

int main(int argc, char* argv[]) {
//    Default program run
    if (argc != 1)
    {
        return 0;
    }

    BMP bmp_image = load_bmp_image(R"(C:\Users\dryag\Documents\image-edit\kodim10.bmp)");
    BMPProcess bmp_process = BMPProcess(bmp_image);

    save_bmp_image(bmp_image, R"(C:\Users\dryag\Documents\image-edit\kodim10_channel.bmp)");

//    save_bmp_image(bmp_process.get_blue_channel(), R"(C:\Users\dryag\Documents\image-edit\kodim10_blue_channel.bmp)");
//    save_bmp_image(bmp_process.get_red_channel(), R"(C:\Users\dryag\Documents\image-edit\kodim10_red_channel.bmp)");
//    save_bmp_image(bmp_process.get_green_channel(), R"(C:\Users\dryag\Documents\image-edit\kodim10_green_channel.bmp)");



    return 0;
}
