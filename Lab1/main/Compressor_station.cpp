#include "Compressor_station.h"


int Compressor_station::MaxId = 1000;

// Конструктор КС
Compressor_station::Compressor_station() {
    name = "Non";
    number_of_workshops = 0;
    this->active_workshops = 0;
    efficianty = 0;
    ID = ++MaxId;
}

// Конструктор КС для загрузки
Compressor_station::Compressor_station(string name, int number_of_workshops, int active_workshops, int efficianty) {
    this->name = name;
    this->number_of_workshops = number_of_workshops;
    this->active_workshops = active_workshops;
    this->efficianty = efficianty;
}

// Ввод информации о КС
void Compressor_station::WriteInfo() {
    ENTER;

    cout << "Введите название КС:" << endl;
    cin.ignore(1000000, '\n');
    getline(cin, name);

    cout << "Введите кол-во цехов:" << endl;
    number_of_workshops = GetCorrectNumber(0, 10);

    cout << "Введите кол-во работающих цехов" << endl;
    active_workshops = GetCorrectNumber(0, number_of_workshops);

    cout << "Введите эффективность станции(0-100)" << endl;
    efficianty = GetCorrectNumber(0, 100);

}

// Просмотр информации КС
void Compressor_station::ShowInfo() {
    setlocale(LC_ALL, "RU");
    cout << "КС " << name << "; Кол-во цехов: " << number_of_workshops << "; Рабочие цеха: " 
        << active_workshops << "; Эффктивность: " << efficianty << "; Id: " << ID << endl;
}


void Compressor_station::Edit(int active) {
    active_workshops = active;
}


// Редактирование КС
void Compressor_station::Edit()
{
    ENTER;
    ShowInfo();
    cout << "Изменить кол-во рабочих цехов:" << endl;
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

