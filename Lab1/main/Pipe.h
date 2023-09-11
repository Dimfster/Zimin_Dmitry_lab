#pragma once

#include "Utilites.h"


using namespace std;

struct Pipe {
    string name;
    float length;
    int diameter;
    bool in_repair;

    Pipe();
    Pipe(string name, float length, int diameter, bool in_repair);

    void WhiteInfo();

    void ShowInfo();

    void Edit();

    void SaveInfo(ofstream& file);

};




