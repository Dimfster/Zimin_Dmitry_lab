#include "Pipe.h"


// ����������� �����
Pipe::Pipe() {
    name = "Non";
    length = 0.0;
    diameter = 0;
    in_repair = false;
}

// ����������� ����� ��� ��������
Pipe::Pipe(string name, float length, int diameter, bool in_repair) {
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->in_repair = in_repair;
}

// ���� ���������� � �����
void Pipe::WhiteInfo() {
    CLEAR;

    cout << "������� �������� �����:" << endl;
    cin.ignore(1000000, '\n');
    getline(cin, name);

    cout << "������� ����� �����(�):" << endl;
    length = GetCorrectNumber(1.0, 100000000);

    cout << "������� ������� �����(��):" << endl;
    diameter = GetCorrectNumber(300, 1400);

    cout << "������� ��������� �����:(0 - � �������; 1 - � ������������)" << endl;
    if (GetCorrectNumber(0, 1)) {
        in_repair = true;
    }
    else {
        in_repair = false;
    }
}

// �������� ���������� �����
void Pipe::ShowInfo() {
    cout << "����� " << name << "; �����: " << length << "; �������: " << diameter
        << "; ���������:(0 - � �������, 1 - � ������������): " << in_repair << endl;
}

// �������������� �����
void Pipe::Edit()
{
    CLEAR;
    ShowInfo();
    cout << "�������� ��������� �����?(0 - ���, 1 - ��)" << endl;
    int answer = GetCorrectNumber(0, 1);
    if (answer) {
        in_repair = !in_repair;
    }

}

// ���������� ������ ����� � ����
void Pipe::SaveInfo(ofstream& file) {
    if (file.is_open()) {
        file << name << ";" << length << ";" << diameter << ";" << in_repair <<";" << endl;
    }
}


