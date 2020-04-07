#include <iostream>
#include "queue.h"

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
class BST
{
private:
    Node<T>* root = NULL;

public:
    BST() {};
    void insert(T);

    void level_order();

    ~BST() {};
};

template <typename T>
void BST<T>::insert(T elem)
{
    Node<T>* current = root;
    while(current != NULL)
    {
        if(current->key < elem)
        {
            current = current->right;
            cout << "right";
        }
        else
        {
            current = current->left;
            cout << "left";
        }
    }
    cout << "\n";

    Node<T> node(elem);
    current = &node;

}

template <typename T>
void BST<T>::level_order()
{
    Queue<T> que;
    cout << "Level";
}

void solve()
{
    int N = 0;
    int elem = 0;
    BST<int> tree;

    cin >> N;

    while(N--)
    {
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
