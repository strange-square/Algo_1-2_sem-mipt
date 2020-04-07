#include <iostream>
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
    //std::cout << "push_back()";
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

using std::cin;
using std::cout;

template <typename T>
struct Node
{
    T key;
    Node* left;
    Node* right;

    Node<T>(T elem):
        key(elem),
        right(NULL),
        left(NULL)
    {}
};

template <typename T>
struct IsLess {
	bool operator()(const T& l, const T& r) const
	{
		return l < r;
	}
};

template <typename T>
struct Output {
	bool operator()(const T& node) const
	{
		cout << node->key << " ";
	}
};

template <typename T>
struct Delete {
	bool operator()(const T& node) const
	{
		delete[] node;
	}
};

template <typename T>
class BST
{
private:
    Node<T>* root;

public:
    BST() : root(NULL) {};

    template <class TLess = IsLess<T>>
    void insert(T, const TLess& isLess = TLess());

    template <class Tfunc = Output<Node<T>*>>
    void level_order(const Tfunc& func = Tfunc());

    ~BST()
    {
        level_order(Delete<Node<T>*>());
    }
};

template <class T>
template <class TLess>
void BST<T>::insert(T elem, const TLess& isLess)
{
    Node<T>* node = new Node<T>(elem);
    if(root == NULL)
    {
        root = node;
        return;
    }

    Node<T>* current = root;
    Node<T>* parent = NULL;
    bool is_right = true;

    while(current != NULL)
    {
        parent = current;
        bool comp = isLess(current->key, elem);
        current = (comp ? current->right : current->left);
        is_right = comp;
    }

    if (is_right)
        parent->right = node;
    else
        parent->left = node;

}

template <typename T>
template<class Tfunc>
void BST<T>::level_order(const Tfunc& func)
{
    Queue<Node<T>*> que;
    que.push(root);
    Node<T>* current = root;
    while (!que.is_empty())
    {
        current = que.pop();

        if ((current->left) != NULL)
            que.push(current->left);
        if ((current->right) != NULL)
            que.push(current->right);

        func(current);
    }
}

void solve()
{
    int N = 0;
    BST<int> tree;

    cin >> N;

    while(N--)
    {
        int elem;
        cin >> elem;
        tree.insert(elem);
    }

    tree.level_order();
}

int main()
{
    try
    {
        solve();
    }
    catch (...)
    {
        cout << "Some error";
    }
    return 0;
}
