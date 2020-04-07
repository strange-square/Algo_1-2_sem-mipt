//Пара слов называется стековой анаграммой, если одно слово можно получить из другого, проведя последовательность стековых операций с его буквами
//(взять очередную букву исходного слова и поместить ее в стек; взять букву из стека и добавить ее в конец выходного слова).
//Для заданной пары слов требуется определить, можно ли выполнить последовательность стековых операций, переводящую первое слово во второе.
//Все буквы в слове различные. Длина анаграммы ≤ 10000.
#include <iostream>

class Stack
{
private:
    int size_arr, buffer_size;
    int* arr;

    void resize();

public:
    Stack();

    Stack& operator=(const Stack&);

    void  push_back(char value);
    char   pop_back();
    void  cancel_pop();

    ~Stack();
};

Stack::Stack() :
    size_arr(0),
    buffer_size(1)
{
    arr = new char[buffer_size];
}

Stack::~Stack()
{
    delete[] arr;
}

void Stack::push_back(char value)
{
    if (size_arr == buffer_size)
        resize();

    *(arr + size_arr++) = value;
}

char Stack::pop_back()
{
    if (size_arr == 0) return ' ';
    return arr[--size_arr];
}

void Stack::cancel_pop()
{
    size_arr++;
}

void Stack::resize()
{
    buffer_size *= 2;
    char* new_arr = new char [buffer_size] {0};

    char* nptr = new_arr;
    for (char* ptr = arr;  ptr < arr + size_arr; ++ptr, ++nptr)
    {
        *nptr = *ptr;
    }


    delete[] arr;

    arr = new_arr;
}

bool str_is_anagram(char* str_in, char* str_out, int size_str)
{
    Stack st;
    int count_in = 0, count_out = 0;

    while (count_out < size_str)
    {
        while ((str_out[count_out] != str_in[count_in]) && (count_in < size_str))
        {
            //std::cout << str_out[count_out] << " != " << str_in[count_in] << std::endl;
            st.push_back(str_in[count_in++]);
        }

        if (count_in == size_str)
            return false;

        count_out++;
        count_in++;

        while (str_out[count_out] == st.pop_back())
        {
            count_out++;
        }
        st.cancel_pop();
    }
    return true;
}

int main()
{
    char str_in[10005], str_out[10005];

    int i = 0;

    do {
        str_in[i] = getchar();
    } while (str_in[i++] != ' ');

    int size_str = i - 1;

    i = 0;

    do {
        str_out[i++] = getchar();
    } while (i < size_str);

    if (str_is_anagram(str_in, str_out, size_str))
        std::cout << "YES";
    else std::cout << "NO";

    return 0;
}

