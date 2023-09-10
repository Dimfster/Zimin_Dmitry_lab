#include "Pipe.h"



Pipe::Pipe() {
    name = "Non";
    length = 0.0;
    diameter = 0;
    in_repair = false;
}

void Pipe::WhiteInfo() {
    clear;
    cout << "������� �������� �����:" << endl;
    cin >> name;

    cout << "������� ����� �����(�):" << endl;
    length = GetCorrectNumber(0.0, 100000000);

    cout << "������� ������� �����(��):" << endl;
    diameter = GetCorrectNumber(0, 1400);

    cout << "������� ��������� �����:(0 - � �������; 1 - � ������������)" << endl;
    if (GetCorrectNumber(0, 1)) {
        in_repair = true;
    }
    else {
        in_repair = false;
    }
}


void Pipe::ShowInfo() {
    cout << "����� " << name << "; �����: " << length << "; �������: " << diameter
        << "; ���������:(0 - � �������, 1 - � ������������): " << in_repair << endl;
}


void Pipe::Edit()
{
    clear;
    ShowInfo();
    cout << "�������� ��������� �����?(0 - ���, 1 - ��)" << endl;
    int answer = GetCorrectNumber(0, 1);
    if (answer) {
        in_repair = !in_repair;
    }

}

