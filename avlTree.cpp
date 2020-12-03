#include "avlTree.h"
#include <iostream>
#include <cstdlib> 

using namespace std; 


//Constructors
AVLTree::AVLTree() : root(0) {

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
 if(!root){ //cout<<"NO ROOT!"<<endl; 
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
    Node*& rightNode = problemNode->right;      //make a copy of the right node 
    Node*  rightNodeTemp = problemNode->right;  
    //If not Root:
    if(problemNode->parent){ 
        Node*& problemParent = problemNode->parent;                                           //set problem node parent temp
        if(problemParent->left == problemNode) problemParent->left = rightNode;               //set problem node parent LEFT to problem node left
        else problemParent->right = rightNode;                                         //set problem node parent RIGHT  to problem node left 
        rightNode->parent = problemParent;                    //set the problem node right parent to the problem node's parent
        if(rightNode->left){                                  //if the problem node's right child has a left child, it needs to get adopted 
            Node*& childToAdopt = rightNode->left;            //create a ref. for the child to adopt
            childToAdopt->parent = problemNode;              //set the adopted child's parent to the problem node 
            problemNode->right = childToAdopt;                //set the problem Node right to the child to adopt
            problemNode->parent =  rightNode;                //set the problem node's parent to the problem node's right child 
            rightNode->left = problemNode;                   //set the right node's left to problem node
            //pre_order(); //do a preorder print to check
           // cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done rotating
        } else{                                          //if no child to adopt,
            problemNode->right = nullptr;                   //problem node's right becomes nullptr because there's no child to adopt
            problemNode->parent = rightNode;                //problem node's parent becomes right node 
            //pre_order(); //do a preorder print to check
           // cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done rotating
        }
  
    }

    //IF ROOT:
        //cout<<"Rotating Root to the LEFT"<<endl; 
        if(rightNode->left){                                //problem node right child had a left child that needs to be adopted
            Node*& childToAdopt = rightNode->left;          //set a temp variable for child to adopt 
            childToAdopt->parent = problemNode;             //problem node becomes the new parent of the adopted node 
            problemNode->right = childToAdopt;              //problem node right child is equal to child that needs to be adopted
            problemNode->parent = new Node();               //create a new node for parent cause it used to be root and there was no parent
            problemNode->parent = rightNode;                //problem node parent becomes right node
            rightNode->left = problemNode;                  //right node's left becomes problemNode
            rightNode->parent = nullptr;                    //right node's parent becomes a nullptr because it is the new root 
            root = rightNodeTemp;                               //set right node to the new root 
           //pre_order(); //do a preorder print to check
            //cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done with rotation
        } else{                                             //if no child needs to be adopted
            rightNode->parent = nullptr;                    //right node's parent is nullptr because it becomes the new root 
            rightNode->left = problemNode;                  //right node's left becomes the problem node 
            problemNode->parent = new Node();               //create a new node for parent cause it used to be root and there was no parent 
            problemNode->parent = rightNode;              //problem node's parent becomes right node 
            problemNode->right = nullptr;                   //get rid of any connection problem node had to the right 
            root = rightNodeTemp;
          //  pre_order(); //do a preorder print to check
          //  cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done with rotation
        }

}

void AVLTree::rotateRight(Node* problemNode){
    Node*& leftNode = problemNode->left;      //make a copy of the right node 
    Node* leftNodeTemp = problemNode->left;
    //If not Root:
    if(problemNode->parent){ 
        Node*& problemParent = problemNode->parent;                                           //set problem node parent temp
        if(problemParent->left == problemNode) problemParent->left = leftNode;               //set problem node parent LEFT to problem node left
        else problemParent->right = leftNode;                                         //set problem node parent RIGHT  to problem node left 
        leftNode->parent = problemParent;                    //set the problem node right parent to the problem node's parent
        if(leftNode->right){                                  //if the problem node's left child has a right child, it needs to get adopted 
            Node*& childToAdopt = leftNode->right;            //create a ref. for the child to adopt
            childToAdopt->parent = problemNode;              //set the adopted child's parent to the problem node 
            problemNode->left = childToAdopt;                //set the problem Node left to the child to adopt
            problemNode->parent =  leftNode;                //set the problem node's parent to the problem node's left child 
            leftNode->right = problemNode;                   //set the left node's right to problem node
           // pre_order(); //do a preorder print to check
           // cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done rotating
        } else{                                          //if no child to adopt,
            problemNode->left = nullptr;                   //problem node's left becomes nullptr because there's no child to adopt
            problemNode->parent = leftNode;                //problem node's parent becomes right node 
           // pre_order(); //do a preorder print to check
           // cout<<"ROTATION FINISHED"<<endl<<endl;
         return; //done rotating
        }
  
    }

    //IF ROOT:
       // cout<<"Rotating Root to the RIGHT"<<endl; 
        if(leftNode->right){                                //problem node left child had a right child that needs to be adopted
            Node*& childToAdopt = leftNode->right;          //set a temp variable for child to adopt 
            childToAdopt->parent = problemNode;             //problem node becomes the new parent of the adopted node 
            problemNode->left = childToAdopt;              //problem node left child is equal to child that needs to be adopted
            problemNode->parent = new Node();               //create a new node for parent cause it used to be root and there was no parent
            problemNode->parent = leftNode;                //problem node parent becomes left node
            leftNode->right = problemNode;                  //left node's right become a nullptr cause problem node adopted it on it's right 
            leftNode->parent = nullptr;                    //left node's parent becomes a nullptr because it is the new root 
            root = leftNodeTemp;                               //set left node to the new root 
           // pre_order(); //do a preorder print to check
           // cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done with rotation
        } else{                                             //if no child needs to be adopted
            leftNode->parent = nullptr;                    //left node's parent is nullptr because it becomes the new root 
            leftNode->right = problemNode;                  //left node's right becomes the problem node 
            problemNode->parent = new Node();               //create a new node for parent cause it used to be root and there was no parent 
            problemNode->parent = leftNode;                //problem node's parent becomes left node 
            problemNode->left = nullptr;                   //get rid of any connection problem node had to the left 
            root = leftNodeTemp;                               //set left node to the new root
           // if(root){cout<<"hi, there's a root after i set the root"<<endl;}
           // pre_order(); //do a preorder print to check
           // cout<<"ROTATION FINISHED"<<endl<<endl;
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

       if(!n) return false; 

        int leftHeight = getHeight(n->left);
        int rightHeight = getHeight(n->right); 
        //cout<<"Checking heights at "<<n->a<<"."<<n->b<<endl;
        //cout<<"Left Height: "<<leftHeight<<endl;
       // cout<<"Right Height: "<<rightHeight<<endl;

        if(n == root){
            if( abs(leftHeight - rightHeight) <= this->k ){
                //cout<<"PROPERTY NOT BROKEN at ROOT"<<endl<<endl;
                //pre_order(); 
                return true; //this is where you force it to stop
            } else if (leftHeight > rightHeight){
               // cout<<"PROPERTY BROKEN at ROOT: Left side is heavier, doing a root rotation to the right"<<endl<<endl; 
                rotateRight(n); 
                return balanceCheck(n); 
            } 
               // cout<<"PROPERTY BROKEN at ROOT: Right side is heavier, doing a root rotation to the left"<<endl<<endl; 
                rotateLeft(n); 
                return balanceCheck(n); 
        }

        if( abs(leftHeight - rightHeight) <= this->k ){
       // cout<<"PROPERTY NOT BROKEN"<<endl<<endl;
        return balanceCheck(n->parent); 
        } else if (leftHeight > rightHeight){
       // cout<<"PROPERTY BROKEN: Left side is heavier, doing a rotation to the right"<<endl<<endl; 
        rotateRight(n); 
        return balanceCheck(n->parent); 
        } 
        //cout<<"PROPERTY BROKEN: Right side is heavier, doing a rotation to the left"<<endl<<endl; 
        rotateLeft(n); 
        return balanceCheck(n->parent); 
} //end of balance check


double AVLTree::numify(int a, int b){
    //cout<<"NUMFIED: "<<(a*10) + (b*1)<<endl;
    return (a*10) + (b*1); 
}

//Searches: 
bool AVLTree::approx_search(int a, int b){
 if(!root){
   //cout<<"for dev purposes: tree is empty"<<endl;
   return 0; 
 }
 return approx_searcher(a, b, root); 
}

//Recursive helper for approx_search
AVLTree::Node* AVLTree::approx_searcher(int a, int b, Node* n){
 if(a == n->a && b == n->b){
     //cout<<a<<"."<<b<<" is equal to "<<n->a<<"."<<n->b<<endl;
    // cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
     return n; 
 }

 //cout<<"Number we are working with: "<<a<<"."<<b<<endl; 
 //cout<<"Current number at node: "<<n->a<<"."<<n->b<<endl;

 if(a == n->a ){
  // cout<<"The whole number part is equal to what we find here"<<endl;
   if(b < n->b){
      // cout << "the fraction part is smaller so we go to the left"<<endl;
       if(n->left){
        //   cout<<"there was a node there so we continued the check there"<<endl;
           return approx_searcher (a, b, n->left); 
       } else{
        //cout<<"the left child was empty, so wecheck which it's closest to: parent, or parent's parent"<<endl;
        if(n->parent){
            // cout<<"there is a parent, so we check the distances"<<endl;
             int differenceBetweenCurrent = abs( numify(n->a, n->b) - numify(a,b)  ); 
             int differenceBetweenParent =  abs( numify(n->parent->a, n->parent->b) - numify(a,b) ); 
            // cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
             return (differenceBetweenCurrent <= differenceBetweenParent) ? n: n->parent;
         } 
        // cout<<"there was no parent, so we just return the current"<<endl; 
        // cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
        return n; 
       }
   } else {
     //cout<<"the fraction part is bigger so we go to the right"<<endl;
     if(n->right){
         //cout << "there was a node there so we continued the check there"<<endl; 
         return approx_searcher (a, b, n->right); 
     } else{
         //cout << "the right child was empty, so we check which it's closest to: parent, or parent's parent"<<endl; 
         if(n->parent){
             //cout<<"there is a parent, so we check the distances"<<endl;
             int differenceBetweenCurrent = abs( numify(n->a, n->b) - numify(a,b)  ); 
             int differenceBetweenParent =  abs( numify(n->parent->a, n->parent->b) - numify(a,b) ); 
             //cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
             return (differenceBetweenCurrent <= differenceBetweenParent) ? n: n->parent;
         } 
         //cout<<"there was no parent, so we just return the current"<<endl; 
         //cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
         return n; 
     }
   } 
 } else {
    
        if(a < n->a){
               // cout << "the whole  part is smaller so we go to the left"<<endl;
            if(n->left){
               // cout<<"there was a node there so we continued the check there"<<endl;
                return approx_searcher (a, b, n->left); 
            } else{
                //cout<<"the left child was empty, so wecheck which it's closest to: parent, or parent's parent"<<endl;
                if(n->parent){
                    cout<<"there is a parent, so we check the distances"<<endl;
                    int differenceBetweenCurrent = abs( numify(n->a, n->b) - numify(a,b)  ); 
                    int differenceBetweenParent =  abs( numify(n->parent->a, n->parent->b) - numify(a,b) ); 
                    if(differenceBetweenCurrent <= differenceBetweenParent) cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
                    else{cout<<"closest to "<<a<<"."<<b<<" is "<<n->parent->a<<"."<<n->parent->b<<endl<<endl; }
                    
                    return (differenceBetweenCurrent <= differenceBetweenParent) ? n: n->parent;
                } 
                //cout<<"there was no parent, so we just return the current"<<endl; 
                //cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
                return n; 
            }  
        } else{
            //cout<<"the whole part is bigger so we go to the right"<<endl;
            if(n->right){
               // cout << "there was a node there so we continued the check there"<<endl; 
                return approx_searcher (a, b, n->right); 
            } else{
               // cout << "the right child was empty, so we check which it's closest to: parent, or parent's parent"<<endl; 
                if(n->parent){
                   //cout<<"there is a parent, so we check the distances"<<endl;
                    int differenceBetweenCurrent = abs( numify(n->a, n->b) - numify(a,b)  ); 
                    int differenceBetweenParent =  abs( numify(n->parent->a, n->parent->b) - numify(a,b) );  
                    if(differenceBetweenCurrent <= differenceBetweenParent) cout<<"closest to "<<a<<"."<<b<<" is "<<n->a<<"."<<n->b<<endl<<endl;
                    else{ cout<<"closest to "<<a<<"."<<b<<" is "<<n->parent->a<<"."<<n->parent->b<<endl<<endl; }
                    
                    return (differenceBetweenCurrent <= differenceBetweenParent) ? n: n->parent;
                } 
                //cout<<"there was no parent, so we just return the current"<<endl; 
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
  //cout<<"Currently in Search, first running an approx search and save that to a temp"<<endl; 
  Node* temp = approx_searcher(a, b, n); 
  if(temp->a == a & temp->b == b){
      cout<<a<<"."<<b<<" found"<<endl;
      return temp; 
  } 
  cout<<a<<"."<<b<<" not found"<<endl;
  return nullptr; 
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
    // cout<<a<<"."<<b<<" is equal to "<<n->a<<"."<<n->b<<endl;
     return 0; 
 }

 //cout<<"Number we are working with: "<<a<<"."<<b<<endl; 
// cout<<"Current number at node: "<<n->a<<"."<<n->b<<endl;

 if(a == n->a ){
   //cout<<"The whole number part is equal to what we find here"<<endl;
   if(b < n->b){
      // cout << "the fraction part is smaller so we go to the left"<<endl;
       if(n->left){
        //   cout<<"there was a node there so we continued the check there"<<endl;
           return insert (a, b, n->left); 
       } else{
         //  cout<<"the left child was empty, so we insert here"<<endl;
           n->left = new Node (a, b); 
           n->left->parent = n; 
           cout<<a<<"."<<b<<" inserted"<<endl;
           return n;  
       }
   } else {
    // cout<<"the fraction part is bigger so we go to the right"<<endl;
     if(n->right){
        // cout << "there was a node there so we continued the check there"<<endl; 
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
               // cout << "the whole  part is smaller so we go to the left"<<endl;
            if(n->left){
                //cout<<"there was a node there so we continued the check there"<<endl;
                return insert (a, b, n->left); 
            } else{
                //cout<<"the left child was empty, so we added it here"<<endl;
                n->left = new Node (a, b);
                n->left->parent = n;
                cout<<a<<"."<<b<<" inserted"<<endl;
                return n; 
            }  
        } else{
          //  cout<<"the whole part is bigger so we go to the right"<<endl;
            if(n->right){
               // cout << "there was a node there so we continued the check there"<<endl; 
                return insert (a, b, n->right); 
            } else{
               // cout << "the right child was empty, so we added it here"<<endl; 
                n->right = new Node (a, b);
                n->right->parent = n;
                cout<<a<<"."<<b<<" inserted"<<endl;
                return n; 
            }     
        }
    }

} //end of insert function 

//get successor
AVLTree::Node* AVLTree::getSuccessor(Node* n){
    Node* temp = 0; 
    if(n->right != nullptr){
        temp = n->right; 
        while(temp->left != nullptr){
        temp = temp->left; 
        }//end of while 
        return temp; 
    } else{
        Node* temp2 = root; 
	    while(temp2->a != n->a && temp2->b != n->b){
            if( numify(n->a, n->b) <= numify(temp2->a, temp2->b)){
                temp = temp2; 
                temp2 = temp2->left; 
            }//end of if check 
            else{
                temp2 = temp2->right;
            }
	    }//end of second while 
        return temp; 	
      }
      return root;  
}

//remove function 
bool AVLTree::remove(int a, int b){
 if(!root) return false; 
 return 0; 
 //return balanceCheck(remove(a, b, approx_searcher(a,b,root))); 
}

//recursive function for remove
// AVLTree::Node* AVLTree::remove(int a, int b, Node* n){
//     if(a == n->a && b == n->b){ //it's the node, so we proceed to delete
//      Node* temp = getSuccessor(n); 
//      if(n->parent){ //it's not the root 
//       if(n->parent->left == n) n->parent->left = temp; 
//       else { n->parent->right = temp; }
//      }
//      temp->parent = n->parent; 
//      //delete everything in n: 
//      n->parent = nullptr; 
//      n->left = nullptr; 
//      n->right = nullptr; 
//      delete n; 

//      //return the temp node 
//      return temp; 
//     }
//     return nullptr;
// }

