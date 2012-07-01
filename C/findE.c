#include <stdio.h>
#define N 30

int main (void) {
    int i;
    double e, frac[N]={1.0, 1.0};
    for (i = 2; i < N; i++) {
        frac[i] = frac[i-1] * i;
    }


    for (i = 0, e = 0.0; i < N; i++)
    {
        e += (1.0/frac[i]);
    }
    printf("%.50f", e);
    return 0;
}
