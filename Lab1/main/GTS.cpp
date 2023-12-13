#include <filesystem>

#include "Utilites.h"
#include "GTS.h"

#define MIN_ID_PIPE  1
#define MIN_ID_STATION 1001

using namespace std;


//---------------Реализация фильтра-------------------

template <typename T1, typename T2>
using Filter = bool(*)(T1& element, T2 parametr);

template <typename T>
bool CheckByName(T& element, string name) {
    return (element.name.find(name) != string::npos);
}

bool CheckByStatus(Pipe& pipe, bool in_work) {
    return pipe.in_work == in_work;
}

bool CheckByDiameter(Pipe& pipe, int diameter) {
    return pipe.GetDiameter() == diameter;
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


//---------------Утилиты-------------------

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

int GTS::InputExistIdStation() {
    int id;
    do {
        id = GetCorrectNumber(MIN_ID_STATION, Station::GetMaxId());
        if (!stations.contains(id)) { cout << "Нет такой станции!" << endl; }
    } while (!stations.contains(id));
    return id;
}

unordered_set<int> GTS::GetIDs(const ObjectType obj)
{
    switch (obj) {
    case PIPE: { return GetKeys(pipes); }
    case STATION: { return GetKeys(stations); }
    default: { return unordered_set<int>{}; }
    }
}
    
unordered_set<int> GTS::GetEditNumbers(unordered_set<int>& result, const GTS::ObjectType obj)
{
    unordered_set<int> IDs;
    int id;
    int Max_ID;
    switch (obj) {
    case GTS::PIPE: { Max_ID = Pipe::GetMaxId(); break; }
    case GTS::STATION: { Max_ID = Station::GetMaxId(); break; }
    }
    id = GetCorrectNumber(0, Max_ID);
    if (id == 0) { return result; }
    else { IDs.insert(id); }
    do {
        id = GetCorrectNumber(0, Max_ID);
        if (result.contains(id)) {
            IDs.insert(id);
        }
    } while (id != 0);

    return IDs;
}

unordered_set<int> GTS::GetFreePipes(const unordered_set<int>& IDs){
    unordered_set<int> free_IDs;
    for (auto& id : IDs) {
        if (!connections.edges.contains(id)) {
            free_IDs.insert(id);
        }
    }
    return free_IDs;
}


//---------------Создание объектов-------------------
void GTS::CreatePipe(){
    Pipe pipe;
    pipe.WriteInfo();
    pipes.insert({ pipe.GetID(), pipe});
}

void GTS::CreateStateDiameterPipe(Pipe& pipe, int diameter){
    pipe.WriteInfo_WithStateDiameter(diameter);
    pipes.insert({ pipe.GetID(), pipe });
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

void GTS::ViewObjects(unordered_set<int> result, const GTS::ObjectType obj)
{
    switch (obj) {
    case PIPE: { for (int id : result) { pipes.at(id).ShowInfo(); }; return; }
    case STATION: { for (int id : result) { stations.at(id).ShowInfo(); }; return; }
    default: { return; }
    }
}


//---------------Редактирование-------------------
void GTS::EditPipes(unordered_set<int>& IDs)
{
    ENTER;
    ViewObjects(IDs, PIPE);
    cout << "Изменить состояние труб(ы)?(0 - в ремонт, 1 - в рабочее состояние, 2 - изменить на противоположное)" << endl;
    switch (GetCorrectNumber(0, 2))
    {
        case 0: { for (int id : IDs) { pipes.at(id).Edit(Pipe::SET_REPAIR);}      break; }
        case 1: { for (int id : IDs) { pipes.at(id).Edit(Pipe::SET_WORK);}        break; }
        case 2: { for (int id : IDs) { pipes.at(id).Edit(Pipe::SET_OPPOSITE);  }  break; }
        default: { return; }
    }
    cout << endl << "Состояние изменено!" << endl;
}

void GTS::EditStations(unordered_set<int>& IDs)
{
    ENTER;
    ViewObjects(IDs, STATION);
    cout << "Изменить кол-во активных цехов станции(й) на(0-10): " << endl;
    int ans = GetCorrectNumber(0, 10);
    for (int id : IDs) { stations.at(id).Edit(ans); }
    cout << endl << "Состояние изменено!" << endl;
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
            ViewObjects(result, PIPE);
            cout << "Изменить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, PIPE);
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
            ViewObjects(result, STATION);
            cout << "Изменить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, STATION);
            EditStations(numbers);
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
            ViewObjects(result, PIPE);
            cout << "Изменить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, PIPE);
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
            ViewObjects(result, STATION);
            cout << "Изменить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, STATION);
            EditStations(numbers);
        }
        else cout << "Нет подходящих станций";
        break;
    }
    default: { return; }
    }
}

//---------------Удаление-------------------
void GTS::DeletePipes(unordered_set<int>& IDs) { 

    for (auto& pipe_id : IDs) {
        connections.DeleteConnection_ByPipeID(pipe_id);
        pipes.erase(pipe_id);
    }
    cout << endl << "Трубы удалены!" << endl;
}
void GTS::DeleteStations(unordered_set<int>& IDs) { 
    for (auto& station_id : IDs) {
        connections.DeleteConnection_ByStationID(station_id);
        stations.erase(station_id);
    }
    cout << endl << "Станции удалены!" << endl;
}

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
            ViewObjects(result, PIPE);
            cout << "Удалить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, PIPE);
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
            ViewObjects(result, STATION);
            cout << "Удалить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, STATION);
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
            ViewObjects(result, PIPE);
            cout << "Удалить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, PIPE);
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
            ViewObjects(result, STATION);
            cout << "Удалить все(0) или введите нужные ID(введите нужные ID по одному, для окончания выбора введите 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, STATION);
            DeleteStations(numbers);
        }
        else cout << "Нет подходящих станций";
        break;
    }
    default: { return; }
    }
}

//---------------Граф-------------------
void GTS::ViewСonnections() { 
    ENTER;
    connections.ViewConnections();
}

void GTS::CreateСonnection() {
    if (stations.size() < 2) { cout << "Недостаточно станций для создания связи!" << endl; return; }
    ViewStations();
    cout << "Введите ID начальной станции" << endl;
    int from, to, id;
    from = InputExistIdStation();
    cout << "Введите ID конечной станции" << endl;
    to = InputExistIdStation();

    if (connections.UncorrectNodes(from,  to)) { return; }

    cout << "Введите диаметр трубы, которой вы хотите соединить станции:" << endl;
    vector<int> sizes = Pipe::GetSizes();
    int diameter = SwitchNumber(sizes);
    unordered_set<int> result = Find_By_Filter<Pipe, int>(pipes, CheckByDiameter, diameter);
    result = GetFreePipes(result);

    if (!result.size()) {
        cout << "Труб с указанным диаметром не найдено. Хотите создать такую трубу?(0 - нет(выйти), 1 - да)" << endl;
        if (!GetCorrectNumber(0, 1)) { return; }
        else {
            Pipe pipe;
            CreateStateDiameterPipe(pipe,diameter);
            id = pipe.GetID();
            connections.CreateConnection(from, to, id);
            return;
        }
    }

    ViewObjects(result, PIPE);
    cout << "Выберете ID трубы для связи:";
    do {
        id = GetCorrectNumber(MIN_ID_PIPE, Pipe::GetMaxId());
        if (!result.contains(id)) { cout << "Нет такого ID среди найденных труб! Введите ещё раз." << endl; }
    } while (!result.contains(id));

    connections.CreateConnection(from, to, id);
    return;
}

void GTS::DeleteСonnection() {
    if (connections.Empty()) {
        cout << "Нет доступных связей!";
        return;
    }

    connections.ViewConnections();
    cout << "Введите ID удаляемой связи:" << endl;
    int id;
    do {
        id = GetCorrectNumber(MIN_ID_PIPE, Pipe::GetMaxId());
        if (!connections.edges.contains(id)) { cout << "Нет такого ID среди найденных труб! Введите ещё раз." << endl; }
    } while (!connections.edges.contains(id));
    connections.DeleteConnection_ByPipeID(id);
}


void GTS::TopologicalSort() {
    if (connections.Empty()) { cout << "Нет доступных связей!"; return; }
    Graph graph = Graph(connections.edges, connections.nodes, pipes);
    vector<int> result = graph.TopologicalSort();
    if (!result.size()) { cout << "Топологическая сортировка: - "; return; }
    cout << "Топологическая сортировка: ";
    for (auto& i : result) {
        cout << i << " ";
    }
}

void GTS::ShortestPath() {
    if (connections.Empty()) { cout << "Нет доступных связей!"; return; }
    Graph graph = Graph(connections.edges, connections.nodes, pipes);

    connections.ViewConnections();
    cout << "Введите начальную вершину пути:" << endl;
    int StartNode = GetCorrectNumber(MIN_ID_STATION, Station::GetMaxId());

    cout << "Введите конечную вершину пути:" << endl;
    int EndNode = GetCorrectNumber(MIN_ID_STATION, Station::GetMaxId());

    vector<int> result = graph.Metod_Deikstra(StartNode, EndNode);
    if (!result.size()) { cout << "Путь: - "; return; }
    cout << "Путь: ";
    for (auto& i : result) {
        cout << i << " -> ";
    }
    cout << "end" << endl;
    cout << "Длина пути: " << graph.Lenght_ShortestPath(result) << endl;
}

void GTS::MaxFlow() {
    if (connections.Empty()) { cout << "Нет доступных связей!"; return; }
    Graph graph = Graph(connections.edges, connections.nodes, pipes);

    connections.ViewConnections();
    cout << "Введите начальную вершину пути:" << endl;
    int StartNode = GetCorrectNumber(MIN_ID_STATION, Station::GetMaxId());

    cout << "Введите конечную вершину пути:" << endl;
    int EndNode = GetCorrectNumber(MIN_ID_STATION, Station::GetMaxId());

    double result = graph.Ford_Fulkerson(StartNode, EndNode);
    cout << "Максимальный поток: " << result << endl;
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
        file << pipes.size() << " " << stations.size() << " " << connections.edges.size() << endl;
        for (auto& pipe : pipes) { file << pipe.second; }
        for (auto& station : stations) { file << station.second; };
        file << connections;
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
        cout << count << ". " << name.path().filename() << endl;
    }

    ENTER;
    cout << "Выберете номер сохранения" << endl;
    int save = GetCorrectNumber(1, count);

    pipes.clear();
    stations.clear();
    connections.Clear();
    Pipe pipe;
    Station station;
    Edge edge;
    int count_pipes, count_cs, count_connectios;

    file.open(names[save-1]);
    file >> count_pipes >> count_cs >> count_connectios;

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
    while (count_connectios--)
    {
        file >> edge;
        connections.Insert(edge);
    }

    cout << "Файлы загружены!\n" << endl;
    file.close();
}
