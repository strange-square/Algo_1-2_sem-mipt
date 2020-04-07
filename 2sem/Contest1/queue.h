#ifndef QUEUE
#define QUEUE

template <typename T>
class Queue
{
private:
    int size_arr, buffer_size;

    T* arr;
    T* begin_arr;
    T* end_arr ;

    void resize();

public:
    Queue();

    Queue& operator=(const Queue& Q);

    void  push(T value);
    T pop();
    bool is_empty();

    ~Queue();
};

template <typename T>
Queue<T>::Queue():
    size_arr(0),
    buffer_size(1)
{
    arr = new T[buffer_size];

    begin_arr = arr;
    end_arr   = arr;
}

/*
template <typename T>
Queue<T>::Queue& operator=(const Queue& Q)
{
    size_arr = Q.size_arr;
    buffer_size = Q.buffer_size
    arr = Q.arr;

    begin_arr = Q.begin_arr;
    end_arr   = Q.end_arr;
    return *this;
}*/

template <typename T>
Queue<T>::~Queue()
{
    delete[] arr;
}

template <typename T>
bool Queue<T>::is_empty()
{
    return (size_arr == 0);
}

template <typename T>
void Queue<T>::push(T value)
{
    if (size_arr == buffer_size)
        resize();
    size_arr++;

    *(end_arr++) = value; //вставляем значение и сдвигаем конец

    if (end_arr == (arr + buffer_size)) // зацикливаем конец
        end_arr = arr;
}

template <typename T>
T Queue<T>::pop()
{
    if (size_arr == 0)
        return NULL;
    size_arr--;

    T ret_val = *(begin_arr++); //сдвигаем начало

    if (begin_arr == (arr + buffer_size)) // зацикливаем начало
        begin_arr = arr;

    return ret_val;
}

template <typename T>
void Queue<T>::resize()
{
    buffer_size *= 2;
    T* new_arr = new T [buffer_size] {0};

    T* nptr = new_arr; // указатель на первый элемент нового массива
    T* new_end_arr = arr + buffer_size / 2; // указатель на физический конец старого массива

    for (T *ptr = begin_arr; ptr < new_end_arr; ++ptr, ++nptr) // перезаписываем постфикс
        *nptr = *ptr;


    for (T *ptr = arr; ptr < begin_arr; ++ptr, ++nptr) // перезаписываем префикс
        *nptr = *ptr;

    delete[] arr;

    arr = new_arr;
    begin_arr = arr;
    end_arr = arr + buffer_size / 2;
}

#endif
