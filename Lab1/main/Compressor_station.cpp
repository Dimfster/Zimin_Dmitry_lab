#include "Compressor_station.h"


Compressor_station::Compressor_station() {
    name = "Non";
    number_of_workshops = 0;
    active_workshops = 0;
    type = "No";
}


Compressor_station::Compressor_station(string name, int number_of_workshops, int active_workshops, string type) {
    this->name = name;
    this->number_of_workshops = number_of_workshops;
    this->active_workshops = active_workshops;
    this->type = type;
}

void Compressor_station::WhiteInfo() {
    clear;

    cout << "������� �������� ��:" << endl;
    cin >> name;

    cout << "������� ���-�� �����:" << endl;
    number_of_workshops = GetCorrectNumber(0, 10);

    cout << "������� ���-�� ���������� �����" << endl;
    active_workshops = GetCorrectNumber(0, number_of_workshops);

    cout << "������� ��� �������(A, B, C)" << endl;
    cin >> type;

}

void Compressor_station::ShowInfo() {
    cout << "�� " << name << "; ���-�� �����: " << number_of_workshops << "; ������� ����: " << active_workshops << "; ���: " << type << endl;
}


void Compressor_station::Edit()
{
    clear;
    ShowInfo();
    cout << "�������� ���-�� ������� �����:" << endl;
    active_workshops = GetCorrectNumber(0, number_of_workshops);
}


void Compressor_station::SaveInfo(ofstream& file)
{
    if (file.is_open()) {
        file << name << " " << number_of_workshops << " " << active_workshops << " " << type << endl;
    }
}

