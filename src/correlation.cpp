#include "BMPProcess.h"

double BMPProcess::expected_payoff(char channel)
{
    double res;
    res = 1.0 / (bmp.map.bi_width * bmp.map.bi_height);
    uint32_t summ = 0;
    for (size_t i = 0; i < bmp.map.bi_height; i++)
    {
        uint32_t sum = 0;
        for (size_t j = 0; j < bmp.map.bi_width; j++)
        {
            if (channel == 'r') {
                sum += bmp.data[i * bmp.map.bi_width + j].red;
            } else if (channel == 'g') {
                sum += bmp.data[i * bmp.map.bi_width + j].green;
            } else if (channel == 'b') {
                sum += bmp.data[i * bmp.map.bi_width + j].blue;
            }
        }
        summ += sum;
    }
    res *= summ;
    return res;
}

double BMPProcess::quadr_err(char channel)
{
    double res;
    res = 1.0 / ((bmp.map.bi_width * bmp.map.bi_height) - 1);
    double summ = 0;
    double expected_payoff_value = expected_payoff(channel);

    for (size_t i = 0; i < bmp.map.bi_height; i++)
    {
        double sum = 0;
        for (size_t j = 0; j < bmp.map.bi_width; j++)
        {
            double sum_elem = 0;
            if (channel == 'r') {
                sum_elem += bmp.data[i * bmp.map.bi_width + j].red;
            } else if (channel == 'g') {
                sum_elem += bmp.data[i * bmp.map.bi_width + j].green;
            } else if (channel == 'b') {
                sum_elem += bmp.data[i * bmp.map.bi_width + j].blue;
            }
            sum_elem -= expected_payoff_value;
            sum += expected_payoff_value * expected_payoff_value;
        }
        summ += sum;
    }
    res *= summ;
    return sqrt(res);
}

double BMPProcess::correlation(char channel1, char channel2)
{
    int size = bmp.data.size();
    std::vector<uint8_t> a(size);
    std::vector<uint8_t> b(size);
    for (int i = 0; i < size; ++i) {
        if (channel1 == 'r') {
            a[i] = bmp.data[i].red;
        } else if (channel1 == 'g') {
            a[i] = bmp.data[i].green;
        } else if (channel1 == 'b') {
            a[i] = bmp.data[i].blue;
        }
        if (channel2 == 'r') {
            b[i] = bmp.data[i].red;
        } else if (channel2 == 'g') {
            b[i] = bmp.data[i].green;
        } else if (channel2 == 'b') {
            b[i] = bmp.data[i].blue;
        }
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