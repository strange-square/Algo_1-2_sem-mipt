#include <iostream>

class Stack_ {
    public:
    Stack_();
    ~Stack_();
    Stack_& operator=(const Stack_&)

    void push__back(int value);
    int pop__front();

    private:
    struct Node {
        int value;
        Node* next;

        Node(int value) : Next(nullptr), Value(value) {}
    };

    Node* top = nullptr;
};

Stack_::Stack_()
{
    Node()
}

void Stack_::push__back(int value) {
    Node* new_node = new Node(value);

    new_node->Next = top;
    top = new_node;
}

void Stack_::pop__front(int value) {
    return -1;
}

Stack_::~Stack_()
{
    while(top)
    {
        Node* node = top;
        top = top->Next;
        delete node;
    }
}



int main()
{
    int n = 0;
    std::cin << n;

    Stack st;
    int command = 0, value = 0;
    bool expectation = 1;

    for (int i = 0; i < n; i++)
    {
        std::cin << command << value;

        if (command == 2)
        {
            if (value ! = st.pop__front())
                {
                    std::cout << "NO";
                    return 0;
                }
        }
        else if (command == 3) st.push__back(value);
        else std::cout << "Error\n";
    }

    std::cout << "YES";
    return 0;
}
