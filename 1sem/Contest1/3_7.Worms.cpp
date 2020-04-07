//Сурок принес Кроту n упорядоченных кучек червей, таких, что в i-ой кучке содержатся ai червей.
//Он пронумеровал всех этих червей последовательными целыми числами: черви в первой кучке пронумерованы числами от 1 до a1,
//черви во второй кучке пронумерованы числами от a1 + 1 до a1 + a2 и так далее. Смотрите пример для лучшего понимания.
//Крот не может съесть всех червей (Сурок принёс их слишком много для того, чтобы съесть за один подход).
//К тому же, насколько мы знаем, Крот слепой — поэтому Сурок помогает ему, называ номера самых сочных червей.
//Сурок даст Кроту червяка, только если Крот правильно назовет кучку, в которой лежит червяк.
//Крот просит вас ему помочь. Для всех сочных червей, которых назвал Сурок, подскажите Кроту правильные ответы.

#include <iostream>
using namespace std;

int search_heap(int worm, int num_of_heaps, int* end_of_heap)
{
    int i = num_of_heaps/2;
    int half = i/2;

    while (true)
    {
        if ((worm > end_of_heap[i-1]) && (worm <= end_of_heap[i]))
            return i;
        else if (worm > end_of_heap[i])
            i += half;
        else i -= half;
        if (half != 1) half /= 2;
    }
}

int main()
{
    int num_of_heaps = 0;
    cin >> num_of_heaps;

    int* end_of_heap = new int [num_of_heaps+1];
    end_of_heap[0] = 0;
    int size_of_heap = 0, end_pointer = 0;
    for (int i = 1; i <= num_of_heaps; i++)
    {
        cin >> size_of_heap;
        end_pointer += size_of_heap;
        end_of_heap[i] = end_pointer;
    }

    int num_of_worms = 0;
    cin >> num_of_worms;

    int worm = 0;
    for (int i = 0; i < num_of_worms; i++)
    {
        cin >> worm;
        cout << search_heap(worm, num_of_heaps, end_of_heap) << "\n";

    }

    return 0;
}
