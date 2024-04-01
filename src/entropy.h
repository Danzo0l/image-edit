#ifndef IMAGE_EDIT_ENTROPY_H
#define IMAGE_EDIT_ENTROPY_H

#include <iostream>
#include <vector>
#include <cmath>

#include "bmp.h"

template<class T>
double entropy(const std::vector<T>& a){
    double result = 0;
    std::vector<int> counts(256, 0);
    int totalPixels = a.size();

    for (unsigned char pixel : a) {
        counts[pixel]++;
    }

    for (int i = 0; i < 256; i++) {
        if (counts[i] > 0) {
            double probability = static_cast<double>(counts[i]) / totalPixels;
            result -= probability * log2(probability);
        }
    }

    return result;
}

void entropyYCbCr(const std::vector<RGB>& pixels, int H, int W);

void entropyRGB(const std::vector<RGB>& pixels, int H, int W);

#endif //IMAGE_EDIT_ENTROPY_H
