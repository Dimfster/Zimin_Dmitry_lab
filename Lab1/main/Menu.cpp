#include "Menu.h"
#include "Utilites.h"

using namespace std;
//---------------Показ объектов-------------------
void View_Menu(GTS& GasSystem)
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
            GasSystem.ViewPipes();

            break;
        }
        case 2: {
            ENTER;
            cout << "----------Станции-----------" << endl;
            GasSystem.ViewStations();

            break;
        }

        case 3: {
            ENTER;
            cout << "----------Трубы-----------" << endl;
            GasSystem.ViewPipes();
            ENTER;
            cout << "----------Станции-----------" << endl;
            GasSystem.ViewStations();
            ENTER;
            break;
        }

        case 0: { return;}
        }
        return;
    }
}

//---------------Редактирование-------------------
void EditOnePipe(GTS& GasSystem)
{
    ENTER;
    cout << "Список труб:\n";
    GasSystem.ViewPipes();
    cout << "Выберете редактируемую трубу:";
    auto keys = GasSystem.GetIDs(GTS::PIPE);
    int number = GetCorrectNumber<int>(1, INT_MAX);
    if (!keys.contains(number)) { cout << "Нет трубы с подходящим ID!" << endl; return; }
    unordered_set<int> key = { number };
    GasSystem.EditPipes(key);
}

void EditOneStation(GTS& GasSystem) {
    ENTER;
    cout << "Список станций:\n";
    GasSystem.ViewStations();
    cout << "Выберете редактируемую станцию:";
    auto keys = GasSystem.GetIDs(GTS::STATION);
    int number = GetCorrectNumber<int>(1, INT_MAX);
    if (!keys.contains(number)) { cout << "Нет станции с подходящим ID!" << endl; return; }
    unordered_set<int> key = { number };
    GasSystem.EditStations(key);
}

void Edit_Pipes(GTS& GasSystem){
    if (!GasSystem.HasObject(GTS::PIPE)) { cout << "Нет доступных труб!" << endl; return; }

    cout << "1. Редактировать одну трубу по выбору\n"
        << "2. Редактировать по фильтру\n"
        << "0. Выход"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
        case 1: { EditOnePipe(GasSystem); break; }
        case 2: {
            cout << "Выберете фильтр поиска:" <<
                "\n1.По имени" <<
                "\n2.По состоянию"; ENTER;

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

void Edit_Stations(GTS& GasSystem)
{
    if (!GasSystem.HasObject(GTS::STATION))
    {
        cout << "Нет доступных станций!" << endl;
        return;
    }

    cout << "1. Редактировать одну станцию по выбору\n"
        << "2. Редактировать по фильтру\n"
        << "0. Выход"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
    case 1:{ EditOneStation(GasSystem); break; }

    case 2:{
        cout << "Выберете фильтр поиска:" <<
            "\n1.По имени" <<
            "\n2.По проценту неактивых цехов станции" <<
            "\n0.Выход"; ENTER;

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
    cout << "1. Редактирование труб\n"
        << "2. Редактирование станций\n"
        << "0. Назад"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
        case 1:{ Edit_Pipes(GasSystem); break; }
        case 2:{ Edit_Stations(GasSystem); break; }
        case 0: { break; }
    }
}

//---------------Удаление-------------------

void DeleteOnePipe(GTS& GasSystem)
{
    ENTER;
    cout << "Список труб:\n";
    GasSystem.ViewPipes();
    cout << "Выберете удаляемую трубу:";
    auto keys = GasSystem.GetIDs(GTS::PIPE);
    int number = GetCorrectNumber<int>(1, INT_MAX);
    if (!keys.contains(number)) { cout << "Нет трубы с подходящим ID!" << endl; return; }
    unordered_set<int> key = { number };
    GasSystem.DeletePipes(key);
}

void DeleteOneStation(GTS& GasSystem) {
    ENTER;
    cout << "Список станций:\n";
    GasSystem.ViewStations();
    cout << "Выберете удаляемую станцию:";
    auto keys = GasSystem.GetIDs(GTS::STATION);
    int number = GetCorrectNumber<int>(1, INT_MAX);
    if (!keys.contains(number)) { cout << "Нет станции с подходящим ID!" << endl; return; }
    unordered_set<int> key = { number };
    GasSystem.DeleteStations(key);
}

void Delete_Pipes(GTS& GasSystem)
{
    if (!GasSystem.HasObject(GTS::PIPE)) { cout << "Нет доступных труб!" << endl; return; }

    cout << "1. Удалить одну трубу по выбору\n"
        << "2. Удалить по фильтру\n"
        << "0. Выход"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
    case 1: { DeleteOnePipe(GasSystem); break; }
    case 2: {
        cout << "Выберете фильтр поиска:" <<
            "\n1.По имени" <<
            "\n2.По состоянию"; ENTER;

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
    if (!GasSystem.HasObject(GTS::STATION)) { cout << "Нет доступных станций!" << endl; return; }

    cout << "1. Удалить одну станцию по выбору\n"
        << "2. Удалить по фильтру\n"
        << "0. Выход"; ENTER;

    switch (GetCorrectNumber(0, 2))
    {
        case 1: { DeleteOnePipe(GasSystem); break; }
        case 2: {
            cout << "Выберете фильтр поиска:" <<
                "\n1.По имени" <<
                "\n2.По проценту неактивых цехов станции"; ENTER;

            switch (GetCorrectNumber(0, 2))
            {
                case 1:{ GasSystem.Delete_ByName(GTS::STATION); break; }
                case 2:{ GasSystem.Delete_ByParametr(GTS::STATION); break; }
                case 0: { break; }
            }
            break;
        }
    }

}

void Delete_Menu(GTS& GasSystem)
{
    cout << "1. Удаление труб\n"
        << "2. Удаление станций\n"
        << "0. Назад" << endl;

    switch (GetCorrectNumber(0, 2))
    {
        case 1: { Delete_Pipes(GasSystem); break; }
        case 2: { Delete_Stations(GasSystem); break; }
        case 0: { break; }
    }
}

//---------------Удаление-------------------
void Create_Connection(GTS& GasSystem) {
    GasSystem.CreateСonnection();
}

void Delete_Connection() {

}

void Graph_Menu(GTS& GasSystem) {
    ENTER;
    cout << "1. Показать связи\n" <<
        "2. Добавить связь\n" <<
        "3. Удалить связь\n" <<
        "4. Топологическая сортировка\n" <<
        "0. Выход\n" << endl;

    switch (GetCorrectNumber(0, 4)) {
        case 1: { GasSystem.ViewСonnections(); break; }
        case 2: { GasSystem.CreateСonnection(); break; }
        case 3: { GasSystem.DeleteСonnection(); break; }
        case 4: { GasSystem.TopologicalSort(); break; }
        case 0: { return; }
    }
}


void MainMenu(GTS& GasSystem)
{
    while (1) {
        ENTER;
        cout << "\n1. Добавить трубу\n" <<
            "2. Добавить КС\n" <<
            "3. Просмотр объектов\n" <<
            "4. Редактирование\n" <<
            "5. Удаление\n" <<
            "6. Граф\n" <<
            "7. Сохранить\n" <<
            "8. Загрузить\n" <<
            "0. Выход\n" << endl;

        switch (GetCorrectNumber(0, 8))
        {
        case 1: { GasSystem.CreatePipe(); break; }
        
        case 2: { GasSystem.CreateCS(); break;}

        case 3: { View_Menu(GasSystem); break; }

        case 4: { Edit_Menu(GasSystem); break; }

        case 5: { Delete_Menu(GasSystem); break; }

        case 6: { Graph_Menu(GasSystem); break; }

        case 7: { GasSystem.SaveConfiguration(); break; }

        case 8: { GasSystem.LoadConfiguration(); break; }

        case 0: { return;}
        }
    }
}