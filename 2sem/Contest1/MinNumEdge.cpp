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

    void resize();

public:
    Graph(int V = 0) : V(V) {
        buffer_size = V > 1 ? 2 * V : 2;
        arr = new Node* [buffer_size] {nullptr};
    }

    void insert_v();
    void insert_e(int, int);
    void output();

    int* BFS(int);

    ~Graph() {};
};

void Graph::resize()
{
    Node** new_arr = new Node* [buffer_size*2] {nullptr};

    for(int i = 0; i < buffer_size; i++)
        new_arr[i] = arr[i];

    delete[] arr;
    buffer_size = 2*buffer_size;
    arr = new_arr;
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

    arr[v2] = new Node(v1, arr[v2]);
    arr[v1] = new Node(v2, arr[v1]);
}

int* Graph::BFS(int v)
{
    int* dist = new int[V];
    for (int i = 0; i < V; i++)
        dist[i] = 0;

    Queue<int> q;
    q.push(v);

    bool was[V];
    for (int i = 0; i < V; i++)
        was[i] = false;
    was[v] = true;


    int s;
    while(!q.is_empty())
    {
        s = q.pop();
        Node* current = arr[s];
        while(current != nullptr){
            if (!was[current->key]) {
                was[current->key] = true;
                dist[current->key] = dist[s] + 1;
                q.push(current->key);
            }
            current = current->next;
        }
    }

    return dist;
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


int main()
{
    int V = 0;
    int E = 0;
    cin >> V >> E;
    Graph graph(V);
    int l, m, milk;
    cin >> l >> m >> milk;
    l--, m--, milk--;

    int v1, v2;
    while(E--)
    {
        cin >> v1 >> v2;
        graph.insert_e(v1-1, v2-1);
    }

    int* d_l = graph.BFS(l);
    int* d_m = graph.BFS(m);
    int* d_milk = graph.BFS(milk);
    int minim = INT_MAX;
    for (int i = 0; i < V; i++)
        minim = minim < d_l[i] + d_m[i] + d_milk[i] ? minim : d_l[i] + d_m[i] + d_milk[i];
    cout << minim;
}
