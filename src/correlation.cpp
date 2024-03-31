#include "BMPProcess.h"

double BMPProcess::correlation(const std::vector<uint8_t> &a, const std::vector<uint8_t> &b) {
     size_t size = a.size();

    if (a.size() != b.size()){
        std::cout << "!! correlation(): a.size() != b.size() !!" << std::endl;
        size = std::min(a.size(), b.size());
    }
    // МО
    double m_a = 0, m_b = 0;
    for (int i = 0; i < size; i++){
        m_a += a[i];
        m_b += b[i];
    }
    m_a /= size;
    m_b /= size;
    double b_a = 0, b_b = 0;
    for (int i = 0; i < size; i++){
        b_a += (a[i] - m_a) * (a[i] - m_a);
        b_b += (b[i] - m_b) * (b[i] - m_b);
    }
    b_a /= size - 1;
    b_b /= size - 1;
    b_a = sqrt(b_a);
    b_b = sqrt(b_b);
    double result = 0;
    for (int i = 0; i < size; i++){
        result += (a[i] - m_a) * (b[i] - m_b);
    }
    result /= size;
    result /= b_a * b_b;
    if ((result > 1.0) || (result < -1.0))
    {
        std::cout << "!! correlation(): result != [-1; 1] !!" << std::endl;
    }
    return result;
}

double BMPProcess::autocorrelation(const std::vector<uint8_t>& src, int x, int y) {
    int32_t H = bmp.map.bi_height - abs(y);
    int32_t W = bmp.map.bi_width - abs(x);

    const uint8_t *start = src.data() + (abs(y) * W) + abs(x);

    auto a = std::vector<uint8_t>();
    auto b = std::vector<uint8_t>();


    for (int i = 1; i < H - y; i++){
        for (int j = 1; j < W - x; j++){
            a.push_back(start[i * W + j]);
        }
    }

    for (int m = y + 1; m < H; m++){
        for (int n = x + 1; n < W; n++){
            b.push_back(start[m * W + n]);
        }
    }

    return correlation(a, b);
}