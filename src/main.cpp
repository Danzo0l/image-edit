#include <cstring>
#include "bmp.h"
#include "BMPProcess.h"

void task3(const std::string& imagePath);
void task4a(const std::string& imagePath);
void task4b(const std::string& imagePath);

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

void task4b(const std::string& imagePath) {

}