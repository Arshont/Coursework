#include "FrequencyTable.h"
#include "Introsort.h"

#include <stdexcept>

FrequencyTable::FrequencyTable(size_t capacity) : head_(-1), tail_(-1), size_(0),capacity_(capacity)
{
	try
	{
		array_ = new FrequencyTableElement[capacity];
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("Ошибка. Некорректно задан размер очереди. Завершение программы.");
	}
}

FrequencyTable::FrequencyTable(const FrequencyTable& table) :head_(table.head_), tail_(table.tail_), size_(table.size_), capacity_(table.capacity_)
{
	array_ = new FrequencyTableElement[table.capacity_];
	for (size_t i = 0; i < table.size_;i++)
	{
		array_[i] = table.array_[i];
	}
}


FrequencyTable::FrequencyTable(FrequencyTable&& table) noexcept
{
	swap(table);
	table.array_ = nullptr;
}

FrequencyTable& FrequencyTable::operator=(const FrequencyTable& table)
{
	if (this != &table)
	{
		head_ = table.head_;
		tail_ = table.tail_;
		size_ = table.size_;
		capacity_ = table.capacity_;
		array_ = new FrequencyTableElement[table.capacity_];
		for (size_t i = 0; i < table.size_; i++)
		{
			array_[i] = table.array_[i];
		}
	}
	return *this;
}

FrequencyTable& FrequencyTable::operator=(FrequencyTable&& table) noexcept
{
	if (this != &table)
	{
		swap(table);
		//table.array_ = nullptr;
	}
	return *this;
}

FrequencyTable::~FrequencyTable()
{
	delete[] array_;
}

void FrequencyTable::swap(FrequencyTable& table) noexcept
{
	std::swap(capacity_, table.capacity_);
	std::swap(size_, table.size_);
	std::swap(head_, table.head_);
	std::swap(tail_, table.tail_);
	std::swap(array_, table.array_);
}

FrequencyTableElement FrequencyTable::back() const
{
	return array_[tail_];
}

void FrequencyTable::pushBack(const FrequencyTableElement& elem)
{
	if (isFull())
	{
		throw std::overflow_error("Ошибка. Очередь переполнена. Завершение программы.");
	}
	else if (isEmpty())
	{
		head_ = 0;
		tail_ = 0;
		size_++;
	}
	else
	{
		size_++;
		tail_ = (tail_ + 1) % size_;
	}
	array_[tail_] = elem;
}

FrequencyTableElement FrequencyTable::popBack()
{
	FrequencyTableElement item;
	if (isEmpty())
	{
		throw std::underflow_error("Ошибка. Попытка удаления из пустой очереди. Завершение программы.");
	}
	else
	{
		item = array_[tail_];
		if (head_ == tail_)
		{
			head_ = -1;
			tail_ = -1;
		}
		else
		{
			if (tail_ == 0)
			{
				tail_ = size_ - 1;
			}
			else
			{
				tail_ = (tail_ - 1) % size_;
			}
		}
		size_--;
	}
	return item;
}

FrequencyTableElement FrequencyTable::front() const
{
	return array_[head_];
}

void FrequencyTable::pushFront(const FrequencyTableElement& elem)
{
	if (isFull())
	{
		throw std::overflow_error("Ошибка. Очередь переполнена. Завершение программы.");
	}
	else if (isEmpty())
	{
		head_ = 0;
		tail_ = 0;
		size_++;
	}
	else
	{
		size_++;
		if (head_ == 0)
		{
			head_ = size_ - 1;
		}
		else
		{
			head_ = (head_ -1) % (size_ - 1);
		}
	}
	array_[tail_] = elem;
}


FrequencyTableElement FrequencyTable::popFront()
{
	FrequencyTableElement item;
	if (isEmpty())
	{
		throw std::underflow_error("Ошибка. Попытка удаления из пустой очереди. Завершение программы.");
	}
	else
	{
		item = array_[head_];
		if (head_ == tail_)
		{
			head_ = -1;
			tail_ = -1;
		}
		else
		{
			head_ = (head_ + 1) % (size_ + 1);
		}
		size_--;
	}
	return item;
}

size_t FrequencyTable::getSize() const
{
	return size_;
}

bool FrequencyTable::isEmpty() const
{
	return (size_ == 0) || head_ == -1 && tail_ == -1;
}

bool FrequencyTable::isFull() const
{
	return size_ == capacity_;
}

FrequencyTableElement FrequencyTable::operator[](const size_t index) const
{
	return array_[index];
}

void FrequencyTable::merge(FrequencyTable& frequencyTable)
{
	size_t size = frequencyTable.getSize();
	for (size_t i = 0; i < size; i++)
	{
		pushBack(frequencyTable[i]);
	}
}

void FrequencyTable::addCodes(const bool& code)
{
	if (!isEmpty())
	{
		int i = head_;
		while (i != tail_)
		{
			array_[i].code_.pushBack(code);

			i = (i + 1) % size_;
		}
		array_[i].code_.pushBack(code);
	}
}

void FrequencyTable::sort()
{
	introSort(array_, head_, tail_);
}