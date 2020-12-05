#include "avlTree.h"

#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{

    //Parse the input:
    string argument = argv[1];
    std::string delimiter = ", ";
    size_t pos = 0;
    std::string token;
    vector<string> commands;

    //First get the number and use that to create the tree:
    int avlSize = stoi(argument.substr(0, argument.find(delimiter)));
    argument.erase(0, argument.find(delimiter) + delimiter.length());

    AVLTree avl = AVLTree(avlSize);

    while ((pos = argument.find(delimiter)) != std::string::npos) {
        token = argument.substr(0, pos);
        commands.push_back(token);
        argument.erase(0, pos + delimiter.length());
    }
    token = argument.substr(0, argument.length());
    commands.push_back(token);

    for (string s : commands) {
        std::string func_delimiter = " ";
        size_t func_pos = 0;
        std::string func_token;
        string currentFunction = s.substr(0, s.find(func_delimiter));

        if (currentFunction.compare("in_order") == 0) {
            avl.in_order();
            continue;
        }
        else if (currentFunction.compare("pre_order") == 0) {
            avl.pre_order();
            continue;
        }
        else if (currentFunction.compare("insert") == 0) {
            s.erase(0, s.find(func_delimiter) + func_delimiter.length());
            vector<int> funcArgs;
            while ((func_pos = s.find(func_delimiter)) != std::string::npos) {
                func_token = s.substr(0, func_pos);
                //cout<<"Func Token: "<<func_token<<endl;
                int arg = stoi(func_token);
                funcArgs.push_back(arg);
                s.erase(0, func_pos + func_delimiter.length());
            }
            func_token = s.substr(0, s.length());
            funcArgs.push_back(stoi(func_token));
            avl.insert(funcArgs[0], funcArgs[1]);
        }
        else if (currentFunction.compare("approx_search") == 0) {
            s.erase(0, s.find(func_delimiter) + func_delimiter.length());
            vector<int> funcArgs;
            while ((func_pos = s.find(func_delimiter)) != std::string::npos) {
                func_token = s.substr(0, func_pos);
                //cout<<"Func Token: "<<func_token<<endl;
                int arg = stoi(func_token);
                funcArgs.push_back(arg);
                s.erase(0, func_pos + func_delimiter.length());
            }
            func_token = s.substr(0, s.length());
            funcArgs.push_back(stoi(func_token));
            avl.approx_search(funcArgs[0], funcArgs[1]);
        }
        else if (currentFunction.compare("search") == 0) {
            s.erase(0, s.find(func_delimiter) + func_delimiter.length());
            vector<int> funcArgs;
            while ((func_pos = s.find(func_delimiter)) != std::string::npos) {
                func_token = s.substr(0, func_pos);
                //cout<<"Func Token: "<<func_token<<endl;
                int arg = stoi(func_token);
                funcArgs.push_back(arg);
                s.erase(0, func_pos + func_delimiter.length());
            }
            func_token = s.substr(0, s.length());
            funcArgs.push_back(stoi(func_token));
            avl.search(funcArgs[0], funcArgs[1]);
        }
        else if (currentFunction.compare("delete") == 0) {
            s.erase(0, s.find(func_delimiter) + func_delimiter.length());
            vector<int> funcArgs;
            while ((func_pos = s.find(func_delimiter)) != std::string::npos) {
                func_token = s.substr(0, func_pos);
                //cout<<"Func Token: "<<func_token<<endl;
                int arg = stoi(func_token);
                funcArgs.push_back(arg);
                s.erase(0, func_pos + func_delimiter.length());
            }
            func_token = s.substr(0, s.length());
            funcArgs.push_back(stoi(func_token));
            avl.remove(funcArgs[0], funcArgs[1]);
        }
    }

    return 0;
}