#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::ofstream;
using std::ifstream;

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

template <typename T>
T* rand_pivot(T* part_begin, T* part_end)
{
    srand(time(0));
    return part_begin + rand() % (part_end - part_begin);
}

template <class T, class TLess = IsLess<T>>
T* mid_pivot(T* part_begin, T* part_end,
                                const TLess& isLess = TLess())
{
    T* mid = (part_end - part_begin) / 2 + part_begin;

    if (isLess(*mid, *part_begin))
        swap (part_begin, mid);

    if (isLess(*part_end, *part_begin))
        swap (part_begin, part_end);

    if (isLess(*mid, *part_end))
        swap (part_end, mid);

    return part_end;
}

template <class T, class TLess = IsLess<T>>
T* partition (T* part_begin, T* part_end,
                                const TLess& isLess = TLess())
{
    T* i = part_begin;
    T* pivot = rand_pivot(part_begin, part_end + 1);
    //T* pivot = mid_pivot(part_begin, part_end, isLess);
    //T* pivot = part_end;

    swap (pivot, part_end);


    for (T* j = part_begin; j != part_end; j++)
    {
        if (isLess(*j, *part_end))
        {
            swap(i, j);
            i++;
        }
    }

    swap (part_end, i);

    return i;
}


template <class T, class TLess = IsLess<T>>
void quicksort (T* part_begin, T* part_end,
                                const TLess& isLess = TLess())
{
    if (part_begin != part_end)
    {
        T* pivot = partition(part_begin, part_end - 1, isLess);

        quicksort(part_begin, pivot, isLess);
        quicksort(pivot + 1, part_end, isLess);
    }
}

void solve()
{
    ifstream fin("rand3.txt");
    int N = 1000000;

    int* arr = new int [N];
    for (int i = 0; i < N; ++i)
        fin >> arr[i];

    fin.close();

    quicksort(arr, arr + N);


    ofstream fout("rand3_sort1.txt", ofstream::trunc);

    for (int i = 0; i < N; ++i)
        fout << arr[i] << "\n";
    fout.close();

    delete[] arr;
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

