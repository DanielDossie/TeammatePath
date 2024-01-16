#include "LLNode.h"
#include "Vertex.h"
#include <limits>

using namespace std;

Vertex::Vertex() {
    name = "";
    year = 0;
    team = false;
    count = 0;
    color = "white";
    distance = INT_MAX;
    pred = nullptr;
    predTeam = nullptr;
}

Vertex::Vertex(string n, int y, bool t) {
    name = n;
    year = y;
    team = t;
    count = 0;
    color = "white";
    distance = INT_MAX;
    pred = nullptr;
    predTeam = nullptr;
}

void Vertex::playerRead(string n) {
    name = n;
    count = 0;
}

void Vertex::teamRead(string n, int y) {
    name = n;
    year = y;
    team = true;
    count = 0;
}

void Vertex::show(){
    cout << "Name: " << name << " " << "Team: " << team << " " << "Year: " << year << endl;
}
/*
Vertex::~Vertex() {
    
    //delete list;
    delete pred;
    delete predTeam;
    pred = nullptr;
    predTeam = nullptr;
    
}
*/