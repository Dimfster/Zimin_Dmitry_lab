#pragma once
#include <iostream> // Поток Ввода-вывода
#include <fstream> // Файловый поток
#include <string> 
#include <vector>
#include <unordered_map>
#include <map>

#include <list>

#include <Windows.h> // Системная библиотека(для очистки командоной строки и ввода любой клавиши)
#include <conio.h>
#include <sstream>
#include <filesystem>


#define ENTER std::cout << std::endl << std::endl;


// Функция проверки значения
template <typename T1,typename T2>
T1 GetCorrectNumber(T1 min, T2 max)
{
    T1 x;
    while ((std::cin >> x).fail()	
        || std::cin.peek() != '\n'
        || x < min || x > max)		
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "\nНеверный ввод данных!" << std::endl;
        std::cout << "Введите число от " << min << " до " << max << std::endl;
    }
    return x;
}



// Используется для удобства выбора в консоли
template <typename T>
std::map<int, int> Create_Console_Map(const std::unordered_map<int, T>& conteiner)
{
    std::map<int, int> new_map;
    int i = 0;
    for (auto& element : conteiner) {
        i++;
        new_map.insert({ i,element.first });
    }
    return new_map;
}

 
//---------------Выбор функции-------------------

using Function = void(*)();

inline void Switch(std::vector<Function> functions)
{
    int size = functions.size();
    int answer = GetCorrectNumber(0, size);
    if (answer)
    {
        functions[answer - 1]();
    }
    return;
}

// Ожидание ввода клавиши
inline void Wait() 
{
    while (true)
    {
        if (_kbhit()) break;
    }
}






