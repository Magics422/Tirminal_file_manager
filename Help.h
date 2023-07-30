#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

void help()
{
	std::cout << "Avaible commad: remove; create, exists, info, copy, move, rename." << std::endl;
	std::cout << "For examle: delete file: 'remove . / test.txt'" << std::endl;
	std::cout << "Type 'help' for help with program" << std::endl;
	std::cout << "Type 'exit' for exit from program" << std::endl;
}