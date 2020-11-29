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
 bool insert(int a, int b);
 bool search(int a, int b); 
 bool approx_search(int a, int b); 
 bool remove(int a, int b); 
 void in_order(); 
 void pre_order(); 
 
 //Public utility
 double numify(int a, int b);

 private: 

    struct Node{
        int a; //whole value 
        int b; //fraction value 
        Node *parent, *right, *left; 
        //int leftheight; //height on the left
       // int rightheight; //height on the right
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
    Node* searcher(int a, int b, Node* n);  
    Node* approx_searcher(int a, int b, Node* n);
    Node* insert(int a, int b, Node* n);
    Node* getSuccessorNode(Node* n); 
    Node* getPredecessorNode(Node* n); 

}; 

#endif