#include <stdio.h>

int esPotenciaDe2(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

int main() {
    for (int i = 1; i <= 64; i++) {
        if (esPotenciaDe2(i)) {
            printf("%d es potencia de 2\n", i);
        }
    }
    return 0;
}
