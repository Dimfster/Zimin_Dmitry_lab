#include <filesystem>

#include "Utilites.h"
#include "GTS.h"

#define MIN_ID_PIPE  1
#define MIN_ID_STATION 1001

using namespace std;


//---------------���������� �������-------------------

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


//---------------�������-------------------

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
        if (!stations.contains(id)) { cout << "��� ����� �������!" << endl; }
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


//---------------�������� ��������-------------------
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


//---------------����� ��������-------------------
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


//---------------��������������-------------------
void GTS::EditPipes(unordered_set<int>& IDs)
{
    ENTER;
    ViewObjects(IDs, PIPE);
    cout << "�������� ��������� ����(�)?(0 - � ������, 1 - � ������� ���������, 2 - �������� �� ���������������)" << endl;
    switch (GetCorrectNumber(0, 2))
    {
        case 0: { for (int id : IDs) { pipes.at(id).Edit(Pipe::SET_REPAIR);}      break; }
        case 1: { for (int id : IDs) { pipes.at(id).Edit(Pipe::SET_WORK);}        break; }
        case 2: { for (int id : IDs) { pipes.at(id).Edit(Pipe::SET_OPPOSITE);  }  break; }
        default: { return; }
    }
    cout << endl << "��������� ��������!" << endl;
}

void GTS::EditStations(unordered_set<int>& IDs)
{
    ENTER;
    ViewObjects(IDs, STATION);
    cout << "�������� ���-�� �������� ����� �������(�) ��(0-10): " << endl;
    int ans = GetCorrectNumber(0, 10);
    for (int id : IDs) { stations.at(id).Edit(ans); }
    cout << endl << "��������� ��������!" << endl;
}

void GTS::Edit_ByName(const ObjectType obj)
{
    switch (obj) {
    case PIPE: {
        ENTER;
        cout << "������� ��� �����:" << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Pipe, string>(pipes, CheckByName, name);
        if (result.size())
        {
            ViewObjects(result, PIPE);
            cout << "�������� ���(0) ��� ������� ������ ID(������� ������ ID �� ������, ��� ��������� ������ ������� 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, PIPE);
            EditPipes(numbers);
        }
        else cout << "��� ���������� ����";
        break;
    }
    case STATION: {
        ENTER;
        cout << "������� ��� �������:" << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Station, string>(stations, CheckByName, name);
        if (result.size())
        {
            ViewObjects(result, STATION);
            cout << "�������� ���(0) ��� ������� ������ ID(������� ������ ID �� ������, ��� ��������� ������ ������� 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, STATION);
            EditStations(numbers);
        }
        else cout << "��� ���������� �������";
        break;
    }
    default: { return; }
    }

}

void GTS::Edit_ByParametr(const ObjectType obj){
    switch (obj) {
    case PIPE: {
        ENTER;
        cout << "������� ��������� �����:(0 - � �������, 1 - ��������)" << endl;
        unordered_set<int> result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, GetCorrectNumber(0, 1));
        if (result.size())
        {
            ViewObjects(result, PIPE);
            cout << "�������� ���(0) ��� ������� ������ ID(������� ������ ID �� ������, ��� ��������� ������ ������� 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, PIPE);
            EditPipes(numbers);
        }
        else cout << "��� ���������� ����";
        break;
    }
    case STATION: {
        ENTER;
        cout << "������� ������� ��������� ����� �������:" << endl;
        unordered_set<int> result = Find_By_Filter<Station, int>(stations, CheckByWorkshop, GetCorrectNumber(0, 100));
        if (result.size())
        {
            ViewObjects(result, STATION);
            cout << "�������� ���(0) ��� ������� ������ ID(������� ������ ID �� ������, ��� ��������� ������ ������� 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, STATION);
            EditStations(numbers);
        }
        else cout << "��� ���������� �������";
        break;
    }
    default: { return; }
    }
}

//---------------��������-------------------
void GTS::DeletePipes(unordered_set<int>& IDs) { 

    for (auto& pipe_id : IDs) {
        connections.DeleteConnection_ByPipeID(pipe_id);
        pipes.erase(pipe_id);
    }
    cout << endl << "����� �������!" << endl;
}
void GTS::DeleteStations(unordered_set<int>& IDs) { 
    for (auto& station_id : IDs) {
        connections.DeleteConnection_ByStationID(station_id);
        stations.erase(station_id);
    }
    cout << endl << "������� �������!" << endl;
}

void GTS::Delete_ByName(const ObjectType obj)
{
    switch (obj) {
    case PIPE: {
        ENTER;
        cout << "������� ��� �����:" << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Pipe, string>(pipes, CheckByName, name);
        if (result.size())
        {
            ViewObjects(result, PIPE);
            cout << "������� ���(0) ��� ������� ������ ID(������� ������ ID �� ������, ��� ��������� ������ ������� 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, PIPE);
            DeletePipes(numbers);
        }
        else cout << "��� ���������� ����";
        break;
    }
    case STATION: {
        ENTER;
        cout << "������� ��� �������:" << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Station, string>(stations, CheckByName, name);
        if (result.size())
        {
            ViewObjects(result, STATION);
            cout << "������� ���(0) ��� ������� ������ ID(������� ������ ID �� ������, ��� ��������� ������ ������� 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, STATION);
            DeleteStations(numbers);
        }
        else cout << "��� ���������� �������";
        break;
    }
    default: { return; }
    }

}

void GTS::Delete_ByParametr(const ObjectType obj) {
    switch (obj) {
    case PIPE: {
        ENTER;
        cout << "������� ��������� �����:(0 - � �������, 1 - ��������)" << endl;
        unordered_set<int> result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, GetCorrectNumber(0, 1));
        if (result.size())
        {
            ViewObjects(result, PIPE);
            cout << "������� ���(0) ��� ������� ������ ID(������� ������ ID �� ������, ��� ��������� ������ ������� 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, PIPE);
            DeletePipes(numbers);
        }
        else cout << "��� ���������� ����";
        break;
    }
    case STATION: {
        ENTER;
        cout << "������� ������� ��������� ����� �������:" << endl;
        unordered_set<int> result = Find_By_Filter<Station, int>(stations, CheckByWorkshop, GetCorrectNumber(0, 100));
        if (result.size())
        {
            ViewObjects(result, STATION);
            cout << "������� ���(0) ��� ������� ������ ID(������� ������ ID �� ������, ��� ��������� ������ ������� 0)" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, STATION);
            DeleteStations(numbers);
        }
        else cout << "��� ���������� �������";
        break;
    }
    default: { return; }
    }
}

//---------------����-------------------
void GTS::View�onnections() { 
    ENTER;
    connections.ViewConnections();
}

void GTS::Create�onnection() {
    if (stations.size() < 2) { cout << "������������ ������� ��� �������� �����!" << endl; return; }
    ViewStations();
    cout << "������� ID ��������� �������" << endl;
    int from, to, id;
    from = InputExistIdStation();
    cout << "������� ID �������� �������" << endl;
    to = InputExistIdStation();

    if (connections.UncorrectNodes(from,  to)) { return; }

    cout << "������� ������� �����, ������� �� ������ ��������� �������:" << endl;
    vector<int> sizes = Pipe::GetSizes();
    int diameter = SwitchNumber(sizes);
    unordered_set<int> result = Find_By_Filter<Pipe, int>(pipes, CheckByDiameter, diameter);
    result = GetFreePipes(result);

    if (!result.size()) {
        cout << "���� � ��������� ��������� �� �������. ������ ������� ����� �����?(0 - ���(�����), 1 - ��)" << endl;
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
    cout << "�������� ID ����� ��� �����:";
    do {
        id = GetCorrectNumber(MIN_ID_PIPE, Pipe::GetMaxId());
        if (!result.contains(id)) { cout << "��� ������ ID ����� ��������� ����! ������� ��� ���." << endl; }
    } while (!result.contains(id));

    connections.CreateConnection(from, to, id);
    return;
}

void GTS::Delete�onnection() {
    if (connections.Empty()) {
        cout << "��� ��������� ������!";
        return;
    }

    connections.ViewConnections();
    cout << "������� ID ��������� �����:" << endl;
    int id;
    do {
        id = GetCorrectNumber(MIN_ID_PIPE, Pipe::GetMaxId());
        if (!connections.edges.contains(id)) { cout << "��� ������ ID ����� ��������� ����! ������� ��� ���." << endl; }
    } while (!connections.edges.contains(id));
    connections.DeleteConnection_ByPipeID(id);
}


void GTS::TopologicalSort() {
    if (connections.Empty()) { cout << "��� ��������� ������!"; return; }
    Graph graph = Graph(connections.edges, connections.nodes, pipes);
    vector<int> result = graph.TopologicalSort();
    if (!result.size()) { cout << "�������������� ����������: - "; return; }
    cout << "�������������� ����������: ";
    for (auto& i : result) {
        cout << i << " ";
    }
}

void GTS::ShortestPath() {
    if (connections.Empty()) { cout << "��� ��������� ������!"; return; }
    Graph graph = Graph(connections.edges, connections.nodes, pipes);

    connections.ViewConnections();
    cout << "������� ��������� ������� ����:" << endl;
    int StartNode = GetCorrectNumber(MIN_ID_STATION, Station::GetMaxId());

    cout << "������� �������� ������� ����:" << endl;
    int EndNode = GetCorrectNumber(MIN_ID_STATION, Station::GetMaxId());

    vector<int> result = graph.Metod_Deikstra(StartNode, EndNode);
    if (!result.size()) { cout << "����: - "; return; }
    cout << "����: ";
    for (auto& i : result) {
        cout << i << " -> ";
    }
    cout << "end" << endl;
    cout << "����� ����: " << graph.Lenght_ShortestPath(result) << endl;
}

void GTS::MaxFlow() {
    if (connections.Empty()) { cout << "��� ��������� ������!"; return; }
    Graph graph = Graph(connections.edges, connections.nodes, pipes);

    connections.ViewConnections();
    cout << "������� ��������� ������� ����:" << endl;
    int StartNode = GetCorrectNumber(MIN_ID_STATION, Station::GetMaxId());

    cout << "������� �������� ������� ����:" << endl;
    int EndNode = GetCorrectNumber(MIN_ID_STATION, Station::GetMaxId());

    double result = graph.Ford_Fulkerson(StartNode, EndNode);
    cout << "������������ �����: " << result << endl;
}
//---------------����������-��������-------------------
void GTS::SaveConfiguration() 
{
    if (HasObject(PIPE) or HasObject(STATION)){
        cout << "������� �������� ����������:" << endl;
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
        cout << "������� ���������!" << endl;
    }
    else { ENTER; cout << "���������� �� ����� ���� ������, �������� ������!" << endl; }
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
    cout << "�������� ����� ����������" << endl;
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

    cout << "����� ���������!\n" << endl;
    file.close();
}
