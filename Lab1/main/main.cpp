#include <iostream>
#include <fstream>

#include "Pipeline.h"
#include "Compressor_station.h"

using namespace std;



template <typename T>
void ViewComponents(vector<T>& vector)
{
    for (int i = 0; i < vector.capacity(); i++) {
        cout << i+1 << ". ";
        vector[i].ShowInfo();
    } 
}



void View(vector<Pipeline>& pipelines, vector<Compressor_station>& stations)
{
    
    while (1) {
        ClearCMD();
        cout << "0. Назад\n" <<
            "1. Список труб\n" <<
            "2. Список КС" << endl;


        switch (GetCorrectNumber(0,2)) {
        case 1: {
            ClearCMD();
            ViewComponents<Pipeline>(pipelines);
            cout << "Нажмите любую клавишу" << endl;
            string x;
            cin >> x;
            break;
        }
        case 2: {
            ClearCMD();
            ViewComponents<Compressor_station>(stations);
            cout << "Нажмите любую клавишу" << endl;
            string x;
            cin >> x;
            break;
        }

        case 0: {
            return;
        }

        }
    }
}



void EditPipeline(vector<Pipeline>& pipelines)
{
    if (pipelines.size()) {
        ClearCMD();
        cout << "Список труб:\n";
        ViewComponents(pipelines);
        cout << "Выберете редактируемую трубу:";
        int number = GetCorrectNumber(1, pipelines.size());
        pipelines[number - 1].Edit();
    }
}


void EditCopressorStation(vector<Compressor_station>& stations) {
    if (stations.size()) {
        ClearCMD();
        cout << "Список станций:\n";
        ViewComponents(stations);
        cout << "Выберете редактируемую станцию:";
        int number = GetCorrectNumber(1, stations.size());
        stations[number - 1].Edit();
    }
}


void SaveConfiguration(){

}


void LoadConfiguration() {

}



int main()
{
    setlocale(LC_ALL, "RU");

    vector<Pipeline> pipelines;
    vector<Compressor_station> stations;


    while (1) {
        ClearCMD();
        cout << "\n1. Добавить трубу\n" <<
            "2. Добавить КС\n" <<
            "3. Просмотр всех объектов\n" <<
            "4. Редактировать трубу\n" <<
            "5. Редактировать КС\n" <<
            "6. Сохранить\n" <<
            "7. Загрузить\n" << endl;
        
       
        switch (GetCorrectNumber(0, 7))
        {

        case 1: {
            Pipeline pipeline;
            pipelines.emplace_back(pipeline);
            break;
        }
        case 2: {
            Compressor_station station;
            stations.emplace_back(station);
            break;
        }
        case 3: {
            View(pipelines, stations);
            break;
        }
        case 4: {
            EditPipeline(pipelines);
            break;
        }
        case 5: {
            EditCopressorStation(stations);
            break;
        }
        case 6: {
            SaveConfiguration();
            break;

        }

        case 7: {
            LoadConfiguration();
            break;

        }

        case 0: {
            return 0;

        }

        }
    }

    return 0;
}
