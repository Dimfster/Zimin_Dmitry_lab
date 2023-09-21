#include "Compressor_station.h"

// Конструктор КС
Compressor_station::Compressor_station() {
    name = "Non";
    number_of_workshops = 0;
    active_workshops = 0;
    type = "No";
}

// Конструктор КС для загрузки
Compressor_station::Compressor_station(string name, int number_of_workshops, int active_workshops, string type) {
    this->name = name;
    this->number_of_workshops = number_of_workshops;
    this->active_workshops = active_workshops;
    this->type = type;
}

// Ввод информации о КС
void Compressor_station::WhiteInfo() {
    CLEAR;

    cout << "Введите название КС:" << endl;
    cin.ignore(1000000, '\n');
    getline(cin, name);

    cout << "Введите кол-во цехов:" << endl;
    number_of_workshops = GetCorrectNumber(0, 10);

    cout << "Введите кол-во работающих цехов" << endl;
    active_workshops = GetCorrectNumber(0, number_of_workshops);

    cout << "Введите тип станции(A, B, C)" << endl;
    cin >> type;

}

// Просмотр информации КС
void Compressor_station::ShowInfo() {
    setlocale(LC_ALL, "RU");
    cout << "КС " << name << "; Кол-во цехов: " << number_of_workshops << "; Рабочие цеха: " << active_workshops << "; Тип: " << type << endl;
}

// Редактирование КС
void Compressor_station::Edit()
{
    CLEAR;
    ShowInfo();
    cout << "Изменить кол-во рабочих цехов:" << endl;
    active_workshops = GetCorrectNumber(0, number_of_workshops);
}

// Сохраниние данных КС в файл
void Compressor_station::SaveInfo(ofstream& file)
{
    if (file.is_open()) {
        file << name << ";" << number_of_workshops << ";" << active_workshops << ";" << type << ";" << endl;
    }
}

