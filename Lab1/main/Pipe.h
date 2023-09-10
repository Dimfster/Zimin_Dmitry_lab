#pragma once

#include "Utilites.h"


using namespace std;

struct Pipe {
    string name;
    float length;
    int diameter;
    bool in_repair;

    Pipe();

    void WhiteInfo();

    void ShowInfo();

    void Edit();

};




