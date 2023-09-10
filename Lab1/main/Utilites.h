#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>

#define clear system("cls");



template <typename T1,typename T2>
T1 GetCorrectNumber(T1 min, T2 max)
{
    T1 x;
    while ((std::cin >> x).fail()	
        || std::cin.peek() != '\n'	
        || x < min || x > max)		
    {
        std::cin.ignore(10000, '\n');
        std::cout << "¬ведите число от " << min << " до " << max << std::endl;
    }
    return x;
}