#pragma once
#include <iostream>
using namespace std;
#include <string>

class Worker{
    public:
    virtual void showInfo() = 0; 
    virtual string getPosition() = 0;
    virtual ~Worker() {}

    int id;
    string name;
    int deptid;
};