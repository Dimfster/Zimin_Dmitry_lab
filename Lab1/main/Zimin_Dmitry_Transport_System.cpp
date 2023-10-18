#include "Utilites.h"
#include "Console_Function.h"
#include "Compressor_station.h"
#include "Pipe.h"


// Основной цикл
int main()
{
    setlocale(LC_ALL, "ru");

    unordered_map<int,Pipe> pipes;
    unordered_map<int, Compressor_station> stations;


    while (1) {
        ENTER;
        cout << "\n1. Добавить трубу\n" <<
            "2. Добавить КС\n" <<
            "3. Просмотр всех объектов\n" <<
            "4. Редактировать трубу\n" <<
            "5. Редактировать КС\n" <<
            "6. Сохранить\n" <<
            "7. Загрузить\n" << 
            "8. Поиск труб по фильтру\n" <<
            "9. Поиск станций по фильтру\n" <<
            "0. Выход\n" << endl;
        
       
        switch (GetCorrectNumber(0, 9))
        {

        case 1: {
            Pipe pipe;
            pipe.WriteInfo();
            pipes.insert({ pipe.ID, pipe });
            break;
        }
        case 2: {
            Compressor_station station;
            station.WriteInfo();
            stations.insert({ station.ID, station });
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
        case 8: {
            SearchPipes(pipes);
            break;
        }

        case 9: {
            SearchCS(stations);
            break;
        }

        case 0: {
            return 0;

        }

        }
    }

    return 0;
}
