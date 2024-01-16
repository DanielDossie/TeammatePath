#ifndef _VERTEX_H
#define _VERTEX_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <cctype>
#include <ctype.h>
#include <unistd.h>
#include "LL.h"
#include <limits.h>

using namespace std;

class Vertex {
    public:
        Vertex();
        Vertex(string name, int year, bool team);
        void playerRead(string n);
        void teamRead(string n, int y);
        string getName() {return name;};
        int getYear() {return year;};
        void setColor(string c){color = c;};
        void setDistance(int d){distance = d;};
        void setPred(Vertex* v){pred = v;};
        string getColor() {return color;};
        int getDistance() { return distance;};
        Vertex* getPred() { return pred;};
        LL list;
        void show();
        int count;
        bool team;
        Vertex *predTeam;
        //~Vertex();
    private:
        string name;
        int year;
        string color;
        int distance;
        Vertex *pred;
};

#endif