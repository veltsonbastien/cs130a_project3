#include "avlTree.h"
#include <iostream>
#include <cstdlib> 

using namespace std; 


//Constructors
AVLTree::AVLTree() : root(0) {
    cout <<"hi"<<endl;
} 
AVLTree::AVLTree(int k) {
    root = nullptr;
    this->k = k; 
}

//Destructor 
//AVLTree::~AVLTree(){}

//Utilities: 

bool AVLTree::balanceCheck(Node* n){ 
 if(n == root) return true; 
 return 0;


} //end of balance check

void AVLTree::rotateLeft(Node* n){}

void AVLTree::rotateRight(Node* n){ }

AVLTree::Node* AVLTree::getSuccessorNode(Node* n){ return 0; }

AVLTree::Node* AVLTree::getPredecessorNode(Node* n){ return 0; }

double AVLTree::numify(int a, int b){
    cout<<"NUMFIED: "<<(a*10) + (b*1)<<endl;
    return (a*10) + (b*1); 
}

//Searches: 
bool AVLTree::approx_search(int a, int b){
 if(!root){
   cout<<"for dev purposes: tree is empty"<<endl;
 }
 return approx_searcher(a, b, root); 
}

//Recursive helper for approx_search
AVLTree::Node* AVLTree::approx_searcher(int a, int b, Node* n){
 if(a == n->a && b == n->b){
     cout<<a<<"."<<b<<" is equal to "<<n->a<<"."<<n->b<<endl;
     cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
     return n; 
 }

 cout<<"Number we are working with: "<<a<<"."<<b<<endl; 
 cout<<"Current number at node: "<<n->a<<"."<<n->b<<endl;

 if(a == n->a ){
   cout<<"The whole number part is equal to what we find here"<<endl;
   if(b < n->b){
       cout << "the fraction part is smaller so we go to the left"<<endl;
       if(n->left){
           cout<<"there was a node there so we continued the check there"<<endl;
           return approx_searcher (a, b, n->left); 
       } else{
        cout<<"the left child was empty, so wecheck which it's closest to: parent, or parent's parent"<<endl;
        if(n->parent){
             cout<<"there is a parent, so we check the distances"<<endl;
             int differenceBetweenCurrent = abs( numify(n->a, n->b) - numify(a,b)  ); 
             int differenceBetweenParent =  abs( numify(n->parent->a, n->parent->b) - numify(a,b) ); 
             cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
             return (differenceBetweenCurrent <= differenceBetweenParent) ? n: n->parent;
         } 
         cout<<"there was no parent, so we just return the current"<<endl; 
         cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
        return n; 
       }
   } else {
     cout<<"the fraction part is bigger so we go to the right"<<endl;
     if(n->right){
         cout << "there was a node there so we continued the check there"<<endl; 
         return approx_searcher (a, b, n->right); 
     } else{
         cout << "the right child was empty, so we check which it's closest to: parent, or parent's parent"<<endl; 
         if(n->parent){
             cout<<"there is a parent, so we check the distances"<<endl;
             int differenceBetweenCurrent = abs( numify(n->a, n->b) - numify(a,b)  ); 
             int differenceBetweenParent =  abs( numify(n->parent->a, n->parent->b) - numify(a,b) ); 
             cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
             return (differenceBetweenCurrent <= differenceBetweenParent) ? n: n->parent;
         } 
         cout<<"there was no parent, so we just return the current"<<endl; 
         cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
         return n; 
     }
   } 
 } else {
    
        if(a < n->a){
                cout << "the whole  part is smaller so we go to the left"<<endl;
            if(n->left){
                cout<<"there was a node there so we continued the check there"<<endl;
                return approx_searcher (a, b, n->left); 
            } else{
                cout<<"the left child was empty, so wecheck which it's closest to: parent, or parent's parent"<<endl;
                if(n->parent){
                    cout<<"there is a parent, so we check the distances"<<endl;
                    int differenceBetweenCurrent = abs( numify(n->a, n->b) - numify(a,b)  ); 
                    int differenceBetweenParent =  abs( numify(n->parent->a, n->parent->b) - numify(a,b) ); 
                    if(differenceBetweenCurrent <= differenceBetweenParent) cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
                    else{cout<<"closest to "<<a<<"."<<b<<" is "<<n->parent->a<<"."<<n->parent->b<<endl<<endl; }
                    
                    return (differenceBetweenCurrent <= differenceBetweenParent) ? n: n->parent;
                } 
                cout<<"there was no parent, so we just return the current"<<endl; 
                cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
                return n; 
            }  
        } else{
            cout<<"the whole part is bigger so we go to the right"<<endl;
            if(n->right){
                cout << "there was a node there so we continued the check there"<<endl; 
                return approx_searcher (a, b, n->right); 
            } else{
                cout << "the right child was empty, so we check which it's closest to: parent, or parent's parent"<<endl; 
                if(n->parent){
                    cout<<"there is a parent, so we check the distances"<<endl;
                    int differenceBetweenCurrent = abs( numify(n->a, n->b) - numify(a,b)  ); 
                    int differenceBetweenParent =  abs( numify(n->parent->a, n->parent->b) - numify(a,b) );  
                    if(differenceBetweenCurrent <= differenceBetweenParent) cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
                    else{cout<<"closest to "<<a<<"."<<b<<" is "<<n->parent->a<<"."<<n->parent->b<<endl<<endl; }
                    
                    return (differenceBetweenCurrent <= differenceBetweenParent) ? n: n->parent;
                } 
                cout<<"there was no parent, so we just return the current"<<endl; 
                cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
                return n; 
            }     
        }
    }
}

//Search 

bool AVLTree::search(int a, int b){
    if(!root){
        return false; 
    }
    return searcher(a, b, root);
}

AVLTree::Node* AVLTree::searcher(int a, int b, Node* n){
  //first run an approx search 
  cout<<"Currently in Search, first running an approx search and save that to a temp"<<endl; 
  Node* temp = approx_searcher(a, b, n); 
  if(temp->a == a & temp->b == b){
      cout<<a<<"."<<b<<" found"<<endl;
      return temp; 
  } 
  cout<<a<<"."<<b<<" not found"<<endl;
  return 0; 
} 

//Insert value
bool AVLTree::insert(int a, int b){ 
    //if root is null, set this to value to root 
    if(!root){
        root = new Node (a, b); 
        cout<<a<<"."<<b<<" inserted"<<endl;
        return true; 
    }
    return balanceCheck(insert(a, b, root)); 
}

//Recursive Helper for insert 
AVLTree::Node* AVLTree::insert(int a, int b, Node* n){
 if(a == n->a && b == n->b){
     cout<<a<<"."<<b<<" is equal to "<<n->a<<"."<<n->b<<endl;
     return 0; 
 }

 cout<<"Number we are working with: "<<a<<"."<<b<<endl; 
 cout<<"Current number at node: "<<n->a<<"."<<n->b<<endl;

 if(a == n->a ){
   cout<<"The whole number part is equal to what we find here"<<endl;
   if(b < n->b){
       cout << "the fraction part is smaller so we go to the left"<<endl;
       if(n->left){
           cout<<"there was a node there so we continued the check there"<<endl;
           return insert (a, b, n->left); 
       } else{
           cout<<"the left child was empty, so we insert here"<<endl;
           n->left = new Node (a, b); 
           n->left->parent = n; 
           cout<<a<<"."<<b<<" inserted"<<endl;
           return n;  
       }
   } else {
     cout<<"the fraction part is bigger so we go to the right"<<endl;
     if(n->right){
         cout << "there was a node there so we continued the check there"<<endl; 
         return insert (a, b, n->right); 
     } else{
         n->right = new Node (a, b); 
         n->right->parent = n;
         cout<<a<<"."<<b<<" inserted"<<endl;
         return n; 
     }
   } 
 } else {
    
        if(a < n->a){
                cout << "the whole  part is smaller so we go to the left"<<endl;
            if(n->left){
                cout<<"there was a node there so we continued the check there"<<endl;
                return insert (a, b, n->left); 
            } else{
                cout<<"the left child was empty, so we added it here"<<endl;
                n->left = new Node (a, b);
                n->left->parent = n;
                cout<<a<<"."<<b<<" inserted"<<endl;
                return n; 
            }  
        } else{
            cout<<"the whole part is bigger so we go to the right"<<endl;
            if(n->right){
                cout << "there was a node there so we continued the check there"<<endl; 
                return insert (a, b, n->right); 
            } else{
                cout << "the right child was empty, so we added it here"<<endl; 
                n->right = new Node (a, b);
                n->right->parent = n;
                cout<<a<<"."<<b<<" inserted"<<endl;
                return n; 
            }     
        }
    }

} //end of insert function 

//Recursive helper for destructor 
bool AVLTree::remove(int a, int b){ return 0;  }

//Prints: 
void AVLTree::in_order(){}
void AVLTree::pre_order(){}
