#include <iostream>

/*
 * The following function convolves an input signal X and an impulse response H
 * to produce the output signal Y.
 *
 * Assumptions:
 *  - x has n elements
 *  - h has m elements
 *  - y has n + m - 1 elements
 */

void Convolve(const double* x, int n, const double* h, int m, double* y) {
    // Zero out y
    for (int i = 0; i < n+m-1; i++) {
        y[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            y[i + j] += x[i] * h[j];
        }
    }
}

void PrintArray(double* x, int n, int prec = 3) {
    std::cout.precision(prec);
    std::cout << std::fixed;
    std::cout << "{" << x[0];
    for (int i = 1; i < n; i++) {
        std::cout << ", " << x[i];
    }
    std::cout << "}" << std::endl;
}

int main(int argc, char** argv) {

    // cos wave with k = 3
    double x[16] = { 1.0,  0.382683432365,  -0.707106781187,  -0.923879532511,  -1.83697019872e-16,  0.923879532511,  0.707106781187,  -0.382683432365,  -1.0,  -0.382683432365,  0.707106781187,  0.923879532511,  5.51091059616e-16,  -0.923879532511,  -0.707106781187,  0.382683432365, };

    double h[3] = {-1};
    double y[16];

    std::cout << "Convolving x and h..." << std::endl;

    Convolve(x, 16, h, 1, y);

    PrintArray(x, 16);
    PrintArray(h, 1);
    PrintArray(y, 16);

    return 0;
}