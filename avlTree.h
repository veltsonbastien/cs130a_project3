#ifndef AVLTREE_H
#define AVLTREE_H 

//#include <iostream>
//using namespace std; 

class AVLTree{
 public: 
 AVLTree();      //constructor 
 AVLTree(int k); //constructor taking k as a parameter 
 //~AVLTree();     //destructor 
 
 //Method Functions: 
 bool search(int a, int b);  
 void approx_search(int a, int b); 
 bool insert(int a, int b); 
 bool remove(int a, int b); 
 void in_order(); 
 void pre_order(); 
 
 private: 

    struct Node{
        int a; //whole value 
        int b; //fraction value 
        Node *parent, *right, *left; 
        Node(int whole, int fraction) {
            a = whole; 
            b = fraction;
            parent = nullptr;
            right = nullptr;
            left = nullptr;
        }
    }; 

    //Private Member variables: 
    Node* root;
    int k; //the k that is passed in 

    //Other Utility Functions:
    bool balanceCheck(Node* n);
    void rotateLeft(Node* problemNode); 
    void rotateRight(Node* problemNode); 
    Node* getSuccessorNode(Node* n); 
    Node* getPredecessorNode(Node* n); 
 

}; 

#endif