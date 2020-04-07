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

    template < class TLess = IsLess<T> >
    void insert(T elem, const TLess& isLess = TLess());

    template <class Tfunc = Output< Node<T>*> >
    void level_order(const Tfunc& func = Tfunc());

    ~BST()
    {
        level_order(Delete< Node<T>* >());
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
    Queue< Node<T>* > que;
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
    const static TLess isLess;

public:
    Treap() : root(NULL) {};
    Treap(const Treap<T, TLess>& other) : root(copy_treap(other.root)) {};

    Treap(Node< Pair<T, int> >* node) : root(node) {};

    Treap& operator= (const Treap &Tr);

    Pair< Treap<T, TLess>, Treap<T, TLess> > split(T);

    static Treap<T, TLess> merge(const Treap<T, TLess>&, const Treap<T, TLess>&);

    /*
    Treap<T, TLess> left() const {
        return Treap(root->left);
    }

    Treap<T, TLess> right() const {
        return Treap(root->right);
    }

    void set_left(const Treap<T, TLess>& Tr) {
        // TODO delete child
        root->left = copy_treap(Tr.root);
    }

    void set_right(const Treap<T, TLess>& Tr) {
        // TODO delete child
        root->right = copy_treap(Tr.root);
    }
    */

    void insert(T, int);

    //template <class Tfunc = Output<Node<T>*>>
    //void level_order(const Tfunc& func = Tfunc());

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
{;
    if (root == NULL)
        return Pair<Treap<T, TLess>, Treap<T, TLess> >(NULL, NULL);

    Treap<T> Tr1;
    Treap<T> Tr2;
    Pair<Treap<T, TLess>, Treap<T, TLess> > Tr1_Tr2;

    if (elem > root->key.X)
    {
        Treap<T> Tr_temp(root->right);
        Tr1_Tr2 = Tr_temp.split(elem);
        Tr_temp.root->right = copy_treap(Tr1.root);

        return Pair<Treap<T, TLess>, Treap<T, TLess>>(*this, Tr2);
    }

    else
    {
        Treap<T> Tr_temp(root->left);
        Tr1_Tr2 = Tr_temp.split(elem);
        Tr_temp.root->left = copy_treap(Tr2.root);

        return Pair<Treap<T, TLess>, Treap<T, TLess>>(Tr1, *this);
    }
}

template<typename T, class TLess>
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
}

template<typename T, class TLess>
void Treap<T, TLess>::insert(T elem, int priority)
{
    /*Pair<T, int> P(elem, priority);
    Node<Pair<T, int>>* node = new Node<Pair<T, int>>(P);
    if(root == NULL)
    {
        root = node;
        return;
    }

    Node<Pair<T, int>>* current = root;
    Node<Pair<T, int>>* parent = NULL;
    T split_key = root->key.X;

    while(!isLess(current->key.Y, priority))
    {
        parent = current;
        bool comp = isLess(current->key.X, elem);
        current = (comp ? current->right : current->left);
    }

    split(split_key);

    if (is_right)
        parent->right = node;
    else
        parent->left = node;*/
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
