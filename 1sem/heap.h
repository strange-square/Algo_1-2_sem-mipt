template <typename T>
void swap (T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
struct IsLess {
	bool operator()(const T& l, const T& r) const
	{
		return l < r;
	}
};

template <typename T>
class Heap
{
private:
    int size_arr, buffer_size;
    T* arr;

    void resize();

public:
    Heap(T*, int);
    Heap& operator=(const Heap&);
    Heap (const Heap&);

    void  push (T value);
    T   pop_min();
    void  sift_down(int index);
    void  sift_up(int index);
    bool  is_empty();

    ~Heap();
};

template <typename T>
Heap<T>::Heap(T* new_arr, int size) :
    size_arr(size),
    buffer_size(size+1)
{
    arr = new_arr;
    for (int i = size/2; i >= 0; i--)
        sift_down(i);

}

template <typename T>
Heap<T>::~Heap()
{
    delete[] arr;
}

template <typename T>
Heap<T>& Heap<T>::operator=(const Heap& other)
{
    if (this != &other) // защита от неправильного самоприсваивания
    {
        //выделяем "новую" память и копируем элементы
        T* tmp_arr = new T[other.buffer_size];

        T* nptr = tmp_arr;
        T* end_arr = other.arr + other.size_arr;
        for (T* ptr = other.arr;  ptr < end_arr; ++ptr, ++nptr)
        {
            *nptr = *ptr;
        }

        // освобождаем "старую" память
        delete [] arr;

        //присваиваем значения в "новой" памяти объекту
        arr = tmp_arr;
        size_arr = other.size_arr;
        buffer_size = other.buffer_size;
    }
    // по соглашению всегда возвращаем *this
    return *this;
}

template <typename T>
Heap<T>::Heap (const Heap& other)
{
    size_arr = other.size_arr;
    buffer_size = other.buffer_size;
    arr = new T[buffer_size];

    T* nptr = arr;
    T* end_arr = other.arr + size_arr;
    for (T* ptr = other.arr;  ptr < end_arr; ++ptr, ++nptr)
    {
        *nptr = *ptr;
    }
}

template <typename T>
void Heap<T>::push(T value)
{
    if ((++size_arr) == buffer_size)
        resize();
    arr[size_arr - 1] = value;
    sift_up(size_arr - 1);
}

template <class T, class TLess = IsLess<T>>
T Heap<T>::pop_min(T* arr, int last,
                        const TLess& isLess = TLess())
{
    T min = arr[0];
    arr[0] = arr[last];
    sift_down(arr, last+1, 0, isLess);
    return min;
}

template <class T, class TLess = IsLess<T>>
void Heap<T>::sift_down(T* arr, int size_arr, int i,
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
void Heap<T>::sift_up(T* arr, int elem,
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

template <typename T>
void Heap<T>::resize()
{
    buffer_size *= 2;
    int* new_arr = new int [buffer_size] {0};

    int* nptr = new_arr;
    int* end_arr = arr + size_arr;
    for (int* ptr = arr;  ptr < end_arr; ++ptr, ++nptr)
    {
        *nptr = *ptr;
    }

    delete[] arr;

    arr = new_arr;
}

template <typename T>
bool Heap<T>::is_empty()
{
    return (size_arr == 1);
}

