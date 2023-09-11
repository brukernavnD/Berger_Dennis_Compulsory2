#include <iostream>
#include <ctime>
using namespace std;

/// <summary>
/// function to find the size of an array.
///	Found on https://www.geeksforgeeks.org/how-to-print-size-of-an-array-in-a-function-in-c/
/// </summary>
/// <typeparam name="N"></typeparam>
/// <param name="array"></param>
template <size_t N>
int GetArraySize(int (&array)[N])
{
	//find size of array
	const int size = sizeof(array) / sizeof(int);

	//return size of array
	return size;
}

/// <summary>
/// function to fill integer array with random numbers
/// </summary>
/// <typeparam name="N"></typeparam>
/// <param name="array"></param>
/// <param name="min"></param>
/// <param name="max"></param>
template <size_t N>
void FillArray(int (&array)[N], const int min = 0, const int max = 256)
{
	//fill array with random numbers
	for (int i = 0; i < GetArraySize(array); i++)
	{
		//generate random number
		const int random = min + rand() % max + 1;

		//add random number to array
		array[i] = random;
	}
}

/// <summary>
/// function to print integer array values
/// </summary>
/// <typeparam name="N"></typeparam>
/// <param name="array"></param>
template <size_t N>
void PrintArray(int (&array)[N])
{
	//print array
	for (int i = 0; i < GetArraySize(array); i++)
	{
		cout << "element " << i << " : " << array[i] << endl;
	}
}

/// <summary>
/// non recursive bubble sort algorithm
/// </summary>
/// <typeparam name="N"></typeparam>
/// <param name="array"></param>
template <size_t N>
void BubbleSort(int (&array)[N])
{
	//sort array
	for (int i = 0; i < GetArraySize(array); i++)
	{
		//find smallest number in array
		int smallest = array[i];
		int smallestIndex = i;

		for (int j = i + 1; j < GetArraySize(array); j++)
		{
			if (array[j] < smallest)
			{
				smallest = array[j];
				smallestIndex = j;
			}
		}

		//swap smallest number with current number
		int temp = array[i];
		array[i] = smallest;
		array[smallestIndex] = temp;
	}
}

/// <summary>
/// partition helper function for quick sort
/// </summary>
/// <param name="array"></param>
/// <param name="left"></param>
/// <param name="right"></param>
/// <param name="pivot"></param>
/// <returns></returns>
int Partition(int* array, int left, int right, const int pivot)
{
	//while left is less than or equal to right
	while (left <= right)
	{
		//find element on left that should be on right
		while (array[left] < pivot)
		{
			left++;
		}

		//find element on right that should be on left
		while (array[right] > pivot)
		{
			right--;
		}

		//swap elements and move left and right indices
		if (left <= right)
		{
			int temp = array[left];
			array[left] = array[right];
			array[right] = temp;

			left++;
			right--;
		}
	}

	//return left index
	return left;
}

/// <summary>
/// recursive quick sort algorithm
/// </summary>
/// <param name="array"></param>
/// <param name="left"></param>
/// <param name="right"></param>
void QuickSort(int* array, const int left, const int right)
{
	//if array is empty or has 1 element, return
	if (left >= right)
	{
		return;
	}

	//pick pivot
	int pivot = array[(left + right) / 2];

	//partition array
	int index = Partition(array, left, right, pivot);

	//sort sub arrays
	QuickSort(array, left, index - 1);
	QuickSort(array, index, right);
}

/// <summary>
/// recursive merge sort algorithm
/// </summary>
/// <param name="array"></param>
/// <param name="left"></param>
/// <param name="right"></param>
void MergeSort(int* array, const int left, const int right)
{
	//if array is empty or has 1 element, return
	if (left >= right)
	{
		return;
	}

	//find middle of array
	int middle = (left + right) / 2;

	//sort left half
	MergeSort(array, left, middle);

	//sort right half
	MergeSort(array, middle + 1, right);

	//merge sorted halves
	int leftIndex = left;
	int rightIndex = middle + 1;
	int tempIndex = 0;

	//create temporary array
	int* temp = new int[right - left + 1];

	//merge halves into temporary array
	while (leftIndex <= middle && rightIndex <= right)
	{
		if (array[leftIndex] <= array[rightIndex])
		{
			temp[tempIndex] = array[leftIndex];
			leftIndex++;
		}
		else
		{
			temp[tempIndex] = array[rightIndex];
			rightIndex++;
		}

		tempIndex++;
	}

	//copy remaining elements from left half
	while (leftIndex <= middle)
	{
		temp[tempIndex] = array[leftIndex];
		leftIndex++;
		tempIndex++;
	}

	//copy remaining elements from right half
	while (rightIndex <= right)
	{
		temp[tempIndex] = array[rightIndex];
		rightIndex++;
		tempIndex++;
	}

	//copy temporary array into original array
	for (int i = left; i <= right; i++)
	{
		array[i] = temp[i - left];
	}

	//delete temporary array
	delete[] temp;
}

int main()
{
	//seed the random generator
	srand(time(nullptr));

	////create array of 10 integers and fill it with random numbers
	int RandArray[100];
	FillArray(RandArray);

	//print our array
	cout << "Array of " << GetArraySize(RandArray) << " random numbers: " << endl << endl;
	PrintArray(RandArray);

	////sort our array and then print it again using bubble sort
	BubbleSort(RandArray);
	cout << endl << "sorted array using BubbleSort (iterative): " << endl << endl;
	PrintArray(RandArray);

	////sort our array and then print it again using quick sort
	QuickSort(RandArray, 0, GetArraySize(RandArray) - 1);
	cout << endl << "sorted array using QuickSort (recursively): " << endl << endl;
	PrintArray(RandArray);

	//sort our array and then print it again using merge sort
	MergeSort(RandArray, 0, GetArraySize(RandArray) - 1);
	cout << endl << "sorted array using MergeSort (recursively): " << endl << endl;
	PrintArray(RandArray);
}
