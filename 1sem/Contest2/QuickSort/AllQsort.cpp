#include <iostream>
#include <fstream>
#include <ctime>

using std::cin;
using std::cout;
using std::ofstream;
using std::ifstream;

clock_t my_time;

template <typename T>
class Stack
{
private:
    int size_arr, buffer_size;
    T* arr;

    void resize();

public:
    Stack();

    Stack& operator=(const Stack&);

    void push_back(T value);
    T pop_back();
    bool is_empty();

    ~Stack();
};

template <typename T>
Stack<T>::Stack() :
    size_arr(0),
    buffer_size(1)
{
    arr = new T[buffer_size];
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] arr;
}

template <typename T>
void Stack<T>::push_back(T value)
{
    if (size_arr == buffer_size)
        resize();

    *(arr + size_arr++) = value;
}

template <typename T>
T Stack<T>::pop_back()
{
    if (!is_empty())
        return arr[--size_arr];
}

template <typename T>
bool Stack<T>::is_empty()
{
    return size_arr == 0;
}

template <typename T>
void Stack<T>::resize()
{
    buffer_size *= 2;
    T* new_arr = new T [buffer_size];

    T* nptr = new_arr;
    for (T* ptr = arr;  ptr < arr + size_arr; ++ptr, ++nptr)
    {
        *nptr = *ptr;
    }


    delete[] arr;

    arr = new_arr;
}

template <typename T>
struct Pair{
    T l;
    T r;
    Pair<T> (T left, T right) : l(left), r(right) {};
    Pair<T> () {};
};

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
    //T* pivot = rand_pivot(part_begin, part_end + 1);
    T* pivot = mid_pivot(part_begin, part_end, isLess);
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
void insertsort(T* arr, T* end_arr,
                const TLess& isLess = TLess())
{
    T temp = *arr;
    T *j = nullptr;
    for (T* i = arr; i != end_arr; ++i)
    {
        temp = *i;
        for (j = i; (j != arr) && (!isLess(*(j-1), temp)); --j)
            *j = *(j-1);
        *j = temp;
    }
}

template <class T, class TLess = IsLess<T>>
void quicksort (T* part_begin, T* part_end,
                                const TLess& isLess = TLess())
{
    clock_t start_time = clock();

    if (part_begin != part_end)
    {
        T* pivot = partition(part_begin, part_end - 1, isLess);

        quicksort(part_begin, pivot, isLess);
        quicksort(pivot + 1, part_end, isLess);
    }
    my_time = clock() - start_time;
}

template <class T, class TLess = IsLess<T>>
T* partition_2 (T* part_begin, T* part_end,
                                const TLess& isLess = TLess())
{
    T* i = part_begin;
    T* j = part_end - 1;
    //T* pivot = rand_pivot(part_begin, part_end + 1);
    T* pivot = mid_pivot(part_begin, part_end, isLess);
    //T* pivot = part_end;

    swap (pivot, part_end);

    do {
        while (isLess(*i, *part_end)) i++;
        while ( isLess(*part_end, *j)) j--;
        if (i <= j) {
          swap(i, j);
          i++; j--;
        }
      } while ( i<=j );

    swap (part_end, i);

    return i;
}

template <class T, class TLess = IsLess<T>>
void quicksort_norec (T* part_begin, T* part_end,
                                const TLess& isLess = TLess())
{
    clock_t start_time = clock();
    Stack < Pair<T*> > s;
    Pair <T*> pair_be(part_begin, part_end);
    s.push_back(pair_be);

    while (!s.is_empty())
    {
        Pair <T*> pair = s.pop_back();
        if (pair.r - pair.l <= 0)
            continue;
        T* pivot = partition_2(pair.l, pair.r, isLess);
        Pair <T*> pair_left(pair.l, pivot - 1);
        Pair <T*> pair_right(pivot + 1, pair.r);

        if (pivot - pair.l > pair.r - pivot)
        {
           s.push_back(pair_left);
           s.push_back(pair_right);
        }
        else
        {
           s.push_back(pair_right);
           s.push_back(pair_left);
        }
    }
    my_time = clock() - start_time;
}

template <class T, class TLess = IsLess<T>>
void quicksort_onerec (T* part_begin, T* part_end,
                                const TLess& isLess = TLess())
{
    clock_t start_time = clock();
    Stack < Pair<T*> > s;
    Pair <T*> pair_be(part_begin, part_end);
    s.push_back(pair_be);

    while (!s.is_empty())
    {
        Pair <T*> pair = s.pop_back();
        if (pair.r - pair.l <= 0)
            continue;
        T* pivot = partition_2(pair.l, pair.r, isLess);

        if (pivot - pair.l > pair.r - pivot)
        {
           Pair <T*> pair_left(pair.l, pivot - 1);
           s.push_back(pair_left);
           quicksort_onerec(pivot + 1, pair.r, isLess);
        }
        else
        {
           Pair <T*> pair_right(pivot + 1, pair.r);
           s.push_back(pair_right);
           quicksort_onerec(pair.l, pivot - 1, isLess);
        }
    }
    my_time = clock() - start_time;
}

template <class T, class TLess = IsLess<T>>
void quicksort_insert (T* part_begin, T* part_end,
                                const TLess& isLess = TLess())
{
    clock_t start_time = clock();
    if (part_end - part_begin > 50)
    {
        T* pivot = partition_2(part_begin, part_end - 1, isLess);

        quicksort_insert(part_begin, pivot, isLess);
        quicksort_insert(pivot + 1, part_end, isLess);
    }

    else
    {
        insertsort(part_begin, part_end, isLess);
    }
    my_time = clock() - start_time;
}

void solve()
{

    int N = 10;
    int arr[N];
    for (int i = 0; i < N; ++i)
        cin >> arr[i];
    quicksort_norec(arr, arr + N);
    for (int i = 0; i < N; ++i)
        cout << arr[i];
    /*ifstream fin("rand1.txt");
    int N = 1000000;

    int* arr = new int [N];
    for (int i = 0; i < N; ++i)
        fin >> arr[i];

    fin.close();

    quicksort_insert(arr, arr + N);
    cout << my_time << "\n";

    fin.open("rand2.txt");

    arr = new int [N];
    for (int i = 0; i < N; ++i)
        fin >> arr[i];

    fin.close();

    quicksort_insert(arr, arr + N);
    cout << my_time << "\n";

    fin.open("rand3.txt");

    arr = new int [N];
    for (int i = 0; i < N; ++i)
        fin >> arr[i];

    fin.close();

    quicksort_insert(arr, arr + N);
    cout << my_time << "\n";

    fin.open ("partly_sorted.txt");

    arr = new int [N];
    for (int i = 0; i < N; ++i)
        fin >> arr[i];

    fin.close();

    quicksort_insert(arr, arr + N);
    cout << my_time << "\n";

    fin.open("sorted.txt");

    arr = new int [N];
    for (int i = 0; i < N; ++i)
        fin >> arr[i];

    fin.close();

    quicksort_norec(arr, arr + N);
    cout << my_time << "\n";

    delete[] arr;*/
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

