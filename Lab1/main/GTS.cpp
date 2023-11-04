#include "Utilites.h"
#include "Pipe.h"
#include "Compressor_station.h"
#include "GTS.h"


using namespace std;


//---------------���������� �������-------------------

template <typename T1, typename T2>
using Filter = bool(*)(T1& element, T2 parametr);

template <typename T>
bool CheckByName(T& element, string name) {
    return (element.name.find(name) != string::npos);
}

bool CheckByStatus(Pipe& pipe, bool in_repair) {
    return pipe.in_repair == in_repair;
}

bool CheckByWorkshop(Compressor_station& station, int active) {
    return station.active_workshops == active;
}

template <typename Element, typename Parametr>
vector<int> Find_By_Filter(unordered_map<int, Element>& elements, Filter<Element, Parametr> filter, Parametr parametr)
{
    vector<int> result;
    for (auto& element : elements)
    {
        if (filter(element.second, parametr))
            result.push_back(element.second.GetID());
    }
    return result;
}



GTS::GTS()
{}



//---------------�������� ��������-------------------
void GTS::CreatePipe()
{
    Pipe pipe;
    pipe.WriteInfo();
    pipes.insert({ pipe.GetID(), pipe});
}


void GTS::CreateCS()
{
    Compressor_station station;
    station.WriteInfo();
    stations.insert({ station.GetID(), station });
}


//---------------����� ��������-------------------
void GTS::View()
{

    while (1) {
        ENTER;
        cout << "0. �����\n" <<
            "1. ������ ����\n" <<
            "2. ������ ��\n" <<
            "3. �������� ��" << endl;


        switch (GetCorrectNumber(0, 3)) {
            case 1: {
                ENTER;
                cout << "----------�����-----------" << endl;
                ViewComponents<Pipe>(pipes);
                cout << "������� ����� �������" << endl;
                Wait();
                break;
            }
            case 2: {
                ENTER;
                cout << "----------�������-----------" << endl;
                ViewComponents<Compressor_station>(stations);
                cout << "������� ����� �������" << endl;
                Wait();
                break;
            }

            case 3: {
                ENTER;
                cout << "----------�����-----------" << endl;
                ViewComponents<Pipe>(pipes);
                ENTER;
                cout << "----------�������-----------" << endl;
                ViewComponents<Compressor_station>(stations);
                ENTER;
                cout << "������� ����� �������" << endl;
                Wait();
                break;
            }

            case 0: {
                return;
            }
        }

        return;
    }
}


//---------------����� ��������-------------------
template <typename Struct>
vector<int> Search_By_Name(unordered_map<int, Struct>& structure)
{
    string name;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, name);

    vector<int> result = Find_By_Filter<Struct, string>(structure, CheckByName, name);
    return result;
}

template <typename Struct>
vector<int> Search_By_Status(unordered_map<int, Struct>& structure)
{
    vector<int> result = Find_By_Filter<Struct, bool>(structure, CheckByStatus, GetCorrectNumber(0, 1));
    return result;
}

template <typename Struct>
vector<int> Search_By_Workshop(unordered_map<int, Struct>& structure)
{
    vector<int> result = Find_By_Filter<Struct, int>(structure, CheckByWorkshop, GetCorrectNumber(0, 1));
    return result;
}


void GTS::Search()
{
    cout << "1. ����� ����\n"
        << "2. ����� �������\n"
        << "0. �����" << endl;

    switch (GetCorrectNumber(0, 2))
    {
    case 1:
    {
        SearchPipes();
        break;
    }
    case 2:
    {
        SearchCS();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void GTS::SearchPipes()
{
    switch (GetCorrectNumber(0, 2))
    {
        case 1:
        {
            ENTER;
            cout << "������� ��� �����:" << endl;
            vector<int> result = Search_By_Name(pipes);
            if (result.size())
            {
                for (auto& id : result) pipes.at(id).ShowInfo();

            }
            else cout << "��� ���������� ����";
            break;
        }
        case 2:
        {
            ENTER;
            cout << "������� ��������� �����:" << endl;
            vector<int> result = Search_By_Status(pipes);
            if (result.size())
            {
                for (auto& id : result) pipes.at(id).ShowInfo();
            }
            else cout << "��� ���������� ����";
            break;
        }
        case 0:
        {
            break;
        }
    }
}

void GTS::SearchCS()
{
    switch (GetCorrectNumber(0, 2))
    {
        case 1:
        {
            ENTER;
            cout << "������� ��� ������b:" << endl;
            vector<int> result = Search_By_Name(stations);
            if (result.size())
            {
                for (auto& id : result) stations.at(id).ShowInfo();

            }
            else cout << "��� ���������� �������";
            break;
        }
        case 2:
        {
            ENTER;
            cout << "������� ��������� �������:" << endl;
            vector<int> result = Search_By_Workshop(stations);
            if (result.size())
            {
                for (auto& id : result) stations.at(id).ShowInfo();
            }
            else cout << "��� ���������� �������";
            break;
        }
        case 0:
        {
            break;
        }
    }
}


//---------------��������������-------------------
void GTS::Edit()
{
    cout << "1. �������������� ����\n"
        << "2. �������������� �������\n"
        << "0. �����" << endl;

    switch (GetCorrectNumber(0, 2))
    {
        case 1:
        {
            EditPipes();
            break;
        }
        case 2:
        {
            EditCS();
            break;
        }
        case 0:
        {
            break;
        }
    }
}

void GTS::EditPipes()
{
    if (!pipes.size())
    {
        cout << "��� ��������� ����!\n" <<
            "������� ����� �������" << endl;
        Wait();
        return;
    }

    cout << "1. ������������� ���� ����� �� ������\n"
        << "2. ������������� �� �������\n"
        << "0. �����" << endl;


    switch (GetCorrectNumber(0, 2))
    {
        case 1:
        {
            EditOnePipe();
            break;
        }
        case 2:
        {
            EditSomePipes();
            break;
        }
        case 0:
        {
            break;
        }
    }

}

void GTS::EditCS() {
    if (!stations.size()) {
        cout << "��� ��������� ��!\n" <<
            "������� ����� �������" << endl;
        Wait();
        return;
    }

    cout << "1. ������������� ���� ������� �� ������\n"
        << "2. ������������� �� �������\n"
        << "0. �����" << endl;

    switch (GetCorrectNumber(0, 2))
    {
        case 1:
        {
            EditOneCS();
            break;
        }
        case 2:
        {
            EditSomeCS();
            break;
        }
        case 0:
        {
            break;
        }
    }

}



void GTS::EditOnePipe()
{
    ENTER;
    cout << "������ ����:\n";
    ViewComponents(pipes);
    cout << "�������� ������������� �����:";
    EditOne(pipes);
}

void GTS::EditOneCS()
{
    ENTER;
    cout << "������ �������:\n";
    ViewComponents(stations);
    cout << "�������� ������������� �������:";
    EditOne(stations);
}


void GTS::EditSomePipes()
{
    if (!pipes.size())
    {
        cout << "��� ��������� ����!";
        return;
    }

    cout << "�������� ������ ������:" <<
        "\n1.�� �����" <<
        "\n2.�� ���������" << endl;

    switch (GetCorrectNumber(0, 2))
    {
        case 1:
        {
            ENTER;
            cout << "������� ��� �����:" << endl;
            vector<int> result = Search_By_Name(pipes);
            if (result.size())
            {
                for (auto& id : result) pipes.at(id).ShowInfo();
                cout << "�������� ��������� ����?(0 - ���, 1 - ��)" << endl;
                int answer = GetCorrectNumber(0, 1);
                for (auto& id : result) pipes.at(id).Edit(answer);
            }
            else cout << "��� ���������� ����";
            break;
        }
        case 2:
        {
            ENTER;
            cout << "������� ��������� �����:" << endl;
            vector<int> result = Search_By_Status(pipes);
            if (result.size())
            {
                for (auto& id : result) pipes.at(id).ShowInfo();
                cout << "�������� ��������� ����?(0 - ���, 1 - ��)" << endl;
                int answer = GetCorrectNumber(0, 1);
                for (auto& id : result) pipes.at(id).Edit(answer);
            }
            else cout << "��� ���������� ����";
            break;
        }
        case 0:
        {
            break;
        }
    }
}

void GTS::EditSomeCS()
{
    if (!pipes.size())
    {
        cout << "��� ��������� ����!";
        return;
    }

    cout << "�������� ������ ������:"<<
        "\n1.�� �����" << 
        "\n2.�� ���������" << endl;

    switch (GetCorrectNumber(0, 2))
    {
        case 1:
        {
            ENTER;
            cout << "������� ��� �������:" << endl;
            vector<int> result = Search_By_Name(stations);
            if (result.size())
            {
                for (auto& id : result) stations.at(id).ShowInfo();
                cout << "�������� ���������� �������� ����� ��:(0 - 10)" << endl;
                int answer = GetCorrectNumber(0, 10);
                for (auto& id : result) stations.at(id).Edit(answer);
            }
            else cout << "��� ���������� �������";
            break;
        }
        case 2:
        {
            ENTER;
            cout << "������� ���������� �������� ����� �������:" << endl;
            vector<int> result = Search_By_Workshop(stations);
            if (result.size())
            {
                for (auto& id : result) stations.at(id).ShowInfo();
                cout << "�������� ���������� �������� ����� ��:(0 - 10)" << endl;
                int answer = GetCorrectNumber(0, 10);
                for (auto& id : result) stations.at(id).Edit(answer);
            }
            else cout << "��� ���������� �������";
            break;
        }
        case 0:
        {
            break;
        }
    }
}


//---------------����������-��������-------------------
void GTS::SaveConfiguration() {
    if (pipes.size() and stations.size()) {
        cout << "������� �������� ����������:" << endl;
        string name;
        cin.ignore(10000, '\n');
        getline(cin, name);
        name = "Saves/" + name + ".txt";

        ofstream file;
        file.open(name, ios::out);
        file << pipes.size() << " " << stations.size() << endl;
        for (auto& pipe : pipes)
            file << pipe.second;
        for (auto& station : stations)
            file << station.second;
        file.close();

        ENTER;
        cout << "������� ���������!\n������� ����� �������" << endl;
        Wait();
    }

    else ENTER; cout << "���������� �� ����� ���� ������, �������� ������!" << endl;

}

void GTS::LoadConfiguration() {
    ENTER;
    ifstream file;
    std::string path = "Saves\\";
    int count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        cout << count << ". " << name << endl;
    }

    ENTER;
    cout << "�������� ����� ����������" << endl;
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


            for (count_pipes; count_pipes > 0; count_pipes--)
            {
                Pipe pipe;
                file >> pipe;
                pipes.insert({ pipe.GetID(), pipe });
            }

            Compressor_station station;
            for (count_cs; count_cs > 0; count_cs--)
            {

                file >> station;
                stations.insert({ station.GetID(), station });
            }

            cout << "����� ���������!\n" << "������� ����� �������" << endl;
            Wait();
            break;
        }
    }
}































/*
//---------------��������������-------------------


vector<int> Search_By_Name_Pipes()
{
    vector<int> result;
    //ENTER;
    //cout << "������� ��� �����:" << endl;
    string name;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, name);

    result = Find_By_Filter<Pipe, string>(pipes, CheckByName, name);
    return result;
}


vector<int> Search_By_Name_Stations(unordered_map<int, Compressor_station>& stations)
{

    vector<int> result;
    //ENTER;
    //cout << "������� ��� �������:" << endl;
    string name;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, name);

    result = Find_By_Filter<Compressor_station, string>(stations, CheckByName, name);
    if (result.size()) for (auto& id : result) stations.at(id).ShowInfo();
    else cout << "��� ���������� �������";
    return result;
}


vector<int> Search_By_Status_Pipes(unordered_map<int, Pipe>& pipes)
{
    ENTER;
    vector<int> result;
    cout << "������� ��������� �����:" << endl;
    result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, GetCorrectNumber(0, 1));

    if (result.size()) for (auto& id : result) pipes.at(id).ShowInfo();
    else cout << "��� ���������� ����";
}


vector<int> Search_By_Efficianty_Stations(unordered_map<int, Compressor_station>& stations)
{
    ENTER;
    vector<int> result;
    cout << "������� ������������� �������:" << endl;
    result = Find_By_Filter<Compressor_station, int>(stations, CheckByEfficianty, GetCorrectNumber(0, 1));

    if (result.size()) for (auto& id : result) stations.at(id).ShowInfo();
    else cout << "��� ���������� �������";
}
*/