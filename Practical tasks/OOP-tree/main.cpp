#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Par.h"

int main()
{
    Par app;
    app.BuildTree();
    return app.Exec();
}
