#ifndef IMAGE_EDIT_DPCM_H
#define IMAGE_EDIT_DPCM_H

#include "entropy.h"
#include "histogram.h"

std::vector<int> DPCMr1(const std::vector<unsigned char>& a, int H, int W, const std::string& outputPath);

std::vector<int> DPCMr2(const std::vector<unsigned char>& a, int H, int W, const std::string& outputPath);

std::vector<int> DPCMr3(const std::vector<unsigned char>& a, int H, int W, const std::string& outputPath);

std::vector<int> DPCMr4(const std::vector<unsigned char>& a, int H, int W, const std::string& outputPath);

void DPCMforRGB(std::vector<RGB> pixels, int H, int W, const std::string& outputPath);
void DPCMforYCbCr(std::vector<RGB> pixels, int H, int W, const std::string& outputPath);


#endif //IMAGE_EDIT_DPCM_H
