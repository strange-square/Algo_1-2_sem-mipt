#ifndef MY_BST
#define MY_BST
#include <iostream>

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
    ~Node<T>()
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
		std::cout << node->key << " ";
	}
};

template <typename T>
struct Delete {
	bool operator()(const T& node) const
	{
		delete node;
	}
};

template < typename T, class TLess = IsLess<T> >
class BST
{
private:
    Node<T>* root;
    TLess isLess;

public:
    BST() : root(NULL){};

    void insert(T elem);

    template < class Tfunc = Output< Node<T>* > >
    void level_order(const Tfunc& func = Tfunc());

    ~BST()
    {
        level_order(Delete< Node<T>* >());
    }
};

template<typename T, class TLess>
void BST<T, TLess>::insert(T elem)
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

template <typename T, class TLess>
template<class Tfunc>
void BST<T, TLess>::level_order(const Tfunc& func)
{
    Queue< Node<T>* > que;
    que.push(root);
    Node<T>* current = root;
    while (!que.is_empty())
    {
        current = que.pop();
        if (current != NULL)
        {
            que.push(current->left);
            que.push(current->right);
            func(current);
        }
    }
}

#endif
