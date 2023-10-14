#include "Compressor_station.h"


int Compressor_station::MaxId = 1000;

// Конструктор КС
Compressor_station::Compressor_station() {
    name = "Non";
    number_of_workshops = 0;
    this->active_workshops = 0;
    type = "type";
    ID = ++MaxId;
}

// Конструктор КС для загрузки
Compressor_station::Compressor_station(string name, int number_of_workshops, int active_workshops, string type) {
    this->name = name;
    this->number_of_workshops = number_of_workshops;
    this->active_workshops = active_workshops;
    this->type = type;
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

    cout << "Введите тип станции(A, B, C)" << endl;
    cin >> type;

}

// Просмотр информации КС
void Compressor_station::ShowInfo() {
    setlocale(LC_ALL, "RU");
    cout << "КС " << name << "; Кол-во цехов: " << number_of_workshops << "; Рабочие цеха: " 
        << active_workshops << "; Тип: " << type << "; Id: " << ID << endl;
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
    active_workshops = GetCorrectNumber(0, number_of_workshops);
    Edit(GetCorrectNumber(0, number_of_workshops));
}


ofstream& operator << (ofstream& file, const Compressor_station& CS) {
    if (file.is_open()) {
        file << CS.name << endl;
        file << CS.number_of_workshops << endl;
        file << CS.active_workshops << endl;
        file << CS.type << endl;
        file << CS.ID << endl;
    }
    return file;
}


ifstream& operator >> (ifstream& file, Compressor_station& CS) {
    if (file.is_open()) {
        file >> CS.name;
        file >> CS.number_of_workshops;
        file >> CS.active_workshops;
        file >> CS.type;
        file >> CS.ID;
    }
    return file;
}

