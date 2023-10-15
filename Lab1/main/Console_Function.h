#pragma once

#include "Compressor_station.h"
#include "Pipe.h"



using namespace std;


// �������� ����� �������
void Wait();


// ���������� ��� ���������� �������
template <typename T>
void ViewComponents(unordered_map<int, T>& map);


template <typename T>
map<int, int> Create_Console_Map(const unordered_map<int, T>& conteiner);


// ���������� ���� ��������� ���� � �������
void View(unordered_map<int, Pipe>& pipes, unordered_map<int, Compressor_station>& stations);


// ���� ������ ������������� ����� 
void EditPipeline(unordered_map<int, Pipe>& pipes);


// ���� ������ ������������� ��
void EditCopressorStation(unordered_map<int, Compressor_station>& stations);

// �������� ������������
void SaveConfiguration(const unordered_map<int, Pipe>& pipes, const unordered_map<int, Compressor_station>& stations);


// �������� ������������
void LoadConfiguration(unordered_map<int, Pipe>& pipes, unordered_map<int, Compressor_station>& stations);



void SearchPipes(unordered_map<int, Pipe>& pipes);


void SearchCS(unordered_map<int, Compressor_station>& stations);
