#include "manager.h"
#include <string>
Manager::Manager(int id, string name, int dId) {
    this->id = id;
    this->name = name;
    this->deptid = dId;
}

void Manager::showInfo() {
    cout << "Employee id: " << this->id 
         << "\tEmployee name: " << this->name
         << "\tEmployee's position: " << this->getPosition()
         << "\tPosition task: Complete tasks assigned by the boss and assign tasks to employees." << endl;
}

string Manager::getPosition() {
    return string("manager");
}