#include "Pipe.h"
#include <math.h>

using namespace std;

int Pipe::MaxId = 0;

vector<int> Pipe::possible_diameters = {500, 700, 1000, 1400};


// Конструктор трубы
Pipe::Pipe() 
{
    name = "Non";
    length = 0.0;
    diameter = 0;
    in_work = 0;
    ID = ++MaxId;
}

// Конструктор трубы для загрузки
Pipe::Pipe(string name, float length, int diameter, bool in_work) {
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->in_work = in_work;
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

    if (GetCorrectNumber(0, 1)) { in_work = true; }
    else { in_work = false;}
}

void Pipe::WriteInfo_WithStateDiameter(int diameter) {
    ENTER;
    cout << "Введите название трубы:" << endl;
    name = input_string();


    cout << "Введите длину трубы(м):" << endl;
    length = GetCorrectNumber(1.0, 100000000.);

    this->diameter = diameter;

    cout << "Введите состояние трубы:(0 - в ремонте; 1 - в эксплуатации)" << endl;

    if (GetCorrectNumber(0, 1)) { in_work = true; }
    else { in_work = false; }
}

// Просмотр информации трубы
void Pipe::ShowInfo() {
    string status = in_work ? " работает " : " в ремонте";
    cout << "Труба " << name << "; Длина: " << length << "; Диаметр: " << diameter
        << "; Состояние:" << status <<"; Id: " << ID << endl;
}


void Pipe::Edit(const Action act) {
    switch (act) {
    case SET_WORK: { in_work = true; return; }
    case SET_REPAIR: { in_work = false; return; }
    case SET_OPPOSITE: { in_work = !in_work; return; }
    default: {return;}
    }
}

double Pipe::GetCapacity() const {
    double capacity = sqrt(pow(diameter, 5) / length);
    return in_work ? capacity: -DBL_MAX;
}

ofstream& operator << (ofstream& file, const Pipe& pipe) {
    if (file.is_open()) {
        file << pipe.name << endl;
        file << pipe.length << endl;
        file << pipe.diameter << endl;
        file << pipe.in_work << endl;
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
        file >> pipe.in_work;
        file >> pipe.ID;
        Pipe::MaxId = (Pipe::MaxId < pipe.ID) ? pipe.ID : Pipe::MaxId;
    }
    return file;
}

