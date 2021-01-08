#include <complex.h>
#include "function.h"

double complex f (int domain_dim, double complex input_values[]) {
    double complex norm, s = 0;

    for (int i = 0; i < domain_dim; i++) {
        s += input_values[i]*input_values[i];
    }
    
    norm = csqrt(s);
    
    return norm;
}