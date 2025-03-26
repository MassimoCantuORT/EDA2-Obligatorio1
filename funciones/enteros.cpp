#ifndef ENTEROS_FUNC
#define ENTEROS_FUNC

#include <cmath>

int hacerPositivo(int i) {
    if (i < 0)
    {
        return i * -1;
    }
    return i;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int esPrimo(int num)
{
    if (num % 2 == 0)
        return false;
    int sqrNum = sqrt(num);
    for (int i = 3; i <= sqrNum; i = i + 2)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int siguientePrimo(int num)
{
    int primoNum = num;
    while (!esPrimo(primoNum))
    {
        primoNum++;
    };
    return primoNum;
}

#endif