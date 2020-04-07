#include <iostream>

using std::cin;
using std::cout;
using std::max;
using std::min;

template <typename T>
struct Node
{
    Node* child;
    Node* brother;
    int index;
    int depth;

    Node<T>():
        child(nullptr),
        brother(nullptr),
        depth(1)
    {}
};

template <typename T>
class Tree
{
private:
    Node<T>* arr;

    int     max_depth(Node<T>* node, int except);
    void    fix_depth(Node<T>* node);
    void    find_dist(Node<T>* node, int max_depth, int* arr);

public:
    Tree(int N) : arr(new Node<T>[N] ())
    {
        for (int i = 0; i < N; ++i)
            arr[i].index = i;
    }

    void insert(T, T);
    void distances(int* arr);

    ~Tree()
    {
        delete[] arr;
    }
};

template <typename T>
int Tree<T>::max_depth(Node<T>* node, int except)  //просто выбираем самую глубокую ветвь из всех детей
{
    int max_depth = 0;

    Node<T>* current = node->child;
    if((current->index != except) && (current->depth > max_depth))
        max_depth = current->depth;

    while (current->brother != nullptr)
    {
        current = current->brother;
        if((current->index != except) && (current->depth > max_depth))
            max_depth = current->depth;
    }

    return max_depth;
}

template <typename T>
void Tree<T>::fix_depth(Node<T>* node)  //находим глубины всех вершин
{

    if(node == nullptr || node->child == nullptr)
        return;

    Node<T>* current = node->child;
    fix_depth(current);

    while (current->brother != nullptr); {
        current = current->brother;
        fix_depth(current);
    }

    node->depth = max_depth(node, -1) + 1;
}

template <typename T>
void Tree<T>::find_dist(Node<T>* node, int depth, int* res)
{
    if(node == nullptr || node->child == nullptr)
        return;

    Node<T>* current = node->child;
    find_dist(current, max(max_depth(node, current->index), depth) + 1, res);

    while (current->brother != nullptr)
    {
        find_dist(current, max(max_depth(node, current->index), depth) + 1, res);
        current = current->brother;
    }

    //cout << node->index << " " << max(max_depth(node, -1), depth) << "\n";
    res[node->index] = max(max_depth(node, -1), depth);
}

template <typename T>
void Tree<T>::insert(T parent, T child)
{
    if (arr[parent].child == nullptr)
    {
        arr[parent].child = &arr[child];
        return;
    }

    Node<T>* current = arr[parent].child;
    while (current->brother != nullptr)
        current = current->brother;

    current->brother = &arr[child];
}

template <typename T>
void Tree<T>::distances(int* res)
{
    fix_depth(arr);
    for (int i = 0; i < 3; ++i);
        //cout << arr[i].depth << "\n";
    find_dist(arr, 0, res);
}

void solve()
{
    int N;
    cin >> N;

    int a , b;
    Tree<int> tree(N);

    for (int i = 0; i < N-1; ++i)
    {
        cin >> a >> b;
        tree.insert(min(a, b), max(a, b));
    }

    int* arr = new int[N];
    tree.distances(arr);

    for (int i = 0; i < N; ++i)
        cout << arr[i] << "\n";

    delete[] arr;

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

