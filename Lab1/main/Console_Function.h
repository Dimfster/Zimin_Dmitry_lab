#pragma once

#include "Compressor_station.h"
#include "Pipe.h"



using namespace std;


// �������� ����� �������
void Wait();


// ���������� ��� ���������� �������
template <typename T>
void ViewComponents(vector<T>& vector);



// ���������� ���� ��������� ���� � �������
void View(vector<Pipe>& pipes, vector<Compressor_station>& stations);


// ���� ������ ������������� ����� 
void EditPipeline(vector<Pipe>& pipes);

// ���� ������ ������������� ��
void EditCopressorStation(vector<Compressor_station>& stations);

// �������� ������������
void SaveConfiguration(vector<Pipe>& pipes, vector<Compressor_station>& stations);


// �������� ������������
void LoadConfiguration(vector<Pipe>& pipes, vector<Compressor_station>& stations);





