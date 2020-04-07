#include <iostream>

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
    return T();
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
