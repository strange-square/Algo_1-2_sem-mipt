//На числовой прямой окрасили N отрезков.
//Известны координаты левого и правого концов каждого отрезка (Li и Ri). Найти длину окрашенной части числовой прямой.

#include <iostream>

#define cin std::cin
#define cout std::cout

struct Point
{
    int value = 0;
    bool closed = false;

};

bool comparator_point(const Point& left, const Point& right)
    {
        return left.value <= right.value;
    }

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

template <typename T>
void sift_up(T* arr, int elem, bool (*comp)(const T&, const T&))
{
    int par = par_i(elem);
    while ((elem != 0) && (comp(arr[elem],arr[par])))
    {
        swap (arr[elem], arr[par]);
        elem = par;
        par = par_i(par);
    }
}

template <typename T>
void sift_down(T* arr, int size_arr, int i, bool (*comp)(const T&, const T&))
{
    int left = 0;
    int right = 0;
    int min = 0;

    while (2*i + 1 < size_arr)
    {
        left = 2*i + 1;
        right = 2*i + 2;
        min = left;

        if ((right < size_arr) && (comp(arr[right], arr[left])))
            min = right;

        if (comp(arr[i], arr[min]))
            break;

        swap(arr[min], arr[i]);
        i = min;
    }
}

template <typename T>
T pop_min(T* arr, int last, bool (*comp)(const T&, const T&))
{
    T min = arr[0];
    arr[0] = arr[last];
    sift_down(arr, last+1, 0, comp);
    return min;
}

int colored_line (Point* arr, int size_arr, bool (*comp)(const Point&, const Point&))
{
    int sum = 0;
    int open_balance = 0;
    Point temp_point;
    int temp_begin = 0;

    for (int i = 0; i < size_arr; ++i)
    {
        temp_point = pop_min(arr, size_arr-i-1, comp);

        if (open_balance == 0) temp_begin = temp_point.value;

        if (temp_point.closed)
            open_balance--;
        else open_balance++;

        if (open_balance == 0) sum += temp_point.value - temp_begin;

    }

    return sum;
}

template <typename T>
void Heap_sort(T* arr, int size_arr, bool (*compare)(const T&, const T&))
{
    for (int i = size_arr/2; i >= 0; i--)
        sift_down(arr, size_arr, i, compare);

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
    Heap_sort(point, N, comparator_point);

    /*for (int i = 0; i < N; ++i) cout << point[i].value << " ";
    cout << "\n";*/



    cout << colored_line(point, N, comparator_point);

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
