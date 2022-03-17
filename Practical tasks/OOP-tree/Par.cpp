#include "Par.h"
#include <iostream>
#include <vector> 
#include <string> 
using namespace std;
/*void Par::BuildTree()
{
    Base* temp_parent;
    Base* temp_child;
    int type;
    string parent_name, child_name;
    cin >> parent_name;
    SetName(parent_name);
    temp_parent = this;
    while (1) {
        cin >> parent_name;
        cin >> child_name;
        if (parent_name == child_name) return;
        if (parent_name != temp_parent -> GetName()) {
            if (parent_name == temp_child -> GetName()) {
                temp_parent = temp_child;
            }
            else continue;
        }
        temp_child = new Child(temp_parent, child_name);
   }
}*/
void Par::BuildTree()
{
    string nameP, nameD;
    int class_type;
    int is_ready = 1;
    cin >> nameP;
    this->SetName(nameP);
    while (1)
    {
        cin >> nameP;
        if (nameP == "endtree")
            break;
        cin >> nameD >> class_type >> is_ready;
        if (FindByName(nameD)) {
            cout << "Ошибка уникальности имени!\n";
            break;
        }
        if (class_type == 2)
        {
            Base* obj2 = new a2(FindByName(nameP), nameD);
            obj2->SetState(is_ready);
        }
        else if (class_type == 3)
        {
            Base* obj3 = new a3(FindByName(nameP), nameD);
            obj3->SetState(is_ready);
        }
        else if (class_type == 4)
        {
            Base* obj4 = new a4(FindByName(nameP), nameD);
            obj4->SetState(is_ready);
        }
        else if (class_type == 5)
        {
            Base* obj5 = new a5(FindByName(nameP), nameD);
            obj5->SetState(is_ready);
        }
        else if (class_type == 6)
        {
            Base* obj5 = new a5(FindByName(nameP), nameD);
            obj5->SetState(is_ready);
        }
    }
}
int Par::Exec()
{
    this->PrintNames(1);
    return 0;
}
/*int Par::Exec()
{
    this->PrintNames();
    return 0;
}*/
