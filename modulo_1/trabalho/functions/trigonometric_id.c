#include <complex.h>
#include "function.h"

double complex f (int domain_dim, double complex input_values[]) {
    double complex accumulator = 0, s, c;

    for (int i = 0; i < domain_dim; i++) {
        s = csin(input_values[i]);
        c = ccos(input_values[i]);
        accumulator += s*s + c*c;
    }
    
    return accumulator;
}