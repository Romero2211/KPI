#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>
#include "todo.h"

#ifndef FILES_H
#define FILES_H

using namespace std;

string getFileName();

fstream openBinaryFile(const string& filename, const string& mode);

void menu();

#endif