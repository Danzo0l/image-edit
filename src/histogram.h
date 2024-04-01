#ifndef IMAGE_EDIT_HISTOGRAM_H
#define IMAGE_EDIT_HISTOGRAM_H

#include <vector>
#include <iostream>
#include <fstream>
#include "bmp.h"

template<class T>
void printHistogram(std::vector<T> data, const std::string& path){
    std::ofstream file(path);
    if (!file.is_open()){
        std::cout << "file wasn't open!";
        exit(-1);
    }

    for (int i = 0; i < data.size(); i++){
        file << i << "=" << (int) data[i] << std::endl;
    }

    std::cout << path + " created." << std::endl;

    file.close();
}

void printRGB(const std::vector<RGB>& a, int H, int W, const std::string& outputPath);

void printYCbCr(const std::vector<RGB>& a, int H, int W, const std::string& outputPath);

#endif //IMAGE_EDIT_HISTOGRAM_H
