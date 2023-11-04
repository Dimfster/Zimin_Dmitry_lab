#pragma once

#include "Utilites.h"


class Compressor_station {
    int number_of_workshops;
    int efficianty;
    int ID;
    inline static int MaxId = 1000;
    
public:

    std::string name;
    int active_workshops;

    Compressor_station();
    Compressor_station(std::string name, int number_of_workshops, int active_workshops, int efficianty);

    void WriteInfo();

    void ShowInfo();

    void Edit();

    void Edit(int active);

    void SetMaxId(int MaxId) { this->MaxId = MaxId; };
    int GetMaxId() { return MaxId; };

    int GetID() { return ID; };

    friend std::ofstream& operator << (std::ofstream& out, const Compressor_station& CS);
    friend std::ifstream& operator >> (std::ifstream& file, Compressor_station& CS);
};