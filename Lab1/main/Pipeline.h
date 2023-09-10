#pragma once

#include <iostream>
#include <vector>
#include "Utilites.h"


using namespace std;

struct Pipeline {
    string name;
    float length;
    int diameter;
    bool in_repair;

    Pipeline();

    void ShowInfo();

    void Edit();
};
