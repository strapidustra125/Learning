/***********************************************************************************************
 * 
 * Успешная попытка: 79330647
 * 
 * -- ПРИНЦИП РАБОТЫ --
 * 
 * Реализовал Дек на кольцевом буффере: 2 указателя (на первый и на последний элементы), размер
 * и сам динамический массив.
 * 
 * Методы добавления push_back и push_front сначала проверяют размер: если об равен 
 * максимальному размеру массива, то добавлять некуда, возврат false. Далее рассматривается 
 * corner case, когда размер = 0 => не надо смещать указатели, а просто записать элемент в 
 * текущую позицию указателя. А если размер не нулевой, то указатель смещается.
 * Проверок пересечения указателей не делаю, потому что достаточно проверки размера Дека.
 * 
 * Методы удаления pop_back и pop_front так же сначала проверяют размер, но уже на 0. Далее 
 * corner case на size = 1 => смещать указатель не надо, т.к. это последний элемент.
 * 
 * Все функции чтения входных данных реализовал соответствующими функциями. Даже первые 2 числа  
 * читаю через std::getline, т.к. если просто прочитать строковую переменную через std::cin, 
 * потом первый std::getline прочитает пустую строку. 
 * 
 * Обработка команд просто через if, не стал вводить красивые emum'ы, потому что программа 
 * маленькая и понятная. Везде использую this для полей класса внутри класса, чтобы визуально
 * поля класса отличались от обычных переменных.
 * 
 * -- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
 * 
 * Все операции контролирует размер массива, который может изменииться только с шагом 1, поэтому 
 * указатели не обгонят друг друга. Остальные частные случаи обработаны: добавление в пустой 
 * массив и взятие из массива с размером 1 - в этих случаях не надо двигать указатели, только 
 * менять ращмер.
 * 
 * -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 * 
 * Все 4 операции выполняются за О(1), т.к. нигде нет циклов, кроме чтения входных данных (но от
 * него избавиться не получится).
 * 
 * -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 * 
 * Все переменные, кроме размера массива _deque, занимают О(1) памяти. А массив - О(n), поэтому 
 * общие затраты памяти - О(n), где n - размер кольцевого буффера.
 * 
 **********************************************************************************************/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

#ifdef MY_IDE
#define out fout
#define in fin
#else
#define out std::cout
#define in std::cin
#endif

std::ifstream fin("in.txt");
std::ofstream fout("out.txt");

#define MAX_DEQUE_SIZE 50000

class Deque
{
private:

	int* _deque;
	int _size;
	int _maxSize;

	int _head;
	int _tail;

public:

	Deque(const int & dequeMaxSize=MAX_DEQUE_SIZE)
	{
		this->_maxSize = dequeMaxSize;
		this->_size = 0;
		this->_deque = new int[dequeMaxSize];

		this->_head = 0;
		this->_tail = 0;
	}

	bool push_back(const int& value);
	bool push_front(const int& value);
	bool pop_back(int& value);
	bool pop_front(int& value);

	int size() const;
};


bool Deque::push_back(const int& value)
{
	if (this->size() == this->_maxSize) return false;

	if(this->size())
		if (this->_tail == 0) this->_tail = this->_maxSize - 1;
		else this->_tail--;
	
	this->_deque[this->_tail] = value;

	this->_size++;
	return true;
}

bool Deque::push_front(const int& value)
{
	if (this->size() == this->_maxSize) return false;

	if (this->size())
		if (this->_head == this->_maxSize - 1) this->_head = 0;
		else this->_head++;

	this->_deque[this->_head] = value;

	this->_size++;
	return true;
}

bool Deque::pop_back(int& value)
{
	if (!this->size()) return false;

	value = this->_deque[this->_tail];

	if(this->size() != 1)
		if (this->_tail == this->_maxSize - 1) this->_tail = 0;
		else this->_tail++;

	this->_size--;
	return true;
}

bool Deque::pop_front(int& value)
{
	if (!this->size()) return false;

	value = this->_deque[this->_head];

	if (this->size() != 1)
		if (this->_head == 0) this->_head = this->_maxSize - 1;
		else this->_head--;

	this->_size--;
	return true;
}

int Deque::size() const
{
	return this->_size;
}




int readCommandsNumber()
{
	std::string line;
	std::getline(in, line);
	return std::stoi(line);
}

int readMaxDequeSize()
{
	std::string line;
	std::getline(in, line);
	return std::stoi(line);
}

std::string readCommand(int& param)
{
	std::string commandLine;
	std::getline(in, commandLine);

	if (commandLine.find(' ') == std::string::npos) return commandLine;

	std::string command = "";
	std::string number = "";
	bool secondWord = false;

	for (int j = 0; j < commandLine.size(); j++)
	{
		if (secondWord) number += commandLine[j];
		else
		{
			if (commandLine[j] == ' ') secondWord = true;
			else command += commandLine[j];
		}
	}

	param = std::stoi(number);
	return command;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int commandsNumber = readCommandsNumber();
	Deque deque(readMaxDequeSize());

	for (int i = 0; i < commandsNumber; i++)
	{
		int param;
		std::string command = readCommand(param);

		if(command == "push_front")
		{
			if (!deque.push_front(param)) out << "error" << std::endl;
		}
		else if (command == "push_back")
		{
			if (!deque.push_back(param)) out << "error" << std::endl;
		}
		else if (command == "pop_front")
		{
			int value;
			if (!deque.pop_front(value)) out << "error" << std::endl;
			else out << value << std::endl;
		}
		else if (command == "pop_back")
		{
			int value;
			if (!deque.pop_back(value)) out << "error" << std::endl;
			else out << value << std::endl;
		}
	}

	return 0;
}