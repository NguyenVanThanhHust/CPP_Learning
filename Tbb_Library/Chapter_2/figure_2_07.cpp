#include <algorithm>
#include <iostream>
#include <vector>
#include <tbb/tbb.h>

using std::cout;
using std::endl;

void figure_2_07(int M, double *a, double *b, double *c){
    for (size_t i = 0; i < M; i++){
        for (size_t j = 0; j < M; j++){
            int c_index = i*M+j;
            for (size_t k = 0; k < M; k++){
                c[c_index] += a[i*M + j] * b[k*M +j];
            }
        }
    }
}

int main(){
    const int M = 1024;
    const int MxM = M * M;
    double *a = new double[MxM];
    double *b = new double[MxM];
    double *c = new double[MxM];
    double *c_expected = new double[MxM];

    // init arrays
    std::fill(a, a + MxM, 1.0);
    std::fill(b, b + MxM, 1.0);
    std::fill(c, c + MxM, 0.0);
    std::fill(c_expected, c_expected + MxM, M);
    double serial_time = 0.0;
    {
        tbb::tick_count t0 = tbb::tick_count::now();
        figure_2_07(M, a, b, c);
        serial_time = (tbb::tick_count::now() - t0).seconds();
        if (!std::equal(c, c + MxM, c_expected)){
            std::cerr << "ERROR: c array does not match expected values" << std::endl;
        }
    }
    std::cout << "serial_time == " << serial_time << " seconds" << std::endl;
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] c_expected;
    return 0;
}