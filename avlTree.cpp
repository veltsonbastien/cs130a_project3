#include "avlTree.h"
#include <iostream>

using namespace std; 



//Constructors
AVLTree::AVLTree() : root(0) {} 
AVLTree::AVLTree(int k) {
    root = nullptr;
    this->k = k; 
}


//Destructor 
//AVLTree::~AVLTree(){}

//Recursive helper for destructor 
bool AVLTree::remove(int a, int b){ return 0;  }

bool AVLTree::insert(int a, int b){ 
    //if root is null, set this to value to root 
    if(!root){
        root = new Node (a, b); 
        cout<<a<<"."<<b<<" inserted"<<endl;
        return true; 
    }
    return 0; 
}

//Searches: 
bool AVLTree::search(int a, int b){ return 0; } 
void AVLTree::approx_search(int a, int b){ }

//Prints: 
void AVLTree::in_order(){}
void AVLTree::pre_order(){}

//Utilities: 

bool AVLTree::balanceCheck(Node* n){ return 0; }

void AVLTree::rotateLeft(Node* n){}

void AVLTree::rotateRight(Node* n){ }

AVLTree::Node* AVLTree::getSuccessorNode(Node* n){ }

AVLTree::Node* AVLTree::getPredecessorNode(Node* n){ }