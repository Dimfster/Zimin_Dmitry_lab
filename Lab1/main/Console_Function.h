#pragma once

#include "Compressor_station.h"
#include "Pipe.h"



using namespace std;


// Ожидание ввода клавиши
void Wait();


// Показывает все компоненты вектора
template <typename T>
void ViewComponents(unordered_map<int, T>& map);


template <typename T>
map<int, int> Create_Console_Map(const unordered_map<int, T>& conteiner);


// Показывает меню просмотра труб и станций
void View(unordered_map<int, Pipe>& pipes, unordered_map<int, Compressor_station>& stations);


// Меню выбора редактируемой трубы 
void EditPipeline(unordered_map<int, Pipe>& pipes);


// Меню выбора редактируемой КС
void EditCopressorStation(unordered_map<int, Compressor_station>& stations);

// Сохрание конфигурации
void SaveConfiguration(const unordered_map<int, Pipe>& pipes, const unordered_map<int, Compressor_station>& stations);


// Загрузка конфигурации
void LoadConfiguration(unordered_map<int, Pipe>& pipes, unordered_map<int, Compressor_station>& stations);



void SearchPipes(unordered_map<int, Pipe>& pipes);


void SearchCS(unordered_map<int, Compressor_station>& stations);
