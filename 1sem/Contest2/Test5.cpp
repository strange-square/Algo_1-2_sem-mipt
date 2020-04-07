//Имеется рекуррентная последовательность A1, A2, ..., AN, строящаяся по следующему правилу:
//A1 = K
//Ai+1 = (Ai * M) % (2^32-1) % L
//Требуется найти сумму всех нечётных по порядку элементов в отсортированной по неубыванию последовательности по модулю L.

#include <iostream>

using std::cin;
using std::cout;

typedef unsigned long long ull;
const unsigned int size_rad = 256 * 256;

template <typename T>
void swap (T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
};

template <typename T>
struct GetDigit
{
    const ull mult_rad = 256 * 256 - 1;
    unsigned int operator()(const T& i, const size_t r) const
	{
        return (i >> 8 * r) & (mult_rad);
	}
};

template <class T, class TGet = GetDigit<T>>
void count_sort (T* arr, size_t arr_size, T* res_arr, size_t key,
                        const TGet& get_rad = TGet())
{
    size_t* value_arr = new size_t [size_rad];
    size_t count = 0;
    size_t j = 0;
    size_t tmp = 0;

    for (j = 0; j < size_rad; ++j)
            value_arr[j] = 0;

    for (j = 0; j < arr_size; ++j){
        value_arr[get_rad(arr[j], key)]++;
    }
    count = 0;

    for (j = 0; j < size_rad; ++j)
    {
        tmp = value_arr[j];
        value_arr[j] = count;
        count += tmp;
    }

    for (j = 0; j < arr_size; ++j)
    {
        res_arr[value_arr[get_rad(arr[j], key)]] = arr[j];
        value_arr[get_rad(arr[j], key)] ++;
    }
}

template <class T, class TGet = GetDigit<T>>
void LSD_sort (T* arr, size_t arr_size,
                        const TGet& get_rad = TGet())
{
    const unsigned int size_rad = 256 * 256;
    size_t* value_arr = new size_t [size_rad];
    T* res_arr = new T [arr_size];

    for (size_t key = 0; key < sizeof(T)/2; ++key)
    {
        count_sort(arr, arr_size, res_arr, key);

        swap(arr, res_arr);
    }

    delete[] res_arr;
    delete[] value_arr;
}

void solve()
{


    ull N = 0;
    ull K = 0;
    ull M = 0;
    ull L = 0;

    cin >> N >> K >> M >> L;

    unsigned int* arr = new unsigned int[N];

    arr[0] = K;
    for (ull i = 1; i < N; i++)
    {
        arr[i] = (unsigned int)(((arr[i-1] * M) & 0xFFFFFFFFU) % L);
    }

    LSD_sort(arr, N);

    ull sum = 0;
    for (ull i = 0; i < N; i += 2){
        sum += arr[i];
        if (sum >= L) sum %= L;
    }
    cout << sum;

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
