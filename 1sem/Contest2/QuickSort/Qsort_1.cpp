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

template <class T, class TLess = IsLess<T>>
T* partition (T* part_begin, T* part_end,
                                const TLess& isLess = TLess())
{
    T* i = part_begin;
    T* pivot = part_begin + rand() % (part_end - part_begin);

    swap (pivot, part_end);


    for (T* j = part_begin; j < part_end; j++)
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
void quicksort (T* arr, T* part_begin, T* part_end,
                                const TLess& isLess = TLess())
{
    if (part_begin < part_end)
    {
        T* pivot = partition(part_begin, part_end, isLess);

        quicksort(arr, part_begin, pivot - 1, isLess);
        quicksort(arr, pivot + 1, part_end, isLess);
    }
}

/*void solve()
{
    int N = 0;
    cin >> N;

    int* arr = new int [N];
    for (int i = 0; i < N; ++i)
        cin >> arr[i];

    quicksort(arr, arr, arr+N-1);

    for (int i = 0; i < N; ++i)
        cout << arr[i] << " ";
    return;

}*/

void solve()
{
    ifstream fin("rand2.txt");
    int N = 1000000;

    int* arr = new int [N];
    for (int i = 0; i < N; ++i)
        fin >> arr[i];

    fin.close();

    quicksort(arr, arr, arr+N-1);


    ofstream fout("rand_sort.txt", ofstream::trunc);
    for (int i = 0; i < N; ++i)
        fout << arr[i] << "\n";
    fout.close();

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
