#ifndef STACK
#define STACK

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

    void push(T value);
    T pop();
    void cancel_pop();
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
void Stack<T>::push(T value)
{
    if (size_arr == buffer_size)
        resize();

    *(arr + size_arr++) = value;
}


template <typename T>
T Stack<T>::pop()
{
    if (size_arr == 0) return (T)0;
    return arr[--size_arr];
}


template <typename T>
void Stack<T>::cancel_pop()
{
    size_arr++;
}

template <typename T>
bool Stack<T>::is_empty()
{
    return (size_arr == 0);
}

template <typename T>
void Stack<T>::resize()
{
    buffer_size *= 2;
    T* new_arr = new T [buffer_size] {0};

    T* nptr = new_arr;
    for (T* ptr = arr;  ptr < arr + size_arr; ++ptr, ++nptr)
        *nptr = *ptr;


    delete[] arr;

    arr = new_arr;
}
#endif
