#ifndef CODEVECTOR_H
#define CODEVECTOR_H

#include "CodeVectorExceptions.h"

class CodeVector
{
public:
	CodeVector(size_t capacity = 16);
	CodeVector(const CodeVector& vector);
	CodeVector(CodeVector&& vector) noexcept;
	CodeVector& operator=(const CodeVector& vector);
	CodeVector& operator=(CodeVector&& vector) noexcept;
	~CodeVector();

	size_t getSize() const;
	void pushBack(const bool& code);

	bool operator[](const size_t index) const;
	void swap(CodeVector& vector) noexcept;

private:
	size_t capacity_;
	size_t size_;
	bool* array_;

	
};

#endif // !CODEVECTOR