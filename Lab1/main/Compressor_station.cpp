#include "Compressor_station.h"


Compressor_station::Compressor_station() {
    name = "Non";
    number_of_workshops = 0;
    active_workshops = 0;
    type = "No";
}

void Compressor_station::WhiteInfo() {
    clear;

    cout << "Введите название КС:" << endl;
    cin >> name;

    cout << "Введите кол-во цехов:" << endl;
    number_of_workshops = GetCorrectNumber(0, 10);

    cout << "Введите кол-во работающих цехов" << endl;
    active_workshops = GetCorrectNumber(0, number_of_workshops);

    cout << "Введите тип станции(A, B, C)" << endl;
    cin >> type;

}

void Compressor_station::ShowInfo() {
    cout << "КС " << name << "; Кол-во цехов: " << number_of_workshops << "; Рабочие цеха: " << active_workshops << "; Тип: " << type << endl;
}


void Compressor_station::Edit()
{
    clear;
    ShowInfo();
    cout << "Изменить кол-во рабочих цехов:" << endl;
    active_workshops = GetCorrectNumber(0, number_of_workshops);
}