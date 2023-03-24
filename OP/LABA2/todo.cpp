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

string taskDescriptionToString(const char* description) {
    string str;
    for (int i = 0; i < 100; i++) {
        if (description[i] == '\0') {
            break;
        }
        str += description[i];
    }
    return str;
}

void createNewTask(Task& task) {
    cout << "Enter task description: ";
    cin.ignore(); 
    cin.getline(task.description, 100);

    cout << "Enter start time (24-hour clock in hh:mm format): ";
    string start_time_input;
    getline(cin, start_time_input);
    double start_time = stoi(start_time_input.substr(0, 2)) * 60 + stoi(start_time_input.substr(3, 2));
    task.start_time = start_time;

    cout << "Enter duration (in minutes): ";
    cin >> task.duration;
    return;
}

void addNewTask(const string& filename) {
    fstream file = openBinaryFile(filename, "app"); 
    if (!file) {
        cerr << "Error: could not open file " << filename << endl;
        return;
    }
    Task task;
    createNewTask(task);
    file.write(reinterpret_cast<char*>(&task), sizeof(task));
    file.close();
}

Task* getNextTask(const string& filename, int current_time_minutes) {
    fstream file = openBinaryFile(filename, "read");
    if (!file) {
        cerr << "Error: could not open file " << filename << endl;
        return nullptr;
    }

    Task* next_task = nullptr;
    Task task;
    int next_start_time = INT_MAX;
    while (file.read(reinterpret_cast<char*>(&task), sizeof(task))) {
        int task_end_time = task.start_time + task.duration;
        if (task.start_time >= current_time_minutes && task.start_time < next_start_time) {
            next_task = new Task(task);
            next_start_time = task.start_time;
        }
        else if (task.start_time < current_time_minutes && task_end_time > current_time_minutes && task_end_time < next_start_time) {
            next_task = new Task(task);
            next_start_time = task_end_time;
        }
    }

    file.close();
    if (next_task != nullptr) {
        next_task->description[sizeof(next_task->description) - 1] = '\0';
    }
    return next_task;
}

void createToDoList(const string& filename) {
    fstream file = openBinaryFile(filename, "write");
    if (!file) {
        cerr << "Error: could not create file " << filename << endl;
        return;
    }
    char option;
    while (true) {
        Task task;
        createNewTask(task);
        file.write(reinterpret_cast<char*>(&task), sizeof(task));
        cout << "Do you want to add another task? (y/n): ";
        cin >> option;
        if (option == 'n' || option == 'N') {
            break;
        }
    }
    file.close();
}

void printTask(const Task& task) {
    cout << "Task description: " << taskDescriptionToString(task.description) << endl;
    cout << "Start time: " << setfill('0') << setw(2) << static_cast<int>(task.start_time / 60) << ":" << setfill('0') << setw(2) << static_cast<int>(task.start_time) % 60 << endl;
    cout << "Duration: " << task.duration << " minutes" << endl;
}

void printSchedule(const string& filename) {
    fstream file = openBinaryFile(filename, "read");
    if (!file) {
        cerr << "Error: could not open file " << filename << endl;
        return;
    }
    vector<Task> tasks;
    Task task;
    while (file.read(reinterpret_cast<char*>(&task), sizeof(task))) {
        tasks.push_back(task);
    }
    sort(tasks.begin(), tasks.end(), [](const Task& t1, const Task& t2) {
        return t1.start_time < t2.start_time;
        });
    cout << "Schedule:" << endl;
    for (const Task& t : tasks) {
        printTask(t);
        cout << endl;
    }

    file.close();
}

void calculateFreeTime(const string& filename) {
    fstream file = openBinaryFile(filename, "read");
    if (!file) {
        cerr << "Error: could not open file " << filename << endl;
        return;
    }
    vector<Task> tasks;
    Task task;
    while (file.read(reinterpret_cast<char*>(&task), sizeof(task))) {
        tasks.push_back(task);
    }
    sort(tasks.begin(), tasks.end(), [](const Task& t1, const Task& t2) {
        return t1.start_time < t2.start_time;
        });
    file.close();

    ofstream outputFile("output.bin", ios::out | ios::binary);
    if (!outputFile) {
        cerr << "Error: could not open file output.bin for writing" << endl;
        return;
    }

    int last_end_time = 13 * 60;
    for (const Task& task : tasks) {
        if (task.start_time >= last_end_time) {
            int free_start_time = last_end_time;
            int free_end_time = task.start_time;
            int free_duration = free_end_time - free_start_time;
            string outputString = "FreeTime " + to_string(static_cast<int>(free_start_time / 60)) + ":" + to_string(free_start_time % 60) + "-" + to_string(static_cast<int>(free_end_time / 60)) + ":" + to_string(free_end_time % 60) + " " + to_string(free_duration) + " minutes\n";
            outputFile.write(outputString.c_str(), outputString.size());
        }
        int task_end_time = task.start_time + task.duration;
        last_end_time = max(last_end_time, task_end_time);
    }

    if (last_end_time < 21 * 60) {
        int free_start_time = last_end_time;
        int free_end_time = 21 * 60;
        int free_duration = free_end_time - free_start_time;
        string outputString = "FreeTime " + to_string(static_cast<int>(free_start_time / 60)) + ":" + to_string(free_start_time % 60) + "-" + to_string(static_cast<int>(free_end_time / 60)) + ":" + to_string(free_end_time % 60) + " " + to_string(free_duration) + " minutes\n";
        outputFile.write(outputString.c_str(), outputString.size());
    }

    outputFile.close();
}