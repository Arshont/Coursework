#ifndef CODEVECTOREXCEPTIONS_H
#define CODEVECTOREXCEPTIONS_H

#include <exception>

class WrongVectorSize
	:public std::exception
{
public:
	char const* what() const override
	{
		return "Ошибка. Размер сектора задан некорректно. Завершение программы.";
	}
};

class VectorOverflow
	:public std::exception
{
public:
	char const* what() const override
	{
		return "Ошибка. Вектор переполнен. Завершение программы.";
	}
};

#endif // !CODEVECTOREXCEPTIONS