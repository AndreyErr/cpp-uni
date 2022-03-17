#ifndef PAR_H
#define PAR_H
#include "Base.h"
#include "Child.h"
#include "a2.h"
#include "a3.h"
#include "a4.h"
#include "a5.h" 
#include "a6.h" 
class Par : public Base {
public:
    void BuildTree();
    int Exec();
};
#endif
