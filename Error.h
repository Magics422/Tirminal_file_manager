#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

void error()
{
    std::cout << "Incorrect syntax or unknown command. Try help for more details." << std::endl;
}