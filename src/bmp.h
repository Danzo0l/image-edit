#ifndef IMAGE_EDIT_BMP_H
#define IMAGE_EDIT_BMP_H

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#pragma pack(1)
struct tagBITMAPFILEHEADER {
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_reserved1;
    uint16_t bf_reserved2;
    uint32_t bf_off_bits;
};

struct tagBITMAPINFOHEADER {
    uint32_t bi_size;
    int32_t bi_width;
    int32_t bi_height;
    uint16_t bi_planes;
    uint16_t bi_bit_count;
    uint32_t bi_compression;
    uint32_t bi_size_image;
    int32_t bi_x_pixels_per_meter;
    int32_t bi_y_pixels_per_meter;
    uint32_t bi_colors_used;
    uint32_t bi_colors_important;
};
#pragma pop

struct RGB {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

struct BMP {
    tagBITMAPFILEHEADER header;
    tagBITMAPINFOHEADER map;
    std::vector<RGB> palette;
    std::vector<RGB> data;
};

BMP load_bmp_image(const std::string& filename);

void save_bmp_image(const BMP& bmp, const std::string& filename);

void print_image_header(const BMP& bmp);

#endif //IMAGE_EDIT_BMP_H
