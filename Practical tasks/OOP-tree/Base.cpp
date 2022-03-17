#include "Base.h"
#include <iostream> 
using namespace std;
Base::Base(Base* parent, string name) {
    this->parent = parent;
    if (parent != 0)
        parent->children.push_back(this);
    SetName(name);
}
void Base::SetName(string name) {
    this->name = name;
}

string Base::GetName() {
    return this->name;
}

Base* Base::GetParent() {
    return parent;
}

void Base::SetParent(Base* parent) {
    if (parent && this->parent) {
        for (int i = 0; i < this->parent->children.size(); i++) {
            if (this->parent->children[i] == this) {
                this->parent->children.erase(children.begin() + i);
            }
        }
        this->parent = parent;
        this->parent->children.push_back(this);
    }
}
/*void Base::PrintNames() {
    if (children.empty()) return;
    if(parent == 0)
        cout << name;
    cout << endl << name;
    for(int i = 0; i < children.size(); i++){
        if(children.size() > 0){
            cout << "  " << children[i] -> GetName();
        }
    }
    for(int i = 0; i < children.size(); i++){
        if(children.size() > 0){
            children[i] -> PrintNames();
        }
    }
}*/
/*void Base::PrintNames()
{
    if(parent == 0)
    {
        cout << "Test result";
        cout << endl << "The object " << GetName() << " is ready";
        SetState(1);
    }
    for(int i = 0; i < children.size(); i++)
    {
        if(GetReadyStat() <= 0){
            cout << endl << "The object " << children[i]->GetName() << " is not ready";
            children[i]->PrintNames();
        }
        else if(children[i]->GetReadyStat() > 0)
        {
            cout << endl << "The object " << children[i]->GetName() << " is ready";
            children[i]->PrintNames();
        }
        else if(children[i]->GetReadyStat() <= 0)
        {
            cout << endl << "The object " << children[i]->GetName() << " is not ready";
            children[i]->PrintNames();
        }
    }
}*/
void Base::PrintNames(int step) {
    if (children.empty()) return;
    if (parent == 0)
    {
        cout << "Object tree" << "\n";
        cout << name;
    }
    for (int i = 0; i < children.size(); i++) {
        if (children.size() > 0)
        {
            cout << "\n";
            for (int h = 0; h < step; h++)
                cout << "    ";
            cout << children[i]->GetName();
            children[i]->PrintNames(step + 1);
        }
    }
}

int Base::GetReadyStat() {
    return is_ready;
}

Base* Base::FindByName(string name)
{
    if (this->name == name)
        return this;
    for (int i = 0; i < this->children.size(); ++i)
    {
        Base* b = children[i]->FindByName(name);
        if (b != NULL)
            return b;
    }
    return nullptr;
}

void Base::SetState(int is_ready)
{
    this->is_ready = is_ready;
}
