#include "avlTree.h" 

#include <iostream>
using namespace std; 

int main(){
 AVLTree avl = AVLTree(1); 
  cout<<endl;
   cout<<endl;
 cout<<"INSERTS TESTING:"<<endl; 
 avl.insert(4,5);
 avl.insert(4,4);
 avl.insert(3,4);
 avl.insert(5,0);

 cout<<endl;
  cout<<endl;
 cout<<"SEARCH TESTING"<<endl; 
 avl.search(4,4); 
 avl.search(5,3);
 avl.search(3,4); 

 cout<<endl; 
  cout<<endl;
 cout<<"APPROX SEARCH TESTING"<<endl; 
 avl.approx_search(3,4); 
 avl.approx_search(4,6);
 avl.approx_search(4,3); 
 avl.approx_search(3,9); 

}