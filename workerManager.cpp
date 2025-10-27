#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>

WorkerManager::WorkerManager() {
    this->mEmpArray = nullptr;
    this->empNum = 0;
    this->fileIsEmpty = true;
    ifstream ifs("empFile.txt", ios::in);
    if (!ifs.is_open()) {
        cout << "File not found, creating new file..." << endl;
        ofstream ofs("empFile.txt", ios::out);
        ofs.close();
        this->fileIsEmpty = true;
        return;
    }
}

void WorkerManager::show_menu(){
    cout << "*********************************************" << endl;
    cout << "******************* Welcome *****************" << endl;
    cout << "************** 0. Exit The System ***********" << endl;
    cout << "************** 1. Add Employee **************" << endl;
    cout << "*********** 2. Show Employee Info ***********" << endl;
    cout << "************** 3. Delete Employee ***********" << endl;
    cout << "************** 4. Modify Employee ***********" << endl;
    cout << "************** 5. Search Employee ***********" << endl;
    cout << "************** 6. Sort Using ID *************" << endl;
    cout << "*********** 7. Clear All Employee ***********" << endl;
    cout << "*********************************************" << endl;
    cout << endl;
}

void WorkerManager::ExitSystem() {
    cout << "See You In The Future" << endl;
    system("pause");
    exit(0);
}

void WorkerManager::add_emp() {
    cout << "Enter number of employees to add: " << endl;
    int addNum = 0;
    cin >> addNum;
    if(addNum > 0) {
        int newSize = this->empNum + addNum;
        Worker ** newSpace = new Worker*[newSize];
        if(this->mEmpArray != NULL) {
            for(int i = 0; i < this->empNum; i++) {
                newSpace[i] = this->mEmpArray[i];
            }
        }
        // Save old data + new data into newSpace
        for (int i = 0; i < addNum; i++) {
            int id;
            string name;
            int dselect;

            do {
                cout << "Enter employee id: ";
                cin >> id;
                cout << "Enter name: ";
                cin >> name;
                cout << "Select position: (1.Employee 2.Manager 3.Boss): ";
                cin >> dselect;
                if(dselect != 1 && dselect != 2 && dselect != 3) {
                    cout << "Invalid position!" << endl;
                }
            } while(dselect != 1 && dselect != 2 && dselect != 3);

            Worker *worker = nullptr;
            switch (dselect) {
                case 1:
                    worker = new Employee(id, name, 1);
                    break;
                case 2:
                    worker = new Manager(id, name, 2);
                    break;
                case 3:
                    worker = new Boss(id, name, 3);
                    break;
            }
            newSpace[this->empNum + i] = worker;
        }

        if (this->mEmpArray != nullptr) {
            for (int i = 0; i < this->empNum; i++) {
                if (this->mEmpArray[i] != nullptr) {
                    delete this->mEmpArray[i];
                }
            }
            delete[] this->mEmpArray;
            this->mEmpArray = nullptr;
        }


        // assign new array
        this->mEmpArray = newSpace;
        this->empNum = newSize;
        this->fileIsEmpty = false;

        cout << "Added " << addNum << " employees successfully." << endl;
        this->save();

    }

    else {
        cout << "Error, must > 0" << endl;
    }
    system("pause");
    system("cls");

}

void WorkerManager::save() {
    if (this->empNum == 0 || this->mEmpArray == nullptr) {
        return; // do not overwrite file if no data
    }

    ofstream ofs("empFile.txt", ios::out);
    for (int i = 0; i < this->empNum; i++) {
        if (this->mEmpArray[i] != nullptr) {
            ofs << this->mEmpArray[i]->id << " "
                << this->mEmpArray[i]->name << " "
                << this->mEmpArray[i]->getPosition() << endl;
        }
    }
    ofs.close();
}

int WorkerManager::getEmpNum(){
    ifstream ifs;
    ifs.open("empFile.txt", ios::in);

    int id;
    string name;
    int dId;
    int num = 0;

    while(ifs >> id && ifs >> name && ifs >> dId) {
        num++;
    }
    return num;
}

void WorkerManager::init_Emp() {
    ifstream ifs;
    ifs.open("empFile.txt", ios::in);
    int id;
    string name;
    int dId;
    int index = 0;

    while(ifs >> id && ifs >> name && ifs >> dId) {
        Worker *worker = NULL;
        if(dId == 1) {
            worker = new Employee(id,name,dId);
        }
        else if(dId == 2) {
            worker = new Manager(id,name,dId);
        }
        else if(dId == 3) {
            worker = new Boss(id,name,dId);
        }
        this->mEmpArray[index] = worker;
        index++;
    }
    ifs.close();
}

void WorkerManager::showEmp(){
    ifstream ifs;
    ifs.open("empFile.txt", ios::in);
    if(this->fileIsEmpty) {
        cout << "The file does not exist" << endl;
    }
    else {
        for(int i = 0; i < empNum; i++) {
            this->mEmpArray[i]->showInfo();  
        }
    }
    system("pause");
    system("cls");
}

void WorkerManager::Del_Emp() {
    if(this->fileIsEmpty) {
        cout << "File does not exist" << endl;
    }
    else {
        int id = 0;
        cout << "Enter employee id to delete: " << endl;
        cin >> id;

        int index = this->isExist(id);

        if(index != -1) {
            for(int i = index; i < this->empNum - 1; i++) {
                this->mEmpArray[i] = this->mEmpArray[i + 1];
            }
            this->empNum--;
            this->save();
            cout << "Delete successfully" << endl;
        }
        else {
            cout << "Delete failed, employee does not exist" << endl;
        }
    }
    system("pause");
    system("cls");
}

int WorkerManager::isExist(int id){
    if (this->mEmpArray == NULL || this->empNum == 0) {
        return -1; // no data to search
    }

    for (int i = 0; i < this->empNum; i++) {
        if (this->mEmpArray[i] != NULL && this->mEmpArray[i]->id == id) {
            return i;  // found
        }
    }
    return -1; 
}

void WorkerManager::Mod_Emp() {
    if (this->fileIsEmpty) {
        cout << "File does not exist" << endl;
    } 
    else {
        int id;
        cout << "Enter the employee id to modify: " << endl;
        cin >> id;

        int ret = this->isExist(id);
        if (ret != -1) {
            delete this->mEmpArray[ret];

            int newId = 0;
            string newName;
            int dSelect = 0;

            cout << "Enter new id: ";
            cin >> newId;
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin,newName);
            cout << "Enter new position (1.Employee 2.Manager 3.Boss): ";
            cin >> dSelect;

            Worker *worker = nullptr;
            switch (dSelect) {
                case 1:
                    worker = new Employee(newId, newName, dSelect);
                    break;
                case 2:
                    worker = new Manager(newId, newName, dSelect);
                    break;
                case 3:
                    worker = new Boss(newId, newName, dSelect);
                    break;
                default:
                    cout << "Invalid selection!" << endl;
                    return;
            }

            this->mEmpArray[ret] = worker;
            cout << "Modify successfully!" << endl;
            this->save();
        }
        else {
            cout << "Modify unsuccessful, employee does not exist." << endl;
        }
    }

    system("pause");
    system("cls");
}

void WorkerManager::Find_Emp() {
    if(this->fileIsEmpty) {
        cout << "File does not exist" << endl;
    }
    else {
        cout << "Choose search by:" << endl;
        cout << "1. Search by ID" << endl;
        cout << "2. Search by Name" << endl;

        int select = 0;
        cin >> select;

        if(select == 1) {
            int id;
            cout << "Enter employee's id: " << endl;
            cin >> id;
            int ret = isExist(id);
            if(ret != -1) {
                cout << "Search success. Information of employee: " << endl;
                this->mEmpArray[ret]->showInfo();
            }
            else {
                cout << "Search unsuccessful. Employee does not exist" << endl;
            }
        }
        else if(select == 2) {
            cout << "Enter employee's name: " << endl;
            string name;
            cin.ignore();
            getline(cin,name);

            bool flag = false;

            for(int i = 0; i < empNum; i++) {
                if(this->mEmpArray[i]->name == name) {
                    cout << "Search success. Employee id: " << this->mEmpArray[i]->id
                         << "Information of employee: " << endl;
                         flag = true;
                         this->mEmpArray[i]->showInfo();
                }
            }

            if(flag == false) {
                cout << "Search unsuccessful. Employee does not exist" << endl;
            }
        }
        else {
            cout << "Invalid choice (1 or 2 allowed only)" << endl;
        }
    }
    system("pause");
    system("cls");
}

void WorkerManager::Sort_Emp() {
    if (this->fileIsEmpty) {
        cout << "File does not exist" << endl;
        system("pause");
        system("cls");
        return;
    }

    int select = 0;
    do {
        cout << "Choose sorting method: " << endl;
        cout << "1. Sort ascending" << endl;
        cout << "2. Sort descending" << endl;
        cin >> select;
        if (select != 1 && select != 2) {
            cout << "Invalid choice, only 1 or 2 allowed" << endl;
        }
    } while (select != 1 && select != 2);

    // Selection sort
    for (int i = 0; i < this->empNum - 1; i++) {
        int minOrMax = i;
        for (int j = i + 1; j < this->empNum; j++) {
            if (select == 1) { // Ascending
                if (this->mEmpArray[minOrMax]->id > this->mEmpArray[j]->id) {
                    minOrMax = j;
                }
            } else if (select == 2) { // Descending
                if (this->mEmpArray[minOrMax]->id < this->mEmpArray[j]->id) {
                    minOrMax = j;
                }
            }
        }

        if (i != minOrMax) {
            Worker* temp = this->mEmpArray[i];
            this->mEmpArray[i] = this->mEmpArray[minOrMax];
            this->mEmpArray[minOrMax] = temp;
        }
    }

    cout << "Sort successfully. After sorting: " << endl;
    this->save();
    this->showEmp();  // ✅ only once, after sorting
}

void WorkerManager::Clean_File(){
    int select = 0;
    do{
        cout << "Sure to clear all? " << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cin >> select;
        if(select != 1 && select != 2) {
            cout << "Invalid choice, only 1 and 2 allowed" << endl;
        }
    }while(select != 1 && select != 2);

    if(select == 1) {
        ofstream ofs("empFile.txt", ios::trunc);
        ofs.close();
        if(this->mEmpArray != NULL) {
            for(int i = 0; i < this->empNum; i++) {
                delete this->mEmpArray[i];
                this->mEmpArray[i] = NULL;
            }

            delete[] this->mEmpArray;
            this->mEmpArray = NULL;
            this->empNum = 0;
            this->fileIsEmpty = true;
        }
        cout << "Clear successfully" << endl;
    }
    system("pause");
    system("cls");
}

WorkerManager::~WorkerManager() {
    if (this->mEmpArray != nullptr) {
        for (int i = 0; i < this->empNum; i++) {
            if (this->mEmpArray[i] != nullptr) {
                delete this->mEmpArray[i];
                this->mEmpArray[i] = nullptr;
            }
        }
        delete[] this->mEmpArray;
        this->mEmpArray = nullptr;
    }
}
