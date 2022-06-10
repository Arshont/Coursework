#ifndef FREQUENCYTABLEELEMENT_H
#define FREQUENCYTABLEELEMENT_H

#include "CodeVector.h"

struct FrequencyTableElement
{
	unsigned char ch_;
	size_t frequency_;
	CodeVector code_;

	FrequencyTableElement() :ch_('\0'), frequency_(0), code_() {}

	FrequencyTableElement(const unsigned char ch, const size_t freq)
	{
		ch_ = ch;
		frequency_ = freq;
		code_ = *(new CodeVector());
	}

	FrequencyTableElement& operator=(const FrequencyTableElement& elem)
	{
		if (this != &elem)
		{
			ch_ = elem.ch_;
			frequency_ = elem.frequency_;
			code_ = elem.code_;
		}
		return *this;
	}

	~FrequencyTableElement(){}

	bool operator<(const FrequencyTableElement& other) const
	{
		return frequency_ < other.frequency_;
	}

	bool operator>=(const FrequencyTableElement& other) const
	{
		return !(*this < other);
	}

	bool operator>(const FrequencyTableElement& other) const
	{
		return frequency_ > other.frequency_;
	}

	bool operator<=(const FrequencyTableElement& other) const
	{
		return !(*this > other);
	}
};

#endif // !FREQUENCYTABLEELEMENT_H