#include "bmp.h"

BMP copyBMP(BMP &bmp) {
    BMP n;
    n.map = bmp.map;
    n.header = bmp.header;
    n.data = std::vector<RGB>(bmp.data.size());
    for (int i = 0; i < bmp.data.size(); ++i) {
        auto &rgb = bmp.data[i];
        n.data[i] = { rgb.blue, rgb.green, rgb.red };
    }
    return n;
}

BMP load_bmp_image(const std::string& filename) {
    BMP bmp;
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
        exit(1);
    }
    file.read(reinterpret_cast<char*>(&bmp.header), sizeof(tagBITMAPFILEHEADER));
    file.read(reinterpret_cast<char*>(&bmp.map), sizeof(tagBITMAPINFOHEADER));
    if (bmp.map.bi_bit_count != 24) {
        std::cerr << "Image is not True Color 24 BMP!";
        exit(-1);
    }

    if (bmp.map.bi_size_image == 0) {
        bmp.map.bi_size_image = bmp.header.bf_size - sizeof(bmp.map) - sizeof(bmp.header);
    }

    size_t dataSize = bmp.map.bi_size_image;
    bmp.data.resize(dataSize/(sizeof(RGB)));
    file.read(reinterpret_cast<char*>(bmp.data.data()),  bmp.map.bi_size_image);

    file.close();
    return bmp;
}


void save_bmp_image(const BMP& bmp, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        exit(1);
    }
    file.write(reinterpret_cast<const char*>(&bmp.header), sizeof(tagBITMAPFILEHEADER));
    file.write(reinterpret_cast<const char*>(&bmp.map), sizeof(tagBITMAPINFOHEADER));
    file.write(reinterpret_cast<const char*>(bmp.data.data()), bmp.map.bi_size_image);
    file.close();
}


void print_image_header(const BMP& bmp)
{
    std::cout
        << "FILE: " << std::endl
        << "bf_type: " << bmp.header.bf_type << "," << std::endl
        << "bf_size: " << bmp.header.bf_size << "," << std::endl
        << "bf_reserved1: " << bmp.header.bf_reserved1 << "," << std::endl
        << "bf_reserved2: " << bmp.header.bf_reserved2 << "," << std::endl
        << "bf_off_bits: " << bmp.header.bf_off_bits << "," << std::endl
        << "MAP:" << std::endl

        << "bi_size: " << bmp.map.bi_size << ", " << std::endl
        << "bi_width: " << bmp.map.bi_width << ", " << std::endl
        << "bi_height: " << bmp.map.bi_height << ", " << std::endl
        << "bi_planes: " << bmp.map.bi_planes << ", " << std::endl
        << "bi_bit_count: " << bmp.map.bi_bit_count << ", " << std::endl
        << "bi_compression: " << bmp.map.bi_compression << ", " << std::endl
        << "bi_size_image: " << bmp.map.bi_size_image << ", " << std::endl
        << "bi_x_pixels_per_meter: " << bmp.map.bi_x_pixels_per_meter << ", " << std::endl
        << "bi_y_pixels_per_meter: " << bmp.map.bi_y_pixels_per_meter << ", " << std::endl
        << "bi_colors_used: " << bmp.map.bi_colors_used << ", " << std::endl
        << "bi_colors_important: " << bmp.map.bi_colors_important << ", " << std::endl;

}
