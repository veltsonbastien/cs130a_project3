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

//Prints: 
void AVLTree::in_order(){
  if(!root) return; 
  in_order(root); 
  cout<<endl;
}

void AVLTree::in_order(Node* n){
 if(n->left) in_order(n->left);
 cout<<n->a<<"."<<n->b<<" "; 
 if(n->right) in_order(n->right);
}

void AVLTree::pre_order(){
 if(!root){
cout<<"no root"<<endl;
 return; 
 }  
 pre_order(root); 
 cout<<endl; 
}

void AVLTree::pre_order(Node* n){
 if(n){
    cout<<n->a<<"."<<n->b<<" "; 
    pre_order(n->left); 
    pre_order(n->right); 
   }
}


void AVLTree::rotateLeft(Node* problemNode){
    Node* temp = problemNode;           //make a copy of problem node 

    //If not Root:
    if(problemNode->parent){   //that means it is a root cause there is no parent 
        problemNode->parent->left = problemNode->left;   //set problem node parent left to problem node left
        problemNode->left->parent = problemNode->parent; //set the problem node left parent to the problem node's parent 
        if(problemNode->right->left){                    //if the problem node's right child has a left child, it needs to get adopted 
         problemNode->right = problemNode->right->left;  //set problem node's right to child that needs to be adopted
         problemNode->right->parent = problemNode;       //adopted child has new parent as problem node 
         problemNode->left->right = nullptr;             //problem node left child loses affiliation with child it gave up
         problemNode->left = nullptr;                    //problem node loses any connection to any left child 
         pre_order(); //do a preorder print to check
         return; //done rotating
        } else{                                          //if no child to adopt,
         problemNode->parent->left = problemNode->left;  //set the problem node parent's left child to problem node's left child 
         problemNode->left->parent = problemNode->parent;//set the problem node left's parent to the problem node's parent 
         problemNode->parent = problemNode->left;        //set problem node's parent to the problem node's old left  child 
         problemNode->left = nullptr;                    //problem node loses affiliation with left child 
         problemNode->right = nullptr;                   //problem node loses affiliation with right child
         pre_order(); //do a preorder print to check
         return; //done rotating
        }
    }

    //IF ROOT:
        cout<<"Rotating Root to the LEFT"<<endl; 
        if(problemNode->right->left){                     //problem node right child had a left child that needs to be adopted
        problemNode->right->left->parent = problemNode; //problem node becomes the new parent of the adopted node 
        problemNode->right = problemNode->right->left;  //problem node right child is equal to child that needs to be adopted
        problemNode->right->left = nullptr;             //problem node's right child gives up left child to adoption
        pre_order(); //do a preorder print to check
        return; //done with rotation
        } else{                                          //if no child needs to be adopted
        problemNode->right->left = new Node();          //no node there yet 
        problemNode->right->left = problemNode;         //problem node left child's right child becomes problem node
        problemNode->parent = problemNode->left;        //problem node's parent becomes it's old left child 
        root = problemNode->left;                       //new root becomes the problem node on the left 
        problemNode->left = nullptr;                    //problemNode's left becomes a nullptr
        problemNode->right = nullptr;                   //problemNode's right also becomes a nullptr
        pre_order(); //do a preorder print to check
        return; //done with rotation
        }

}

void AVLTree::rotateRight(Node* problemNode){
    
    //If not Root:
    if(problemNode->parent){   //that means it is a root cause there is no parent 
        problemNode->parent->right = problemNode->right;   //set problem node parent right to problem node right
        problemNode->right->parent = problemNode->parent; //set the problem node right parent to the problem node's parent 
        if(problemNode->left->right){                    //if the problem node's left child has a right child, it needs to get adopted 
         problemNode->left = problemNode->left->right;  //set problem node's left to child that needs to be adopted
         problemNode->left->parent = problemNode;       //adopted child has new parent as problem node 
         problemNode->right->left = nullptr;             //problem node right child loses affiliation with child it gave up
         problemNode->right = nullptr;                    //problem node loses any connection to any right child 
         pre_order(); //do a preorder print to check
         return; //done rotating
        } else{                                          //if no child to adopt,
         problemNode->parent->right = problemNode->right;  //set the problem node parent's right child to problem node's right child 
         problemNode->right->parent = problemNode->parent;//set the problem node right's parent to the problem node's parent 
         problemNode->parent = problemNode->right;        //set problem node's parent to the problem node's old right  child 
         problemNode->left = nullptr;                    //problem node loses affiliation with left child 
         problemNode->right = nullptr;                   //problem node loses affiliation with right child
         pre_order(); //do a preorder print to check
         return; //done rotating
        }
    }

    //IF ROOT:
        cout<<"Rotating Root to the RIGHT"<<endl; 
        if(problemNode->left->right){                     //problem node left child had a right child that needs to be adopted
        problemNode->left->right->parent = problemNode;   //problem node becomes the new parent of the adopted node 
        problemNode->left = problemNode->left->right;     //adopted child's parent becomes problem node
        problemNode->left->right = nullptr;               //problem node left loses afilition with the left child 
        problemNode->parent = problemNode->left;          //problem node's parent becomes it's old left child 
        root = problemNode->left;                         //new root becomes the problem node on the left 
        problemNode->right = nullptr;                     //problem node loses affiliation with right child   
        problemNode->left->right = nullptr;             //problem node's left child gives up right child to adoption
        pre_order(); //do a preorder print to check
        return; //done with rotation
        } else{                                          //if no child needs to be adopted
        problemNode->left->right = new Node();          //create a new node at that area
        problemNode->left->right = problemNode;         //problem node right child's left child becomes problem node
        problemNode->parent = problemNode->left;        //problem node's parent becomes it's old right child 
        root = problemNode->left;                       //new root becomes the problem node on the left 
        problemNode->left = nullptr;                    //problemNode's left becomes a nullptr
        problemNode->right = nullptr;                   //problemNode's right also becomes a nullptr
        pre_order(); //do a preorder print to check
        return; //done with rotation
        }
 }


int AVLTree::getHeight(Node* n){
 if(n == nullptr) return 0; 
 if(n->left == nullptr && n->right== nullptr) return 1; 
    
 if(n->right){
     return 1+getHeight(n->right); 
 }

 if(n->left){
     return 1+getHeight(n->left); 
 }
 
 return 0; 
}

bool AVLTree::balanceCheck(Node* n){ 

if(n == root){
     cout<<"THIS K: "<<this->k<<endl;
    int leftHeight = getHeight(n->left);
    int rightHeight = getHeight(n->right); 
    cout<<"Checking heights at "<<n->a<<"."<<n->b<<endl;
    cout<<"Left Height: "<<leftHeight<<endl;
    cout<<"Right Height: "<<rightHeight<<endl;
     if( abs(leftHeight - rightHeight) <= this->k ){
        cout<<"property not broken"<<endl<<endl;
        return true;
     } else if (leftHeight > rightHeight){
        cout<<"PROPERTY BROKEN: Left side is heavier, doing a rotation to the right"<<endl<<endl; 
        rotateRight(n); 
        return balanceCheck(n->parent); 
        } 
        cout<<"PROPERTY BROKEN: Left side is heavier, doing a rotation to the right"<<endl<<endl; 
        rotateLeft(n); 
        return balanceCheck(n->parent); 
 }

 cout<<"THIS K: "<<this->k<<endl;
 int leftHeight = getHeight(n->left);
 int rightHeight = getHeight(n->right); 
 cout<<"Checking heights at "<<n->a<<"."<<n->b<<endl;
 cout<<"Left Height: "<<leftHeight<<endl;
 cout<<"Right Height: "<<rightHeight<<endl;

 if( abs(leftHeight - rightHeight) <= this->k ){
   cout<<"property not broken"<<endl<<endl;
   return balanceCheck(n->parent); 
 } else if (leftHeight > rightHeight){
   cout<<"PROPERTY BROKEN: Left side is heavier, doing a rotation to the right"<<endl<<endl; 
   rotateRight(n); 
   return balanceCheck(n->parent); 
 } 
   cout<<"PROPERTY BROKEN: Left side is heavier, doing a rotation to the right"<<endl<<endl; 
   rotateLeft(n); 
   return balanceCheck(n->parent); 
} //end of balance check

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
        cout<<a<<"."<<b<<" inserted"<<endl<<endl;
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
           cout<<a<<"."<<b<<" inserted"<<endl<<endl;
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
         cout<<a<<"."<<b<<" inserted"<<endl<<endl;
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
                cout<<a<<"."<<b<<" inserted"<<endl<<endl;
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
                cout<<a<<"."<<b<<" inserted"<<endl<<endl;
                return n; 
            }     
        }
    }

} //end of insert function 

//Recursive helper for destructor 
bool AVLTree::remove(int a, int b){ return 0;  }

