#include "Pipe.h"

using namespace std;



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
    cin.ignore(1000000, '\n');
    getline(cin, name);

    cout << "Введите длину трубы(м):" << endl;
    length = GetCorrectNumber(1.0, 100000000);

    cout << "Введите диаметр трубы(мм):" << endl;
    diameter = GetCorrectNumber(100, 1400);

    cout << "Введите состояние трубы:(0 - в ремонте; 1 - в эксплуатации)" << endl;
    if (GetCorrectNumber(0, 1)) {
        in_repair = true;
    }
    else {
        in_repair = false;
    }
}

// Просмотр информации трубы
void Pipe::ShowInfo() {
    cout << "Труба " << name << "; Длина: " << length << "; Диаметр: " << diameter
        << "; Состояние:(0 - в ремонте, 1 - в эксплуатации): " << in_repair <<"; Id: " << ID << endl;
}


void Pipe::Edit(int status) {
    if (status) in_repair = !in_repair;
}


// Редактирование трубы
void Pipe::Edit()
{
    ENTER;
    ShowInfo();
    cout << "Изменить состояние трубы?(0 - нет, 1 - да)" << endl;
    Edit(GetCorrectNumber(0, 1));
}



ostream& operator << (ostream& out, const Pipe& pipe)
{
    return out;
}

istream& operator >> (istream& in, Pipe& pipe) 
{
    return in;
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
        file >> pipe.name;
        file >> pipe.length;
        file >> pipe.diameter;
        file >> pipe.in_repair;
        file >> pipe.ID;
    }
    return file;
}

