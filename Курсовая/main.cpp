#include "functions.h"
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		interfaceCustom();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what();
		return -1;
	}
	return 0;
}