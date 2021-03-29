# include <stdio.h>

int main(void)
{
    int i,j;
    int prime[10000];
    for(i = 2; i <= 100; ++i)
        prime[i] = 1;
    for(i = 2; i <=100; ++i)
    {
        if(prime[i])
            printf("%d",i);
        for(j = 2 * i; j <= 100; j += i)
            prime[j] = 0;
    }


    return 0;
}
