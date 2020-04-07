#ifndef INSERTSORT_H
#define INSERTSORT_H

template <typename T>
struct IsLessInsert
{
    bool operator()(const T& l, const T& r) const
    {
        return l < r;
    }
};

template <class T, class TLess = IsLessInsert<T>>
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

#endif /* INSERTSORT_H */
