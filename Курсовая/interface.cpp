#include "functions.h"


inline void greeting()
{
	std::cout << "Начата работа с программой, вам будут доступны следующие команды:\n"
		<< "DECODE - запускает процесс декодирования файла, выбранного в качесвте входного.\n Результат будет расположен в файле, заданным выходным. Недоступна, если не выбраны входной и выходной файлы.\n"
		<< "COMPARE - сравнивает два файла посимвольно.\n"
		<< "EXIT - завершает выполение программы.\n"
		<< "Команды следует вводить не более одной на строку. Можете начинать вводить команды.\n";
}

void interfaceCustom()
{
	greeting();
	std::string command = "";
	while (true)
	{
		std::cout << "Main: ";
		std::getline(std::cin, command, '\n');
		if (command == "ENCODE")
		{
			encode();
		}
		else if (command == "DECODE")
		{
			decode();
		}
		else if (command == "COMPARE")
		{
			compare();
		}
		else if (command == "EXIT")
		{
			std::cout << "Выполнение программы завершено.";
			return;
		}
		else
		{
			std::cout << "Введена некорректная команда. Повторите ввод.\n";
		}
	}
}