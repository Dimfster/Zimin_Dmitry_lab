#pragma once

#include "Utilites.h"
#include "Pipe.h"
#include "Compressor_station.h"


class GTS
{

    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, Compressor_station> stations;


public:
    
    GTS();
    //---------------Создание объектов-------------------
    void CreatePipe();
    void CreateCS();

    //---------------Показ объектов-------------------
    void View();

    template <typename Struct>
    void ViewComponents(std::unordered_map<int, Struct>& conteiner)
    {
        int i = 1;
        for (auto& element : conteiner) {
            std::cout << i << ". ";
            i++;
            element.second.ShowInfo();
        }
    }

    template <typename Struct>
    void ViewComponentsByID(std::vector<int> IDs, std::unordered_map<int, Struct>& conteiner)
    {
        int i = 1;
        for (auto& id : IDs) {
            std::cout << i << ". ";
            i++;
            conteiner.at(id).ShowInfo();
        }
    }


    //---------------Поиск объектов-------------------
    void Search();
    void SearchPipes();
    void SearchCS();

    //---------------Редактирование-------------------
    void Edit();

    void EditPipes();
    void EditCS();

    void EditOnePipe();
    void EditOneCS();
    void EditSomePipes();
    void EditSomeCS();

    template <typename Struct>
    void EditOne(std::unordered_map<int, Struct>& struct_one)
    {
        std::map<int, int> new_map = Create_Console_Map(struct_one);
        int number = GetCorrectNumber(1, struct_one.size());
        struct_one[new_map[number]].Edit();
    }

    template <typename Struct>
    void EditSome(std::unordered_map<int, Struct>& struct_one)
    {
        std::map<int, int> new_map = Create_Console_Map(struct_one);
        int number = GetCorrectNumber(1, struct_one.size());
        struct_one[new_map[number]].Edit();
    }


    //---------------Сохранение-Загрузка-------------------
    void SaveConfiguration();
    void LoadConfiguration();

};