#ifndef CHILD_H
#define CHILD_H
#include "Base.h" 
class Child : public Base { 
public:
	Child(Base* parent, string name) :Base(parent, name) {};
};
#endif
