#pragma once

#ifndef MYFORM_H
#define MYFORM_H

#include <Windows.h>
#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Drawing;

class NumberFile {
private:
    std::vector<int> numbers;

public:
    NumberFile();

    std::vector<int> GetNumbers() const;

    void AddNumber(int number);

    void FilterAndIncreaseNumbers(int rangeStart, int rangeEnd, int increment);

    void WriteNumbersToFile(const std::string& outputPath);

    void ReadNumbersFromFile(const std::string& inputPath);
};

public ref class MainForm : public Form {
private:
    TextBox^ numberTextBox;
    TextBox^ rangeStartTextBox;
    TextBox^ rangeEndTextBox;
    TextBox^ incrementTextBox;
    TextBox^ inputFileTextBox;
    TextBox^ outputFileTextBox;
    Button^ addButton;
    Button^ runButton;
    Button^ loadButton;
    Button^ displayInputButton;
    Button^ displayOutputButton;
    Label^ resultLabel;
    Button^ createInputButton;

    NumberFile* numberFile;

public:
    MainForm();

    ~MainForm();

private:
    void InitializeComponents();

    void OnAddButtonClick(Object^ sender, EventArgs^ e);

    void OnLoadButtonClick(Object^ sender, EventArgs^ e);

    void OnCreateInputButtonClick(Object^ sender, EventArgs^ e);

    void OnRunButtonClick(Object^ sender, EventArgs^ e);

    void OnDisplayInputButtonClick(Object^ sender, EventArgs^ e);

    void OnDisplayOutputButtonClick(Object^ sender, EventArgs^ e);

    int ConvertToInt(System::String^ input);

    std::string ConvertToStdString(System::String^ input);

    std::string ConvertToStdStringg(System::String^ input);

    System::String^ ConvertToSystemString(const std::string& input);
};
#endif 