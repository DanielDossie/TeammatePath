#include "LLNode.h"
#include "LL.h"
#include "Vertex.h"

using namespace std;

LLNode* LL::insert(LLNode* newnode) {
  if (head == nullptr){
    head = newnode;
    tail = newnode;
    return newnode;
  }
  tail->next = newnode;
  tail = newnode;
  num_elements++;
  return newnode;
}

LLNode* LL::remove(){
    LLNode *temp;
    temp = head;
    head = head->next;
    if(head == nullptr){
      tail = nullptr;
    }
    return temp;
  
}

void LL::show(){
    for (LLNode *np = head; np != nullptr; np = np->next) {
		  np->data->show();
    }
}

LL::~LL() {
    /*
    LLNode* curr = head;
    while (curr != nullptr) {
        LLNode *next;
        next = curr->next;
        //delete curr->data;
        delete curr;
        curr = next;
    }
    */
    //delete head;
    head = nullptr;
    //delete tail;
}