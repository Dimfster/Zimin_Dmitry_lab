#pragma once

#include <iostream>
#include "Utilites.h"

using namespace std;


struct Compressor_station {
    string name;
    int number_of_workshops;
    int active_workshops;
    string type;

    Compressor_station();
    Compressor_station(string name, int number_of_workshops, int active_workshops, string type);

    void WhiteInfo();

    void ShowInfo();

    void Edit();

    void SaveInfo(ofstream& file);

};

