//В базе данных хранится N записей, вида (Name, a1, a2, … , ak) — во всех записях одинаковое число параметров.
//На вход задачи подаётся приоритет полей — перестановка на числах 1,...,k — записи нужно вывести в соответствии с этим приоритетом.
//В случае, если приоритет полей таков: 3 4 2 1, то это следует воспринимать так: надо читать как:
//приоритет значений из 3 колонки самый высокий, приоритет значений из колонки 4 ниже, приоритет значений из колонки 2 ещё ниже,
//а приоритет значений из колонки 1 самый низкий.

#include <iostream>

using std::cin;
using std::cout;

struct Data
{
    char* name;
    int* arr;

    Data() : name(nullptr), arr(nullptr){}
    ~Data() {}

    Data& operator=(const Data& right)
    {
        if (this == &right)
            return *this;

        name = right.name;
        arr = right.arr;
        return *this;
    }

    void update(int* a, char* n)
    {
        arr = a;
        name = n;
    }
};

template <typename T>
struct IsLess {
	bool operator()(const T& l, const T& r) const
	{
		return l < r;
	}
};

template <class T, class TLess = IsLess<T>>
void InsertSort(T* arr, T* end_arr,
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

class CompareWithPriority {
public:
	CompareWithPriority(const int* priority, const int* priority_end) :
                        priority_(priority), priority_end_(priority_end) {}

	bool operator() (const Data& left, const Data& right) const
	{
        for (int const* i = priority_; i != priority_end_; ++i)
        {
            if (left.arr[*i] != right.arr[*i]) return left.arr[*i] > right.arr[*i];
        }
        return true;
	}
private:

	const int* priority_;
	const int* priority_end_;
};

int main()
{
    int N = 0;
    int k = 0;
    cin >> N >> k;

    int* priority = new int [k];
    for (int i = 0; i < k; ++i)
    {
        cin >> priority[i];
        priority[i]--;
    }

    Data* data = new Data[N];
    char* buffer_name = new char [1000*1000 + 1];

    for (int i = 0; i < N; ++i)
    {
        int name_size = 0;
        cin.get();
        do
        {
            cin.get(buffer_name[name_size]);
        } while (buffer_name[name_size++] != ' ');

        char* name = new char[name_size];
        for (int p = 0; p < name_size; ++p)
            name[p] = buffer_name[p];
        name[name_size - 1] = '\n';


        int* arr = new int[k];
        for (int j = 0; j < k; ++j)
        {
            cin >> arr[j];
        }
        data[i].update(arr, name);
    }

    CompareWithPriority comparator (priority, priority + k);
    InsertSort(data, data + N, comparator);

    for (int i = 0; i < N; ++i)
    {
        int j = 0;
        do
        {
            cout << data[i].name[j++];
        } while (data[i].name[j-1] != '\n');
    }

    for (int i = 0; i < N; ++i)
    {
        delete[] data[i].arr;
        delete[] data[i].name;
    }
    delete[] buffer_name;
    delete[] data;
    delete[] priority;

    return 0;
}
