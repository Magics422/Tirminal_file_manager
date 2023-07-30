#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

void make_file()
{
    std::ofstream MyFile("Test.txt");
    MyFile.close();

    std::ofstream MyFile1("test_2.txt");
    MyFile.close();

    std::cout << "All .txt File in our path:" << std::endl;
}