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
void ViewComponents(vector<T>& vector)
{
    for (int i = 0; i < vector.size(); i++) {
        cout << i + 1 << ". ";
        vector[i].ShowInfo();
    }
}



// Показывает меню просмотра труб и станций
void View(vector<Pipe>& pipes, vector<Compressor_station>& stations)
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
void EditPipeline(vector<Pipe>& pipes)
{
    if (pipes.empty()) {
        ENTER;
        cout << "Список труб:\n";
        ViewComponents(pipes);
        cout << "Выберете редактируемую трубу:";
        int number = GetCorrectNumber(1, pipes.size());
        pipes[number - 1].Edit();
    }
    else {
        cout << "Нет доступных труб!" <<
            "Нажмите любую клавишу" << endl;
        Wait();
    }
}

// Меню выбора редактируемой КС
void EditCopressorStation(vector<Compressor_station>& stations) {
    if (stations.empty()) {
        ENTER;
        cout << "Список станций:\n";
        ViewComponents(stations);
        cout << "Выберете редактируемую станцию:";
        int number = GetCorrectNumber(1, stations.size());
        stations[number - 1].Edit();
    }
    else {
        cout << "Нет доступных КС!" <<
            "Нажмите любую клавишу" << endl;
        Wait();
    }
}

// Сохрание конфигурации
void SaveConfiguration(vector<Pipe>& pipes, vector<Compressor_station>& stations) {
    cout << "Введите название сохранения:" << endl;
    string name;
    cin.ignore(10000, '\n');
    getline(cin, name);
    name = "Saves/" + name + ".txt";

    ofstream file;
    file.open(name, ios::out);
    file << pipes.size() << " " << stations.size() << endl;
    for (int i = 0; i < pipes.size(); i++) file << pipes[i];
    for (int i = 0; i < stations.size(); i++) file << stations[i];
    file.close();

    ENTER;
    cout << "Успешно сохранено!\nНажмите любую клавишу" << endl;
    Wait();
}


// Загрузка конфигурации
void LoadConfiguration(vector<Pipe>& pipes, vector<Compressor_station>& stations) {
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
                pipes.push_back(pipe);
            }

            Compressor_station station;
            for (count_cs; count_cs > 0; count_cs--) {
                file >> station;
                stations.push_back(station);
            }

            cout << "Файлы загружены!\n" << "Нажмите любую клавишу" << endl;
            Wait();
            break;
        }
    }
}





