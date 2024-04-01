#include <cstring>
#include "bmp.h"
#include "BMPProcess.h"
#include "DPCM.h"

void task3(const std::string& imagePath);
void task4a(const std::string& imagePath);
void task4b(const std::string& imagePath);
void task5(const std::string& imagePath);
void task6(const std::string& imagePath);
void task7(const std::string& imagePath, const std::string& originalImagePath);
void task14(const std::string& imagePath);

int main(int argc, char* argv[])
{
//    Default program run
    if (argc < 2) {
        return 0;
    }

    if (strcmp(argv[1], "-task3") == 0){
        task3(argv[2]);
    } else if (strcmp(argv[1], "-task4a") == 0) {
        task4a(argv[2]);
    } else if (strcmp(argv[1], "-task4b") == 0) {
        task4b(argv[2]);
    } else if (strcmp(argv[1], "-task5") == 0) {
        task5(argv[2]);
    } else if (strcmp(argv[1], "-task6") == 0) {
        task6(argv[2]);
    } else if (strcmp(argv[1], "-task7") == 0) {
        task7(argv[2], argv[3]);
    } else if (strcmp(argv[1], "-task14") == 0) {
        task14(argv[2]);
    }
}

void task3(const std::string& imagePath) {
    std::string redPath = imagePath.substr(0, imagePath.size() - 4) + ".red.bmp";
    std::string greenPath = imagePath.substr(0, imagePath.size() - 4) + ".green.bmp";
    std::string bluePath = imagePath.substr(0, imagePath.size() - 4) + ".blue.bmp";

    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);

    save_bmp_image(bmp_process.bmp_blue_channel(), bluePath);
    save_bmp_image(bmp_process.bmp_red_channel(), redPath);
    save_bmp_image(bmp_process.bmp_green_channel(), greenPath);

    std::cout << redPath << std::endl;
    std::cout << greenPath << std::endl;
    std::cout << bluePath << std::endl;
}

void task4a(const std::string& imagePath) {
    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);
    std::cout << "{" << std::endl <<
              "\t\"R&B\": " << bmp_process.correlation(bmp_process.pixels_red_channel(), bmp_process.pixels_blue_channel()) << "," << std::endl <<
              "\t\"R&G\": " << bmp_process.correlation(bmp_process.pixels_red_channel(), bmp_process.pixels_green_channel()) << "," << std::endl <<
              "\t\"G&B\": " << bmp_process.correlation(bmp_process.pixels_green_channel(), bmp_process.pixels_blue_channel()) << std::endl <<
              "}" << std::endl;
}

void task4b(const std::string& imagePath) {
    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);

    const int x_step = 1;
    const int x_end = bmp_image.map.bi_width / 4, x_start = -(x_end - 1);

    const int y_step = 5;
    const int y_end = 10, y_start = -y_end;

    std::vector<uint8_t> pixel_channels[] = {
            bmp_process.pixels_red_channel(),
            bmp_process.pixels_green_channel(),
            bmp_process.pixels_blue_channel(),
            bmp_process.pixels_Y_channel(),
            bmp_process.pixels_cb_channel(),
            bmp_process.pixels_cr_channel()
    };

    for (int i = 0; i < 6; ++i) {
        std::cout << "NEXT_CHANNEL" << std::endl;
        for (int iy = y_start; iy <= y_end; iy+=y_step) {
            for (int ix = x_start; ix <= x_end; ix+=x_step) {
                double corr = bmp_process.autocorrelation(pixel_channels[i], ix, iy);
                // y <value> x <value> corr <value>
                std::cout << " " << iy << " " << ix <<
                        " " << corr << std::endl;
            }
            std::cout << "NEXT_Y" << std::endl;
        }
    }
}

void task5(const std::string& imagePath) {
    std::string YCbCr_path = imagePath.substr(0, imagePath.size() - 4) + ".ycbcr.bmp";
    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);

    save_bmp_image(bmp_process.RGB24_to_YCbCr(), YCbCr_path);
    bmp_process.set_BMP(bmp_process.RGB24_to_YCbCr());

    std::cout << "{" << std::endl <<
              "\t\"Y&Cb\": " << bmp_process.correlation(bmp_process.pixels_red_channel(), bmp_process.pixels_blue_channel()) << "," << std::endl <<
              "\t\"Y&Cr\": " << bmp_process.correlation(bmp_process.pixels_green_channel(), bmp_process.pixels_blue_channel()) << std::endl <<
              "\t\"Cb&Cr\": " << bmp_process.correlation(bmp_process.pixels_red_channel(), bmp_process.pixels_green_channel()) << "," << std::endl <<
              "}" << std::endl;

    std::cout << YCbCr_path << std::endl;
}

void task6(const std::string& imagePath) {
    std::string y_Path = imagePath.substr(0, imagePath.size() - 4) + ".Y.bmp";
    std::string cb_Path = imagePath.substr(0, imagePath.size() - 4) + ".cb.bmp";
    std::string cr_Path = imagePath.substr(0, imagePath.size() - 4) + ".cr.bmp";

    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);

    save_bmp_image(bmp_process.get_Y_channel(), y_Path);
    save_bmp_image(bmp_process.get_cb_channel(), cb_Path);
    save_bmp_image(bmp_process.get_cr_channel(), cr_Path);

    std::cout << y_Path << std::endl;
    std::cout << cb_Path << std::endl;
    std::cout << cr_Path << std::endl;
}

void task7(const std::string& imagePath, const std::string& originalImagePath) {
    std::string YCbCr_path = imagePath.substr(0, imagePath.size() - 4) + ".reserved.bmp";

    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);

    save_bmp_image(bmp_process.YCbCr_to_RGB24(), YCbCr_path);

    std::cout << YCbCr_path << std::endl;
    std::cout << "PSNR &R: " << bmp_process.PSNR('r', originalImagePath) << std::endl;
    std::cout << "PSNR &G: " << bmp_process.PSNR('g', originalImagePath) << std::endl;
    std::cout << "PSNR &B: " << bmp_process.PSNR('b', originalImagePath) << std::endl;
}

void task14(const std::string& imagePath) {
    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);


    DPCMforRGB(bmp_image.data, bmp_image.map.bi_height, bmp_image.map.bi_width, imagePath + ".DPCM");
    std::cout << std::endl;
//    DPCMforYCbCr(bmp_process.RGB24_to_YCbCr().data, bmp_image.map.bi_height, bmp_image.map.bi_width, imagePath + ".DPCM");
    std::cout << std::endl;
}