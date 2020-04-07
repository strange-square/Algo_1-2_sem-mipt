//Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k
//Реализуйте стратегию выбора опорного элемента “случайный элемент”.
//Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

#include <iostream>

using std::cin;
using std::cout;

template <typename T>
void swap (T* a, T* b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
struct IsLess {
	bool operator()(const T& l, const T& r) const
	{
		return l < r;
	}
};

template <class T, class TLess = IsLess<T>>
T* partition (T* part_begin, T* part_end,
                                    const TLess& isLess = TLess())
{
    T* i = part_begin;
    T* pivot = part_begin + rand() % (part_end - part_begin);

    swap (pivot, part_end);


    for (T* j = part_begin; j < part_end; j++)
    {
        if (isLess(*j,*part_end))
        {
            swap(i, j);
            i++;
        }
    }

    swap (part_end, i);

    return i;
}


template <class T, class TLess = IsLess<T>>
T find_k (T* arr, T* arr_end, T* k,
                            const TLess& isLess = TLess())
{
    T* part_begin = arr;
    T* part_end = arr_end;

    while (true)
    {
        if (part_begin == part_end)
            return *part_end;

        T* pivot = partition(part_begin, part_end, isLess);

        if (k == pivot)
            return *pivot;

        else if (k < pivot)
            part_end = pivot;

        else
            part_begin = pivot + 1;
    }
}

void solve()
{
    int N = 0, k = 0;
    cin >> N >> k;

    int* arr = new int[N];
    for (int i = 0; i < N; ++i)
        cin >> arr[i];

    cout << find_k(arr, arr+N-1, arr+k);

    return;
}

int main()
{
    try {
        solve();
    } catch(...){
        cout << "Some error";
    }
    return 0;
}


