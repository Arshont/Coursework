#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>


void maxHeapify(FrequencyTableElement*& array, const size_t& n, const size_t& i)
{
	size_t largest = i;
	size_t left = i * 2 + 1;
	size_t right = i * 2 + 2;
	
	if (left < n && array[left] > array[largest])
	{
		largest = left;
	}
	if (right < n && array[right] > array[largest])
	{
		largest = right;
	}
	if (largest != i)
	{
		//std::swap(array[i], array[largest]);
		std::swap(array[largest].ch_, array[i].ch_);
		std::swap(array[largest].frequency_, array[i].frequency_);
		std::swap(array[largest].code_, array[i].code_);
		maxHeapify(array, n, largest );
	}
}


void buildMaxHeap(FrequencyTableElement*& array, const size_t& n, const size_t& i)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		maxHeapify(array, n, i );
	}
}


void heapSort(FrequencyTableElement*& array, const size_t& l, const size_t& r)
{
	size_t tempSize = r - l + 1;
	FrequencyTableElement* temp = new FrequencyTableElement[tempSize];

	for (size_t i = 0; i < tempSize; i++)
	{
		temp[i] = array[l + i];
	}

	buildMaxHeap(temp, tempSize, 0 );

	for (int i = tempSize - 1; i >= 0; i--)
	{
		std::swap(temp[0].ch_, temp[i].ch_);
		std::swap(temp[0].frequency_, temp[i].frequency_);
		std::swap(temp[0].code_, temp[i].code_);
		//temp[0].code_.swap(temp[i].code_);
		maxHeapify(temp, i, 0 );
	}

	for (size_t i = 0; i < tempSize; i++)
	{
		array[l + i] = temp[i];
	}
}


int partition(FrequencyTableElement*& array, const size_t& p, const size_t& r)
{
	FrequencyTableElement x = array[r];
	int i = p - 1;

	for (int j = p; j <= r - 1; j++)
	{
		if (array[j] <= x)
		{
			i++;
			std::swap(array[j], array[i]);
		}
	}
	std::swap(array[r], array[i + 1]);

	return i + 1;
}


void quickSort(FrequencyTableElement*& array, const size_t& l, const size_t& r, size_t depth)
{
	depth--;
	if (depth == 0)
	{
		heapSort(array, l, r );
	}
	else
	{
		if (l < r)
		{
			
			int m = partition(array, l, r );
			quickSort(array, l, m - 1 , depth);
			quickSort(array, m + 1, r , depth);
		}
	}
}


void introSort(FrequencyTableElement*& array, const size_t& leftIndex, const size_t& rightIndex)
{
	size_t maxDepth = static_cast<size_t>(log(rightIndex - leftIndex + 1));
	quickSort(array, leftIndex, rightIndex , maxDepth);
}


bool isOrdered(FrequencyTableElement* begin, const FrequencyTableElement* end)
{
	bool ordered = true;
	while ((begin != end) && ordered)
	{
		FrequencyTableElement* prev = begin;
		++begin;
		if ((begin != end) && (*prev > *begin))
		{
			ordered = false;
		}
	}
	return ordered;
}


#endif // !FUNCTIONS_H