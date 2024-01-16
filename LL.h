#ifndef _LL_H
#define _LL_H

#include <iostream>
//#include "Vertex.h"
#include "LLNode.h"

class Vertex;

using namespace std;

class LL {
	public:
		LL() {head = nullptr; num_elements = 0;};
		LLNode* insert(LLNode* newnode);
		LLNode* remove();
		void show();
		int getNumElements() { return num_elements; };
		//bool find(Vertex vertex);
		LLNode *getHead() { return head; };
		LLNode *getTail() { return tail;};
        ~LL();
		
	private:
        int num_elements;
        LLNode* head = nullptr;
		LLNode* tail = nullptr;
};

#endif