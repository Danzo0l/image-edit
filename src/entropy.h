#ifndef IMAGE_EDIT_ENTROPY_H
#define IMAGE_EDIT_ENTROPY_H

#include <iostream>
#include <vector>
#include <cmath>

#include "bmp.h"

template<class T>
double entropy(const std::vector<T>& a);

void entropyYCbCr(const std::vector<RGB>& pixels, int H, int W);

void entropyRGB(const std::vector<RGB>& pixels, int H, int W);

#endif //IMAGE_EDIT_ENTROPY_H
