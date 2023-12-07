#include "Pipe.h"

using namespace std;

int Pipe::MaxId = 0;

vector<int> Pipe::possible_diameters = {500, 700, 1000, 1400};


// Конструктор трубы
Pipe::Pipe() 
{
    name = "Non";
    length = 0.0;
    diameter = 0;
    in_repair = 0;
    ID = ++MaxId;
}

// Конструктор трубы для загрузки
Pipe::Pipe(string name, float length, int diameter, bool in_repair) {
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->in_repair = in_repair;
}

// Ввод информации о трубе
void Pipe::WriteInfo() {
    ENTER;
    cout << "Введите название трубы:" << endl;
    name = input_string();


    cout << "Введите длину трубы(м):" << endl;
    length = GetCorrectNumber(1.0, 100000000.);

    cout << "Выберете диаметр трубы:" << endl;
    diameter = SwitchNumber(possible_diameters);

    cout << "Введите состояние трубы:(0 - в ремонте; 1 - в эксплуатации)" << endl;

    if (GetCorrectNumber(0, 1)) { in_repair = true; }
    else { in_repair = false;}
}

void Pipe::WriteInfo_WithStateDiameter(int diameter) {
    ENTER;
    cout << "Введите название трубы:" << endl;
    name = input_string();


    cout << "Введите длину трубы(м):" << endl;
    length = GetCorrectNumber(1.0, 100000000.);

    this->diameter = diameter;

    cout << "Введите состояние трубы:(0 - в ремонте; 1 - в эксплуатации)" << endl;

    if (GetCorrectNumber(0, 1)) { in_repair = true; }
    else { in_repair = false; }
}

// Просмотр информации трубы
void Pipe::ShowInfo() {
    string status = in_repair ? " работает " : " в ремонте";
    cout << "Труба " << name << "; Длина: " << length << "; Диаметр: " << diameter
        << "; Состояние:" << status <<"; Id: " << ID << endl;
}


void Pipe::Edit(const Action act) {
    switch (act) {
    case SET_WORK: { in_repair = true; return; }
    case SET_REPAIR: { in_repair = false; return; }
    case SET_OPPOSITE: { in_repair = !in_repair; return; }
    default: {return;}
    }
}

ofstream& operator << (ofstream& file, const Pipe& pipe) {
    if (file.is_open()) {
        file << pipe.name << endl;
        file << pipe.length << endl;
        file << pipe.diameter << endl;
        file << pipe.in_repair << endl;
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
        file >> pipe.in_repair;
        file >> pipe.ID;
        Pipe::MaxId = (Pipe::MaxId < pipe.ID) ? pipe.ID : Pipe::MaxId;
    }
    return file;
}

