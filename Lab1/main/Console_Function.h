#pragma once

#include "Compressor_station.h"
#include "Pipe.h"



using namespace std;


// Ожидание ввода клавиши
void Wait();


// Показывает все компоненты вектора
template <typename T>
void ViewComponents(vector<T>& vector);



// Показывает меню просмотра труб и станций
void View(vector<Pipe>& pipes, vector<Compressor_station>& stations);


// Меню выбора редактируемой трубы 
void EditPipeline(vector<Pipe>& pipes);

// Меню выбора редактируемой КС
void EditCopressorStation(vector<Compressor_station>& stations);

// Сохрание конфигурации
void SaveConfiguration(vector<Pipe>& pipes, vector<Compressor_station>& stations);


// Загрузка конфигурации
void LoadConfiguration(vector<Pipe>& pipes, vector<Compressor_station>& stations);





