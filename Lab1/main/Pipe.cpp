#include "Pipe.h"

using namespace std;



// ����������� �����
Pipe::Pipe() 
{
    name = "Non";
    length = 0.0;
    diameter = 0;
    in_repair = 0;
    ID = ++MaxId;
}

// ����������� ����� ��� ��������
Pipe::Pipe(string name, float length, int diameter, bool in_repair) {
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->in_repair = in_repair;
}

// ���� ���������� � �����
void Pipe::WriteInfo() {
    ENTER;
    cout << "������� �������� �����:" << endl;
    name = input_string(cin);


    cout << "������� ����� �����(�):" << endl;
    length = GetCorrectNumber(cin, 1.0, 100000000.);

    cout << "������� ������� �����(��):" << endl;
    diameter = GetCorrectNumber(cin, 100, 1400);

    cout << "������� ��������� �����:(0 - � �������; 1 - � ������������)" << endl;
    if (cin,GetCorrectNumber(cin, 0, 1)) {
        in_repair = true;
    }
    else {
        in_repair = false;
    }
}

// �������� ���������� �����
void Pipe::ShowInfo() {
    cout << "����� " << name << "; �����: " << length << "; �������: " << diameter
        << "; ���������:(0 - � �������, 1 - � ������������): " << in_repair <<"; Id: " << ID << endl;
}


void Pipe::Edit(int status) {
    if (status) in_repair = !in_repair;
}


// �������������� �����
void Pipe::Edit()
{
    ENTER;
    ShowInfo();
    cout << "�������� ��������� �����?(0 - ���, 1 - ��)" << endl;
    Edit(GetCorrectNumber(cin, 0, 1));
}




ofstream& operator << (ofstream& file, const Pipe& pipe) {
    if (file.is_open()) {
        file << pipe.name << endl;
        file << pipe.length << endl;
        file << pipe.diameter << endl;
        file << pipe.in_repair << endl;
        file << pipe.ID << endl;
    }
    return file;
}

ifstream& operator >> (ifstream& file, Pipe& pipe) {
    if (file.is_open()) {
        file >> ws;
        getline(file, pipe.name);
        file >> pipe.length;
        file >> pipe.diameter;
        file >> pipe.in_repair;
        file >> pipe.ID;
    }
    return file;
}

