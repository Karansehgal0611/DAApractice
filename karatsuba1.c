#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long int power(int base, int exp) {
    long long int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

long long int karatsuba(long long int x, long long int y) {
    if (x < 10 || y < 10) {
        return x * y;
    }

    int size = fmax(log10(x) + 1, log10(y) + 1);
    int half = size / 2;

    long long int a = x / power(10, half);
    long long int b = x % power(10, half);
    long long int c = y / power(10, half);
    long long int d = y % power(10, half);

    long long int ac = karatsuba(a, c);
    long long int bd = karatsuba(b, d);
    long long int ad_bc = karatsuba(a + b, c + d) - ac - bd;

    return ac * power(10, 2 * half) + ad_bc * power(10, half) + bd;
}

int main() {
    long long int x, y;

    printf("Enter first number: ");
    scanf("%lld", &x);

    printf("Enter second number: ");
    scanf("%lld", &y);

    long long int result = karatsuba(x, y);

    printf("Multiplication result: %lld\n", result);

    return 0;
}

