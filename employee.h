#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "worker.h"

class Employee:public Worker{
    public:
    Employee(int,string,int);
    virtual void showInfo();
    virtual string getPosition();
};