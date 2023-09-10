#pragma once
#include <Windows.h>


inline void ClearCMD() {
    system("cls"); // ��� ������� ���������� ������
}



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
        std::cout << "������� ����� �� " << min << " �� " << max << std::endl;
    }
    return x;
}