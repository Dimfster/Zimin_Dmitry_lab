#pragma once

#include "Utilites.h"

using namespace std;

class Pipe {
    string name;
    float length;
    int diameter;
    bool in_repair;
    int ID;

    

public:
    static int MaxId;

    Pipe();
    Pipe(const string name, const float length, const int diameter, const bool in_repair);

    void WriteInfo();

    void ShowInfo();

    void Edit();

    void Edit(const int answer);

    friend ofstream& operator << (ofstream& out, const Pipe& pipe);
    friend ifstream& operator >> (ifstream& file, Pipe& pipe);
};




