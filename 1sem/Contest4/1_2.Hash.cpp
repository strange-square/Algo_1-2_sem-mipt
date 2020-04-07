#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

template <typename T>
struct Cell{
    T value;
    bool clean;
};

template <typename T>
class Hash_table
{
private:

    int buffer_size;
    int busy_cell;
    T null_elem;

    Cell<T>* arr;

    bool add(T elem);
    bool del(T elem);
    int check(T elem);
    int find_pos(T elem, Cell<T>* cur_arr);

    int hash_1(T elem);
    int hash_2(T elem);
    void rehash();

public:

    Hash_table<T>(T elem);
    ~Hash_table<T>();

    bool command(char c, T elem);

};

template <typename T>
Hash_table<T>::Hash_table(T elem): buffer_size(2), busy_cell(0)
{
    null_elem = elem;
    arr = new Cell<T> [buffer_size];

    for (int i = 0; i < buffer_size; ++i)
        arr[i]= {elem, true};
}

template <typename T>
Hash_table<T>::~Hash_table()
{
    delete[] arr;
}

template <typename T>
bool Hash_table<T>::command(char c, T elem)
{
    if (c == '+')
        return add(elem);

    else if (c == '-')
        return del(elem);

    else if (c == '?')
        return (check(elem) != -1);
}

template <typename T>
int Hash_table<T>::find_pos(T elem, Cell<T>* cur_arr)
{
    unsigned int h1 = hash_1(elem);
    unsigned int h2 = hash_2(elem);

    while (!cur_arr[h1].clean && !(!cur_arr[h1].clean && (cur_arr[h1].value == null_elem)))
    {
        h1 = (h1 + h2) % buffer_size;
    }

    return h1;
}

template <typename T>
bool Hash_table<T>::add(T elem)
{
    if(check(elem) != -1)
        return false;

    if (buffer_size*3/4 == busy_cell)
        rehash();

    int h = find_pos(elem, arr);

    arr[h].clean = false;
    arr[h].value = elem;
    ++busy_cell;

    return true;
}

template <typename T>
bool Hash_table<T>::del(T elem)
{
    int h = check(elem);
    if(h == -1)
        return false;

    arr[h].value = null_elem;
    --busy_cell;

    return true;
}

template <typename T>
int Hash_table<T>::check(T elem)
{
    unsigned int h1 = hash_1(elem);
    unsigned int h2 = hash_2(elem);
    int i = buffer_size;

    while ( !(arr[h1].value == elem) && !(arr[h1].clean) && (i-- != 0))
        h1 = (h1 + h2) % buffer_size;

    if (arr[h1].value == elem)
        return h1;
    return -1;
}

template <typename T>
int Hash_table<T>::hash_1(T elem)
{
    int h = (int)elem[0];
    int size = elem.size();
    int p = 3;

    for (int i = 1; i < size; ++i)
        h = (h*p + (int)elem[i]) % buffer_size;

    return h%buffer_size;
}

template <typename T>
int Hash_table<T>::hash_2(T elem)
{
    int h = (int)elem[0];
    int size = elem.size();
    int p = 5;

    for (int i = 1; i < size; ++i)
        h = (h*p + (int)elem[i]) % buffer_size;

    return (h % 2) ? h%buffer_size : (h + 1)%buffer_size;
}

template <typename T>
void Hash_table<T>::rehash()
{
    buffer_size *= 2;
    busy_cell = 0;
    Cell<T>* old_arr = arr;
    arr = new Cell<T> [buffer_size];


    int end_arr = buffer_size / 2;

    for (int i = 0; i < buffer_size; ++i)
    {
        arr[i].clean = true;
        arr[i].value = null_elem;
    }

    for (int i = 0; i < end_arr; ++i)
    {
        if (old_arr[i].value == null_elem)
            continue;
        add(old_arr[i].value);
    }

    delete[] old_arr;
}

void solve()
{
    char c;
    string s;
    Hash_table<string> table("");

    while (cin >> c)
    {
        cin >> s;

        if (table.command(c, s))
            cout << "OK\n";
        else
            cout << "FAIL\n";
    }

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
