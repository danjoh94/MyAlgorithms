#include <iostream>
#include <fstream>
#include <time.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Chart.H>
#include <Windows.h>;

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

 
long long int getTickCount(void)
{
#if defined _WIN32 || defined WINCE
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	return (long long int)counter.QuadPart;
#elif defined __linux || defined __linux__
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC, &tp);
	return (int64)tp.tv_sec * 1000000000 + tp.tv_nsec;
#elif defined __MACH__ && defined __APPLE__
	return (int64)mach_absolute_time();
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (int64)tv.tv_sec * 1000000 + tv.tv_usec;
#endif
}

double getTickFrequency(void)
{
#if defined _WIN32 || defined WINCE
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return (double)freq.QuadPart;
#elif defined __linux || defined __linux__
	return 1e9;
#elif defined __MACH__ && defined __APPLE__
	static double freq = 0;
	if (freq == 0)
	{
		mach_timebase_info_data_t sTimebaseInfo;
		mach_timebase_info(&sTimebaseInfo);
		freq = sTimebaseInfo.denom * 1e9 / sTimebaseInfo.numer;
	}
	return freq;
#else
	return 1e6;
#endif
}

int main(int argc, char** argv)
{
	srand(time(0)); // set seed for random generator rand()
	const int size = 100;
	int arr[size];
	
	// create a random array
	for (size_t i = 0; i < size; i++)
		arr[i] = rand() % 100;
	
	
	// create fstream, write unsorted array -> txt file
	std::fstream fs;
	fs.open("unsorted.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	for (size_t i = 0; i < size; i++)
		fs << arr[i] << endl;
	fs.close();
	long long int t1 = getTickCount();
	// meregesort the array
	mergesort(arr, sizeof(arr) / sizeof(int));
	
	cout << "Time (in s): "<< (getTickCount() - t1) / getTickFrequency() << " count: " << 100000 << endl;
	// sorted array -> txt file
	fs.open("sorted.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	for (size_t i = 0; i < size; i++)
		fs << arr[i] << endl;
	fs.close();

	return 0;
}