//Имеется рекуррентная последовательность A1, A2, ..., AN, строящаяся по следующему правилу:
//A1 = K
//Ai+1 = (Ai * M) % (2^32-1) % L
//Требуется найти сумму всех нечётных по порядку элементов в отсортированной по неубыванию последовательности по модулю L.

#include <iostream>

using std::cin
using std::cout

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
void radix_sort (T* arr, T* arr_end,
                        const TLess& isLess = TLess())
{

}

void solve()
{
    unsigned long long N = 0;
    unsigned long long K = 0;
    unsigned long long M = 0;
    unsigned long long L = 0;

    cin >> N >> K >> M >> L;

    unsigned int* arr = new unsigned int[N];

    arr[0] = K;
    for (unsigned long long i = 1; i < N; i++)
        arr[i] = (unsigned int)(((arr[i-1] * M) & 0xFFFFFFFFU) % L);

    radix_sort(arr, arr, arr+N-1);

    unsigned long long sum = 0;
    for (unsigned long long i = 0; i < N; i += 2)
        sum = (sum + arr[i]) % L;

    cout << sum;
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
