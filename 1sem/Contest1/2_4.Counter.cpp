// “Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N.
//Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
//(Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й, затем 7-й, потом 1-й, потом 8-й,
//за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.) Необходимо определить номер уцелевшего. N, k ≤ 10000.

#include <iostream>

void shift(int* arr, int moved, int size_arr)
{
    for (int i=moved; i<size_arr; i++)
        arr[i] = arr[i+1];
}

int deleter(int* arr, int size_arr, int k)
{
    int moved = 0;

    while (size_arr != 1)
    {
        moved = (moved + k - 1) % size_arr;
        shift(arr, moved, --size_arr);
    }

    return arr[0];
}

int main()
{
    int size_arr = 0, k = 0;
    std::cin >> size_arr >> k;

    int* arr = new int [size_arr];
    for (int i = 0; i < size_arr; i++)
        arr[i] = i+1;

    std::cout << deleter(arr, size_arr, k);

    return 0;
}
