#include <stdio.h>
#include <stdlib.h>

#include <math.h>

double series_term (long long int k);

int main(int argc, char const *argv[])
{
    long long int N;
    double pi = 0.0;

    sscanf(argv[1], "%lld", &N); // ler quantidade de termos dos argumentos de linha de comando

    for (long long int k = N; k > 0; k--) {
    // for (long long int k = 1; k < N; k++) {
        pi += series_term(k);
    }
    pi *= 4.0;
    
    printf("Valor obtido: %.15f\n", pi);
    printf("Diferença do valor obtido para M_PI: %.15f\n", 
        M_PI > pi ? M_PI - pi : pi - M_PI);

    return 0;
}

double series_term (long long int k) {
    double term = 1.0 / (double) (2*k - 1);

    if (k % 2 == 0) {
        term = -term;
    }

    return term;
}