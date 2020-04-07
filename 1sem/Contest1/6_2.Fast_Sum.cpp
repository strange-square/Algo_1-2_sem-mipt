//Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
//Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений.
//Требуется написать программу, которая определяет минимальное время, достаточное для вычисления суммы заданного набора чисел.
#include <iostream>

class Heap
{
private:
    int size_arr, buffer_size;
    int* arr;

    void resize();

public:
    Heap(int*, int);
    Heap& operator=(const Heap&);
    Heap (const Heap&);

    void  push (int value);
    int   pop_min();
    void  sift_down(int index);
    void  sift_up(int index);
    bool  is_empty();

    ~Heap();
};

Heap::Heap(int* new_arr, int size) :
    size_arr(size),
    buffer_size(size+1)
{
    arr = new_arr;
    for (int i = size/2; i >= 0; i--)
        sift_down(i);

}

Heap::~Heap()
{
    delete[] arr;
}

Heap& Heap::operator=(const Heap& other)
{
    if (this != &other) // защита от неправильного самоприсваивания
    {
        //выделяем "новую" память и копируем элементы
        int* tmp_arr = new int[other.buffer_size];

        int* nptr = tmp_arr;
        int* end_arr = other.arr + other.size_arr;
        for (int* ptr = other.arr;  ptr < end_arr; ++ptr, ++nptr)
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


Heap::Heap (const Heap& other)
{
    size_arr = other.size_arr;
    buffer_size = other.buffer_size;
    arr = new int[buffer_size];

    int* nptr = arr;
    int* end_arr = other.arr + size_arr;
    for (int* ptr = other.arr;  ptr < end_arr; ++ptr, ++nptr)
    {
        *nptr = *ptr;
    }
}

void Heap::push(int value)
{
    if ((++size_arr) == buffer_size)
        resize();
    arr[size_arr - 1] = value;
    sift_up(size_arr - 1);
}

int Heap::pop_min()
{
    int min = arr[0];
    arr[0] = arr [--size_arr];
    sift_down(0);
    return min;
}

void Heap::sift_down(int i)
{
    while (2*i + 1 < size_arr)
    {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int j = left;

        if ((right < size_arr) && (arr[right] < arr[left]))
            j = right;
        if (arr[i] <= arr[j])
            break;

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i = j;
    }
}

void Heap::sift_up(int i)
{
    while (arr[i] < arr[(i - 1) / 2]) //поднимаем, пока элемент больше отца
    {
        int temp = arr[i];
        arr[i] = arr[(i - 1) / 2];
        arr[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
    }
}

void Heap::resize()
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

bool Heap::is_empty()
{
    return (size_arr == 1);
}

int min_sum(Heap& heap)
{
    int min_sum = 0;
    int global_sum = 0;
    while (!heap.is_empty())
    {
        min_sum = heap.pop_min() + heap.pop_min();
        heap.push(min_sum);
        global_sum += min_sum;
    }
    return global_sum;
}

int main()
{
    int n = 0;
    std::cin >> n;
    int* arr = new int [n];
    for (int i = 0; i<n; i++)
        std::cin >> arr[i];
    Heap heap(arr, n);
    for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
    std::cout << "\n";

    std::cout << min_sum(heap);
    delete[] arr;
    return 0;
}
