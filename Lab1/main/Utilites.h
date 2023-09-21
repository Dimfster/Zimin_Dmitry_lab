#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <sstream>


#define CLEAR system("cls");


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