#include "Converter.h"
#include <iostream>
#include <map>

void printHelp()
{
	std::cout << "parse (fileName) : parsing file." << std::endl;
	std::cout << "print : print info about parsed file." << std::endl;
	std::cout << "out (fileName) (meshName) (materialName) : mesh export to .SWM file" << std::endl;
	std::cout << "help : print help message." << std::endl;
	std::cout << "exit : exit this program." << std::endl;
}


int main()
{
	Converter parser;

	std::cout << "ASE Parser : .ASE -> .SWM" << std::endl;

	for (;;)
	{
		std::cout << ">>>";

		std::string command;

		std::cin >> command;

		if (command == "parse")
		{
			char fileName[256];

			std::cin.getline(fileName, 256);

			if (parser.parse(fileName + 1))
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
			parser.printInfo();
		}
		else if (command == "help")
		{
			printHelp();
		}
		else if (command == "out")
		{
			std::string file, mesh, material;

			std::cin >> file >> mesh >> material;

			if (parser.out(file, mesh, material))
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