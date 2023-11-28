#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"


class GTS
{
public:
    enum ObjectType { PIPE, STATION };
    bool HasObject(const ObjectType obj);

    std::unordered_set<int> GetIDs (const ObjectType obj);

    GTS();
    //---------------�������� ��������----------------
    void CreatePipe();
    void CreateCS();

    //---------------����� ��������-------------------
    void ViewPipes();
    void ViewStations();

    //---------------��������������-------------------
    void EditPipes(std::unordered_set<int>& IDs);
    void EditCS(std::unordered_set<int>& IDs);

    void Edit_ByName(const ObjectType obj);

    void Edit_ByParametr(const ObjectType obj);
    //---------------��������-------------------
    void DeletePipes(std::unordered_set<int>& IDs);
    void DeleteStations(std::unordered_set<int>& IDs);


    void DeletePipes(std::vector<int>& ids);
    void DeleteStations(std::vector<int>& ids);

    void Delete_ByName(const ObjectType obj);

    void Delete_ByParametr(const ObjectType obj);

    //---------------����������-��������-------------------
    void SaveConfiguration();
    void LoadConfiguration();


private:
    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, Station> stations;
};