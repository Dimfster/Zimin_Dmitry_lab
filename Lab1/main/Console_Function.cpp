#include "Console_Function.h"


// �������� ����� �������
void Wait() {
    while (true)
    {
        if (_kbhit()) break;
    }
}


// ���������� ��� ���������� �������
template <typename T>
void ViewComponents(vector<T>& vector)
{
    for (int i = 0; i < vector.size(); i++) {
        cout << i + 1 << ". ";
        vector[i].ShowInfo();
    }
}



// ���������� ���� ��������� ���� � �������
void View(vector<Pipe>& pipes, vector<Compressor_station>& stations)
{

    while (1) {
        ENTER;
        cout << "0. �����\n" <<
            "1. ������ ����\n" <<
            "2. ������ ��\n" << 
            "3. �������� ��" << endl;


        switch (GetCorrectNumber(0, 3)) {
        case 1: {
            ENTER;
            cout << "----------�����-----------" << endl;
            ViewComponents<Pipe>(pipes);
            cout << "������� ����� �������" << endl;
            Wait();
            break;
        }
        case 2: {
            ENTER;
            cout << "----------�������-----------" << endl;
            ViewComponents<Compressor_station>(stations);
            cout << "������� ����� �������" << endl;
            Wait();
            break;
        }

        case 3: {
            ENTER;
            cout << "----------�����-----------" << endl;
            ViewComponents<Pipe>(pipes);
            ENTER;
            cout << "----------�������-----------" << endl;
            ViewComponents<Compressor_station>(stations);
            ENTER;
            cout << "������� ����� �������" << endl;
            Wait();
            break;
        }

        case 0: {
            return;
        }

        }
    }
}


// ���� ������ ������������� ����� 
void EditPipeline(vector<Pipe>& pipes)
{
    if (pipes.empty()) {
        ENTER;
        cout << "������ ����:\n";
        ViewComponents(pipes);
        cout << "�������� ������������� �����:";
        int number = GetCorrectNumber(1, pipes.size());
        pipes[number - 1].Edit();
    }
    else {
        cout << "��� ��������� ����!" <<
            "������� ����� �������" << endl;
        Wait();
    }
}

// ���� ������ ������������� ��
void EditCopressorStation(vector<Compressor_station>& stations) {
    if (stations.empty()) {
        ENTER;
        cout << "������ �������:\n";
        ViewComponents(stations);
        cout << "�������� ������������� �������:";
        int number = GetCorrectNumber(1, stations.size());
        stations[number - 1].Edit();
    }
    else {
        cout << "��� ��������� ��!" <<
            "������� ����� �������" << endl;
        Wait();
    }
}

// �������� ������������
void SaveConfiguration(vector<Pipe>& pipes, vector<Compressor_station>& stations) {
    cout << "������� �������� ����������:" << endl;
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
    cout << "������� ���������!\n������� ����� �������" << endl;
    Wait();
}


// �������� ������������
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
    cout << "�������� ����� ����������" << endl;
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

            cout << "����� ���������!\n" << "������� ����� �������" << endl;
            Wait();
            break;
        }
    }
}





