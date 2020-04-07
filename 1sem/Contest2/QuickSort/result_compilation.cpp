#include <iostream>
#include <fstream>

using std::ofstream;
using std::ifstream;

int main()
{

    ifstream fin("result_pivot_rand_standard_partition_test_1_1.txt");
    float* result_pivot_rand_standard_partition_test_1_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_rand_standard_partition_test_1_1[i];
    fin.close();

    fin.open("result_pivot_rand_optimized_partition_test_1_1.txt");
    float* result_pivot_rand_optimized_partition_test_1_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_rand_optimized_partition_test_1_1[i];
    fin.close();

    fin.open("result_pivot_mid_standard_partition_test_1_1.txt");
    float* result_pivot_mid_standard_partition_test_1_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_mid_standard_partition_test_1_1[i];
    fin.close();

    fin.open("result_pivot_mid_optimized_partition_test_1_1.txt");
    float* result_pivot_mid_optimized_partition_test_1_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_mid_optimized_partition_test_1_1[i];
    fin.close();

    fin.open("result_pivot_end_standard_partition_test_1_1.txt");
    float* result_pivot_end_standard_partition_test_1_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_end_standard_partition_test_1_1[i];
    fin.close();

    fin.open("result_pivot_end_optimized_partition_test_1_1.txt");
    float* result_pivot_end_optimized_partition_test_1_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_end_optimized_partition_test_1_1[i];
    fin.close();

    fin.open("result_pivot_rand_standard_partition_test_2_1.txt");
    float* result_pivot_rand_standard_partition_test_2_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_rand_standard_partition_test_2_1[i];
    fin.close();

    fin.open("result_pivot_rand_optimized_partition_test_2_1.txt");
    float* result_pivot_rand_optimized_partition_test_2_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_rand_optimized_partition_test_2_1[i];
    fin.close();

    fin.open("result_pivot_mid_standard_partition_test_2_1.txt");
    float* result_pivot_mid_standard_partition_test_2_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_mid_standard_partition_test_2_1[i];
    fin.close();

    fin.open("result_pivot_mid_optimized_partition_test_2_1.txt");
    float* result_pivot_mid_optimized_partition_test_2_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_mid_optimized_partition_test_2_1[i];
    fin.close();

    fin.open("result_pivot_end_standard_partition_test_2_1.txt");
    float* result_pivot_end_standard_partition_test_2_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_end_standard_partition_test_2_1[i];
    fin.close();

    fin.open("result_pivot_end_optimized_partition_test_2_1.txt");
    float* result_pivot_end_optimized_partition_test_2_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_end_optimized_partition_test_2_1[i];
    fin.close();

    fin.open("result_pivot_rand_standard_partition_test_3_1.txt");
    float* result_pivot_rand_standard_partition_test_3_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_rand_standard_partition_test_3_1[i];
    fin.close();

    fin.open("result_pivot_rand_optimized_partition_test_3_1.txt");
    float* result_pivot_rand_optimized_partition_test_3_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_rand_optimized_partition_test_3_1[i];
    fin.close();

    fin.open("result_pivot_mid_standard_partition_test_3_1.txt");
    float* result_pivot_mid_standard_partition_test_3_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_mid_standard_partition_test_3_1[i];
    fin.close();

    fin.open("result_pivot_mid_optimized_partition_test_3_1.txt");
    float* result_pivot_mid_optimized_partition_test_3_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_mid_optimized_partition_test_3_1[i];
    fin.close();

    fin.open("result_pivot_end_standard_partition_test_3_1.txt");
    float* result_pivot_end_standard_partition_test_3_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_end_standard_partition_test_3_1[i];
    fin.close();

    fin.open("result_pivot_end_optimized_partition_test_3_1.txt");
    float* result_pivot_end_optimized_partition_test_3_1 = new float[4];
    for (int i = 0; i < 4; ++i)
        fin >> result_pivot_end_optimized_partition_test_3_1[i];
    fin.close();
}
