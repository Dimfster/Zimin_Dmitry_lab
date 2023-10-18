#pragma once

#include "Console_Function.h"


// Ожидание ввода клавиши
void Wait() {
    while (true)
    {
        if (_kbhit()) break;
    }
}


// Показывает все компоненты вектора
template <typename T>
void ViewComponents(unordered_map<int, T>& conteiner)
{
    int i = 1;
    for (auto& element : conteiner){
        cout << i << ". ";
        i++;
        element.second.ShowInfo();
    }
        
}

template <typename T>
map<int, int> Create_Console_Map(const unordered_map<int, T>& conteiner)
{
    map<int, int> new_map;
    int i = 0;
    for (auto& element : conteiner) {
        i++;
        new_map.insert({ i,element.first });
    }
    return new_map;
}


template <typename T1, typename T2>
using Filter = bool(*)(T1& element, T2 parametr);

template <typename T>
bool CheckByName(T& element, string name) {
    return (element.name.find(name) != string::npos);
}

bool CheckByStatus(Pipe& pipe, bool in_repair) {
    return pipe.in_repair == in_repair;
}

bool CheckByActive(Compressor_station& station, int active_workshops) {
    return station.active_workshops == active_workshops;
}

template <typename T1, typename T2>
vector<int> Find_By_Filter(unordered_map<int, T1>& elements, Filter<T1, T2> filter, T2 parametr)
{
    vector<int> result;
    for (auto& element : elements)
    {
        if (filter(element.second, parametr)) result.push_back(element.second.ID);
    }
    return result;
}


// Показывает меню просмотра труб и станций
void View(unordered_map<int, Pipe>& pipes, unordered_map<int, Compressor_station>& stations)
{

    while (1) {
        ENTER;
        cout << "0. Назад\n" <<
            "1. Список труб\n" <<
            "2. Список КС\n" << 
            "3. Показать всё" << endl;


        switch (GetCorrectNumber(0, 3)) {
        case 1: {
            ENTER;
            cout << "----------Трубы-----------" << endl;
            ViewComponents<Pipe>(pipes);
            cout << "Нажмите любую клавишу" << endl;
            Wait();
            break;
        }
        case 2: {
            ENTER;
            cout << "----------Станции-----------" << endl;
            ViewComponents<Compressor_station>(stations);
            cout << "Нажмите любую клавишу" << endl;
            Wait();
            break;
        }

        case 3: {
            ENTER;
            cout << "----------Трубы-----------" << endl;
            ViewComponents<Pipe>(pipes);
            ENTER;
            cout << "----------Станции-----------" << endl;
            ViewComponents<Compressor_station>(stations);
            ENTER;
            cout << "Нажмите любую клавишу" << endl;
            Wait();
            break;
        }

        case 0: {
            return;
        }

        }
    }
}



// Меню выбора редактируемой трубы 
void EditPipeline(unordered_map<int, Pipe>& pipes)
{
    if (!pipes.size())
    {
        cout << "Нет доступных труб!\n" <<
            "Нажмите любую клавишу" << endl;
        Wait();
        return;
    }

    cout << "1. Редактировать одну трубу по выбору\n"
        << "2. Редактировать по фильтру\n"
        << "0. Выход" << endl;
    

    switch (GetCorrectNumber(0, 2))
    {
        case 1:
        {
            ENTER;
            cout << "Список труб:\n";
            ViewComponents(pipes);
            cout << "Выберете редактируемую трубу:";

            map<int, int> new_map = Create_Console_Map(pipes);
            int number = GetCorrectNumber(1, pipes.size());
            pipes[new_map[number]].Edit();   
            break;
        }
        case 2:
        {
            ENTER;
            vector<int> result;
            cout << "Введите состояние трубы:" << endl;
            result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, GetCorrectNumber(0, 1));
            if (result.size())
            {
                for (auto& id : result) pipes.at(id).ShowInfo();
                cout << "На какое состояние изменить?(0 - в ремонт, 1 - в рабочее состояние)" << endl;
                int answer = GetCorrectNumber(0, 1);
                for (auto& id : result) pipes.at(id).Edit(answer);
                cout << endl << "Состояние труб изменено!";
            }
            else cout << "Нет подходящих труб";

            break;
        }
        case 0:
        {
            return;
        }
    }

}



// Меню выбора редактируемой КС
void EditCopressorStation(unordered_map<int, Compressor_station>& stations) {
    if (!stations.size()) {
        cout << "Нет доступных КС!\n" <<
            "Нажмите любую клавишу" << endl;
        Wait();
        return;
    }

    cout << "1. Редактировать одну станцию по выбору\n"
        << "2. Редактировать по фильтру\n"
        << "0. Выход" << endl;


    switch (GetCorrectNumber(0, 2))
    {
        case 1:
        {
            ENTER;
            cout << "Список станций:\n";
            ViewComponents(stations);
            cout << "Выберете редактируемую станцию:";

            map<int, int> new_map = Create_Console_Map(stations);
            int number = GetCorrectNumber(1, stations.size());
            stations[new_map[number]].Edit();
            break;
        }
        case 2:
        {
            ENTER;
            vector<int> result;
            cout << "Введите кол-во активных цехов:" << endl;
            result = Find_By_Filter<Compressor_station, int>(stations, CheckByActive, GetCorrectNumber(0, 10));
            if (result.size())
            {
                for (auto& id : result) stations.at(id).ShowInfo();
                cout << "Изменить кол-во активных цехов на:" << endl;
                int answer = GetCorrectNumber(0, 10);
                for (auto& id : result) stations.at(id).Edit(answer);
                cout << endl << "Состояние станций изменено!";
            }
            else cout << "Нет подходящих станций";
            break;
        }
        case 0:
        {
            return;
        }
    }
}


// Сохрание конфигурации
void SaveConfiguration(const unordered_map<int, Pipe>& pipes, const unordered_map<int, Compressor_station>& stations) {
    if (pipes.size() and stations.size()) {
        cout << "Введите название сохранения:" << endl;
        string name;
        cin.ignore(10000, '\n');
        getline(cin, name);
        name = "Saves/" + name + ".txt";

        ofstream file;
        file.open(name, ios::out);
        file << pipes.size() << " " << stations.size() << endl;
        for (auto& pipe : pipes) file << pipe.second;
        for (auto& station: stations) file << station.second;
        file.close();

        ENTER;
        cout << "Успешно сохранено!\nНажмите любую клавишу" << endl;
        Wait();
    }
    
    else ENTER; cout << "Сохранение не может быть пустым, запишите данные!" << endl;

}


// Загрузка конфигурации
void LoadConfiguration(unordered_map<int, Pipe>& pipes, unordered_map<int, Compressor_station>& stations) {
    ENTER;
    ifstream file;
    std::string path = "Saves\\";
    int count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        cout << count << ". " << name << endl;
    }
    ENTER;
    cout << "Выберете номер сохранения" << endl;
    int save = GetCorrectNumber(1, count);
    
    count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        if (count == save) {
            pipes.clear();
            stations.clear();

            file.open(name);

            int count_pipes;
            int count_cs;
            file >> count_pipes;
            file >> count_cs;

            Pipe pipe;
            for (count_pipes; count_pipes > 0; count_pipes--){
                file >> pipe;
                pipes.insert({pipe.ID, pipe});
            }

            Compressor_station station;
            for (count_cs; count_cs > 0; count_cs--) {
                file >> station;
                stations.insert({station.ID, station});
            }

            cout << "Файлы загружены!\n" << "Нажмите любую клавишу" << endl;
            Wait();
            break;
        }
    }
}



void SearchPipes(unordered_map<int, Pipe>& pipes) 
{
    if (pipes.size())
    {
        cout << "Выберете фильтр поиска:\n1. По имени\n2. По состоянию" << endl;
        vector<int> result;

        switch (GetCorrectNumber(1, 2))
        {
            case 1:
            {
                cout << "Введите имя трубы:" << endl;
                string name;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                getline(cin, name);

                result = Find_By_Filter<Pipe, string>(pipes, CheckByName, name);
                break;
            }
            case 2:
            {
                cout << "Введите состояние трубы:" << endl;
                result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, GetCorrectNumber(0, 1));
                break;
            }
        }

        if (result.size())
        {
            for (auto& id : result) pipes.at(id).ShowInfo();
        }
        else cout << "Нет подходящих труб";
    }
    else cout << "Нет доступных труб!";

    
}


void SearchCS(unordered_map<int, Compressor_station>& stations)
{
    if (stations.size())
    {
        cout << "Выберете фильтр поиска:\n1. По имени\n2. По активным цехам" << endl;
        vector<int> result;

        switch (GetCorrectNumber(1, 2))
        {
        case 1:
        {
            cout << "Введите имя станции:" << endl;
            string name;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            getline(cin, name);

            result = Find_By_Filter<Compressor_station, string>(stations, CheckByName, name);
            break;
        }
        case 2:
        {
            cout << "Введите кол-во активных станций:" << endl;
            result = Find_By_Filter<Compressor_station, int>(stations, CheckByActive, GetCorrectNumber(0, 10));
            break;
        }
        }

        if (result.size())
        {
            for (auto& id : result) stations[id].ShowInfo();
        }
        else cout << "Нет подходящих станций";
    }
    else cout << "Нет доступных станций!";

}
