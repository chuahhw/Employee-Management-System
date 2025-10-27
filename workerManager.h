#pragma once //prevent header 重复
#include <iostream>
using namespace std;
#include "worker.h"
#include <fstream>

class WorkerManager {
    public:
    WorkerManager();
    void show_menu();
    void ExitSystem();
    ~WorkerManager();
    void add_emp();
    void save();
    void init_Emp();
    void showEmp();
    void Del_Emp();
    int isExist(int id);
    void Mod_Emp();
    void Find_Emp();
    void Sort_Emp();
    void Clean_File();

    bool fileIsEmpty;
    int getEmpNum();
    int empNum;
    Worker **mEmpArray;
};