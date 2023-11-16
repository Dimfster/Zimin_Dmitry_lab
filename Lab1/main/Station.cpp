#include "Station.h"

using namespace std;


// ����������� ��
Station::Station() {
    name = "Non";
    number_of_workshops = 0;
    active_workshops = 0;
    efficianty = 0;
    ID = ++MaxId;
}

// ����������� �� ��� ��������
Station::Station(string name, int number_of_workshops, int active_workshops, int efficianty) {
    this->name = name;
    this->number_of_workshops = number_of_workshops;
    this->active_workshops = active_workshops;
    this->efficianty = efficianty;
}

// ���� ���������� � ��
void Station::WriteInfo() {
    ENTER;

    cout << "������� �������� ��:" << endl;
    name = input_string(cin);

    cout << "������� ���-�� �����:" << endl;
    number_of_workshops = GetCorrectNumber(cin, 0, 10);

    cout << "������� ���-�� ���������� �����" << endl;
    active_workshops = GetCorrectNumber(cin, 0, number_of_workshops);

    cout << "������� ������������� �������(0-100)" << endl;
    efficianty = GetCorrectNumber(cin, 0, 100);

}

// �������� ���������� ��
void Station::ShowInfo() {
    setlocale(LC_ALL, "RU");
    cout << "�� " << name << "; ���-�� �����: " << number_of_workshops << "; ������� ����: " 
        << active_workshops << "; �������������: " << efficianty << "; Id: " << ID << endl;
}


void Station::Edit(int active) {
    active_workshops = active;
    if (active_workshops > number_of_workshops)
    {
        active_workshops = number_of_workshops;
    }
}


// �������������� ��
void Station::Edit()
{
    ENTER;
    ShowInfo();
    cout << "�������� ���-�� ������� �����:" << endl;
    int answer = GetCorrectNumber(cin, 0, number_of_workshops);
    Edit(answer);
}

ofstream& operator << (ofstream& file, const Station& CS) {
    if (file.is_open()) {
        file << CS.name << endl;
        file << CS.number_of_workshops << endl;
        file << CS.active_workshops << endl;
        file << CS.efficianty << endl;
        file << CS.ID << endl;
    }
    return file;
}


ifstream& operator >> (ifstream& file, Station& CS) {
    if (file.is_open()) {
        file >> ws;
        getline(file, CS.name);
        file >> CS.number_of_workshops;
        file >> CS.active_workshops;
        file >> CS.efficianty;
        file >> CS.ID;
        if (CS.ID > Station::MaxId)
            Station::MaxId = CS.ID;
    }
    return file;
}

