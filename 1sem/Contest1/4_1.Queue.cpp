//Реализовать очередь с динамическим зацикленным буфером.
//Формат входных данных.
//В первой строке количество команд n. n ≤ 1000000.
//Каждая команда задаётся как 2 целых числа: a b.
//a = 1 - push front
//a = 2 - pop front
//a = 3 - push back
//a = 4 - pop back
//Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
//Если дана команда pop*, то число b - ожидаемое значение.Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
//Формат выходных данных.
//Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

#include <iostream>

class Queue
{
private:
    int size_arr, buffer_size;

    int* arr;
    int* begin_arr;
    int* end_arr ;

    void resize();

public:
    Queue_();

    Queue_& operator=(const Queue_& Q);

    void  push_back(int value);
    int   pop_front();

    ~Queue_();
};

Queue_::Queue_() :
    size_arr(0),
    buffer_size(1)
{
    arr = new int[buffer_size];

    begin_arr = arr;
    end_arr   = arr;
}

/*Queue_::Queue_& operator=(const Queue_& Q)
{
    size_arr = Q.size_arr;
    buffer_size = Q.buffer_size
    arr = Q.arr;

    begin_arr = Q.begin_arr;
    end_arr   = Q.end_arr;
    return *this;
}*/

Queue_::~Queue_()
{
    delete[] arr;
}

void Queue_::push_back(int value)
{
    if (size_arr == buffer_size)
        resize();
    size_arr++;

    *(end_arr++) = value; //вставляем значение и сдвигаем конец

    if (end_arr == (arr + buffer_size)) // зацикливаем конец
        end_arr = arr;
}

int Queue_::pop_front()
{
    if (size_arr == 0)
        return -1;
    size_arr--;

    int ret_val = *(begin_arr++); //сдвигаем начало

    if (begin_arr == (arr + buffer_size)) // зацикливаем начало
        begin_arr = arr;

    return ret_val;
}

void Queue_::resize()
{
    buffer_size *= 2;
    int* new_arr = new int [buffer_size] {0};

    int* nptr = new_arr; // указатель на первый элемент нового массива
    int* new_end_arr = arr + buffer_size / 2; // указатель на физический конец старого массива

    for (int *ptr = begin_arr;  ptr < new_end_arr;      ++ptr, ++nptr) // перезаписываем постфикс
        *nptr = *ptr;


    for (int *ptr = arr;        ptr < begin_arr;        ++ptr, ++nptr) // перезаписываем префикс
        *nptr = *ptr;

    delete[] arr;

    arr = new_arr;
    begin_arr = arr;
    end_arr = arr + buffer_size / 2;
}


int main()
{
    int n = 0;
    std::cin >> n;

    Queue_ queue;
    int command = 0, value = 0;

    while (n--)
    {
        std::cin >> command >> value;

        if (command == 2)
        {
            if (value != queue.pop_front())
            {
                std::cout << "NO";
                return 0;
            }
        }
        else if (command == 3)
            queue.push_back(value);
        else
            std::cout << "Error\n";
    }

    std::cout << "YES";

    return 0;
}
