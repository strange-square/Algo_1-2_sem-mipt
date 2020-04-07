#include <fstream>
using std::ofstream;

int main()
{
    ofstream fout("sorted.txt", ofstream::trunc);

    srand(time(0));
    for (int i = 0; i < 1000000; i++)
        fout <<  rand()%1000000 << " ";// запись строки в файл

    fout.close();
    return 0;
}
