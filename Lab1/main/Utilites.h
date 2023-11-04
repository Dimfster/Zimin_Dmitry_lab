#pragma once
#include <iostream> // ����� �����-������
#include <fstream> // �������� �����
#include <string> 
#include <vector>
#include <unordered_map>
#include <map>

#include <list>

#include <Windows.h> // ��������� ����������(��� ������� ���������� ������ � ����� ����� �������)
#include <conio.h>
#include <sstream>
#include <filesystem>


#define ENTER std::cout << std::endl << std::endl;


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



// ������������ ��� �������� ������ � �������
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

 
//---------------����� �������-------------------

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

// �������� ����� �������
inline void Wait() 
{
    while (true)
    {
        if (_kbhit()) break;
    }
}






