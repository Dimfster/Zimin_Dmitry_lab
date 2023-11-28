#include "Menu.h"
#include "Utilites.h"

using namespace std;
//---------------����� ��������-------------------
void View_Menu(GTS& GasSystem)
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
            GasSystem.ViewPipes();

            break;
        }
        case 2: {
            ENTER;
            cout << "----------�������-----------" << endl;
            GasSystem.ViewStations();

            break;
        }

        case 3: {
            ENTER;
            cout << "----------�����-----------" << endl;
            GasSystem.ViewPipes();
            ENTER;
            cout << "----------�������-----------" << endl;
            GasSystem.ViewStations();
            ENTER;
            break;
        }

        case 0: { return;}
        }
        return;
    }
}

//---------------��������������-------------------
void EditOnePipe(GTS& GasSystem)
{
    ENTER;
    cout << "������ ����:\n";
    GasSystem.ViewPipes();
    cout << "�������� ������������� �����:";
    auto keys = GasSystem.GetIDs(GTS::PIPE);
    int number = GetCorrectNumber<int>(1, INT_MAX);
    if (!keys.contains(number)) { cout << "��� ����� � ���������� ID!" << endl; return; }
    unordered_set<int> key = { number };
    GasSystem.EditPipes(key);
}

void EditOneStation(GTS& GasSystem) {
    ENTER;
    cout << "������ �������:\n";
    GasSystem.ViewStations();
    cout << "�������� ������������� �������:";
    auto keys = GasSystem.GetIDs(GTS::STATION);
    int number = GetCorrectNumber<int>(1, INT_MAX);
    if (!keys.contains(number)) { cout << "��� ������� � ���������� ID!" << endl; return; }
    unordered_set<int> key = { number };
    GasSystem.EditCS(key);
}

void Edit_Pipes(GTS& GasSystem){
    if (!GasSystem.HasObject(GTS::PIPE)) { cout << "��� ��������� ����!" << endl; return; }

    cout << "1. ������������� ���� ����� �� ������\n"
        << "2. ������������� �� �������\n"
        << "0. �����"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
        case 1: { EditOnePipe(GasSystem); break; }
        case 2: {
            cout << "�������� ������ ������:" <<
                "\n1.�� �����" <<
                "\n2.�� ���������"; ENTER;

            switch (GetCorrectNumber(0, 2))
            {
                case 1:
                {
                    GasSystem.Edit_ByName(GTS::PIPE);
                    break;
                }
                case 2:
                {
                    GasSystem.Edit_ByParametr(GTS::PIPE);
                    break;
                }
                case 0: { break; }
            }
            break;
        }
    }
}

void Edit_CS(GTS& GasSystem)
{
    if (!GasSystem.HasObject(GTS::STATION))
    {
        cout << "��� ��������� �������!" << endl;
        return;
    }

    cout << "1. ������������� ���� ������� �� ������\n"
        << "2. ������������� �� �������\n"
        << "0. �����"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
    case 1:{ EditOneStation(GasSystem); break; }

    case 2:{
        cout << "�������� ������ ������:" <<
            "\n1.�� �����" <<
            "\n2.�� ���������" <<
            "\n0.�����"; ENTER;

        switch (GetCorrectNumber(0, 2)){
            case 1:
            {
                GasSystem.Edit_ByName(GTS::STATION);
                break;
            }
            case 2:
            {
                GasSystem.Edit_ByParametr(GTS::STATION);
                break;
            }
            case 0: { break; }
        }
        break;
    }
    case 0: { break; }
    }
}

void Edit_Menu(GTS& GasSystem)
{
    cout << "1. �������������� ����\n"
        << "2. �������������� �������\n"
        << "0. �����"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
        case 1:{ Edit_Pipes(GasSystem); break; }
        case 2:{ Edit_CS(GasSystem); break; }
        case 0: { break; }
    }
}

//---------------��������-------------------

void DeleteOnePipe(GTS& GasSystem)
{
    ENTER;
    cout << "������ ����:\n";
    GasSystem.ViewPipes();
    cout << "�������� ��������� �����:";
    auto keys = GasSystem.GetIDs(GTS::PIPE);
    int number = GetCorrectNumber<int>(1, INT_MAX);
    if (!keys.contains(number)) { cout << "��� ����� � ���������� ID!" << endl; return; }
    unordered_set<int> key = { number };
    GasSystem.DeletePipes(key);
}

void DeleteOneStation(GTS& GasSystem) {
    ENTER;
    cout << "������ �������:\n";
    GasSystem.ViewStations();
    cout << "�������� ��������� �������:";
    auto keys = GasSystem.GetIDs(GTS::STATION);
    int number = GetCorrectNumber<int>(1, INT_MAX);
    if (!keys.contains(number)) { cout << "��� ������� � ���������� ID!" << endl; return; }
    unordered_set<int> key = { number };
    GasSystem.DeleteStations(key);
}

void Delete_Pipes(GTS& GasSystem)
{
    if (!GasSystem.HasObject(GTS::PIPE)) { cout << "��� ��������� ����!" << endl; return; }

    cout << "1. ������� ���� ����� �� ������\n"
        << "2. ������� �� �������\n"
        << "0. �����"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
    case 1: { DeleteOnePipe(GasSystem); break; }
    case 2: {
        cout << "�������� ������ ������:" <<
            "\n1.�� �����" <<
            "\n2.�� ���������"; ENTER;

        switch (GetCorrectNumber(0, 2))
        {
        case 1:
        {
            GasSystem.Delete_ByName(GTS::PIPE);
            break;
        }
        case 2:
        {
            GasSystem.Delete_ByParametr(GTS::PIPE);
            break;
        }
        case 0: { break; }
        }
        break;
    }
    }

}

void Delete_Stations(GTS& GasSystem)
{
    if (!GasSystem.HasObject(GTS::STATION)) { cout << "��� ��������� �������!" << endl; return; }

    cout << "1. ������� ���� ����� �� ������\n"
        << "2. ������� �� �������\n"
        << "0. �����"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
        case 1: { DeleteOnePipe(GasSystem); break; }
        case 2: {
            cout << "�������� ������ ������:" <<
                "\n1.�� �����" <<
                "\n2.�� ���������"; ENTER;

            switch (GetCorrectNumber(0, 2))
            {
                case 1:{ GasSystem.Delete_ByName(GTS::PIPE); break; }
                case 2:{ GasSystem.Delete_ByParametr(GTS::PIPE); break; }
                case 0: { break; }
            }
            break;
        }
    }

}

void Delete_Menu(GTS& GasSystem)
{
    cout << "1. �������� ����\n"
        << "2. �������� �������\n"
        << "0. �����" << endl;

    switch (GetCorrectNumber(0, 2))
    {
        case 1: { Delete_Pipes(GasSystem); break; }
        case 2: { Delete_Stations(GasSystem); break; }
        case 0: { break; }
    }
}


void MainMenu(GTS& GasSystem)
{
    while (1) {
        ENTER;
        cout << "\n1. �������� �����\n" <<
            "2. �������� ��\n" <<
            "3. �������� ���� ��������\n" <<
            "4. ��������������\n" <<
            "5. ��������\n" <<
            "6. ���������\n" <<
            "7. ���������\n" <<
            "0. �����\n" << endl;

        switch (GetCorrectNumber(0, 7))
        {
        case 1: { GasSystem.CreatePipe(); break; }
        
        case 2: { GasSystem.CreateCS(); break;}

        case 3: { View_Menu(GasSystem); break; }

        case 4: { Edit_Menu(GasSystem); break; }

        case 5: { Delete_Menu(GasSystem); break; }

        case 6: { GasSystem.SaveConfiguration(); break; }

        case 7: { GasSystem.LoadConfiguration(); break; }

        case 0: { return;}
        }
    }
}