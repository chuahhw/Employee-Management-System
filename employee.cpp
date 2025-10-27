#include "employee.h"

Employee::Employee(int id, string name, int dId) {
    this->id = id;
    this->name = name;
    this->deptid = dId;
}

void Employee::showInfo() {
    cout << "Employee id: " << this->id 
         << "\tEmployee name: " << this->name
         << "\tEmployee's position: " << this->getPosition()
         << "\tPosition task: Complete tasks assigned by managers." << endl;
}

string Employee::getPosition(){
    return string("employee");
}