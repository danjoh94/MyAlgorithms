
#include <iostream>
#include <fstream>
#include <time.h>

using std::ofstream;
using std::cout;
using std::endl;


void printArray(int* arr, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << *(arr + i) << endl;
	}
	cout << "done" << endl;
}

void mergesort(int* arr, int size)
{
	if (size == 1) return;
	if (size == 2)
	{
		if (arr[0] > arr[1])
		{
			int temp = arr[0];
			arr[0] = arr[1];
			arr[1] = temp;
		}
		return;
	}
	int r = size / 2;

	mergesort(arr, r);
	mergesort(arr + r, size - r);

	int* p = new int[size];

	memcpy(p, arr, size * sizeof(int));

	for (int i = 0, j = 0, k = 0; i < size; i++)
	{
		if (arr[j] > arr[k + r])
		{
			p[i] = arr[k + r];
			k++;
		}
		else
		{
			p[i] = arr[j];
			j++;
		}

		if (j >= r)
		{
			memcpy(p + i + 1, arr + k + r, (r - k) * sizeof(int));
			break;
		}
		else if (k >= size - r)
		{
			memcpy(p + i + 1, arr + j, (r - j) * sizeof(int));
			break;
		}
	}
	memcpy(arr, p, size * sizeof(int));

	delete[] p; // free the memory from the heap
}

int main()
{
	srand(time(0)); // set seed for random generator rand()
	const int size = 90000;
	int arr[size];

	// create a random array
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = rand();
	}

	// create fstream, write unsorted array -> txt file
	std::fstream fs;
	fs.open("unsorted.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	for (size_t i = 0; i < size; i++)
	{
		fs << arr[i] << endl;
	}
	fs.close();

	// meregesort the array
	mergesort(arr, sizeof(arr) / sizeof(int));

	// sorted array -> txt file
	fs.open("sorted.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	for (size_t i = 0; i < size; i++)
	{
		fs << arr[i] << endl;
	}
	fs.close();
}