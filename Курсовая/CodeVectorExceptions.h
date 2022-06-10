#ifndef CODEVECTOREXCEPTIONS_H
#define CODEVECTOREXCEPTIONS_H

#include <exception>

class WrongVectorSize
	:public std::exception
{
public:
	char const* what() const override
	{
		return "������. ������ ������� ����� �����������. ���������� ���������.";
	}
};

class VectorOverflow
	:public std::exception
{
public:
	char const* what() const override
	{
		return "������. ������ ����������. ���������� ���������.";
	}
};

#endif // !CODEVECTOREXCEPTIONS