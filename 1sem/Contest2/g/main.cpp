#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <string.h>
#include <iomanip>

#include "quicksort.h"

///______________________IO____________________///

void input(size_t& elem, size_t& iter)
{
    std::cout << "Enter the number of elements:\n";
    std::cin >> elem;
    if (!elem){
        throw "Input error: number of elements cannot be 0";
    }
    std::cout << "Enter the number of iterations:\n";
    std::cin >> iter;
    if (!iter){
        throw "Input error: number of iterations cannot be 0";
    }
}

void inputArray(int *arr, int *arrEnd, std::ifstream &in)
{
    for (int* j = arr; j != arrEnd; ++j)
    {
        in >> *j;
    }
}

void outputArray(const int *arr, const int *arrEnd, std::ofstream &out)
{
    for (const int* j = arr; j != arrEnd; ++j)
    {
        out << *j << ' ';
    }
}

void output(double* results)
{
    for (size_t i = 0; i < QuickModifier::enumSize; ++i)
    {
        std::cout << QuickModifier::toString(static_cast<QuickModifier::MOD> (i)) << '\n';
        std::cout << results[i] << 's' <<'\n';
    }
    std::cout << "Press enter to finish the program and delete files...";
    std::cin.get();
    std::cin.get();
}
///______________________Random_______________________////

int* randIntArray(const int elem)
{
    srand(time(NULL));
    int* ret = new int[elem];
    for (int i = 0; i < elem; ++i)
    {
        ret[i] = rand();
    }
    return ret;
}

///______________________Generations_and_Removing_Files_______________///
void generateFiles(const int elem, const int iter, const std::string baseName,
                                                   const std::string baseExt)
{
    for (int i = 0; i < iter; ++i)
    {
        int* array = randIntArray(elem);
        std::ofstream fout(baseName + std::to_string(i) + baseExt);
        outputArray(array, array + elem, fout);
        fout.close();
        delete[] array;
    }
}

void deleteFiles(const int iter, const std::string baseName,
                                 const std::string baseExt)
{
    for (int i = 0; i < iter; ++i)
    {
        remove((baseName + std::to_string(i) + baseExt).c_str());
    }
}

bool check(int *arr, int *arrEnd)
{
    for (int* i = arr + 1; i != arrEnd; ++i)
    {
        if (*(i - 1) > (*i)) return false;
    }
    return true;
}

void solve()
{
    const std::string BASENAMEINPUT = "UNSORTED_ARRAY_";
    const std::string BASENAMEOUTPUT = "SORTED_ARRAY_";
    const std::string BASEEXT = ".txt";
    const size_t precision = 5;

    std::cout << std::fixed;
    std::cout << std::setprecision(precision);

    size_t numberElements = 0;
    size_t numberIterations = 0;
    input (numberElements, numberIterations);

    generateFiles(numberElements, numberIterations, BASENAMEINPUT, BASEEXT);

    double results[QuickModifier::enumSize] = {};

    for (int j = 0; j < numberIterations; ++j)
    {
        int* array = new int[numberElements];

        std::ifstream fin (BASENAMEINPUT + std::to_string(j) + BASEEXT);
        inputArray(array, array + numberElements, fin);
        fin.close();

        for (int i = QuickModifier::MOD::NONE; i != QuickModifier::MOD::END; ++i){
            for (int M = 0; M < 3; ++M){
                int* curArray = new int[numberElements];
                memcpy (curArray, array, numberElements * sizeof(int));

                size_t start = clock();

                quicksort(curArray, curArray + numberElements, static_cast<QuickModifier::MOD> (i));
                results[i] += (double)(clock() - start) / 1E6;

                if (!check(curArray, curArray + numberElements))
                    throw "Error: your sort isn't correct";

                std::ofstream fout (BASENAMEOUTPUT + std::to_string(j) + BASEEXT);
                outputArray(curArray, curArray + numberElements, fout);
                fout.close();
                delete[] curArray;
            }
        }
        delete[] array;
    }

    for (int i = 0; i < QuickModifier::enumSize; ++i)
    {
        results[i] /= numberIterations * 3;
    }

    output(results);
    deleteFiles(numberIterations, BASENAMEINPUT, BASEEXT);
    deleteFiles(numberIterations, BASENAMEOUTPUT, BASEEXT);
}

int main()
{
    try {
        solve();
    } catch(char const* s){
        std::cout << s;
    } catch (...) {
        std::cout << "Undefined error";
    }
    return 0;
}
