#include "histogram.h"

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

void printRGB(const std::vector<RGB>& a, int H, int W, const std::string& outputPath){
    std::vector<unsigned char> freqR(256, 0);
    std::vector<unsigned char> freqG(256, 0);
    std::vector<unsigned char> freqB(256, 0);
    for (int i = 0; i < H * W; i++){
        freqR[a[i].red]++;
        freqG[a[i].green]++;
        freqB[a[i].blue]++;
    }

    printHistogram(freqR, outputPath + "freqR.txt");
    printHistogram(freqG, outputPath + "freqG.txt");
    printHistogram(freqB, outputPath + "freqB.txt");

    freqR.clear();
    freqB.clear();
    freqG.clear();
}

void printYCbCr(const std::vector<RGB>& a, int H, int W, const std::string& outputPath){
    std::vector<unsigned char> freqY(256, 0);
    std::vector<unsigned char> freqCb(256, 0);
    std::vector<unsigned char> freqCr(256, 0);
    for (int i = 0; i < H * W; i++){
        freqY[a[i].red]++;
        freqCb[a[i].blue]++;
        freqCr[a[i].green]++;
    }

    printHistogram(freqY, outputPath + "freqY.txt");
    printHistogram(freqCb, outputPath + "freqCb.txt");
    printHistogram(freqCr, outputPath + "freqCr.txt");

    freqY.clear();
    freqCr.clear();
    freqCb.clear();
}

