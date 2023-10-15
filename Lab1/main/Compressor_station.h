#pragma once

#include "Utilites.h"


using namespace std;


class Compressor_station {
    int number_of_workshops;
    int efficianty;
    
public:
    int ID;
    static int MaxId;

    string name;
    int active_workshops;

    Compressor_station();
    Compressor_station(string name, int number_of_workshops, int active_workshops, int efficianty);

    void WriteInfo();

    void ShowInfo();

    void Edit();

    void Edit(int active);

    friend ofstream& operator << (ofstream& out, const Compressor_station& CS);
    friend ifstream& operator >> (ifstream& file, Compressor_station& CS);
};

