#ifndef FREQUENCYTABLE_H
#define FREQUENCYTABLE_H

#include "FrequencyTableElement.h"

class FrequencyTable
{
private:

	FrequencyTableElement* array_;

	int head_;
	int tail_;
	size_t size_;
	size_t capacity_;
	
	void swap(FrequencyTable& table) noexcept;

public:
	FrequencyTable(size_t size = 256);
	FrequencyTable(const FrequencyTable& table);
	FrequencyTable(FrequencyTable&& table) noexcept;
	FrequencyTable& operator=(const FrequencyTable& table);
	FrequencyTable& operator=(FrequencyTable&& table) noexcept;
	~FrequencyTable();

	FrequencyTableElement back() const;
	void pushBack(const FrequencyTableElement& elem);
	FrequencyTableElement popBack();

	FrequencyTableElement front() const;
	void pushFront(const FrequencyTableElement& elem);
	FrequencyTableElement popFront();

	size_t getSize() const;
	bool isEmpty() const;
	bool isFull() const;

	FrequencyTableElement operator[](const size_t index) const;

	void merge(FrequencyTable& frequencyTable);
	void addCodes(FrequencyTableElement* ASCIItable, const bool& code);
	
	void sort();


};

#endif // !FREQUENCYTABLE_H