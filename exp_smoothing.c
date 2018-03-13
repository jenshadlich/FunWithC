#include <stdio.h>
#include <stdlib.h>

double smooth(double value);

int main() {

    double input[] = { .0, .1, .2, .3, .4, .5, 1.0, 1.1, 1.0, 1.1, 1.0, 1.05, 1.0, 1.0 };
    int len = sizeof(input) / sizeof(double);

    for (int i = 0; i < len; i++) {
        printf("%.2f => %.2f\n", input[i], smooth(input[i]));
    }

    exit(0);
}

double smooth(double value) {
    double alpha = .54;
    double smoothValue = .0;
    static double oldValue = .0;

    smoothValue = alpha * value + (1 - alpha) * oldValue;
    oldValue = smoothValue;

    return smoothValue;
}
