//На числовой прямой окрасили N отрезков.
//Известны координаты левого и правого концов каждого отрезка (Li и Ri). Найти длину окрашенной части числовой прямой.

#include <iostream>

using std::cin;
using std::cout;

struct Point
{
    int value = 0;
    bool closed = false;

};

template <typename T>
void swap (T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

int par_i (int i)
{
    return (i - 1) / 2;
}

struct ComparePoint{
	bool operator() (const Point& left, const Point& right) const
	{
        return left.value <= right.value;
	}
};

template <typename T>
struct IsLess {
	bool operator()(const T& l, const T& r) const
	{
		return l < r;
	}
};

template <class T, class TLess = IsLess<T>>
void sift_up(T* arr, int elem,
                         const TLess& isLess = TLess())
{
    int par = par_i(elem);
    while ((elem != 0) && (isLess(arr[elem],arr[par])))
    {
        swap (arr[elem], arr[par]);
        elem = par;
        par = par_i(par);
    }
}

template <class T, class TLess = IsLess<T>>
void sift_down(T* arr, int size_arr, int i,
                            const TLess& isLess = TLess())
{
    int left = 0;
    int right = 0;
    int min = 0;

    while (2*i + 1 < size_arr)
    {
        left = 2*i + 1;
        right = 2*i + 2;
        min = left;

        if ((right < size_arr) && (isLess(arr[right], arr[left])))
            min = right;

        if (isLess(arr[i], arr[min]))
            break;

        swap(arr[min], arr[i]);
        i = min;
    }
}

template <class T, class TLess = IsLess<T>>
T pop_min(T* arr, int last,
                        const TLess& isLess = TLess())
{
    T min = arr[0];
    arr[0] = arr[last];
    sift_down(arr, last+1, 0, isLess);
    return min;
}

template <class T, class TLess = IsLess<T>>
int colored_line (T* arr, int size_arr,
                        const TLess& isLess = TLess())
{
    int sum = 0;
    int open_balance = 0;
    T temp_point;
    int temp_begin = 0;

    Heap_sort(arr, size_arr, isLess);

    for (int i = 0; i < size_arr; ++i)
    {
        temp_point = arr[i];
        //pop_min(arr, size_arr-i-1, isLess);

        if (open_balance == 0) temp_begin = temp_point.value;

        if (temp_point.closed)
            open_balance--;
        else open_balance++;

        if (open_balance == 0) sum += temp_point.value - temp_begin;

    }

    return sum;
}

template <class T, class TLess = IsLess<T>>
void Heap_sort(T* arr, int size_arr,
                        const TLess& isLess = TLess())
{
   Heap_build(arr, size_arr, isLess);
   int heapSize = size_arr;
   for (T* i = arr + size_arr - 1; i != arr - 1; ++i)
   {
     swap(*arr, *i);
     heapSize--;
     sift_down(arr, 0, heapSize, isLess);
    }
}

template <class T, class TLess = IsLess<T>>
void Heap_build(T* arr, int size_arr,
                        const TLess& isLess = TLess())
{
    for (int i = size_arr/2; i >= 0; i--)
        sift_down(arr, size_arr, i, isLess);


}

void solve()
{
    int N = 0;
    cin >> N;
    N *= 2;

    Point* point = new Point [N];

    for (int i = 0; i < N; ++i)
    {
        cin >> point[i].value;
        cin >> point[++i].value;
        point[i].closed = true;
    }

    ComparePoint comp;
    Heap_build(point, N, comp);

    cout << colored_line(point, N, comp);

    delete[] point;
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
