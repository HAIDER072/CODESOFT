#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct ToDo {
    int id;
    string task;
};

int ID;

void banner();
void addTask();
void showTask();
int searchTask();
void deleteTask();
void updateTask();

int main() {
    while (true) {
        banner();
        cout << "\n\t1. Add Task";
        cout << "\n\t2. Show Task";
        cout << "\n\t3. Search Task";
        cout << "\n\t4. Delete Task";
        cout << "\n\t5. Update Task";
        cout << "\n\t6. Exit";

        int choice;
        cout << "\n\tEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                showTask();
                break;
            case 3:
                searchTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                updateTask();
                break;
            case 6:
                exit(0);
            default:
                cout << "\n\tInvalid choice!";
        }
    }
    return 0;
}

void banner() {
    cout << "___________________________________" << endl;
    cout << "\t MY TODO" << endl;
    cout << "___________________________________" << endl;
}

void addTask() {
    banner();
    ToDo todo;
    cout << "Enter new Task: ";
    cin.ignore();
    getline(cin, todo.task);

    char save;
    cout << "Save (y/n): ";
    cin >> save;

    if (save == 'y') {
        ID++;
        ofstream fout("todo.txt", ios::app);
        if (!fout.is_open()) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        fout << "\n" << ID;
        fout << "\n" << todo.task;
        fout.close();

        char more;
        cout << "Add more Task? (y/n): ";
        cin >> more;
        if (more == 'y') {
            addTask();
        } else {
            system("cls");
            cout << "Added Successfully" << endl;
            return;
        }
    }
}

void showTask() {
    banner();
    ToDo todo;
    ifstream fin("todo.txt");
    if (!fin.is_open()) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    cout << "Task : " << endl;
    while (fin >> todo.id) {
        fin.ignore();
        getline(fin, todo.task);
        if (todo.task != "") {
            cout << "\t" << todo.id << ": " << todo.task << endl;
        } else {
            cout << "\tEmpty!" << endl;
        }
    }

    fin.close();

    char exit;
    cout << "Exit (y/n): ";
    cin >> exit;

    if (exit != 'y') {
        showTask();
    }
    system("cls");
}

int searchTask() {
    banner();
    int id;
    cout << "Enter task id: ";
    cin >> id;

    ToDo todo;
    ifstream fin("todo.txt");

    while (fin >> todo.id) {
        fin.ignore();
        getline(fin, todo.task);
        if (todo.id == id) {
            cout << "\t" << todo.id << ": " << todo.task << endl;
            fin.close();
            return id;
        }
    }

    fin.close();
    system("cls");
    cout << "Not Found!" << endl;
    return 0;
}

void deleteTask() {
    system("cls");
    int id = searchTask();
    if (id != 0) {
        char del;
        cout << "\n\tDelete? (y/n): ";
        cin >> del;

        if (del == 'y') {
            ToDo todo;
            ofstream tempFile("temp.txt");
            ifstream fin("todo.txt");
            int index = 1;

            while (fin >> todo.id) {
                fin.ignore();
                getline(fin, todo.task);
                if (todo.id != id) {
                    tempFile << "\n" << index;
                    tempFile << "\n" << todo.task;
                    index++;
                    ID--;
                }
            }

            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");
            system("cls");
            cout << "\n\tDelete Successfully!" << endl;
        } else {
            system("cls");
            cout << "\n\tNot Deleted" << endl;
        }
    }
}

void updateTask() {
    system("cls");
    int id = searchTask();
    if (id != 0) {
        ToDo todo;
        ofstream tempFile("temp.txt");
        ifstream fin("todo.txt");

        while (fin >> todo.id) {
            fin.ignore();
            getline(fin, todo.task);
            if (todo.id == id) {
                cout << "\n\tEnter updated task: ";
                cin.ignore();
                getline(cin, todo.task);
            }
            tempFile << "\n" << todo.id;
            tempFile << "\n" << todo.task;
        }

        fin.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        system("cls");
        cout << "\n\tUpdate Successfully!" << endl;
    }
}
