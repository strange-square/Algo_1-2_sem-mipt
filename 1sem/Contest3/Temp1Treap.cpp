#include <iostream>
#include "queue.h"
#include "BST.h"

using std::cin;
using std::cout;

template <typename T>
struct Output_Treap {
	bool operator()(const T& node) const
	{
		cout << node->key.X << " ";
	}
};

template <class T, class F>
struct Pair
{
    T X;
    F Y;

    Pair<T, F>(T a, F b):
        X(a),
        Y(b)
    {}
    Pair<T, F>()
    {}
    ~Pair<T, F>()
    {}
};

template<typename T>
Node< Pair<T, int> >* copy_treap(const Node< Pair<T, int> >* node)
{
    if (!node)
        return NULL;
    using NodeT = Node< Pair<T, int> >;

    NodeT* result = new NodeT(*node);
    result->left = (node->left ? copy_treap(node->left) : NULL);
    result->right = (node->right ? copy_treap(node->right) : NULL);
}

template < typename T, class TLess = IsLess<T> >
class Treap
{
private:
    Node< Pair<T, int> >* root;
    TLess isLess;

public:
    Treap() : root(NULL) {};
    Treap(const Treap<T, TLess>& other) : root(copy_treap(other.root)) {};

    Treap(Node< Pair<T, int> >* node) : root(node) {};

    Treap& operator= (const Treap &Tr);

    Pair< Treap<T, TLess>, Treap<T, TLess> > split(T);

    static Treap<T, TLess> merge(const Treap<T, TLess>&, const Treap<T, TLess>&);

    void insert(T, int);

    template < class Tfunc = Output_Treap< Node< Pair<T, int> >* > >
    void level_order(const Tfunc& func = Tfunc());;

    ~Treap()
    {
        //level_order(Delete<Node<Pair<T, int>>*>());
    }
};

template<typename T, class TLess>
Treap<T, TLess>& Treap<T, TLess>::operator= (const Treap<T, TLess> &Tr)
{
     root = copy_treap(Tr.root);
     return *this;
}

template<typename T, class TLess>
Pair< Treap<T, TLess>, Treap<T, TLess> > Treap<T, TLess>::split(T elem)
{
    if (root == NULL)
        return Pair< Treap<T, TLess>, Treap<T, TLess> >(Treap<T> (), Treap<T> ());

    Pair<Treap<T, TLess>, Treap<T, TLess> > Tr1_Tr2;

    if (isLess(elem, root->key.X))
    {
        Treap<T> Tr_temp(root->left);
        Tr1_Tr2 = Tr_temp.split(elem);
        root->left = copy_treap(Tr1_Tr2.Y.root);

        return Pair<Treap<T, TLess>, Treap<T, TLess>>(Tr1_Tr2.X, *this);

    }

    else
    {
        Treap<T> Tr_temp(root->right);
        Tr1_Tr2 = Tr_temp.split(elem);
        root->right = copy_treap(Tr1_Tr2.X.root);

        return Pair<Treap<T, TLess>, Treap<T, TLess>>(*this, Tr1_Tr2.Y);
    }
}

/*template<typename T, class TLess>
Treap<T, TLess> Treap<T, TLess>::merge(const Treap<T, TLess>& Tr1, const Treap<T, TLess>& Tr2)
{
    using TreapT = Treap<T, TLess>;

    if (Tr2.root == NULL)
        return Tr1;
    if (Tr1.root == NULL)
        return Tr2;

    if (Tr1.root->key.Y > Tr2.root->key.Y)
    {
        TreapT Tr1_copy = Tr1;
        TreapT right(Tr1_copy.root->right);

        right = merge(right, Tr2);
        Tr1_copy.root->right = right.root;

        return Tr1_copy;
    }
    else
    {
        Tr2.root->left = merge(Tr1, Tr2.root->left);
        return Tr2;
    }
}*/

template<typename T, class TLess>
void Treap<T, TLess>::insert(T elem, int priority)
{
    Pair<T, int>* inserted = new Pair<T, int>(elem, priority);
    Node< Pair<T, int> >* node = new Node< Pair<T, int> >(*inserted);

    if(root == NULL)
    {
        root = node;
        return;
    }

    return;

    Node<Pair<T, int> >* current = root;
    Node<Pair<T, int> >* parent = NULL;
    T split_key = root->key.X;
    bool is_right = true;

    while(!isLess(current->key.Y, priority))
    {
        parent = current;
        bool comp = isLess(current->key.X, elem);
        current = (comp ? current->right : current->left);
        is_right = comp;
    }


    if (is_right)
        parent->right = node;
    else
        parent->left = node;

    Treap<T> temp(current);
    Pair<Treap<T, TLess>, Treap<T, TLess> > Tr1_Tr2 = temp.split(split_key);

    node->right = copy_treap(Tr1_Tr2.X.root);
    node->left = copy_treap(Tr1_Tr2.Y.root);
}

template <typename T, class TLess>
template<class Tfunc>
void Treap<T, TLess>::level_order(const Tfunc& func)
{
    Queue< Node<Pair<T, int> >* > que;
    que.push(root);
    Node<Pair<T, int> >* current = root;
    while (!que.is_empty())
    {
        current = que.pop();
        if (current != NULL)
        {
            cout << "current\n";
            que.push(current->left);
            que.push(current->right);
            func(current);
        }
    }
}

void solve()
{
    int N = 0;
    BST<int> tree;
    Treap<int> treap;

    cin >> N;

    int X, Y;
    while(N--)
    {
        cin >> X >> Y;
        tree.insert(X);
        treap.insert(X, Y);
    }

    tree.level_order();
    treap.level_order();
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
