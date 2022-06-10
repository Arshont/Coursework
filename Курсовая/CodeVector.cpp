#include "CodeVector.h"

#include <algorithm>

CodeVector::CodeVector(size_t capacity) : size_(0), capacity_(capacity)
{
	try
	{
		array_ = new bool[capacity];
	}
	catch (...)
	{
		throw WrongVectorSize();
	}
}

CodeVector::CodeVector(const CodeVector& vector)
{
	size_ = vector.size_;
	capacity_ = vector.capacity_;
	array_ = new bool[vector.capacity_];
	for (int i = 0; i < vector.size_; i++)
	{
		array_[i] = vector.array_[i];
	}
}

CodeVector::CodeVector(CodeVector&& vector) noexcept
{
	swap(vector);
	vector.array_ = nullptr;
}

CodeVector& CodeVector::operator=(const CodeVector& vector)
{
	if (this != &vector)
	{
		CodeVector temp(vector);
		swap(temp);
	}
	return *this;
}

CodeVector& CodeVector::operator=(CodeVector&& vector) noexcept
{
	if (this != &vector)
	{
		swap(vector);
		//vector.array_ = nullptr;
	}
	return *this;
}

CodeVector::~CodeVector()
{
	delete[] array_;
}

void CodeVector::swap(CodeVector& vector) noexcept
{
	std::swap(size_, vector.size_);
	std::swap(capacity_, vector.capacity_);
	std::swap(array_, vector.array_);
}

size_t CodeVector::getSize() const
{
	return size_;
}

void CodeVector::pushBack(const bool& code)
{
	if (size_ >= capacity_)
	{
		throw VectorOverflow();
	}
	array_[size_++] = code;
}

bool CodeVector::operator[](const size_t index) const
{
	return array_[index];
}