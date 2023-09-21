#include "Pipe.h"
#include "Compressor_station.h"

using namespace std;


// Показывает все компоненты вектора
template <typename T>
void ViewComponents(vector<T>& vector)
{
    for (int i = 0; i < vector.size(); i++) {
        cout << i+1 << ". ";
        vector[i].ShowInfo();
    } 
}


// Показывает меню просмотра труб и станций
void View(vector<Pipe>& pipes, vector<Compressor_station>& stations)
{
    
    while (1) {
        CLEAR;
        cout << "0. Назад\n" <<
            "1. Список труб\n" <<
            "2. Список КС" << endl;


        switch (GetCorrectNumber(0,2)) {
        case 1: {
            CLEAR
            ViewComponents<Pipe>(pipes);
            cout << "Нажмите любую клавишу" << endl;
            while (true)
            {
                if (_kbhit())
                {
                    break;
                }
            }
            break;
        }
        case 2: {
            CLEAR;
            ViewComponents<Compressor_station>(stations);
            cout << "Нажмите любую клавишу" << endl;
            while (true)
            {
                if (_kbhit())
                {
                    break;
                }
            }
            break;
        }

        case 0: {
            return;
        }

        }
    }
}


// Меню выбора редактируемой трубы 
void EditPipeline(vector<Pipe>& pipes)
{
    if (pipes.size()) {
        CLEAR;
        cout << "Список труб:\n";
        ViewComponents(pipes);
        cout << "Выберете редактируемую трубу:";
        int number = GetCorrectNumber(1, pipes.size());
        pipes[number - 1].Edit();
    }
    else {
        cout << "Нет доступных труб!" <<
            "Нажмите любую клавишу" << endl;
        while (true)
        {
            if (_kbhit())
            {
                break;
            }
        }
    }
}

// Меню выбора редактируемой КС
void EditCopressorStation(vector<Compressor_station>& stations) {
    if (stations.size()) {
        CLEAR;
        cout << "Список станций:\n";
        ViewComponents(stations);
        cout << "Выберете редактируемую станцию:";
        int number = GetCorrectNumber(1, stations.size());
        stations[number - 1].Edit();
    }
    else {
        cout << "Нет доступных КС!" <<
            "Нажмите любую клавишу" << endl;
        while (true)
        {
            if (_kbhit())
            {
                break;
            }
        }
    }
}

// Сохрание конфигурации
void SaveConfiguration(vector<Pipe>& pipes, vector<Compressor_station>& stations){
    ofstream file;
    file.open("pipe_data.txt", ios::out);
    for (int i = 0; i < pipes.size(); i++) {
        pipes[i].SaveInfo(file);
    }
    file.close();

    file.open("KC_data.txt", ios::out);
    for (int i = 0; i < stations.size(); i++) {
        stations[i].SaveInfo(file);
    }
    file.close();

    cout << "Успешно сохранено!\nНажмите любую клавишу" << endl;
    while (true)
    {
        if (_kbhit())
        {
            break;
        }
    }
}

// Загрузка конфигурации
void LoadConfiguration(vector<Pipe>& pipes, vector<Compressor_station>& stations) {

    ifstream file;
    file.open("pipe_data.txt", ios::in);
    string name_p;
    float length;
    int diameter;
    bool in_repair;
    while (!file.eof()) {
        file >> name_p;
        file >> length;
        file >> diameter;
        file >> in_repair;
        Pipe pipe(name_p, length, diameter, in_repair);
        pipes.push_back(pipe);
    }
    pipes.pop_back();
    file.close();


    file.open("KC_data.txt", ios::in);
    string name_kc;
    int number_of_workshops;
    int active_workshops;
    string type;
    while (!file.eof()) {
        file >> name_kc;
        file >> number_of_workshops;
        file >> active_workshops;
        file >> type;
        Compressor_station station(name_kc, number_of_workshops, active_workshops, type);
        stations.push_back(station);
    }
    stations.pop_back();
    file.close();

    cout << "Данные загружены!\nНажмите любую клавишу" << endl;
    while (true)
    {
        if (_kbhit())
        {
            break;
        }
    }
}


// Основной цикл
int main()
{
    setlocale(LC_ALL, "ru");

    vector<Pipe> pipes;
    vector<Compressor_station> stations;


    while (1) {
        CLEAR;
        cout << "\n1. Добавить трубу\n" <<
            "2. Добавить КС\n" <<
            "3. Просмотр всех объектов\n" <<
            "4. Редактировать трубу\n" <<
            "5. Редактировать КС\n" <<
            "6. Сохранить\n" <<
            "7. Загрузить\n" << 
            "0. Выход\n" << endl;
        
       
        switch (GetCorrectNumber(0, 7))
        {

        case 1: {
            Pipe pipe;
            pipe.WhiteInfo();
            pipes.emplace_back(pipe);
            break;
        }
        case 2: {
            Compressor_station station;
            station.WhiteInfo();
            stations.emplace_back(station);
            break;
        }
        case 3: {
            View(pipes, stations);
            break;
        }
        case 4: {
            EditPipeline(pipes);
            break;
        }
        case 5: {
            EditCopressorStation(stations);
            break;
        }
        case 6: {
            SaveConfiguration(pipes, stations);
            break;
        }

        case 7: {
            LoadConfiguration(pipes, stations);
            break;
        }

        case 0: {
            return 0;

        }

        }
    }

    return 0;
}
