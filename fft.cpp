#include <complex>
#include <iostream>
#include <vector>
#include <cmath>

int ReverseBits(int n, int len_n) {
    int left_bit = 1 << (len_n - 1);
    int right_bit = 1;

    while (left_bit > right_bit) {
        if (((n & left_bit) > 0) != ((n & right_bit) > 0)) {
            n = n ^ (left_bit | right_bit);  // flip bits
        }

        left_bit = left_bit >> 1;
        right_bit = right_bit << 1;
    }

    return n;
}

int log_2(int N) {
    int i = -1;
    while (N > 0) {
        N = N >> 1;
        i++;
    }

    return i;
}

void FftPow2(std::complex<double>* x, int N) {
    int log_2_N = log_2(N);

    for (int i = 0, bit_reversed_i; i < N; i++) {
        bit_reversed_i = ReverseBits(i, log_2_N);
        if (bit_reversed_i > i) {
            std::swap(x[i], x[bit_reversed_i]);
        }
    }

    for (int i = 0; i < log_2_N; i++) {
        
    }
}

std::vector<std::complex<double> > FftPow2(std::vector<std::complex<double> > x) {

    int x_sz = x.size();

    if (x_sz <= 1) return x;

    std::vector<std::complex<double> > evens;
    std::vector<std::complex<double> > odds;

    for (int i = 0; i < x_sz; i++) {
        if (i % 2) {
            odds.push_back(x[i]);
        } else {
            evens.push_back(x[i]);
        }
    }

    evens = FftPow2(evens);
    odds = FftPow2(odds);

    // duplicate each wave pattern
    for (int i = 0; i < x_sz/2; i++) {
        evens.push_back(evens[i]);
        odds.push_back(odds[i]);
    }

    std::vector<std::complex<double> > X;

    std::complex<double> s; // will be used to hold the sinusoidal value that
                            // will account for the shift of the odd values
    std::complex<double> j(0.0, 1.0);
    for (int i = 0; i < x_sz; i++) {
        s = exp(-j*2.0*M_PI*double(i)/double(x_sz));
        X.push_back(evens[i] + s * odds[i]);
    }

    return X;
    
}

void Print(std::vector<std::complex<double> > x) {
    std::cout << "{" << x[0];
    for (int i = 1; i < x.size(); i++) {
        std::cout << ", " << x[i];
    }
    std::cout << "}" << std::endl;
}

void SpecialPrint(std::vector<std::complex<double> > x) {
    const int amp = 12;
    for (int i = amp; i >= -amp; i--) {
        for (int k = 0; k < x.size(); k++) {
            if (i > 0 && x[k].real() > 0 && x[k].real() * amp > i) {
                std::cout << "O";
            } else if (i < 0 && x[k].real() < 0 && x[k].real() * amp < i) {
                std::cout << "X";
            } else if (i == 0) {
                std::cout << "-";
            } else {
                std::cout << " ";
            }
        }

        std::cout << "      ";

        for (int k = 0; k < x.size(); k++) {
            if (i > 0 && x[k].imag() > 0 && x[k].imag() * amp > i) {
                std::cout << "O";
            } else if (i < 0 && x[k].imag() < 0 && x[k].imag() * amp < i) {
                std::cout << "X";
            } else if (i == 0) {
                std::cout << "-";
            } else {
                std::cout << " ";
            }
        }

        std::cout << std::endl;
    }

}


int main(int argc, char* argv[]) {

    std::complex<double> zl = 1;

    for (int i = 0; i < 4; i++) {
        zl *= std::complex<double>(0.0, 1.0);
        std::cout << zl << std::endl;
    }

    std::cout << "Reversing 6: " << ReverseBits(8, 4) << std::endl;

    std::vector<std::complex<double> > x;

    for (int i = 0; i < 32; i++) {
        x.push_back(std::complex<double>(0.25 - ((i % 16) + 1)/32.0 , 0.0));
    }


    std::vector<std::complex<double> > X = FftPow2(x);

    Print(x);
    Print(X);

    SpecialPrint(x);
    SpecialPrint(X);

    return 0;
    
}