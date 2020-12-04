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

void AVLTree::printNode(Node* n){
    cout<<"******************"<<endl;
    if(!n){cout<<"NODE IS NULL!"<<endl; return;}
    cout<<"NODE IS: "<<n->a<<"."<<n->b<<endl; 
    if(n->parent) cout<<"NODE's PARENT IS: "<<n->parent->a<<"."<<n->parent->b<<endl; 
    else cout<<"NODE DOESN'T HAVE A PARENT"<<endl;
    if(n->left) cout<<"NODE's LEFT IS: "<<n->left->a<<"."<<n->left->b<<endl; 
    else cout<<"NODE DOESN'T HAVE A LEFT"<<endl;
    if(n->right) cout<<"NODE's RIGHT IS: "<<n->right->a<<"."<<n->right->b<<endl; 
    else cout<<"NODE DOESN'T HAVE A RIGHT"<<endl;
    cout<<"******************"<<endl;
}

//Prints: 
void AVLTree::in_order(){
  if(!root) return; 
  in_order(root); 
  cout<<endl;
}

void AVLTree::in_order(Node* n){
 if(n->left) {in_order(n->left); cout<<" "; }
 cout<<n->a<<"."<<n->b;
 if(n->right){ cout<<" "; in_order(n->right); }
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
    if(n==root) cout<<n->a<<"."<<n->b; 
    else{cout<<" "<<n->a<<"."<<n->b;}
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
                                                                                              //check for Double Rotation:                                                                                    
        if( (rightNodeTemp->left !=nullptr || rightNodeTemp->right != nullptr)                //If either or isn't null continue checking 
        && (
            (rightNodeTemp->left != nullptr && rightNodeTemp->right != nullptr                //if the left and the right one aren't null 
             && (getHeight(rightNodeTemp->left) > getHeight(rightNodeTemp->right)))           //and the left is bigger than the right, there's a double rotation
        || (rightNodeTemp->left !=nullptr && rightNode->right == nullptr))                    // or if the left one isn't null but the right one is
        ){            

        Node* rightLeftNodeTemp = problemNode->right->left;        //set a node copy for the right left node, it'll become the new "root" of this mini tree
        Node* rlnAdoptChildRight = nullptr;                        //child to adopt on the right (in the case of k>1 ) 
        Node* rlnAdoptChildLeft = nullptr;                         //child to adopt on the left  (in the case of k>1 )
                                                                                                              //set the the parent's right to the right left node 
        if(problemParent->left == problemNode) problemParent->left = rightLeftNodeTemp;               //set problem node parent LEFT to problem node left
        else problemParent->right = rightLeftNodeTemp;                                         //set problem node parent RIGHT  to problem node left 
        rightLeftNodeTemp->parent = problemParent;                 //set the right left node's parent to the problem parent to complete the mutual 
        if(rightLeftNodeTemp->right){                              //this means there is a child/tree on the right that has to be adopted 
         rlnAdoptChildRight = rightLeftNodeTemp->right;            //initialize our right child adopt variable to this 
        }
        if(rightLeftNodeTemp->left){                               //this means there is a child/tree on the left that has to be adopted 
         rlnAdoptChildLeft = rightLeftNodeTemp->left;              //initialize our right child adtoip variable to this 
        }
        
        rightLeftNodeTemp->left = problemNode;                     //set the left of that rln node to the problem node
        problemNode->parent = rightLeftNodeTemp;                   //set the parent of problemNode to rln 
         
        rightLeftNodeTemp->right = rightNodeTemp;                  //set the rln right to right node temp 
        rightNodeTemp->parent = rightLeftNodeTemp;                 //set the parent of right node temp to rln

        if(rlnAdoptChildRight) rightNodeTemp->left = rlnAdoptChildRight; //if there was a child to adopt on right, it goes on the left side of right node temp 
        else rightNodeTemp->left = nullptr; 
        if(rlnAdoptChildLeft)  problemNode->right = rlnAdoptChildLeft;   //if there was a child to adopt on left, it goes on the right side of problem node 
        else problemNode->right = nullptr; 
        //pre_order();
        return; 
        } //end of double rotation check 

        if(problemParent->left == problemNode) problemParent->left = rightNodeTemp;               //set problem node parent LEFT to problem node left
        else problemParent->right = rightNodeTemp;                                         //set problem node parent RIGHT  to problem node left 

        rightNodeTemp->parent = problemParent;                    //set the problem node right parent to the problem node's parent
        if(rightNodeTemp->left){                                  //if the problem node's right child has a left child, it needs to get adopted 
            Node* childToAdopt = rightNodeTemp->left;            //create a ref. for the child to adopt
            childToAdopt->parent = problemNode;              //set the adopted child's parent to the problem node 
            rightNodeTemp->left = problemNode;                   //set the right node's left to problem node
            problemNode->right = childToAdopt;                //set the problem Node right to the child to adopt
            problemNode->parent =  rightNodeTemp;                //set the problem node's parent to the problem node's right child 
           // pre_order(); //do a preorder print to check
           // cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done rotating
        } else{                                          //if no child to adopt,
            problemNode->parent = rightNodeTemp;                //problem node's parent becomes right node 
            rightNodeTemp->left = new Node(); 
            rightNodeTemp->left = problemNode; 
            problemNode->right = nullptr;                   //problem node's right becomes nullptr because there's no child to adopt
            
           // rightNode->left = new Node();
           // rightNode->left = problemNode;
           // pre_order(); //do a preorder print to check
           // cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done rotating
        }
  
    }

    //IF ROOT:
        //cout<<"Rotating Root to the LEFT"<<endl; 

       if( (rightNodeTemp->left !=nullptr || rightNodeTemp->right != nullptr)                //If either or isn't null continue checking 
        && (
            (rightNodeTemp->left != nullptr && rightNodeTemp->right != nullptr                //if the left and the right one aren't null 
             && (getHeight(rightNodeTemp->left) > getHeight(rightNodeTemp->right)))           //and the left is bigger than the right, there's a double rotation
        || (rightNodeTemp->left !=nullptr && rightNode->right == nullptr))                    // or if the left one isn't null but the right one is
        ){            

        Node* rightLeftNodeTemp = problemNode->right->left;        //set a node copy for the right left node, it'll become the new "root" of this mini tree
        Node* rlnAdoptChildRight = nullptr;                        //child to adopt on the right (in the case of k>1 ) 
        Node* rlnAdoptChildLeft = nullptr;                         //child to adopt on the left  (in the case of k>1 )
        if(rightLeftNodeTemp->right){                              //this means there is a child/tree on the right that has to be adopted 
         rlnAdoptChildRight = rightLeftNodeTemp->right;            //initialize our right child adopt variable to this 
        }
        if(rightLeftNodeTemp->left){                               //this means there is a child/tree on the left that has to be adopted 
         rlnAdoptChildLeft = rightLeftNodeTemp->left;              //initialize our right child adtoip variable to this 
        }
        
        rightLeftNodeTemp->left = problemNode;                     //set the left of that rln node to the problem node
        problemNode->parent = rightLeftNodeTemp;                   //set the parent of problemNode to rln 
         
        rightLeftNodeTemp->right = rightNodeTemp;                  //set the rln right to right node temp 
        rightNodeTemp->parent = rightLeftNodeTemp;                 //set the parent of right node temp to rln

        if(rlnAdoptChildRight) rightNodeTemp->left = rlnAdoptChildRight; //if there was a child to adopt on right, it goes on the left side of right node temp 
        else rightNodeTemp->left = nullptr; 
        if(rlnAdoptChildLeft)  problemNode->right = rlnAdoptChildLeft;   //if there was a child to adopt on left, it goes on the right side of problem node 
        else problemNode->right = nullptr; 

        root = rightLeftNodeTemp;                                   //set rln to root 
        rightLeftNodeTemp->parent = nullptr;                        //get rid of it's parent if any
        //pre_order();
        return; 
        } //end of double rotation check 

        if(rightNodeTemp->left){                                //problem node right child had a left child that needs to be adopted
            Node*& childToAdopt = rightNodeTemp->left;          //set a temp variable for child to adopt 
            childToAdopt->parent = problemNode;             //problem node becomes the new parent of the adopted node 
            problemNode->right = childToAdopt;              //problem node right child is equal to child that needs to be adopted
            problemNode->parent = new Node();               //create a new node for parent cause it used to be root and there was no parent
            problemNode->parent = rightNodeTemp;                //problem node parent becomes right node
            rightNodeTemp->left = problemNode;                  //right node's left becomes problemNode
            rightNodeTemp->parent = nullptr;                    //right node's parent becomes a nullptr because it is the new root 
            root = rightNodeTemp;                               //set right node to the new root 
           //pre_order(); //do a preorder print to check
            //cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done with rotation
        } else{                                             //if no child needs to be adopted
            rightNodeTemp->parent = nullptr;                    //right node's parent is nullptr because it becomes the new root 
            rightNodeTemp->left = problemNode;                  //right node's left becomes the problem node 
            problemNode->parent = new Node();               //create a new node for parent cause it used to be root and there was no parent 
            problemNode->parent = rightNodeTemp;              //problem node's parent becomes right node 
            problemNode->right = nullptr;                   //get rid of any connection problem node had to the right 
            root = rightNodeTemp;
           // pre_order(); //do a preorder print to check
          //  cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done with rotation
        }

}

void AVLTree::rotateRight(Node* problemNode){
    Node*& leftNode = problemNode->left;      //make a copy of the left node 
    Node* leftNodeTemp = problemNode->left;


    //If not Root:
    if(problemNode->parent){ 
      Node*& problemParent = problemNode->parent;                                           //set problem node parent temp
       if( (leftNodeTemp->right !=nullptr || leftNodeTemp->left != nullptr)                //If either or isn't null continue checking 
        && (
            (leftNodeTemp->right != nullptr && leftNodeTemp->left != nullptr                //if the left and the right one aren't null 
             && (getHeight(leftNodeTemp->right) > getHeight(leftNodeTemp->left)))           //and the left is bigger than the right, there's a double rotation
        || (leftNodeTemp->right !=nullptr && leftNodeTemp->left == nullptr))                    // or if the left one isn't null but the right one is
        ){            

        // printNode(problemNode); 
        // printNode(leftNodeTemp); 
        

        Node* leftRightNodeTemp = problemNode->left->right;        //set a node copy for the left right node, it'll become the new "root" of this mini tree
        Node* lrnAdoptChildRight = nullptr;                        //child to adopt on the right (in the case of k>1 ) 
        Node* lrnAdoptChildLeft = nullptr;                         //child to adopt on the left  (in the case of k>1 )

                                                                                                      //set the the parent's right to the right left node 
        if(problemParent->left == problemNode) problemParent->left = leftRightNodeTemp;               //set problem node parent LEFT to problem node left
        else problemParent->right = leftRightNodeTemp;                                         //set problem node parent RIGHT  to problem node left 

        leftRightNodeTemp->parent = problemParent;                 //set the left right node's parent to the problem parent to complete the mutual 
        if(leftRightNodeTemp->right){                              //this means there is a child/tree on the right that has to be adopted 
         lrnAdoptChildRight = leftRightNodeTemp->right;            //initialize our right child adopt variable to this 
        }
        if(leftRightNodeTemp->left){                               //this means there is a child/tree on the left that has to be adopted 
         lrnAdoptChildLeft = leftRightNodeTemp->left;              //initialize our right child adtoip variable to this 
        }
        
        leftRightNodeTemp->right = problemNode;                     //set the right of that lrn node to the problem node
        problemNode->parent = leftRightNodeTemp;                   //set the parent of problemNode to lrn
         
        leftRightNodeTemp->left = leftNodeTemp;                  //set the lrn left to left node temp 
        leftNodeTemp->parent = leftRightNodeTemp;                 //set the parent of left node temp to lrn

        if(lrnAdoptChildLeft) leftNodeTemp->right = lrnAdoptChildRight; //if there was a child to adopt on left, it goes on the right side of left node temp 
        else leftNodeTemp->right = nullptr; 
        if(lrnAdoptChildRight)  problemNode->left = lrnAdoptChildLeft;   //if there was a child to adopt on right, it goes on the left side of problem node 
        else problemNode->left = nullptr; 
   
       // pre_order();
        return; 
        } //end of double rotation check 

        if(problemParent->left == problemNode) problemParent->left = leftNodeTemp;               //set problem node parent LEFT to problem node left
        else problemParent->right = leftNodeTemp;                                         //set problem node parent RIGHT  to problem node left 
        leftNodeTemp->parent = problemParent;                    //set the problem node right parent to the problem node's parent
        if(leftNode->right){                                  //if the problem node's left child has a right child, it needs to get adopted 
            Node*& childToAdopt = leftNodeTemp->right;            //create a ref. for the child to adopt
            childToAdopt->parent = problemNode;              //set the adopted child's parent to the problem node 
            problemNode->left = childToAdopt;                //set the problem Node left to the child to adopt
            problemNode->parent =  leftNodeTemp;                //set the problem node's parent to the problem node's left child 
            leftNodeTemp->right = problemNode;                   //set the left node's right to problem node
           // pre_order(); //do a preorder print to check
           // cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done rotating
        } else{                                          //if no child to adopt,
            problemNode->parent = leftNodeTemp;                //problem node's parent becomes right node 
            leftNodeTemp->right = new Node(); 
            leftNodeTemp->right = problemNode; 
            problemNode->left = nullptr;                   //problem node's left becomes nullptr because there's no child to adopt
           // pre_order();
           // cout<<"ROTATION FINISHED"<<endl<<endl;
         return; //done rotating
        }
  
    }

    //IF ROOT:
       // cout<<"Rotating Root to the RIGHT"<<endl; 

        if( (leftNodeTemp->right !=nullptr || leftNodeTemp->left != nullptr)                //If either or isn't null continue checking 
        && (
            (leftNodeTemp->right != nullptr && leftNodeTemp->left != nullptr                //if the left and the right one aren't null 
             && (getHeight(leftNodeTemp->right) > getHeight(leftNodeTemp->left)))           //and the left is bigger than the right, there's a double rotation
        || (leftNodeTemp->right !=nullptr && leftNodeTemp->left == nullptr))                    // or if the left one isn't null but the right one is
        ){            

        Node* leftRightNodeTemp = problemNode->left->right;        //set a node copy for the left right node, it'll become the new "root" of this mini tree
        Node* lrnAdoptChildRight = nullptr;                        //child to adopt on the right (in the case of k>1 ) 
        Node* lrnAdoptChildLeft = nullptr;                         //child to adopt on the left  (in the case of k>1 )
    
        if(leftRightNodeTemp->right){                              //this means there is a child/tree on the right that has to be adopted 
         lrnAdoptChildRight = leftRightNodeTemp->right;            //initialize our right child adopt variable to this 
        }
        if(leftRightNodeTemp->left){                               //this means there is a child/tree on the left that has to be adopted 
         lrnAdoptChildLeft = leftRightNodeTemp->left;              //initialize our right child adtoip variable to this 
        }
        
        leftRightNodeTemp->right = problemNode;                     //set the right of that lrn node to the problem node
        problemNode->parent = leftRightNodeTemp;                   //set the parent of problemNode to lrn
         
        leftRightNodeTemp->left = leftNodeTemp;                  //set the lrn left to left node temp 
        leftNodeTemp->parent = leftRightNodeTemp;                 //set the parent of left node temp to lrn

        if(lrnAdoptChildLeft) leftNodeTemp->right = lrnAdoptChildRight; //if there was a child to adopt on left, it goes on the right side of left node temp 
        else leftNodeTemp->right = nullptr; 
        if(lrnAdoptChildRight)  problemNode->left = lrnAdoptChildLeft;   //if there was a child to adopt on right, it goes on the left side of problem node 
        else problemNode->left = nullptr; 

        root = leftRightNodeTemp;                                   //set lrn to root 
        leftRightNodeTemp->parent = nullptr;                        //get rid of it's parent if any
      //  pre_order();
        return; 
        } //end of double rotation check


        if(leftNodeTemp->right){                                //problem node left child had a right child that needs to be adopted
            Node*& childToAdopt = leftNodeTemp->right;          //set a temp variable for child to adopt 
            childToAdopt->parent = problemNode;             //problem node becomes the new parent of the adopted node 
            problemNode->left = childToAdopt;              //problem node left child is equal to child that needs to be adopted
            problemNode->parent = new Node();               //create a new node for parent cause it used to be root and there was no parent
            problemNode->parent = leftNodeTemp;                //problem node parent becomes left node
            leftNodeTemp->right = problemNode;                  //left node's right become a nullptr cause problem node adopted it on it's right 
            leftNodeTemp->parent = nullptr;                    //left node's parent becomes a nullptr because it is the new root 
            root = leftNodeTemp;                               //set left node to the new root 
          //  pre_order(); //do a preorder print to check
           // cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done with rotation
        } else{                                             //if no child needs to be adopted
            leftNodeTemp->parent = nullptr;                    //left node's parent is nullptr because it becomes the new root 
            leftNodeTemp->right = problemNode;                  //left node's right becomes the problem node 
            problemNode->parent = new Node();               //create a new node for parent cause it used to be root and there was no parent 
            problemNode->parent = leftNodeTemp;                //problem node's parent becomes left node 
            problemNode->left = nullptr;                   //get rid of any connection problem node had to the left 
            root = leftNodeTemp;                               //set left node to the new root
           // if(root){cout<<"hi, there's a root after i set the root"<<endl;}
          //  pre_order(); //do a preorder print to check
           // cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done with rotation
        }
   
 }


int getMax(int a, int b){
    return (a>b) ? a:b; 
}

int AVLTree::getHeight(Node* n){
 if(n == nullptr) return 0; 
 if((n->left == nullptr && n->right== nullptr)) return 1; 
 return getMax(getHeight(n->left), getHeight(n->right))+1; 
}

bool AVLTree::balanceCheck(Node* n){ 

       if(!n) return false; 

        int leftHeight = getHeight(n->left);
        int rightHeight = getHeight(n->right); 
        // cout<<endl<<endl;
        // cout<<"Checking heights at "<<n->a<<"."<<n->b<<endl;
        // cout<<"Left Height: "<<leftHeight<<endl;
        // cout<<"Right Height: "<<rightHeight<<endl;
        // cout<<endl<<endl;

        if(n == root){
            if( abs(leftHeight - rightHeight) <= this->k ){
              //  cout<<"PROPERTY NOT BROKEN at ROOT"<<endl<<endl;
                //pre_order(); 
                return true; //this is where you force it to stop
            } else if (leftHeight > rightHeight){
               // cout<<"PROPERTY BROKEN at ROOT: Left side is heavier, doing a root rotation to the right"<<endl<<endl; 
                rotateRight(n); 
              //  pre_order(); 
                return balanceCheck(n); 
            } 
                //cout<<"PROPERTY BROKEN at ROOT: Right side is heavier, doing a root rotation to the left"<<endl<<endl; 
                rotateLeft(n); 
              //  pre_order();
                return balanceCheck(n); 
        }

        if( abs(leftHeight - rightHeight) <= this->k ){
        //cout<<"PROPERTY NOT BROKEN"<<endl<<endl;
        return balanceCheck(n->parent); 
        } else if (leftHeight > rightHeight){
       // cout<<"PROPERTY BROKEN at"<<n->a<<","<<n->b<<": Left side is heavier, doing a rotation to the right"<<endl<<endl; 
        rotateRight(n);
        return balanceCheck(n->parent); 
        } 
       // cout<<"PROPERTY BROKEN at"<<n->a<<","<<n->b<<": Right side is heavier, doing a rotation to the left"<<endl<<endl; 
        rotateLeft(n); 
        //pre_order(); 
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
            //pre_order();
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
        // pre_order();
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
               //  pre_order();
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
                //pre_order();
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
	    while( numify(n->a, n->b) != numify(temp2->a, temp2->b) ){
            if( numify(n->a, n->b) <= numify(temp2->a, temp2->b)){
                temp = temp2; 
                temp2 = temp2->left; 
            }//end of if check 
            else{
                temp2 = temp2->right;
            }
	    }//end of second while 
        //printNode(temp); 
        return temp; 	
      }
      return root;  
}

AVLTree::Node* AVLTree::deleteBalanceChecker(Node* n){
    if(n == nullptr) return nullptr; 
    if(n->left == nullptr && n->right == nullptr ) return n; 
    if(n->left && n->right == nullptr)  deleteBalanceChecker(n->left); 
    if(n->right && n->left == nullptr) deleteBalanceChecker(n->right); 
    if(n->right && n->left){
          if( getHeight(n->right) > getHeight(n->left) ) deleteBalanceChecker(n->right); 
     else if( getHeight(n->left) > getHeight(n->right) ) deleteBalanceChecker(n->left); 
     else deleteBalanceChecker(n->right); 
    }
    return nullptr; 
}

bool AVLTree::deleteBalanceCheck(Node* n){
  if(nullptr) return false; //this should only happen if the one thing delete was a sole root
  return balanceCheck( deleteBalanceChecker(n) ); 
}

//remove function 
bool AVLTree::remove(int a, int b){
 if(!root) return false; 
 return deleteBalanceCheck(remove(a, b, approx_searcher(a,b,root))); 
}

//recursive function for remove
AVLTree::Node* AVLTree::remove(int a, int b, Node* n){
    if(a == n->a && b == n->b){                                       //we found  the node, so we proceed to delete
     Node* successorNode = getSuccessor(n);                           //first thing we do is get the sucessor
     Node* temp = n;                                                  //make a copy of the n

     if(n->parent){                                                     //IF there is a parent (aka it's not root)

        Node* parentTemp = n->parent;                                     //save the parent (if it has one)
        if(successorNode == nullptr){                                    //if that sucessor is a nullptr, we are able to delete it right off the bat 
        if(temp->left){                                               //if it has anything on the left, make sure you don't throw that away, it won't have anything on the right
            n->parent->right = temp->left;                              //set the node's parent's right to that
            temp->left->parent = n->parent;                             //set the left child's parent to node's parent 
            cout<<n->a<<"."<<n->b<<" deleted"<<endl;
            n->left = nullptr;                                          //remove everything from n then eventually delete it: 
            n->right = nullptr; 
            n->parent = nullptr; 
            delete n; 
            return parentTemp;                                          //return the parent to the delete balance check 
        }
        parentTemp->right = nullptr;                                  //if there was no left child/tree to take care of, we just delete it 
      cout<<n->a<<"."<<n->b<<" deleted"<<endl;
        n->left = nullptr; 
        n->right = nullptr; 
         n->parent = nullptr; 
        delete n; 
        return parentTemp;                                           //return parent temp
        } //end of if the sucessor is null
                                                                    //if it reaches here, there IS a successor:   
        if(n->left){                                                  //if n has a left child/tree that needs to be adopted do that 
            Node* nLeftTemp = n->left;                                    //recrusively add it to the bottom of the left of the sucessor 
            if(successorNode->left){
            Node* snrTemp = successorNode->right;                       //set a temp of the successor node left for iterating 
                while(snrTemp){ 
                    if(snrTemp->left == nullptr){                           //if it reaches a nullptr 
                        snrTemp->left = new Node();                           //create a new node there 
                        snrTemp->left = nLeftTemp;                            //set the new node to the n left 
                        nLeftTemp->parent = snrTemp;                         //and set the parent of that n left to that thing 
                    }
                }
            } //end of checking if the successor node has a left 
            else{
                //if it gets here, then the sucessor node didn't have a left, so we can just stick it on there without a while loop
                successorNode->left = new Node(); 
                successorNode->left = nLeftTemp; 
                nLeftTemp->parent = successorNode; 
            }
        } //end of checking if there was a left to adopt in general

        //if it reaches here, there was no left child so we can just focus on doing the main deletion
        //check if it was a left or right child of it's parent 

        if(parentTemp->right == n) parentTemp->right = successorNode;     //its the right child set the right of that parent equal to the sucessor node 
        else parentTemp->left = successorNode;                            //it was the left child  set the left of that parent equal to the sucessor node 

        successorNode->parent = parentTemp;                               //in either case, set the succesor node parent to the parent temp 
                                                                            //do normal deletion 
       cout<<n->a<<"."<<n->b<<" deleted"<<endl;
        n->left = nullptr; 
        n->right = nullptr; 
        n->parent = nullptr; 
        delete n; 
        return parentTemp;                                                //at the end return parent temp

     } //end of if we got an actual parent 
      
    //if here, that means that its a root 
    if(successorNode == nullptr){          //first check if the successor node is a nullptr
     if(n->left){                          //we check if n has a left, if it does, set it as the root 
      Node* nLeftTemp = n->left;           //save the n- left in a temp 
      nLeftTemp->parent = nullptr;         //get rid of it's parent affiliation 
      root = nLeftTemp;                    //set the left temp to the root 
      cout<<n->a<<"."<<n->b<<" deleted"<<endl;
      n->left = nullptr;                   //clean up node as usual 
      n->right = nullptr; 
      delete n; 
      return nLeftTemp;                    //return the left temp which should be root                
     }
     //at this point n doesn't have a left nor a sucessor meaning it's by itself, so we can just get rid of it and return a nullptr 
     cout<<n->a<<"."<<n->b<<" deleted"<<endl;
     n->left = nullptr; 
     n->right = nullptr; 
     delete n; 
     return nullptr;        
    }

    //if we reach here, there is a sucessor node, we first check if the root had a left child/tree 
        if(n->left){                                                  //if n has a left child/tree that needs to be adopted do that 
            Node* nLeftTemp = n->left;                                    //recrusively add it to the bottom of the left of the sucessor 
            if(successorNode->left){
            Node* snrTemp = successorNode->right;                       //set a temp of the successor node left for iterating 
                while(snrTemp){ 
                    if(snrTemp->left == nullptr){                           //if it reaches a nullptr 
                        snrTemp->left = new Node();                           //create a new node there 
                        snrTemp->left = nLeftTemp;                            //set the new node to the n left 
                        nLeftTemp->parent = snrTemp;                         //and set the parent of that n left to that thing 
                    }
                }
            } //end of checking if the successor node has a left 
            else{
                //if it gets here, then the sucessor node didn't have a left, so we can just stick it on there without a while loop
                successorNode->left = new Node(); 
                successorNode->left = nLeftTemp; 
                nLeftTemp->parent = successorNode; 
            }
        } //end of checking if there was a left to adopt in general
         //if it reached here, there was no child to the left, so we just focus on a deletion 
        successorNode->parent = nullptr;                                    //in either case, set the succesor node parent to the nullptr since it's the root
        root = successorNode;                                               //set the root to the successor node 
                                                                            //do normal deletion 
       cout<<n->a<<"."<<n->b<<" deleted"<<endl;
        n->left = nullptr; 
        n->right = nullptr; 
        n->parent = nullptr; 
        delete n; 
        return successorNode;                                                //at the end return parent temp

    } //end of making sure we got the actual node 
 
    return nullptr;

}
