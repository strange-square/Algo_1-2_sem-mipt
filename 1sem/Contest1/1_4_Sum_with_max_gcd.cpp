//Дано натуральное число N. Представить N в виде A + B, так, что НОД(A, B) максимален, 1 ≤ A ≤ B. Вывести A и B.
//Если возможно несколько ответов - вывести ответ с минимальным A. 1 < n ≤ 10 000 000.

#include <iostream>
#include <math.h>
using namespace std;

int min_multiplier (int N)
{
    int min_multiplier = 0, i = 2;

    while ((min_multiplier == 0) && (i <= sqrt(N)))
    {
        if (N % i == 0) min_multiplier = i;
        i++;
    }

    if (min_multiplier == 0) return N;
    return min_multiplier;
}

int min_summand (const int& N)
{
    int min_mult = min_multiplier(N);
    if (min_mult == N) return 1;
    return (N/min_mult);
}

int main()
{
    int N = 0;
    cin >> N;

    int min_summ = min_summand(N);

    cout << min_summ << " " << N - min_summ;
    return 0;
}
