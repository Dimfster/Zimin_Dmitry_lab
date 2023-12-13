#include "Pipe.h"
#include <math.h>

using namespace std;

int Pipe::MaxId = 0;

vector<int> Pipe::possible_diameters = {500, 700, 1000, 1400};


// ����������� �����
Pipe::Pipe() 
{
    name = "Non";
    length = 0.0;
    diameter = 0;
    in_work = 0;
    ID = ++MaxId;
}

// ����������� ����� ��� ��������
Pipe::Pipe(string name, float length, int diameter, bool in_work) {
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->in_work = in_work;
}

// ���� ���������� � �����
void Pipe::WriteInfo() {
    ENTER;
    cout << "������� �������� �����:" << endl;
    name = input_string();


    cout << "������� ����� �����(�):" << endl;
    length = GetCorrectNumber(1.0, 100000000.);

    cout << "�������� ������� �����:" << endl;
    diameter = SwitchNumber(possible_diameters);

    cout << "������� ��������� �����:(0 - � �������; 1 - � ������������)" << endl;

    if (GetCorrectNumber(0, 1)) { in_work = true; }
    else { in_work = false;}
}

void Pipe::WriteInfo_WithStateDiameter(int diameter) {
    ENTER;
    cout << "������� �������� �����:" << endl;
    name = input_string();


    cout << "������� ����� �����(�):" << endl;
    length = GetCorrectNumber(1.0, 100000000.);

    this->diameter = diameter;

    cout << "������� ��������� �����:(0 - � �������; 1 - � ������������)" << endl;

    if (GetCorrectNumber(0, 1)) { in_work = true; }
    else { in_work = false; }
}

// �������� ���������� �����
void Pipe::ShowInfo() {
    string status = in_work ? " �������� " : " � �������";
    cout << "����� " << name << "; �����: " << length << "; �������: " << diameter
        << "; ���������:" << status <<"; Id: " << ID << endl;
}


void Pipe::Edit(const Action act) {
    switch (act) {
    case SET_WORK: { in_work = true; return; }
    case SET_REPAIR: { in_work = false; return; }
    case SET_OPPOSITE: { in_work = !in_work; return; }
    default: {return;}
    }
}

double Pipe::GetCapacity() const {
    double capacity = sqrt(pow(diameter, 5) / length);
    return in_work ? capacity: -DBL_MAX;
}

ofstream& operator << (ofstream& file, const Pipe& pipe) {
    if (file.is_open()) {
        file << pipe.name << endl;
        file << pipe.length << endl;
        file << pipe.diameter << endl;
        file << pipe.in_work << endl;
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
        file >> pipe.in_work;
        file >> pipe.ID;
        Pipe::MaxId = (Pipe::MaxId < pipe.ID) ? pipe.ID : Pipe::MaxId;
    }
    return file;
}

