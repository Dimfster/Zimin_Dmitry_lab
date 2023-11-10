#include "Utilites.h"
#include "Pipe.h"
#include "Station.h"
#include "GTS.h"
#include <format>


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

bool CheckByWorkshop(Station& station, int active) {
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
    Station station;
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


        switch (GetCorrectNumber(cin, 0, 3)) {
            case 1: {
                ENTER;
                cout << "----------�����-----------" << endl;
                ViewComponents<Pipe>(pipes);

                break;
            }
            case 2: {
                ENTER;
                cout << "----------�������-----------" << endl;
                ViewComponents<Station>(stations);

                break;
            }

            case 3: {
                ENTER;
                cout << "----------�����-----------" << endl;
                ViewComponents<Pipe>(pipes);
                ENTER;
                cout << "----------�������-----------" << endl;
                ViewComponents<Station>(stations);
                ENTER;
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
using Searching = vector<int>(*)(Struct& structure);

template <typename Struct>
vector<int> Search_By_Name(unordered_map<int, Struct>& structure)
{
    string name = input_string(cin);
   

    vector<int> result = Find_By_Filter<Struct, string>(structure, CheckByName, name);
    return result;
}

template <typename Struct>
vector<int> Search_By_Status(unordered_map<int, Struct>& structure)
{
    vector<int> result = Find_By_Filter<Struct, bool>(structure, CheckByStatus, GetCorrectNumber(cin, 0, 1));
    return result;
}

template <typename Struct>
vector<int> Search_By_Workshop(unordered_map<int, Struct>& structure)
{
    vector<int> result = Find_By_Filter<Struct, int>(structure, CheckByWorkshop, GetCorrectNumber(cin, 0, 1));
    return result;
}

/*
bool GTS::SearchPipe(Searching<Pipe> search)
{
    ENTER;
    cout << "������� ��� �����:" << endl;
    vector<int> result = search(pipes);

    if (!result.size())
    {
        cout << "��� ���������� ����";
        return false;
    }

    ViewComponentsByID(result, pipes);
    return true;
}
*/

void GTS::Search()
{
    cout << "1. ����� ����\n"
        << "2. ����� �������\n"
        << "0. �����" << endl;

    switch (GetCorrectNumber(cin, 0, 2))
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
    cout << "�������� ������ ������:" <<
        "\n1.�� �����" <<
        "\n2.�� ���������" << endl;
    switch (GetCorrectNumber(cin, 0, 2))
    {
        case 1:
        {
            ENTER;
            cout << "������� ��� �����:" << endl;
            vector<int> result = Search_By_Name(pipes);

            if (!result.size())
            {
                cout << "��� ���������� ����";
            }

            ViewComponentsByID(result, pipes);
            break;
        }
        case 2:
        {
            ENTER;
            cout << "������� ��������� �����:" << endl;
            vector<int> result = Search_By_Status(pipes);
            if (!result.size())
            {
                cout << "��� ���������� ����";
                return;
            }
            ViewComponentsByID(result, pipes);
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
    cout << "�������� ������ ������:" <<
        "\n1.�� �����" <<
        "\n2.�� ���������" << endl;
    switch (GetCorrectNumber(cin, 0, 2))
    {
        case 1:
        {
            ENTER;
            cout << "������� ��� �������:" << endl;
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

    switch (GetCorrectNumber(cin, 0, 2))
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
        cout << "��� ��������� ����!\n" << endl;
        return;
    }

    cout << "1. ������������� ���� ����� �� ������\n"
        << "2. ������������� �� �������\n"
        << "0. �����" << endl;


    switch (GetCorrectNumber(cin, 0, 2))
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
        cout << "��� ��������� ��!\n" << endl;

        return;
    }

    cout << "1. ������������� ���� ������� �� ������\n"
        << "2. ������������� �� �������\n"
        << "0. �����" << endl;

    switch (GetCorrectNumber(cin, 0, 2))
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

    switch (GetCorrectNumber(cin, 0, 2))
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
                int answer = GetCorrectNumber(cin, 0, 1);
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
                int answer = GetCorrectNumber(cin, 0, 1);
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
        cout << "��� ��������� �������!";
        return;
    }

    cout << "�������� ������ ������:"<<
        "\n1.�� �����" << 
        "\n2.�� ���������" << endl;

    switch (GetCorrectNumber(cin, 0, 2))
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
                int answer = GetCorrectNumber(cin, 0, 10);
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
                int answer = GetCorrectNumber(cin, 0, 10);
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

//---------------��������-------------------
void GTS::Delete()
{
    cout << "1. �������� ����\n"
        << "2. �������� �������\n"
        << "0. �����" << endl;

    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        DeletePipes();
        break;
    }
    case 2:
    {
        DeleteStations();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void GTS::DeletePipes()
{
    if (!pipes.size())
    {
        cout << "��� ��������� ����!\n" << endl;
        return;
    }

    cout << "1. ������� ���� ����� �� ������\n"
        << "2. ������� �� �������\n"
        << "0. �����" << endl;


    switch (GetCorrectNumber(cin, 0, 2))
    {
        case 1:
        {
            ENTER;
            cout << "������ ����:\n";
            ViewComponents(pipes);
            auto keys = GetKeys(pipes);
            cout << "��������� �����:";
            DeletePipes(keys);
            break;
        }
        case 2:
        {
            DeleteSomePipes();
            break;
        }
        case 0:
        {
            break;
        }
    }
}

void GTS::DeletePipes(std::vector<int>& ids)
{
    int number = GetCorrectNumber<int>(std::cin, 1, ids.size());
    pipes.erase(ids[number-1]);
}

void GTS::DeleteStations()
{
    if (!pipes.size())
    {
        cout << "��� ��������� �������!\n" << endl;
        return;
    }

    cout << "1. ������� ���� ������� �� ������\n"
        << "2. ������� �� �������\n"
        << "0. �����" << endl;


    switch (GetCorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        ENTER;
        cout << "������ �������:\n";
        ViewComponents(stations);
        cout << "��������� �������:";
        auto keys = GetKeys(stations);
        DeleteStations(keys);
        break;
    }
    case 2:
    {
        DeleteSomeStations();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void GTS::DeleteStations(std::vector<int>& ids)
{
    int number = GetCorrectNumber<int>(std::cin, 1, ids.size());
    stations.erase(ids[number - 1]);
}

void GTS::DeleteSomePipes()
{
    if (!pipes.size())
    {
        cout << "��� ��������� ����!";
        return;
    }

    cout << "�������� ������ ������:" <<
        "\n1.�� �����" <<
        "\n2.�� ���������" << endl;

    switch (GetCorrectNumber(cin, 0, 2))
    {
        case 1:
        {
            ENTER;
            cout << "������� ��� �����:" << endl;
            vector<int> result = Search_By_Name(pipes);
            if (result.size())
            {
                for (auto& id : result) pipes.at(id).ShowInfo();
                cout << "������� �����?(0 - ���, 1 - ��)" << endl;
                if (GetCorrectNumber(cin, 0, 1))
                {
                    for (auto& id : result) pipes.erase(id);
                }
                else { return; }
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
                cout << "������� �����?(0 - ���, 1 - ��)" << endl;
                if (GetCorrectNumber(cin, 0, 1))
                {
                    for (auto& id : result) pipes.erase(id);
                }
                else { return; }
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
void GTS::DeleteSomeStations()
{
    if (!pipes.size())
    {
        cout << "��� ��������� �������!";
        return;
    }

    cout << "�������� ������ ������:" <<
        "\n1.�� �����" <<
        "\n2.�� ���������" << endl;

    switch (GetCorrectNumber(cin, 0, 2))
    {
        case 1:
        {
            ENTER;
            cout << "������� ��� �������:" << endl;
            vector<int> result = Search_By_Name(stations);
            if (result.size())
            {
                for (auto& id : result) stations.at(id).ShowInfo();
                cout << "������� �������?(0 - ���, 1 - ��)" << endl;
                if (GetCorrectNumber(cin, 0, 1))
                {
                    for (auto& id : result) stations.erase(id);
                }
                else { return; }

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
                cout << "������� �������?(0 - ���, 1 - ��)" << endl;
                if (GetCorrectNumber(cin, 0, 1))
                {
                    for (auto& id : result) stations.erase(id);
                }
                else { return; }
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
void GTS::SaveConfiguration() 
{
    if (pipes.size() or stations.size()) {
        cout << "������� �������� ����������:" << endl;
        string name = input_string(cin);
        name = "Saves/" + name + ".txt";

        int MaxId_Pipe;
        int MaxId_Station;
        for (auto& pipe : pipes) 
        {
            MaxId_Pipe = pipe.second.GetMaxId();
            break;
        }
        for (auto& station : stations)
        {
            MaxId_Station = station.second.GetMaxId();
            break;
        }

        ofstream file;
        file.open(name, ios::out);
        file << pipes.size() << " " << stations.size() << " " << MaxId_Pipe << " " << MaxId_Station << endl;
        for (auto& pipe : pipes)
            file << pipe.second;
        for (auto& station : stations)
            file << station.second;
        file.close();

        ENTER;
        cout << "������� ���������!" << endl;
    }

    else
    {
        ENTER; cout << "���������� �� ����� ���� ������, �������� ������!" << endl;
    }
}

void GTS::LoadConfiguration() {
    ENTER;
    ifstream file;
    std::string path = "Saves\\";
    int count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        cout << count << ". " << name << endl;
        //std::format(name);
    }

    ENTER;
    cout << "�������� ����� ����������" << endl;
    int save = GetCorrectNumber(cin, 1, count);

    count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        if (count == save) {
            pipes.clear();
            stations.clear();

            Pipe pipe;
            Station station;

            int count_pipes;
            int count_cs;
            int MaxId_Pipe;
            int MaxId_Station;

            file.open(name);
            file >> count_pipes >> count_cs >> MaxId_Pipe >> MaxId_Station;
            pipe.SetMaxId(MaxId_Pipe);
            station.SetMaxId(MaxId_Station);

            while(count_pipes--)
           // for (count_pipes; count_pipes > 0; count_pipes--)
            {
                file >> pipe;
                pipes.insert({ pipe.GetID(), pipe });
            }

            
            for (count_cs; count_cs > 0; count_cs--)
            {
                file >> station;
                stations.insert({ station.GetID(), station });
            }

            cout << "����� ���������!\n" << endl;
            break;
        }
    }
}

