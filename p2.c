#include<stdio.h>
#include<math.h>

long long int power(int base,int exp)
{
    long long int result=1;
    while(exp>0)
    {
        if(exp%2==1)
        {
            result*=base;
        }
        base*=base;
        exp/=2;
    }
    return result;
}

long long int karatsuba(long long int X, long long int Y)
{
    if(X<10 || Y<10)
        return X*Y;

    int size=fmax(log10(X)+1,log10(Y)+1);
    int half=size/2;
    long long int a=X/power(10,half);
    long long int b=X%power(10,half);
    long long int c=Y/power(10,half);
    long long int d=Y%power(10,half);

    long long int ac= karatsuba(a,c);
    long long int bd= karatsuba(b,d);
    long long int ad_bc=karatsuba(a+b,c+d)-ac-bd;

    return ac*power(10,half*2) + ad_bc*power(10,half)+bd;
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
