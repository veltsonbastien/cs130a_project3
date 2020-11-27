#ifndef AVLTREE_H
#define AVLTREE_H 


using namespace std; 

class AVLTree{
 public: 
 AVLTree();      //constructor 
 AVLTree(int k); //constructor taking k as a parameter 
 ~AVLTree();     //destructor 
 
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
        Node(int v = 0): a(0), b(0), parent(0), left(0), right(0) {}
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