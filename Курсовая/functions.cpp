#include "functions.h"
#include "StreamGuard.h"
#include "CodeTree.h"
#include "FrequencyTable.h"

#include <iomanip>
#include <chrono>

const size_t ASCIIsize = 256;

const char ID[21] = "J3P_fd6~HTO3jkf5.s7&";

bool getFilesForEncoding(std::ifstream& in, std::ofstream& out)
{
	std::string fileName = "";
	std::cout << "Введите имя файла, который нужно закодировать. Если хотите отменить операцию введите BACK.\n";
	std::getline(std::cin, fileName, '\n');
	if (fileName == "BACK")
	{
		return false;
	}
	in.open(fileName);
	while (!in)
	{
		std::cout << "Введено некорректное имя файла, повторите ввод.\n";
		std::getline(std::cin, fileName, '\n');
		if (fileName == "BACK")
		{
			return false;
		}
		in.open(fileName);
	}
	std::cout << "Введите имя файла, в который хотите поместить результат.\n";
	std::getline(std::cin, fileName, '\n');
	if (fileName == "BACK")
	{
		return false;
	}
	out.open(fileName, std::ofstream::binary);
	return true;
}

bool getFilesForDecoding(std::ifstream& in, std::ofstream& out)
{
	std::string fileName = "";
	std::cout << "Введите имя файла, который хотите раскодировать. Если хотите отменить операцию введите BACK.\n";
	char check[21];
	do
	{
		in.clear();
		std::getline(std::cin, fileName, '\n');
		if (fileName == "BACK")
		{
			return false;
		}
		in.open(fileName, std::ifstream::binary);
		if (!in)
		{
			std::cout << "Введено некорректное имя файла, повторите ввод.\n";
			continue;
		}
		in.read(check, strlen(ID));
		check[20] = '\0';
		if (strcmp(check, ID) != 0)
		{
			in.setstate(std::ios::failbit);
			std::cout << "Заданный файл не был закодирован, повторите ввод.\n";
			in.close();
		}
	} while (!in);
	std::cout << "Введите имя файла, в который хотите поместить результат.\n";
	std::getline(std::cin, fileName, '\n');
	if (fileName == "BACK")
	{
		return false;
	}
	out.open(fileName);
	return true;
}

bool getFilesForCompare(std::ifstream& in1, std::ifstream& in2)
{
	std::string fileName = "";
	std::cout << "Введите имя первого файла. Если хотите отменить операцию введите BACK.\n";
	std::getline(std::cin, fileName, '\n');
	if (fileName == "BACK")
	{
		return false;
	}
	in1.open(fileName);
	while (!in1)
	{
		std::cout << "Введено некорректное имя файла, повторите ввод.\n";
		std::getline(std::cin, fileName, '\n');
		if (fileName == "BACK")
		{
			return false;
		}
		in1.open(fileName);
	}
	std::cout << "Введите имя второго файла.\n";
	std::getline(std::cin, fileName, '\n');
	if (fileName == "BACK")
	{
		return false;
	}
	in2.open(fileName);
	while (!in2)
	{
		std::cout << "Введено некорректное имя файла, повторите ввод.\n";
		std::getline(std::cin, fileName, '\n');
		if (fileName == "BACK")
		{
			return false;
		}
		in2.open(fileName);
	}
	return true;
}

void getFrequencies(std::ifstream& in, FrequencyTableElement* ASCIItable)
{
	StreamGuard guard(in);
	in >> std::noskipws;
	unsigned char ch = 0;
	while (!in.eof())
	{
		in >> ch;
		ASCIItable[ch].frequency_++;
	}
	ASCIItable[ch].frequency_--;
}

void getFrequencyTable(FrequencyTableElement* ASCIItable, FrequencyTable& frequencyTable)
{
	size_t i = 0;
	for (size_t i = 0; i < ASCIIsize; i++)
	{
		if (ASCIItable[i].frequency_ > 0)
		{
			ASCIItable[i].ch_ = static_cast<char>(i);
			frequencyTable.pushBack(ASCIItable[i]);
		}
	}
	frequencyTable.sort();
	/*std::sort(frequencyTable.begin(), frequencyTable.end(),
		[](FrequencyTableElement* obj1, FrequencyTableElement* obj2)
		{
			return obj1->frequency_ > obj2->frequency_;
		}
	);*/
}

FrequencyTable getCodes(FrequencyTable& frequencyTable, FrequencyTableElement* ASCIItable)
{
	//if (frequencyTable.getSize() / 2 != 0)
	//{
	//	FrequencyTable left;
	//	FrequencyTable right;
	//	size_t leftSum = 0;
	//	size_t rightSum = 0;
	//	while (!frequencyTable.isEmpty())
	//	{
	//		right.pushFront(frequencyTable.popBack());
	//		rightSum += right.front().frequency_;
	//		while (rightSum > leftSum && !frequencyTable.isEmpty())
	//		{
	//			left.pushBack(frequencyTable.popFront());
	//			leftSum += left.back().frequency_;
	//		}
	//	}
	//	left.addCodes(0);
	//	right.addCodes(1);
	//	/*size_t leftSize = left.getSize();
	//	for (size_t i = 0; i < leftSize; i++)
	//	{
	//		left[i].code_.pushBack(0);
	//	}
	//	size_t rightSize = right.getSize();
	//	for (size_t i = 0; i < rightSize; i++)
	//	{
	//		right[i].code_.pushBack(1);
	//	}*/
	//	/*std::for_each(left.begin(), left.end(),
	//		[](FrequencyTableElement* obj)
	//		{
	//			obj->code_.pushBack(false);
	//		}
	//	);
	//	std::for_each(right.begin(), right.end(),
	//		[](FrequencyTableElement* obj)
	//		{
	//			obj->code_.pushBack(true);
	//		}
	//	);*/
	//	left = getCodes(left);
	//	right = getCodes(right);
	//	left.merge(right);
	//	return std::move(left);
	//}
	if (frequencyTable.getSize() / 2 > 0)
	{
		FrequencyTable left;
		FrequencyTable right;
		size_t leftSum = 0;
		size_t rightSum = 0;

		while (!frequencyTable.isEmpty())
		{
			right.pushFront(frequencyTable.popBack());
			rightSum += right.front().frequency_;
			while (rightSum > leftSum && !frequencyTable.isEmpty())
			{
				left.pushBack(frequencyTable.popFront());
				leftSum += left.back().frequency_;
			}
		}
		left.addCodes(ASCIItable, 0);
		right.addCodes(ASCIItable, 1);
		left = getCodes(left, ASCIItable);
		right = getCodes(right, ASCIItable);
		left.merge(right);
		return left;
	}
	else
	{
		return std::move(frequencyTable);
	}
}

void getCodesInASCIItable(FrequencyTable& frequencyTable, FrequencyTableElement* ASCIItable)
{
	size_t size = frequencyTable.getSize();
	for (size_t i = 0; i < size; i++)
	{
		ASCIItable[frequencyTable[i].ch_].code_ = frequencyTable[i].code_;
	}
}

void getKey(std::ofstream& out, FrequencyTable& frequencyTable)
{
	size_t size = frequencyTable.getSize();
	size_t chSize = sizeof(char);
	size_t countSize = sizeof(size_t);
	out.write(ID, strlen(ID));
	out.write(reinterpret_cast<char*>(&size), countSize);
	char ch;
	size_t freq;
	for (size_t i = 0; i < frequencyTable.getSize(); i++)
	{
		ch = frequencyTable[i].ch_;
		freq = frequencyTable[i].frequency_;
		out.write(reinterpret_cast<char*>(&ch), chSize);
		out.write(reinterpret_cast<char*>(&freq), countSize);
	}
}

void getEncodedText(std::ifstream& in, std::ofstream& out, FrequencyTableElement* ASCIItable)
{
	in.clear();
	in.seekg(0, in.beg);
	size_t bitCount = 0;
	unsigned char byte = 0;
	unsigned char ch = '\0';
	size_t numberOfBits = 0;
	in >> std::noskipws;
	while (!in.eof())
	{
		in >> ch;
		size_t codeSize = ASCIItable[ch].code_.getSize();
		numberOfBits += codeSize;
		for (size_t i = 0; i < codeSize; i++) //Achtung!
		{
			byte = byte | ASCIItable[ch].code_[i] << (7 - bitCount);
			bitCount++;
			if (bitCount == 8)
			{
				bitCount = 0;
				out << byte;
				byte = 0;
			}
		}
	}
	if (bitCount > 0)
	{
		out << byte;
	}
}

void getFrequencyTable(std::ifstream& in, FrequencyTable& frequencyTable, size_t& charCount)
{
	size_t size = 0;
	StreamGuard guard(in);
	size_t countSize = sizeof size_t;
	size_t chSize = sizeof(char);
	in.read(reinterpret_cast<char*>(&(size)), countSize);

	FrequencyTableElement temp;
	unsigned char ch = 0;
	size_t freq = 0;
	for (size_t i = 0; i < size; i++)
	{
		in.read(reinterpret_cast<char*>(&ch), chSize);
		in.read(reinterpret_cast<char*>(&freq), countSize);
		temp.ch_ = ch;
		temp.frequency_ = freq;
		charCount += freq;
		frequencyTable.pushBack(temp);
	}
}

void encode()
{
	std::ifstream in;
	std::ofstream out;
	if (!getFilesForEncoding(in, out))
	{
		return;
	}
	std::cout << "Начинается процесс кодирования, пожалуйста, подождите.\n";
	auto startTime = std::chrono::steady_clock::now();
	FrequencyTableElement ASCIItable[ASCIIsize];
	getFrequencies(in, ASCIItable);
	FrequencyTable frequencyTable;
	getFrequencyTable(ASCIItable, frequencyTable);
	frequencyTable = getCodes(frequencyTable, ASCIItable);
	getCodesInASCIItable(frequencyTable, ASCIItable);
	getKey(out, frequencyTable);
	getEncodedText(in, out, ASCIItable);
	auto endTime = std::chrono::steady_clock::now();
	StreamGuard guard(std::cout);
	std::cout << "Кодирование успешно завершено. Времени затрачено: " << std::fixed << std::setprecision(3) << ((std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime)).count()) / 1000.0 << "с.\n"
		<< "Результат Вы сможете увидеть в файле выходных данных.\n";
}

void decode()
{
	std::ifstream in;
	std::ofstream out;
	if (!getFilesForDecoding(in, out))
	{
		return;
	}
	std::cout << "Начинается процесс раскодирования, пожалуйста, подождите.\n";
	auto startTime = std::chrono::steady_clock::now();
	FrequencyTable frequencyTable;
	size_t charCount = 0;
	getFrequencyTable(in, frequencyTable, charCount);
	//getCodes(frequencyTable);
	CodeTree codeTree;
	codeTree.assembleTree(frequencyTable);
	codeTree.getDecodedText(in, out, charCount);
	auto endTime = std::chrono::steady_clock::now();
	StreamGuard guard(std::cout);
	std::cout << "Раскодирование успешно завершено. Времени затрачено: " << std::fixed << std::setprecision(3) << ((std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime)).count()) / 1000.0 << "с.\n"
		<< "Результат Вы сможете увидеть в файле выходных данных.\n";
}

void compare()
{
	std::ifstream in1;
	std::ifstream in2;
	if (!getFilesForCompare(in1, in2))
	{
		return;
	}
	bool isEqual = std::equal(std::istream_iterator<char>(in1), std::istream_iterator<char>(), std::istream_iterator<char>(in2), std::istream_iterator<char>());
	std::cout << "Равны ли файлы = " << std::boolalpha << isEqual << '\n';
}