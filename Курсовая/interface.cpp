#include "functions.h"


inline void greeting()
{
	std::cout << "������ ������ � ����������, ��� ����� �������� ��������� �������:\n"
		<< "DECODE - ��������� ������� ������������� �����, ���������� � �������� ��������.\n ��������� ����� ���������� � �����, �������� ��������. ����������, ���� �� ������� ������� � �������� �����.\n"
		<< "COMPARE - ���������� ��� ����� �����������.\n"
		<< "EXIT - ��������� ��������� ���������.\n"
		<< "������� ������� ������� �� ����� ����� �� ������. ������ �������� ������� �������.\n";
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
			std::cout << "���������� ��������� ���������.";
			return;
		}
		else
		{
			std::cout << "������� ������������ �������. ��������� ����.\n";
		}
	}
}