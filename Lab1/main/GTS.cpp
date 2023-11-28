#include <filesystem>

#include "Utilites.h"
#include "GTS.h"





using namespace std;


//---------------Реализация фильтра-------------------

template <typename T1, typename T2>
using Filter = bool(*)(T1& element, T2 parametr);

template <typename T>
bool CheckByName(T& element, string name) {
    return (element.name.find(name) != string::npos);
}

bool CheckByStatus(Pipe& pipe, bool in_repair) {
    return pipe.in_repair == in_repair;
}

bool CheckByWorkshop(Station& station, int cent_non_active) {
    return station.GetUnactiveWorkshop() >= cent_non_active;
}

template <typename Element, typename Parametr>
unordered_set<int> Find_By_Filter(unordered_map<int, Element>& elements, Filter<Element, Parametr> filter, Parametr parametr)
{
    unordered_set<int> result;
    for (auto& element : elements)
    {
        if (filter(element.second, parametr))
            result.insert(element.second.GetID());
    }
    return result;
}


GTS::GTS(){}

bool GTS::HasObject(const ObjectType obj)
{
    switch (obj)
    {
    case PIPE: {
        if (pipes.size()) { return true; }
        else { return false; }
    }
    case STATION: {
        if (stations.size()) { return true; }
        else { return false; }
    }
    default: {return false;}
    }
}

std::unordered_set<int> GTS::GetIDs(const ObjectType obj)
{
    switch (obj) {
    case PIPE: { return GetKeys(pipes); }
    case STATION: { return GetKeys(stations); }
    default: { return unordered_set<int>{}; }
    }
}
    
unordered_set<int> GetEditNumbers(unordered_set<int>& result)
{
    unordered_set<int> IDs;
    int id;
    int Max_ID = Pipe::GetMaxId();
    if (!GetCorrectNumber(0, Max_ID)) { return result; }
    do {
        id = GetCorrectNumber(0, Max_ID);
        if (result.contains(id)) {
            IDs.insert(id);
        }
    } while (id != 0);

    return IDs;
}

//---------------Создание объектов-------------------
void GTS::CreatePipe()
{
    Pipe pipe;
    pipe.WriteInfo();
    pipes.insert({ pipe.GetID(), pipe});
}

void GTS::CreateCS()
{
    Station station;
    station.WriteInfo();
    stations.insert({ station.GetID(), station });
}


//---------------Показ объектов-------------------
void GTS::ViewPipes()
{
    int i = 1;
    for (auto& element : pipes) {
        std::cout << i << ". ";
        i++;
        element.second.ShowInfo();
    }
}

void GTS::ViewStations()
{
    int i = 1;
    for (auto& element : stations) {
        std::cout << i << ". ";
        i++;
        element.second.ShowInfo();
    }
}

//---------------Редактирование-------------------
void GTS::EditPipes(unordered_set<int>& IDs)
{
    ENTER;
    for (int id : IDs) { pipes.at(id).ShowInfo(); }

    cout << "Изменить состояние труб(ы)?(0 - в ремонт, 1 - в рабочее состояние, 2 - изменить на противоположное)" << endl;
    switch (GetCorrectNumber(0, 2))
    {
        case 0: { for (int id : IDs) { pipes.at(id).Edit(Pipe::SET_REPAIR);}      return; }
        case 1: { for (int id : IDs) { pipes.at(id).Edit(Pipe::SET_WORK);}        return; }
        case 2: { for (int id : IDs) { pipes.at(id).Edit(Pipe::SET_OPPOSITE);  }  return; }
        default: { return; }
    }
}

void GTS::EditCS(unordered_set<int>& IDs)
{
    ENTER;
    for (int id : IDs) { stations.at(id).ShowInfo(); }
    cout << "Изменить кол-во активных цехов станции(й) на(0-10): " << endl;
    int ans = GetCorrectNumber(0, 10);
    for (int id : IDs) { stations.at(id).Edit(ans); return; }
}

void GTS::Edit_ByName(const ObjectType obj)
{
    switch (obj) {
    case PIPE: {
        ENTER;
        cout << "Введите имя трубы:" << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Pipe, string>(pipes, CheckByName, name);
        if (result.size())
        {
            for (int id : result) { pipes.at(id).ShowInfo(); }
            cout << "Изменить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result);
            EditPipes(numbers);
        }
        else cout << "Нет подходящих труб";
        break;
    }
    case STATION: {
        ENTER;
        cout << "Введите имя станции:" << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Station, string>(stations, CheckByName, name);
        if (result.size())
        {
            for (int id : result) { stations.at(id).ShowInfo(); }
            cout << "Изменить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result);
            EditCS(numbers);
        }
        else cout << "Нет подходящих станций";
        break;
    }
    default: { return; }
    }

}

void GTS::Edit_ByParametr(const ObjectType obj){
    switch (obj) {
    case PIPE: {
        ENTER;
        cout << "Введите состояние трубы:(0 - в ремонте, 1 - работает)" << endl;
        unordered_set<int> result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, GetCorrectNumber(0, 1));
        if (result.size())
        {
            for (int id : result) { pipes.at(id).ShowInfo(); }
            cout << "Изменить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result);
            EditPipes(numbers);
        }
        else cout << "Нет подходящих труб";
        break;
    }
    case STATION: {
        ENTER;
        cout << "Введите процент неактивых цехов станции:" << endl;
        unordered_set<int> result = Find_By_Filter<Station, int>(stations, CheckByWorkshop, GetCorrectNumber(0, 100));
        if (result.size())
        {
            for (int id : result) { stations.at(id).ShowInfo(); }
            cout << "Изменить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result);
            EditCS(numbers);
        }
        else cout << "Нет подходящих станций";
        break;
    }
    default: { return; }
    }
}

//---------------Удаление-------------------
void GTS::DeletePipes(unordered_set<int>& IDs) { for (auto& id : IDs) pipes.erase(id); }
void GTS::DeleteStations(unordered_set<int>& IDs) { for (auto& id : IDs) stations.erase(id); }

void GTS::Delete_ByName(const ObjectType obj)
{
    switch (obj) {
    case PIPE: {
        ENTER;
        cout << "Введите имя трубы:" << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Pipe, string>(pipes, CheckByName, name);
        if (result.size())
        {
            for (int id : result) { pipes.at(id).ShowInfo(); }
            cout << "Изменить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result);
            DeletePipes(numbers);
        }
        else cout << "Нет подходящих труб";
        break;
    }
    case STATION: {
        ENTER;
        cout << "Введите имя станции:" << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Station, string>(stations, CheckByName, name);
        if (result.size())
        {
            for (int id : result) { stations.at(id).ShowInfo(); }
            cout << "Изменить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result);
            DeleteStations(numbers);
        }
        else cout << "Нет подходящих станций";
        break;
    }
    default: { return; }
    }

}

void GTS::Delete_ByParametr(const ObjectType obj) {
    switch (obj) {
    case PIPE: {
        ENTER;
        cout << "Введите состояние трубы:(0 - в ремонте, 1 - работает)" << endl;
        unordered_set<int> result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, GetCorrectNumber(0, 1));
        if (result.size())
        {
            for (int id : result) { pipes.at(id).ShowInfo(); }
            cout << "Изменить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result);
            DeletePipes(numbers);
        }
        else cout << "Нет подходящих труб";
        break;
    }
    case STATION: {
        ENTER;
        cout << "Введите процент неактивых цехов станции:" << endl;
        unordered_set<int> result = Find_By_Filter<Station, int>(stations, CheckByWorkshop, GetCorrectNumber(0, 100));
        if (result.size())
        {
            for (int id : result) { stations.at(id).ShowInfo(); }
            cout << "Изменить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result);
            DeleteStations(numbers);
        }
        else cout << "Нет подходящих станций";
        break;
    }
    default: { return; }
    }
}

//---------------Сохранение-Загрузка-------------------
void GTS::SaveConfiguration() 
{
    if (HasObject(PIPE) or HasObject(STATION)){
        cout << "Введите название сохранения:" << endl;
        string name = input_string();
        name = "Saves/" + name + ".txt";

        ofstream file;
        file.open(name, ios::out);
        file << pipes.size() << " " << stations.size() << endl;
        for (auto& pipe : pipes) { file << pipe.second; }
        for (auto& station : stations) { file << station.second; };
        file.close();
        ENTER;
        cout << "Успешно сохранено!" << endl;
    }
    else { ENTER; cout << "Сохранение не может быть пустым, запишите данные!" << endl; }
}

void GTS::LoadConfiguration() {
    ENTER;
    ifstream file;
    std::string path = "Saves\\";
    vector<std::filesystem::directory_entry> names;
    int count = 0;
    for (auto& name: filesystem::directory_iterator(path)) {
        count++;
        names.push_back(name);
        cout << count << ". " << name << endl;
    }

    ENTER;
    cout << "Выберете номер сохранения" << endl;
    int save = GetCorrectNumber(1, count);

    pipes.clear();
    stations.clear();
    Pipe pipe;
    Station station;
    int count_pipes;
    int count_cs;

    file.open(names[save-1]);
    file >> count_pipes >> count_cs;

    while(count_pipes--)
    {
        file >> pipe;
        pipes.insert({ pipe.GetID(), pipe });
    }
    while (count_cs--)
    {
        file >> station;
        stations.insert({ station.GetID(), station });
    }

    cout << "Файлы загружены!\n" << endl;
    file.close();


}
