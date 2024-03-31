#include <cstring>
#include "bmp.h"
#include "BMPProcess.h"

int main(int argc, char* argv[])
{
//    Default program run
    if (argc < 2)
    {
        return 0;
    }

    if (strcmp(argv[1], "-ch") == 0)
    {
        std::string imagePath = argv[2];
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

        return 0;
    }
    if (strcmp(argv[1], "-correlation") == 0)
    {
        std::string imagePath = argv[2];

        BMP bmp_image = load_bmp_image(imagePath);
        BMPProcess bmp_process = BMPProcess(bmp_image);
        std::cout << "{" << std::endl <<
                "\t\"R&B\": " << bmp_process.correlation('r', 'b') << "," << std::endl <<
                "\t\"R&G\": " << bmp_process.correlation('r', 'g') << "," << std::endl <<
                "\t\"G&B\": " << bmp_process.correlation('g', 'b') << std::endl <<
                "}" << std::endl;

        return 0;
    }
    if (strcmp(argv[1], "-autocorrelation") == 0)
    {
        std::string imagePath = argv[2];

        BMP bmp_image = load_bmp_image(imagePath);
        BMPProcess bmp_process = BMPProcess(bmp_image);
        std::cout << "{" << std::endl <<
                  "\t\"R&B\": " << bmp_process.correlation('r', 'b') << "," << std::endl <<
                  "\t\"R&G\": " << bmp_process.correlation('r', 'g') << "," << std::endl <<
                  "\t\"G&B\": " << bmp_process.correlation('g', 'b') << std::endl <<
                  "}" << std::endl;

        return 0;
    }
}
