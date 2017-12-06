#include <cmath>     /* std::sin and std::cos */
#include <iostream>  /* std::cout */


/* 
 * Assumptions:
 *  - ReX has n/2 + 1 elements
 *  - ImX has n/2 + 1 elements
 *  - x has n elements
 *
 * Note: This is a simple O(N^2) implementation of the Discrete Fourier
 *       Transform.  The Fast Fourier Transform should be used for large
 *       values of N.
 */

void dft(const double* x, double* ReX, double* ImX, int n) {
    // Clear out ReX, ImX as they will act as accumulators
    for (int i = 0; i <= n/2; i++) {
        ReX[i] = 0;
        ImX[i] = 0;
    }

    for (int i = 0; i <= n/2; i++) {
        for (int j = 0; j < n; j++) {
            ReX[i] += std::cos(2*M_PI*i*j/n) * x[j];
            ImX[i] -= std::sin(2*M_PI*i*j/n) * x[j];
        }
    }
}

void inverse_dft(double* x, const double* ReX, const double* ImX, int n) {
    // x as it will act as an accumulator
    for (int i = 0; i <= n/2; i++) {
        x[i] = 0;
    }


    int scaling_factor;
    for (int i = 0; i <= n/2; i++) {
        scaling_factor = (i == 0 || i == n/2) ? n : n/2;

        for (int j = 0; j < n; j++) {
            x[j] += ReX[i] * std::cos(2*M_PI*i*j/n) / scaling_factor;
            x[j] += ImX[i] * std::sin(2*M_PI*i*j/n) / scaling_factor;
        }
    }
}

void print_array(double* x, int n, int prec = 3) {
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

    double ReX[9];
    double ImX[9];

    std::cout << "Before DFT" << std::endl;

    print_array(x, 16);
    print_array(ReX, 9);
    print_array(ImX, 9);

    std::cout << std::endl;

    dft(x, ReX, ImX, 16);

    std::cout << "After DFT: " << std::endl;
    print_array(x, 16);
    print_array(ReX, 9);
    print_array(ImX, 9);

    double rebuilt_x[16];
    inverse_dft(rebuilt_x, ReX, ImX, 16);

    std::cout << "After inverse DFT: " << std::endl;
    print_array(rebuilt_x, 16);
    print_array(ReX, 9);
    print_array(ImX, 9);

    return 0;
}