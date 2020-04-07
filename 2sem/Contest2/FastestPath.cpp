#include <iostream>
#include <climits>
using std::cin;
using std::cout;
using std::min;

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
    int cost;
    bool was;
    Node* next;

    Node(int elem, int p_cost, Node* next=nullptr):
        key(elem),
        cost(p_cost),
        was(false),
        next(next)
    {};
};

class Graph
{
private:
    int V = 0;
    int E = 0;
    int buffer_size = 2;
    Node** neigh_vertex;

    void resize();

public:
    Graph(int V = 0) : V(V) {
        buffer_size = V > 1 ? 2 * V : 2;
        neigh_vertex = new Node* [buffer_size] {nullptr};
    }

    void insert_v();
    void insert_e(int, int, int);
    void output();

    int fastest_path(int, int);

    int* BFS(int);

    ~Graph() {};
};

void Graph::resize()
{
    Node** new_neigh_vertex = new Node* [buffer_size*2] {nullptr};

    for(int i = 0; i < buffer_size; i++)
        new_neigh_vertex[i] = neigh_vertex[i];

    delete[] neigh_vertex;
    buffer_size = 2*buffer_size;
    neigh_vertex = new_neigh_vertex;
}

void Graph::insert_v()
{
    if (V == buffer_size)
        resize();
    V++;
}

void Graph::insert_e(int v1, int v2, int cost)
{
    E++;
    neigh_vertex[v1] = new Node(v2, cost, neigh_vertex[v1]);
}

int Graph::fastest_path(int x, int y)
{
    int* dist = new int[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[x] = 0;

    Queue<int> q;
    q.push(x);

    int s;
    while(!q.is_empty()){
        cout << s;
        s = q.pop();
        Node* current = neigh_vertex[s];
        while(current != nullptr){
            if (!current->was) {
                dist[current->key] = min(dist[current->key], dist[s] + current->cost);
                current->was = true;
                q.push(current->key);
            }
            current = current->next;
        }
    }

    return (dist[y] == INT_MAX) ? -1 : dist[y];
}
/*
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
        Node* current = neigh_vertex[s];
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
}*/

void Graph::output()
{
    for (int i = 0; i < V; i++)
    {
        cout << i << "\n";
        Node* current = neigh_vertex[i];
        while(current != nullptr){
            cout << current->key << "," << current->cost << " ";
            current = current->next;
        }
        cout << "\n";
    }
}


int main()
{
    int V = 0;
    int a = 0, b = 0;
    int x = 0, y = 0;
    cin >> a >> b >> V >> x >> y;
    Graph graph(V);

    int M = V;

    while(V--)
    {
        graph.insert_e(V, ((V+1) % M), a);
        graph.insert_e(V, ((V*V+1) % M), b);
    }

    //graph.output();
    cout << "\n" << graph.fastest_path(x, y);
}
