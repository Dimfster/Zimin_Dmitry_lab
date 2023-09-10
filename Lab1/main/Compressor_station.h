#pragma once

#include <iostream>
#include <vector>
#include "Utilites.h"

using namespace std;


struct Compressor_station {
    string name;
    int number_of_workshops;
    int active_workshops;
    string type;

    Compressor_station();

    void ShowInfo();

    void Edit();
};

