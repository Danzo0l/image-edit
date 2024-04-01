#ifndef IMAGE_EDIT_HISTOGRAM_H
#define IMAGE_EDIT_HISTOGRAM_H

#include <vector>
#include <iostream>
#include <fstream>
#include "bmp.h"

template<class T>
void printHistogram(std::vector<T> data, const std::string& path);

void printRGB(const std::vector<RGB>& a, int H, int W, const std::string& outputPath);

void printYCbCr(const std::vector<RGB>& a, int H, int W, const std::string& outputPath);

#endif //IMAGE_EDIT_HISTOGRAM_H
