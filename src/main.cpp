#include <cstring>
#include "bmp.h"
#include "BMPProcess.h"
#include "bi_color_bmp.h"
#include "DPCM.h"

void task3(const std::string& imagePath);
void task4a(const std::string& imagePath);
void task4b(const std::string& imagePath);
void task5(const std::string& imagePath);
void task6(const std::string& imagePath);
void task7(const std::string& imagePath, const std::string& originalImagePath);
void task8(const std::string& imagePath);
void task14_16(const std::string& imagePath);
void task17(const std::string& imagePath, uint8_t thr);

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
    } else if (strcmp(argv[1], "-task8") == 0) {
        task8(argv[2]);
    } else if (strcmp(argv[1], "-task14_16") == 0) {
        task14_16(argv[2]);
    } else if (strcmp(argv[1], "-task17") == 0) {
        task17(argv[2], (uint8_t)strtoul(argv[3], nullptr, 0) );
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

    std::cout << bmp_image.header.bf_off_bits << std::endl;

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

    save_bmp_image(bmp_process.BMP_RGB24_to_YCbCr(), YCbCr_path);
    bmp_process.set_BMP(bmp_process.BMP_RGB24_to_YCbCr());

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

    BMP bmp_image1 = load_bmp_image(imagePath);
    BMPProcess bmp_process1 = BMPProcess(bmp_image1);
    BMP bmp_image2 = load_bmp_image(imagePath);
    BMPProcess bmp_process2 = BMPProcess(bmp_image2);
    BMP bmp_image3 = load_bmp_image(imagePath);
    BMPProcess bmp_process3 = BMPProcess(bmp_image3);

    save_bmp_image(bmp_process1.get_Y_channel(), y_Path);
    save_bmp_image(bmp_process2.get_cb_channel(), cb_Path);
    save_bmp_image(bmp_process3.get_cr_channel(), cr_Path);

    std::cout << y_Path << std::endl;
    std::cout << cb_Path << std::endl;
    std::cout << cr_Path << std::endl;
}

void task7(const std::string& imagePath, const std::string& originalImagePath) {
    std::string YCbCr_path = imagePath.substr(0, imagePath.size() - 4) + ".reserved.bmp";

    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);

    save_bmp_image(bmp_process.BMP_YCbCr_to_RGB24(), YCbCr_path);

    std::cout << YCbCr_path << std::endl;
    std::cout << "PSNR &R: " << bmp_process.PSNR('r', originalImagePath) << std::endl;
    std::cout << "PSNR &G: " << bmp_process.PSNR('g', originalImagePath) << std::endl;
    std::cout << "PSNR &B: " << bmp_process.PSNR('b', originalImagePath) << std::endl;
}

void task8(const std::string& imagePath) {
    std::string path[] = {
            imagePath.substr(0, imagePath.size() - 4) + ".dec_rm2.bmp",
            imagePath.substr(0, imagePath.size() - 4) + ".dec_aver2.bmp",
            imagePath.substr(0, imagePath.size() - 4) + ".dec_rm4.bmp",
            imagePath.substr(0, imagePath.size() - 4) + ".dec_aver4.bmp",
    };

    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);

    BMPProcess bmp_ed_proc[] = {
            BMPProcess(bmp_process.decimation_remove2()),
            BMPProcess(bmp_process.decimation_average2()),
            BMPProcess(bmp_process.decimation_remove4()),
            BMPProcess(bmp_process.decimation_average4()),
    };

    for (int i = 0; i < 4; ++i) {
        std::cout << "path: " << path[i] << std::endl;
        std::cout << "PSNR &R: " << bmp_ed_proc[i].PSNR('r', imagePath) << std::endl;
        std::cout << "PSNR &G: " << bmp_ed_proc[i].PSNR('g', imagePath) << std::endl;
        std::cout << "PSNR &B: " << bmp_ed_proc[i].PSNR('b', imagePath) << std::endl;

        save_bmp_image(bmp_ed_proc[i].get_BMP(), path[i]);
    }

}

void task14_16(const std::string& imagePath) {
    BMP bmp_image = load_bmp_image(imagePath);
    BMPProcess bmp_process = BMPProcess(bmp_image);


    DPCMforRGB(bmp_image.data, bmp_image.map.bi_width, bmp_image.map.bi_height, imagePath.substr(0, imagePath.size() - 4) + "DPCM\\");
    std::cout << std::endl;
    DPCMforYCbCr(bmp_process.BMP_RGB24_to_YCbCr().data, bmp_image.map.bi_width, bmp_image.map.bi_height, imagePath + ".DPCM");
    std::cout << std::endl;
}

void task17(const std::string& imagePath, uint8_t thr) {
    std::string res_image_path = imagePath.substr(0, imagePath.size() - 4) + ".bicolor.bmp";
    BMP bmp_image = load_bmp_image(imagePath);
    BMP bi_color_image = bi_color_bmp_convert(bmp_image, thr);
    save_bmp_image(bi_color_image, res_image_path);
}
