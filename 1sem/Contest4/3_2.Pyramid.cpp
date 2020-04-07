#include <iostream>
using std::cin;
using std::cout;

long long** create_table(int N)
{
    long long** table = new long long* [N];
    for (int i = 0; i < N; ++i)
    {
        table[i] = new long long [N];

        for (int k = 1; k < i; ++k)
        {
            table[i][k] = 0;
            for (int j = 1; j < k; ++j)
            {
                table[i][k] += table[i-k][j];
            }
        }

        table[i][i] = 1;

        for (int k = i+1; k < N; ++k)
            table[i][k] = 0;
    }
    return table;
}

long long num_pyramids(int N, int base)
{
    long long num = 0;
    long long** table = create_table(N);

    for (int i = 0; i < N; ++i)
        num += table[N-1][i];

    for (int i = 0; i < N; ++i)
        delete[] table[i];
    return num;
}

void solve()
{
    long long N;
    cin >> N;
    N++;

    cout << num_pyramids(N, 1);

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
