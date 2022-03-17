#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <vector> 
#include <string> 
using namespace std; 
class Base { 
protected:
    string name;
    Base* parent;
    vector<Base*> children;
    int is_ready;
public:
    Base(Base* parent = 0, string name = "");
    void SetName(string name);
    string GetName();
    void SetParent(Base* parent);
    Base* GetParent();
    //void PrintNames();         
    void PrintNames(int step);
    Base* FindByName(string name);
    void SetState(int is_ready);
    int GetReadyStat();
};
#endif
