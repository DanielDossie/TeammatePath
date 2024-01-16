#include "LLNode.h"
#include <stdio.h>


LLNode::LLNode() { 
    next = nullptr;
    data = nullptr;
}

LLNode::LLNode(Vertex *newVertex) {
    data = newVertex;
    next = nullptr;
}

LLNode::~LLNode() {
    //delete data;
    data = nullptr;
    //delete next;
    next = nullptr;
}