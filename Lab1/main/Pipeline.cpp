#include "Pipeline.h"

Pipeline::Pipeline() {
    ClearCMD();
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

void Pipeline::ShowInfo() {
    cout << "Труба " << name << "; Длина: " << length << "; Диаметр: " << diameter 
        << "; Состояние:(0 - в ремонте, 1 - в эксплуатации): " << in_repair << endl;
}


void Pipeline::Edit()
{
    ClearCMD();
    ShowInfo();
    cout << "Изменить состояние трубы?(0 - нет, 1 - да)" << endl;
    int answer = GetCorrectNumber(0, 1);
    if (answer) {
        in_repair = !in_repair;
    }
            
}
