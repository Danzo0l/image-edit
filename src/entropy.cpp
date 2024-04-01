#include "entropy.h"

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

void entropyYCbCr(const std::vector<RGB>& pixels, int H, int W){
    std::vector<unsigned char> Y(H * W, 0);
    std::vector<unsigned char> Cb(H * W, 0);
    std::vector<unsigned char> Cr(H * W, 0);
    for (int i = 0; i < H * W; i++){
//        SET RGB -> YCbCr
        Y[i] = pixels[i].red;
        Cb[i] = pixels[i].green;
        Cr[i] = pixels[i].blue;
    }

    std::cout << "entropyY = " << entropy(Y) << std::endl;
    std::cout << "entropyCb = " << entropy(Cb) << std::endl;
    std::cout << "entropyCr = " << entropy(Cr) << std::endl;

    Y.clear();
    Cb.clear();
    Cr.clear();
}

void entropyRGB(const std::vector<RGB>& pixels, int H, int W){
    std::vector<unsigned char> R(H * W, 0);
    std::vector<unsigned char> G(H * W, 0);
    std::vector<unsigned char> B(H * W, 0);
    for (int i = 0; i < H * W; i++){
        R[i] = pixels[i].red;
        G[i] = pixels[i].blue;
        B[i] = pixels[i].green;
    }

    std::cout << "entropyR = " << entropy(R) << std::endl;
    std::cout << "entropyG = " << entropy(G) << std::endl;
    std::cout << "entropyB = " << entropy(B) << std::endl;

    R.clear();
    G.clear();
    B.clear();
}