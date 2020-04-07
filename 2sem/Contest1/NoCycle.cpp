#include <iostream>
#include <climits>
using std::cin;
using std::cout;

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
    int key;
    Node* next;

    Node(int elem, Node* next=nullptr):
        key(elem),
        next(next)
    {};
};

class Graph
{
private:
    int V = 0;
    int E = 0;
    int buffer_size = 2;
    Node** arr;
    int* three;
    int size_tree = 0;
    bool* no_root;
    int num_no_root = 0;

    void resize();

public:
    Graph(int V = 0) : V(V) {
        buffer_size = V > 1 ? 2 * V : 2;
        arr = new Node* [buffer_size] {nullptr};
        three = new int [buffer_size] {0};
        no_root = new bool [buffer_size] {false};
    }

    void insert_v();
    void insert_e(int, int);
    void output();
    void out_three();
    bool isnt_root();

    void sort_list();
    int* BFS(int);
    bool CycleDFS();
    bool ColorDFS(int, int*);

    ~Graph() {};
};

void Graph::resize()
{
    Node** new_arr = new Node* [buffer_size*2] {nullptr};

    for(int i = 0; i < buffer_size; i++)
        new_arr[i] = arr[i];

    delete[] arr;
    arr = new_arr;

    int* new_three = new int [buffer_size*2] {0};

    for(int i = 0; i < buffer_size; i++)
        new_three[i] = three[i];

    delete[] three;
    three = new_three;

    bool* new_root = new bool [buffer_size*2] {false};

    for(int i = 0; i < buffer_size; i++)
        new_root[i] = no_root[i];

    delete[] no_root;
    no_root = new_root;

    buffer_size = 2*buffer_size;
}

bool Graph::isnt_root()
{
    return V == num_no_root;
}

void Graph::insert_v()
{
    if (V == buffer_size)
        resize();
    V++;
}

void Graph::insert_e(int v1, int v2)
{
    E++;
    if (!no_root[v2])
    {
        no_root[v2] = true;
        num_no_root++;
    }
    Node* current = arr[v1];
    Node* parent = nullptr;
    while ((current != nullptr) && (current->key > v2)) {
            parent = current;
            current = current->next;
        }
    Node* ins = new Node(v2, current);
    if (!parent)
        arr[v1] = ins;
    else
        parent->next = ins;
}

bool Graph::CycleDFS()
{
    int* color = new int[V];
    for (int i = 0; i < V; i++)
    {
        color[i] = 0;
        three[i] = 0;
    }
    for (int i = 0; i < V; i++)
        if ((!no_root[i]) && (color[i] == 0) && (!ColorDFS(i, color)))
            return false;
    return true;
}

bool Graph::ColorDFS(int v, int* color)
{
    color[v] = 1;
    /************************three[size_tree++] = v;**/
    bool func_result = true;
    Node* current = arr[v];
    while(current != nullptr){
        if (color[current->key] == 0)
        {
            if(!ColorDFS(current->key, color))
                return false;
            //cout << current->key << " and\n";
            current = current->next;
            //cout << current->key << "\n";
        }
        else if (color[current->key] == 1)
        {
            //cout << current->key << " and\n";
            return false;
        }
        else
            current = current->next; /***************************************************here1**/
    }
    three[size_tree++] = v;
    color[v] = 2;
    return true;
}

void Graph::output()
{
    for (int i = 0; i < V; i++)
    {
        cout << i << "\n";
        Node* current = arr[i];
        while(current != nullptr){
            cout << current->key << " ";
            current = current->next;
        }
        cout << "\n";
    }
}

void Graph::out_three()
{
    for (int i = V-1; i >= 0; i--)
    {
        cout << three[i] << " ";
    }
}


int main()
{
    int V = 0;
    int E = 0;
    cin >> V >> E;
    Graph graph(V);

    int v1, v2;
    while(E--)
    {
        cin >> v1 >> v2;
        graph.insert_e(v1, v2);
    }

    //graph.output();

    if (graph.CycleDFS() && !graph.isnt_root())
    {
        cout << "YES\n";
        graph.out_three();
    }
    else
        cout <<"NO";
}

