#include "Compressor_station.h"


Compressor_station::Compressor_station() {
    ClearCMD();

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
    ClearCMD();
    ShowInfo();
    cout << "�������� ���-�� ������� �����:" << endl;
    active_workshops = GetCorrectNumber(0, number_of_workshops);
}