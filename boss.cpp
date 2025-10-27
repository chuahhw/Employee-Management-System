#include "boss.h"
#include <string>
Boss::Boss(int id, string name, int dId) {
    this->id = id;
    this->name = name;
    this->deptid = dId;
}

void Boss::showInfo() {
    cout << "Employee id: " << this->id 
         << "\tEmployee name: " << this->name
         << "\tEmployee's position: " << this->getPosition()
         << "\tPosition task: Oversee and manage the overall company operations." << endl;
}

string Boss::getPosition() {
    return string("boss");
}