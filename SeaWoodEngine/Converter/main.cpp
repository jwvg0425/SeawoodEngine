#include "Converter.h"
#include <iostream>
#include <map>
#include <memory>

void printHelp()
{
	std::cout << "parse (fileName) : parsing file." << std::endl;
	std::cout << "print : print info about parsed file." << std::endl;
	std::cout << "out (fileName) (nodeName) : node export to .SWM file" << std::endl;
	std::cout << "help : print help message." << std::endl;
	std::cout << "exit : exit this program." << std::endl;
}


int main()
{
	std::unique_ptr<Converter> converter(new Converter);

	std::cout << "ASE Converter : .ASE -> .SWM" << std::endl;

	for (;;)
	{
		std::cout << ">>>";

		std::string command;

		std::cin >> command;

		if (command == "parse")
		{
			char fileName[256];

			std::cin.getline(fileName, 256);

			if (converter->parse(fileName + 1))
			{
				std::cout << "parsing succed." << std::endl;
			}
			else
			{
				std::cout << "parsing failed." << std::endl;
			}
		}
		else if (command == "print")
		{
			converter->printInfo();
		}
		else if (command == "help")
		{
			printHelp();
		}
		else if (command == "out")
		{
			std::string file, node;

			std::cin >> file >> node;

			if (converter->out(file, node))
			{
				std::cout << "out succed." << std::endl;
			}
			else
			{
				std::cout << "out failed." << std::endl;
			}
		}
		else if (command == "exit")
		{
			return 0;
		}
	}

	return 0;
}