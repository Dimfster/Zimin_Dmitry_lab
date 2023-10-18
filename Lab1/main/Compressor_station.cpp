#include "Compressor_station.h"


int Compressor_station::MaxId = 1000;

// ����������� ��
Compressor_station::Compressor_station() {
    name = "Non";
    number_of_workshops = 0;
    this->active_workshops = 0;
    efficianty = 0;
    ID = ++MaxId;
}

// ����������� �� ��� ��������
Compressor_station::Compressor_station(string name, int number_of_workshops, int active_workshops, int efficianty) {
    this->name = name;
    this->number_of_workshops = number_of_workshops;
    this->active_workshops = active_workshops;
    this->efficianty = efficianty;
}

// ���� ���������� � ��
void Compressor_station::WriteInfo() {
    ENTER;

    cout << "������� �������� ��:" << endl;
    cin.ignore(1000000, '\n');
    getline(cin, name);

    cout << "������� ���-�� �����:" << endl;
    number_of_workshops = GetCorrectNumber(0, 10);

    cout << "������� ���-�� ���������� �����" << endl;
    active_workshops = GetCorrectNumber(0, number_of_workshops);

    cout << "������� ������������� �������(0-100)" << endl;
    efficianty = GetCorrectNumber(0, 100);

}

// �������� ���������� ��
void Compressor_station::ShowInfo() {
    setlocale(LC_ALL, "RU");
    cout << "�� " << name << "; ���-�� �����: " << number_of_workshops << "; ������� ����: " 
        << active_workshops << "; ������������: " << efficianty << "; Id: " << ID << endl;
}


void Compressor_station::Edit(int active) {
    active_workshops = active;
}


// �������������� ��
void Compressor_station::Edit()
{
    ENTER;
    ShowInfo();
    cout << "�������� ���-�� ������� �����:" << endl;
    int answer = GetCorrectNumber(0, number_of_workshops);
    Edit(answer);
}

ofstream& operator << (ofstream& file, const Compressor_station& CS) {
    if (file.is_open()) {
        file << CS.name << endl;
        file << CS.number_of_workshops << endl;
        file << CS.active_workshops << endl;
        file << CS.efficianty << endl;
        file << CS.ID << endl;
    }
    return file;
}


ifstream& operator >> (ifstream& file, Compressor_station& CS) {
    if (file.is_open()) {
        file >> CS.name;
        file >> CS.number_of_workshops;
        file >> CS.active_workshops;
        file >> CS.efficianty;
        file >> CS.ID;
    }
    return file;
}

