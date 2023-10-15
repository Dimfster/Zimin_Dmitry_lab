#pragma once

#include "Utilites.h"

using namespace std;

class Pipe {
    float length;
    int diameter;

    
public:
    int ID;
    static int MaxId;

    string name;
    bool in_repair;

    Pipe();
    Pipe(const string name, const float length, const int diameter, const bool in_repair);

    void WriteInfo();

    void ShowInfo();

    void Edit();

    void Edit(const int answer);

    friend ostream& operator << (ostream& out, const Pipe& pipe);
    friend istream& operator >> (istream& file, Pipe& pipe);

    friend ofstream& operator << (ofstream& out, const Pipe& pipe);
    friend ifstream& operator >> (ifstream& file, Pipe& pipe);
};




