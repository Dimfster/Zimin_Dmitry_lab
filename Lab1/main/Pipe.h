#pragma once
#include "Utilites.h"

class Pipe 
{
    float length;
    int diameter;
    int ID;
    static int MaxId;
    static std::vector<int> possible_diameters;
    
public:

    std::string name;
    bool in_repair;
    enum Action {SET_WORK, SET_REPAIR, SET_OPPOSITE};

    Pipe();
    Pipe(const std::string name, const float length, const int diameter, const bool in_repair);

    void WriteInfo();

    void WriteInfo_WithStateDiameter(int diameter);

    void ShowInfo();

    void Edit(const Action);

    static inline std::vector<int> GetSizes() { return possible_diameters; };
    int GetDiameter() { return diameter; };
    static int GetMaxId() { return MaxId; };
    int GetID() { return ID; };

    friend std::ofstream& operator << (std::ofstream& file, const Pipe& pipe);
    friend std::ifstream& operator >> (std::ifstream& file, Pipe& pipe);
};