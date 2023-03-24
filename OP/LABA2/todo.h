#pragma once
#ifndef TODO_H
#define TODO_H

#include <algorithm>
#include <iomanip>
#include <climits>
#include "files.h"


using namespace std;

struct Task;

string taskDescriptionToString(const char* description);

void createNewTask(Task& task);

void addNewTask(const string& filename);

Task* getNextTask(const string& filename, int current_time_minutes);

void createToDoList(const string& filename);

void printTask(const Task& task);

void printSchedule(const string& filename);

void calculateFreeTime(const string& filename);


#endif