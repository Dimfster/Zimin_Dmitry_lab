#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <sstream>


#define CLEAR system("cls");


// ������� �������� ��������
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
        std::cout << "\n�������� ���� ������!" << std::endl;
        std::cout << "������� ����� �� " << min << " �� " << max << std::endl;
    }
    return x;
}