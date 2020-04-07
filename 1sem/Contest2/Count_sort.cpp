#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>

struct Borders {
	int Min;
	int Max;

	Borders(int min, int max) : Min(min), Max(max) {}
};

template <class T, class TGetKey>
Borders GetMinMax(T* arr, int begin, int end, TGetKey getKey)
{
	assert(end > begin);

	int max = getKey(arr[begin]);
	int min = getKey(arr[begin]);
	for(int i = begin + 1; i < end; i++) {
		int key = getKey(arr[i]);
		if (key > max) max = key;
		if (key < min) min = key;
	}

	return Borders(min, max);
}

template <class T, class TGetKey>
void CountingSort(T* arr, int begin, int end, TGetKey getKey)
{
	if(end <= begin) {
		return;
	}

	Borders borders = GetMinMax(arr, begin, end, getKey);

	const int binsCount = borders.Max - borders.Min + 1;
	int* bins = new int[binsCount];
	memset(bins, 0, sizeof(int) * binsCount);

	for( int i = begin; i < end; i++ )
		bins[getKey(arr[i]) - borders.Min]++;

	for ( int i = 1; i < binsCount; i++ )
		bins[i] += bins[i - 1];

	T* arrCopy = new T[end - begin + 1];
	for (int i = begin; i < end; i++ )
		arrCopy[i - begin] = arr[i];

	for (int i = end - 1; i >= begin; i--) {
		T value = arrCopy[i - begin];
		int index = --bins[getKey(value) - borders.Min];
		arr[index + begin] = value;
	}

	delete[] arrCopy;
	delete[] bins;
}

int main()
{
	freopen("my.txt", "r", stdin);

	int size = 0;
	std::cin >> size;
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		std::cin >> arr[i];
	}

	CountingSort(arr, 0, size, [](const int value){return value;});

	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	int strSize = 0;
	std::cin >> strSize;
	std::string* strArr = new std::string[strSize];
	for (int i = 0; i < strSize; i++) {
		std::cin >> strArr[i];
	}

	CountingSort(strArr, 0, strSize,
		[](const std::string& value){ return value.length(); });

	for (int i = 0; i < strSize; i++) {
		std::cout << strArr[i] << std::endl;
	}
	std::cout << std::endl;

	class Compare {
	public:
		Compare(int rank) : rank(rank) {};
		int operator() (const std::string& value)
		{
			if(rank >= value.length()) {
				return 0;
			}
			return static_cast<int>(value[rank]);
		}
	private:
		int rank;
	};

	for(int rank = 10; rank >= 0; rank--) {
		CountingSort(strArr, 0, strSize, Compare(rank)
			//[rank](const std::string& value) {
			//	if(rank >= value.length()) {
			//		return 0;
			//	}
			//	return static_cast<int>(value[rank]);
			//}
		);
	}

	for (int i = 0; i < strSize; i++) {
		std::cout << strArr[i] << std::endl;
	}
	std::cout << std::endl;

	delete[] strArr;
	delete[] arr;
}
