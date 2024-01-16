#ifndef _LLNODE_H
#define _LLNODE_H

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
//#include "LL.h"

using namespace std;

/*
class LL {
	public:
		LL() {head = nullptr; num_elements = 0;};
		LLNode* insert(LLNode* newnode);
		void show();
		//bool find(Vertex vertex);
        ~LL();
		
	private:
        int num_elements;
        LLNode* head = nullptr;
};

class Vertex {
    public:
        Vertex();
        Vertex(string name, int year, bool team);
        void playerRead(string n);
        void teamRead(string n, int y);
        string getName() {return name;};
        int getYear() {return year;};
        LL list;
        void show();
    private:
        string name;
        int year;
        bool team;
};
*/

class Vertex;

class LLNode {
    public:
        LLNode();
        LLNode(Vertex *newVertex);
        Vertex *data;
        LLNode *next;
        ~LLNode();
    private:
};
#endif // _LLNODE_H
