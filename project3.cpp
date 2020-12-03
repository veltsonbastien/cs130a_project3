#include "avlTree.h" 

#include <iostream>
#include <utility> 
#include <cstring> 
#include <vector> 
using namespace std; 

int main(int argc, char* argv[]){
//  AVLTree avl = AVLTree(1); 
//  cout<<endl;
//  cout<<endl;
//  cout<<"INSERTS TESTING:"<<endl; 
//  avl.insert(4,5);
//  avl.insert(4,4);
//  avl.insert(3,4);
//  avl.insert(5,0);

//  cout<<endl;
//  cout<<endl;
//  cout<<"SEARCH TESTING"<<endl; 
//  avl.search(4,4); 
//  avl.search(5,3);
//  avl.search(3,4); 

//  cout<<endl; 
//  cout<<endl;
//  cout<<"APPROX SEARCH TESTING"<<endl; 
//  avl.approx_search(3,4); 
//  avl.approx_search(4,6);
//  avl.approx_search(4,3); 
//  avl.approx_search(3,9); 

//  cout <<endl; 
//  cout <<endl; 
//  cout<<"CHECK PREORDERS THAT HAVE BEEN PRINTING DUE TO INSERTS"<<endl;

//  cout<<endl;
//  cout<<endl;
//  cout<<"IN ORDER CHECK"<<endl; 
//  avl.in_order();

//  cout<<endl; 
//  cout<<endl; 
//  cout<<"DELETE CHECK"<<endl; 
//  avl.remove(5,0); 
//  avl.in_order(); 


//PREPARE FOR SUBMISSION: 

//Parse the input: 
    string argument = argv[1]; 
    std::string delimiter = ", ";
    size_t pos = 0;
    std::string token;
    vector<string> commands; 

    //First get the number and use that to create the tree: 
    int avlSize = stoi(argument.substr(0, argument.find(delimiter))); 
    argument.erase(0, argument.find(delimiter) + delimiter.length() ); 

    AVLTree avl = AVLTree(avlSize); 


 while ((pos = argument.find(delimiter)) != std::string::npos) {
        token = argument.substr(0, pos);
        commands.push_back(token);
        argument.erase(0, pos + delimiter.length());
 }

 for(string s: commands){
    std::string func_delimiter = " ";
    size_t func_pos = 0;
    std::string func_token;   
    string currentFunction = s.substr(0, s.find(func_delimiter)); 

    if(currentFunction.compare("in_order")==0){ avl.in_order(); continue; }
    else if(currentFunction.compare("pre_order")==0) {avl.pre_order(); continue; }
    else if(currentFunction.compare("insert")==0){ 
        s.erase(0, s.find(func_delimiter) + func_delimiter.length());
        vector<int> funcArgs; 
        while((func_pos = s.find(func_delimiter)) != std::string::npos){
            func_token = s.substr(0, func_pos); 
            //cout<<"Func Token: "<<func_token<<endl;
            int arg = stoi(func_token); 
            funcArgs.push_back(arg); 
            s.erase(0, func_pos+func_delimiter.length()); 
        }
        avl.insert(funcArgs[0], funcArgs[1]); 
    }
 }


  return 0; 

}