#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

#include <stdio.h> // для очистки коммандной строки

using namespace std;

void ClearCMD() {
    system("cls"); // для очистки коммандной строки
}


template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((cin >> x).fail()	// check type
        || cin.peek() != '\n'	// is buffer empty (int/float check)
        || x < min || x > max)		// check range
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Введите число от " << min << " до " << max << endl;
    }
    return x;
}

struct Papeline {
    string name;
    float length;
    int diameter;
    bool in_repair;

    void ShowInfo() {
        cout << "Труба " << name << "; Длина: " << length << "; Диаметр: " << diameter << "; Состояние:(0 - в ремонте, 1 - в эксплуатации): " << in_repair << endl;
    }
};


struct Compressor_station {
    string name;
    int number_of_workshops;
    int active_workshops;
    string type;

    void ShowInfo() {
        cout << "КС " << name << "; Кол-во цехов: " << number_of_workshops << "; Рабочие цеха: " << active_workshops << "Тип: " << type << endl;
    }
};



void AddPipeline(vector<Papeline>& pipelines) 
{
    ClearCMD();
    Papeline pipeline;
    cout << "Введите название трубы:" << endl;
    cin >> pipeline.name;

    cout << "Введите длину трубы:" << endl;
    cin >> pipeline.length;

    cout << "Введите диаметр трубы:" << endl;
    cin >> pipeline.diameter;

    cout << "Введите состояние трубы:(0 - в ремонте; 1 - в эксплуатации)" << endl;
    cin >> pipeline.in_repair;

    pipelines.emplace_back(pipeline);


}

void AddCopmressorStation()
{
    ClearCMD();
    Compressor_station station;
    cout << "Введите название КС:" << endl;
    cin >> station.name;

    cout << "Введите кол-во цехов:" << endl;
    cin >> station.number_of_workshops;

    cout << "Введите кол-во работающих цехов" << endl;
    cin >> station.active_workshops;

    cout << "Введите тип станции(A, B, C)" << endl;
    cin >> station.type;



}


template <typename T>
void ViewComponents(vector<T>& vector)
{
    ClearCMD();
    for (int i = 0; i < vector.capacity(); i++) {
        cout << i+1 << ". ";
        vector[i].ShowInfo();
    }
    cout << "Для выхода нажмите Enter" << endl;
    Sleep(1000);
 
}



void View(vector<Papeline>& pipelines, vector<Compressor_station>& stations)
{
    
    while (1) {
        ClearCMD();
        cout << "0. Назад\n" <<
            "1. Список труб\n" <<
            "2. Список КС" << endl;


        switch (GetCorrectNumber(0,2)) {
        case 1: {
            ViewComponents<Papeline>(pipelines);
            break;
        }
        case 2: {
            ViewComponents<Compressor_station>(stations);
            break;
        }

        case 0: {
            return;
        }


        }
    }
    


}



void EditPipeline()
{


}


void EditCopressorStation() {

}


void SaveConfiguration(){

}


void LoadConfiguration() {

}



int main()
{
    setlocale(LC_ALL, "RU");

    vector<Papeline> pipelines;
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
            AddPipeline(pipelines);
            break;
        }
        case 2: {
            AddCopmressorStation();
            break;
        }
        case 3: {
            View(pipelines, stations);
            break;
        }
        case 4: {
            EditPipeline();
            break;
        }
        case 5: {
            EditCopressorStation();
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
        default: {
            cout << "Неизвестное действие. Введите корректное" << endl;
            break;
        }


        }


    }

    return 0;
}
