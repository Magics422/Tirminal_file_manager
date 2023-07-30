//����������� ������������ �������� ��������.�������� �������� ������ ����� ��������� ��������� ������� �� ������������ :
//-remove ${ file } (������� ����, ������ remove . / test.txt)
//- create ${ file } (������� ����, ������ create . / test.txt)
//- exists ${ file } (��������� ������������� �����, ������ create . / test.txt)
//- info ${ file } (�������� ���������� � �����, ������ info . / test.txt)
//- copy ${ file1 } ${ file2 } (����������� ����, ������ copy . / test.txt / tmp / test.txt)
//- move ${ file1 } ${ file2 } (����������� ����, ������ move . / test.txt / tmp / test.txt)
//- rename ${ file } ${ new_file } (������������� ����, ������ rename . / test.txt . / new_test.txt)
//
//����� ������������ ��������� ������ �������������(������������ ������� �������������, � ����� ������������ ��������� ������),
//����� ����� �������� ����������� � �������� ������ ��������� ��������� � unit - ����� ��� ������� �������� ���������������� ������.

#include <iostream>
#include <filesystem>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include "Make_f.h" //������� ��� �������� ���� ��������� ������
#include "Error.h" // ������� ������ ������
#include "Help.h" // ������� ������ �������
using namespace std::filesystem;

using namespace std;


int main(int argc, char* argv[])
{
    make_file();
    help();
    
    std::string s;
    
    while (s != "exit") //������� ����, ���� �� ����� �������� ������� ��� ������
    {
        std::getline(cin, s);
        std::vector<string> v; // ������� ������ �� �������� ������ �������������

        auto is_space = [](unsigned char c) -> bool { return isspace(c); };

        for (std::string::const_iterator e = s.cbegin(), b = find_if_not(e, s.cend(), is_space);
            b != s.cend();
            b = find_if_not(e, s.cend(), is_space))
        {
            e = find_if(b, s.cend(), is_space);
            v.emplace_back(b, e);
        }
        // ������� ���������� ��� ����� IF � ������ �������
        bool found_help = binary_search(v.begin(), v.end(), "help"); 
        bool found_remove = binary_search(v.begin(), v.end(), "remove");
        bool found_create = binary_search(v.begin(), v.end(), "create");
        bool found_exists = binary_search(v.begin(), v.end(), "exists");
        bool found_info = binary_search(v.begin(), v.end(), "info");
        bool found_copy = binary_search(v.begin(), v.end(), "copy");
        bool found_move = binary_search(v.begin(), v.end(), "move");
        bool found_rename = binary_search(v.begin(), v.end(), "rename");
        // ������� ���� ������� �� �������� ����� � ��������� �������
        if (found_help)
        {
            help();
        }
                else if(found_remove)
        {
            remove(v[1].c_str());
            cout << "File" << v[1] << " was deleted." << endl;
        }
                else if (found_create)
        {
            ofstream outfile(v[1]);
            outfile.close();
            cout << "You file create." << endl;
        }
                else if (found_exists)
        {
            if (!filesystem::exists(v[1]))
            {
                cout << "File not found!" << endl;
            }
            else 
            {
                cout << "File already exists!"<< endl;
            }
        }
                else if (found_info)
        {
            fstream file(v[1]);
            int size = 0;
            file.seekg(0, std::ios::end);
            size = file.tellg();
            cout << "Size your file : " << size << " byte." << endl;
            file.close();
        }
                else if (found_copy)
        {
            ifstream  src(v[1], ios::binary);
            ofstream  dst(v[2], ios::binary);

            dst << src.rdbuf();
            cout << "File copy complited." << endl;
        }
                else if (found_move)
        {
            string src(v[1]);
            string dst(v[2]);
            string cmd = "copy " + src + " " + dst;
            system(cmd.c_str());
            cout << "File moving copmlited." << endl;
        }
                else if (found_rename)
        {
            const filesystem::path path = current_path();
            filesystem::rename(path / v[1], path / v[2]);
            cout << "File rename copmlited." << endl;
        }
        else
        {
            error();
        }
    }
}


