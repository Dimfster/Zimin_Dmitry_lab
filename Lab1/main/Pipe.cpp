#include "Pipe.h"


Pipe::Pipe() {
    name = "Non";
    length = 0.0;
    diameter = 0;
    in_repair = false;
}


Pipe::Pipe(string name, float length, int diameter, bool in_repair) {
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->in_repair = in_repair;
}

void Pipe::WhiteInfo() {
    clear;
    cout << "Введите название трубы:" << endl;
    cin >> name;

    cout << "Введите длину трубы(м):" << endl;
    length = GetCorrectNumber(0.0, 100000000);

    cout << "Введите диаметр трубы(мм):" << endl;
    diameter = GetCorrectNumber(0, 1400);

    cout << "Введите состояние трубы:(0 - в ремонте; 1 - в эксплуатации)" << endl;
    if (GetCorrectNumber(0, 1)) {
        in_repair = true;
    }
    else {
        in_repair = false;
    }
}


void Pipe::ShowInfo() {
    cout << "Труба " << name << "; Длина: " << length << "; Диаметр: " << diameter
        << "; Состояние:(0 - в ремонте, 1 - в эксплуатации): " << in_repair << endl;
}


void Pipe::Edit()
{
    clear;
    ShowInfo();
    cout << "Изменить состояние трубы?(0 - нет, 1 - да)" << endl;
    int answer = GetCorrectNumber(0, 1);
    if (answer) {
        in_repair = !in_repair;
    }

}

void Pipe::SaveInfo(ofstream& file) {
    if (file.is_open()) {
        file << name << " " << length << " " << diameter << " " << in_repair << endl;
    }
}


