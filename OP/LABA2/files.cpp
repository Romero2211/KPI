#define _CRT_SECURE_NO_WARNINGS

#include "files.h"
#include "todo.h"

using namespace std;

struct Task {
    char description[100] = "";
    double start_time = 0.0;
    int duration = 0;

    Task() = default;
};

string getFileName() {
    string filename;
    cout << "Enter file name: ";
    getline(cin, filename);
    return filename;
}

fstream openBinaryFile(const string& filename, const string& mode) {
    fstream file;
    if (mode == "read") {
        file.open(filename, ios::in | ios::binary);
    }
    else if (mode == "write") {
        file.open(filename, ios::out | ios::binary);
    }
    else if (mode == "app") {
        file.open(filename, ios::out | ios::binary | ios::app);
    }
    return file;
}

void menu() {
    setlocale(LC_ALL, "");
    string filename = getFileName();
    int choice;
    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Create a to-do list" << endl;
        cout << "2. View schedule" << endl;
        cout << "3. Get next task" << endl;
        cout << "4. Calculate free time" << endl;
        cout << "5. Exit" << endl;
        cout << "6. Add to to-do list" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            createToDoList(filename);
            break;
        case 2:
            printSchedule(filename);
            break;
        case 3: {
            cout << "Enter current time (24-hour clock in hh:mm format): ";
            string current_time_input;
            cin.ignore();
            getline(cin, current_time_input);
            int current_time_minutes = stoi(current_time_input.substr(0, 2)) * 60 + stoi(current_time_input.substr(3, 2));
            Task* next_task = getNextTask(filename, current_time_minutes);
            if (next_task) {
                cout << "Next task:" << endl;
                printTask(*next_task);
                delete next_task;
            }
            else {
                cout << "No tasks scheduled." << endl;
            }
            break;
        }
        case 4: {
            calculateFreeTime(filename);
            ifstream file("output.bin", ios::binary);
            if (file.is_open()) {
                char ch;
                while (file.read(&ch, sizeof(ch))) {
                    cout << ch;
                }
                file.close();
            }
            else {
                cerr << "Error" << endl;
            }
            break;
        }
        case 5:
            cout << "Exiting program..." << endl;
            return;
        case 6:
            addNewTask(filename);
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
        }
        cout << endl;
    }
}