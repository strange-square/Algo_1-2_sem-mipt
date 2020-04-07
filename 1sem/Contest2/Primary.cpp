#include <iostream>

using namespace std;

bool f(const int& a, const int& b)
{
    return a < b;
}

template <class T, class TLess = IsLess<T>>
void InsertSort(T* arr, T* end_arr,
                const TLess& isLess = TLess())
{
    T temp = *arr;
    T *j = nullptr;
    for (T* i = arr; i != end_arr; ++i)
    {
        temp = *i;
        for (j = i; (j != arr) && (!f(*(j-1), temp)); --j)
            *j = *(j-1);
        *j = temp;
    }
}

int main()
{
    int* a = new int[10] {5, 1, 3, 4, 9, -1, 7, 4, 2, 1};
    InsertSort(a, a + 10);
    for (int i = 0; i < 10; ++i)
        cout << a[i] << ' ';
}
