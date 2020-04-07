//Дана очень длинная последовательность целых чисел длины n.
//Требуется вывести в отсортированном виде её первые k элементов.
//Последовательность может не помещаться в память. Время работы O(n * log(k)).
//Доп. память O(k). Использовать слияние.

#include<iostream>
using std::cin;
using std::cout;
#define INT_MAX 2147483647

template <typename T>
struct IsLess {
	bool operator()(const T& l, const T& r) const
	{
		return l < r;
	}
};

template <class T, class TLess = IsLess<T>>
T* MergeSort(T* arr, int len,
                        const TLess& isLess = TLess())
{
    if (len == 1) return arr;

    T* left = new T[len/2];
    for (int i = 0; i < len/2; i++) left[i] = arr[i];

    T* right = new T[len - len/2];
    for (int i = 0; i < len - len/2; i++) right[i] = arr[len/2 + i];

    left = MergeSort(left, len/2, isLess);
    right = MergeSort(right, len - len/2, isLess);

    arr = Merge (left, right, len, isLess);

    delete[] right;
    delete[] left;
    return arr;
}

template <class T, class TLess = IsLess<T>>
T* Merge(T* left, T* right, int len,
                        const TLess& isLess = TLess())
{
    T* result_arr = new T [len];
    int k1 = 0;
    int k2 = 0;

    for (int i = 0; i < len; i++) {

        if ((k2 == len - len/2) || ((k1 < len/2) && (isLess(left[k1], right[k2])))) {
            result_arr[i] = left[k1];
            k1++;
        }
        else {
            result_arr[i] = right[k2];
            k2++;
        }
    }

    return result_arr;
}

int main()
{
    int N = 0, k = 0;
    cin >> N >> k;

    int* arr = new int [2*k];
    for (int i = 0; i < 2*k; ++i)
        arr[i] = INT_MAX;

    while (N > k)
    {
        for (int i = k; i < 2*k; ++i)
            cin >> arr[i];
        arr = Merge(arr, MergeSort(arr + k, k), 2*k);
        N-=k;
    }

    for (int i = k; i < k+N; ++i)
        cin >> arr[i];
    arr = Merge(arr, MergeSort(arr + k, k), 2*k);



    for (int i = 0; i < k; ++i)
        cout << arr[i] << " ";

    delete[] arr;

    return 0;
}
