#include <cstring>
#include "bmp.h"
#include "BMPProcess.h"

void task3(const std::string& imagePath);
void task4a(const std::string& imagePath);
void task5(const std::string& imagePath);
void task6(const std::string& imagePath);
void task7(const std::string& imagePath, const std::string& originalImagePath);

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
    } else if (strcmp(argv[1], "-task5") == 0) {
        task5(argv[2]);
    } else if (strcmp(argv[1], "-task6") == 0) {
        task6(argv[2]);
    } else if (strcmp(argv[1], "-task7") == 0) {
        task7(argv[2], argv[3]);
    }
}

void task3(const std::string& imagePath) {
    std::string redPath = imagePath.substr(0, imagePath.size() - 4) + ".red.bmp";
    std::string greenPath = imagePath.substr(0, imagePath.size() - 4) + ".green.bmp";
    std::string bluePath = imagePath.substr(0, imagePath.size() - 4) + ".blue.bmp";

    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);

    save_bmp_image(bmp_process.get_blue_channel(), bluePath);
    save_bmp_image(bmp_process.get_red_channel(), redPath);
    save_bmp_image(bmp_process.get_green_channel(), greenPath);

    std::cout << redPath << std::endl;
    std::cout << greenPath << std::endl;
    std::cout << bluePath << std::endl;
}

void task4a(const std::string& imagePath) {
    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);
    std::cout << "{" << std::endl <<
              "\t\"R&B\": " << bmp_process.correlation('r', 'b') << "," << std::endl <<
              "\t\"R&G\": " << bmp_process.correlation('r', 'g') << "," << std::endl <<
              "\t\"G&B\": " << bmp_process.correlation('g', 'b') << std::endl <<
              "}" << std::endl;
}

void task5(const std::string& imagePath) {
    std::string YCbCr_path = imagePath.substr(0, imagePath.size() - 4) + ".ycbcr.bmp";

    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);

    save_bmp_image(bmp_process.RGB24_to_YCbCr(), YCbCr_path);

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