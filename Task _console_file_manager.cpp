//Реализовать терминальный файловый менеджер.Файловый менеджер должен уметь выполнять введенные команды от пользователя :
//-remove ${ file } (удалить файл, пример remove . / test.txt)
//- create ${ file } (создать файл, пример create . / test.txt)
//- exists ${ file } (проверить существование файла, пример create . / test.txt)
//- info ${ file } (получить информацию о файле, пример info . / test.txt)
//- copy ${ file1 } ${ file2 } (скопировать файл, пример copy . / test.txt / tmp / test.txt)
//- move ${ file1 } ${ file2 } (переместить файл, пример move . / test.txt / tmp / test.txt)
//- rename ${ file } ${ new_file } (переименовать файл, пример rename . / test.txt . / new_test.txt)
//
//Стоит обрабатывать возможные ошибки пользователей(неправильные команды пользователей, а также неправильные аргументы команд),
//также стоит добавить логирование в ключевых местах файлового менеджера и unit - тесты для системы парсинга пользовательских команд.

#include <iostream>
#include <filesystem>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include "Make_f.h" //Функция для создания двух текстовых файлов
#include "Error.h" // Функция вызова ошибки
#include "Help.h" // Функция вызова справки
using namespace std::filesystem;

using namespace std;


int main(int argc, char* argv[])
{
    make_file();
    help();
    
    std::string s;
    
    while (s != "exit") //Создаем цикл, пока не будет сообщена команда для выхода
    {
        std::getline(cin, s);
        std::vector<string> v; // Создаем вектор из введеной строки пользователем

        auto is_space = [](unsigned char c) -> bool { return isspace(c); };

        for (std::string::const_iterator e = s.cbegin(), b = find_if_not(e, s.cend(), is_space);
            b != s.cend();
            b = find_if_not(e, s.cend(), is_space))
        {
            e = find_if(b, s.cend(), is_space);
            v.emplace_back(b, e);
        }
        // Создаем переменные для циков IF и поиска команды
        bool found_help = binary_search(v.begin(), v.end(), "help"); 
        bool found_remove = binary_search(v.begin(), v.end(), "remove");
        bool found_create = binary_search(v.begin(), v.end(), "create");
        bool found_exists = binary_search(v.begin(), v.end(), "exists");
        bool found_info = binary_search(v.begin(), v.end(), "info");
        bool found_copy = binary_search(v.begin(), v.end(), "copy");
        bool found_move = binary_search(v.begin(), v.end(), "move");
        bool found_rename = binary_search(v.begin(), v.end(), "rename");
        // Создаем наши условия на найденые слова в элементах вектора
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


