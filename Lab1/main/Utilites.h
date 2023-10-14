#pragma once
#include <iostream> // Поток Ввода-вывода
#include <fstream> // Файловый поток
#include <string> 
#include <vector>
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