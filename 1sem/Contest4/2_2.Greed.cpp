#include <iostream>
using std::cin;
using std::cout;

struct Time
{
    int begining = 0;
    int ending = 0;
};

struct CompareTime{
	bool operator() (const Time& left, const Time& right) const
	{
        return left.ending <= right.ending;
	}
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


//____________________________________________QUIK_SORT_____________________________________________________________//

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
T* partition (T* part_begin, T* part_end,
                                const TLess& isLess = TLess())
{
    T* i = part_begin;
    T* j = part_end - 1;
    T* pivot = mid_pivot(part_begin, part_end, isLess);

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
void quicksort_insert (T* part_begin, T* part_end,
                                const TLess& isLess = TLess())
{
    clock_t start_time = clock();
    if (part_end - part_begin > 50)
    {
        T* pivot = partition(part_begin, part_end - 1, isLess);

        quicksort_insert(part_begin, pivot, isLess);
        quicksort_insert(pivot + 1, part_end, isLess);
    }

    else
    {
        insertsort(part_begin, part_end, isLess);
    }
}
//______________________________________________________________________________________________________________//

template <class T>
T* resize(T* arr, int buffer_size)
{
    buffer_size *= 2;
    T* new_arr = new T [buffer_size];

    T* nptr = new_arr;
    T* end_arr = arr + buffer_size / 2;

    for (T *ptr = arr; ptr != end_arr; ++ptr, ++nptr)
        *nptr = *ptr;

    return new_arr;
}

int num_applications (Time* arr, int size_arr)
{
    int num = 1;

    CompareTime comp;
    quicksort_insert(arr, arr+size_arr, comp);

    int cur = 0;

    for (int i = 0; i < size_arr; ++i)
    {
        if (arr[i].begining >= arr[cur].ending)
        {
            cur = i;
            num++;
        }
    }
    return num;
}

void solve()
{
    int num = 0;
    int buffer_size = 2;

    Time* time = new Time [buffer_size];

    while (cin >> time[num].begining)
    {
        cin >> time[num].ending;
        num++;

        if (num == buffer_size)
        {
            Time* temp = resize(time, buffer_size);
            delete[] time;
            time = temp;
            buffer_size *= 2;
        }
    }

    cout << num_applications (time, num);

    delete[] time;
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
