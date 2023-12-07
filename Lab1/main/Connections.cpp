#include "Connections.h"

using namespace std;

bool Connections::Empty()
{
    if (edges.size()) { return true; }
    else { return false; }
}

bool Connections::UncorrectNodes(int from, int to)
{
    if (nodes.contains(from) && nodes.contains(to)) {
        cout << "Станции уже задействованы!" << endl; return true;
    }
    else if (from == to) {
        cout << "Нельзя посторить связь к той же станции!" << endl; return true;
    }
    else { return false; }
}

void Connections::CreateConnection(int from, int to, int id) {
    if (UncorrectNodes(from, to)) { return; }
    if (edges.contains(id)) {
        cout << "Станции или труба уже задействованы!" << endl; return;
    }
    Edge edge = Edge(from, to, id);
    edges.insert({ id, edge });
    nodes.insert(from);
    nodes.insert(to);
    cout << endl << "Связь создана!" << endl;
    return;
}

void Connections::ViewConnections()
{
    if (edges.empty()) { cout << "Нет связей!" << endl; }
    for (auto& edge : edges) {
        cout << "Связь: Труба " << edge.second.pipe << " соединяет станции "
            << edge.second.from << " -> " << edge.second.to << endl;
    }
}

void Connections::DeleteConnection(int id) {
    if (edges.contains(id)) {
        Edge edge = edges.at(id);
        ResetNodes();
        edges.erase(id);
        cout << endl << "Связь удалена!" << endl;
    }
}

void Connections::ResetNodes()
{
    nodes.clear();
    for (auto& edge : edges) {
        nodes.insert(edge.second.from);
        nodes.insert(edge.second.to);
    }
}



ofstream& operator << (ofstream& file, const Connections& connections) {
    if (file.is_open()) {
        for (auto& edge : connections.edges) { file << edge.second; }
    }
    return file;
}