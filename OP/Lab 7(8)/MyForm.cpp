#include "MyForm.h"

NumberFile::NumberFile() {}

std::vector<int> NumberFile::GetNumbers() const {
    return numbers;
}

    void NumberFile::AddNumber(int number) {
        numbers.push_back(number);
    }

    void NumberFile::FilterAndIncreaseNumbers(int rangeStart, int rangeEnd, int increment) {
        std::vector<int> filteredNumbers;
        bool numbersFound = false;  // Flag to check if numbers are found in the gap

        for (int number : numbers) {
            if (number >= rangeStart && number <= rangeEnd) {
                int result = number * increment;
                if (result < number) {
                    throw std::overflow_error("An overflow occurred during increment.");
                }
                filteredNumbers.push_back(result);
                numbersFound = true;  // Set the flag to true if numbers are found
            }
        }

        if (!numbersFound) {
            throw std::runtime_error("No numbers found in the specified gap.");
        }

        numbers = filteredNumbers;
    }

    void NumberFile::WriteNumbersToFile(const std::string& outputPath) {
        std::ofstream outputFile(outputPath, std::ios::binary);
        if (!outputFile) {
            throw std::runtime_error("Failed to open the output file.");
        }

        for (int number : numbers) {
            outputFile.write(reinterpret_cast<const char*>(&number), sizeof(int));
        }
        outputFile.close();
    }

    void NumberFile::ReadNumbersFromFile(const std::string& inputPath) {
        std::ifstream inputFile(inputPath, std::ios::binary);
        if (!inputFile) {
            throw std::runtime_error("Failed to open the input file.");
        }

        numbers.clear();

        inputFile.seekg(0, std::ios::end);
        int fileSize = inputFile.tellg();
        int numNumbers = fileSize / sizeof(int); 

        inputFile.seekg(0, std::ios::beg);

        numbers.reserve(numNumbers); 

        for (int i = 0; i < numNumbers; ++i) {
            int number;
            inputFile.read(reinterpret_cast<char*>(&number), sizeof(int));
            numbers.push_back(number);
        }

        inputFile.close();
    }


    MainForm::MainForm() {
        numberFile = new NumberFile();
        InitializeComponents();
    }

    MainForm::~MainForm() {
        delete numberFile;
    }

    void MainForm::InitializeComponents() {
        this->Text = "Number File Processor";
        this->Size = Drawing::Size(450, 450);
        this->StartPosition = FormStartPosition::CenterScreen;

        Label^ numberLabel = gcnew Label();
        numberLabel->Text = "Number:";
        numberLabel->Location = Point(10, 10);
        numberLabel->AutoSize = true;
        this->Controls->Add(numberLabel);

        Button^ createInputButton = gcnew Button();
        createInputButton->Text = "Create Input";
        createInputButton->Location = Point(310, 180);
        createInputButton->Size = Drawing::Size(80, 20);
        createInputButton->Click += gcnew EventHandler(this, &MainForm::OnCreateInputButtonClick);
        this->Controls->Add(createInputButton);


        numberTextBox = gcnew TextBox();
        numberTextBox->Location = Point(10, 30);
        numberTextBox->Size = Drawing::Size(100, 20);
        this->Controls->Add(numberTextBox);

        addButton = gcnew Button();
        addButton->Text = "Add";
        addButton->Location = Point(120, 30);
        addButton->Size = Drawing::Size(60, 20);
        addButton->Click += gcnew EventHandler(this, &MainForm::OnAddButtonClick);
        this->Controls->Add(addButton);

        Label^ rangeLabel = gcnew Label();
        rangeLabel->Text = "Range:";
        rangeLabel->Location = Point(10, 60);
        rangeLabel->AutoSize = true;
        this->Controls->Add(rangeLabel);

        rangeStartTextBox = gcnew TextBox();
        rangeStartTextBox->Location = Point(10, 80);
        rangeStartTextBox->Size = Drawing::Size(100, 20);
        this->Controls->Add(rangeStartTextBox);

        Label^ rangeToLabel = gcnew Label();
        rangeToLabel->Text = "to";
        rangeToLabel->Location = Point(120, 80);
        rangeToLabel->AutoSize = true;
        this->Controls->Add(rangeToLabel);

        rangeEndTextBox = gcnew TextBox();
        rangeEndTextBox->Location = Point(140, 80);
        rangeEndTextBox->Size = Drawing::Size(100, 20);
        this->Controls->Add(rangeEndTextBox);

        Label^ incrementLabel = gcnew Label();
        incrementLabel->Text = "Increment:";
        incrementLabel->Location = Point(10, 110);
        incrementLabel->AutoSize = true;
        this->Controls->Add(incrementLabel);

        incrementTextBox = gcnew TextBox();
        incrementTextBox->Location = Point(10, 130);
        incrementTextBox->Size = Drawing::Size(100, 20);
        this->Controls->Add(incrementTextBox);

        Label^ inputFileLabel = gcnew Label();
        inputFileLabel->Text = "Input File:";
        inputFileLabel->Location = Point(10, 160);
        inputFileLabel->AutoSize = true;
        this->Controls->Add(inputFileLabel);

        inputFileTextBox = gcnew TextBox();
        inputFileTextBox->Location = Point(10, 180);
        inputFileTextBox->Size = Drawing::Size(200, 20);
        this->Controls->Add(inputFileTextBox);

        loadButton = gcnew Button();
        loadButton->Text = "Load";
        loadButton->Location = Point(220, 180);
        loadButton->Size = Drawing::Size(60, 20);
        loadButton->Click += gcnew EventHandler(this, &MainForm::OnLoadButtonClick);
        this->Controls->Add(loadButton);

        Label^ outputFileLabel = gcnew Label();
        outputFileLabel->Text = "Output File:";
        outputFileLabel->Location = Point(10, 210);
        outputFileLabel->AutoSize = true;
        this->Controls->Add(outputFileLabel);

        outputFileTextBox = gcnew TextBox();
        outputFileTextBox->Location = Point(10, 230);
        outputFileTextBox->Size = Drawing::Size(200, 20);
        this->Controls->Add(outputFileTextBox);

        runButton = gcnew Button();
        runButton->Text = "Run";
        runButton->Location = Point(10, 270);
        runButton->Size = Drawing::Size(75, 23);
        runButton->Click += gcnew EventHandler(this, &MainForm::OnRunButtonClick);
        this->Controls->Add(runButton);

        displayInputButton = gcnew Button();
        displayInputButton->Text = "Display Input";
        displayInputButton->Location = Point(100, 270);
        displayInputButton->Size = Drawing::Size(100, 23);
        displayInputButton->Click += gcnew EventHandler(this, &MainForm::OnDisplayInputButtonClick);
        this->Controls->Add(displayInputButton);

        displayOutputButton = gcnew Button();
        displayOutputButton->Text = "Display Output";
        displayOutputButton->Location = Point(210, 270);
        displayOutputButton->Size = Drawing::Size(100, 23);
        displayOutputButton->Click += gcnew EventHandler(this, &MainForm::OnDisplayOutputButtonClick);
        this->Controls->Add(displayOutputButton);

        resultLabel = gcnew Label();
        resultLabel->Location = Point(10, 300);
        resultLabel->AutoSize = true;
        this->Controls->Add(resultLabel);
    }

    void MainForm::OnAddButtonClick(Object^ sender, EventArgs^ e) {
        int number = ConvertToInt(numberTextBox->Text);
        numberFile->AddNumber(number);
        numberTextBox->Text = "";
    }

    void MainForm::OnLoadButtonClick(Object^ sender, EventArgs^ e) {
        String^ inputFilePath = inputFileTextBox->Text;
        std::string inputFile = ConvertToStdString(inputFilePath);
        try {
            numberFile->ReadNumbersFromFile(inputFile);
            resultLabel->Text = "\nInput file loaded successfully.\nFile: " + inputFilePath;
        }
        catch (const std::exception& ex) {
            MessageBox::Show(ConvertToSystemString(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void MainForm::OnCreateInputButtonClick(Object^ sender, EventArgs^ e) {
        std::string inputFilePath = ConvertToStdStringg(inputFileTextBox->Text);
        try {
            numberFile->WriteNumbersToFile(inputFilePath);
            resultLabel->Text = "\nInput file created successfully.\nFile: " + inputFileTextBox->Text;
        }
        catch (const std::exception& ex) {
            MessageBox::Show(ConvertToSystemString(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void MainForm::OnRunButtonClick(Object^ sender, EventArgs^ e) {
        int rangeStart = ConvertToInt(rangeStartTextBox->Text);
        int rangeEnd = ConvertToInt(rangeEndTextBox->Text);
        int increment = ConvertToInt(incrementTextBox->Text);
        std::string outputFilePath = ConvertToStdString(outputFileTextBox->Text);

        try {
            numberFile->FilterAndIncreaseNumbers(rangeStart, rangeEnd, increment);
            numberFile->WriteNumbersToFile(outputFilePath);
            resultLabel->Text = "\nFile processed successfully.\nOutput file: " + outputFileTextBox->Text;
        }
        catch (const std::exception& ex) {
            MessageBox::Show(ConvertToSystemString(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void MainForm::OnDisplayInputButtonClick(Object^ sender, EventArgs^ e) {
        String^ inputFilePath = inputFileTextBox->Text;
        std::string inputFile = ConvertToStdString(inputFilePath);
        try {
            numberFile->ReadNumbersFromFile(inputFile);
            std::stringstream ss;
            ss << "\nInput numbers: ";
            for (int number : numberFile->GetNumbers()) {
                ss << number << " ";
            }
            resultLabel->Text = ConvertToSystemString(ss.str());
        }
        catch (const std::exception& ex) {
            MessageBox::Show(ConvertToSystemString(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void MainForm::OnDisplayOutputButtonClick(Object^ sender, EventArgs^ e) {
        String^ outputFilePath = outputFileTextBox->Text;
        std::string outputFile = ConvertToStdString(outputFilePath);
        try {
            numberFile->ReadNumbersFromFile(outputFile);
            std::stringstream ss;
            ss << "\nOutput numbers: ";
            for (int number : numberFile->GetNumbers()) {
                ss << number << " ";
            }
            resultLabel->Text = ConvertToSystemString(ss.str());
        }
        catch (const std::exception& ex) {
            MessageBox::Show(ConvertToSystemString(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    int MainForm::ConvertToInt(System::String^ input) {
        std::string strInput = ConvertToStdString(input);
        return std::stoi(strInput);
    }

    std::string MainForm::ConvertToStdString(System::String^ input) {
        return msclr::interop::marshal_as<std::string>(input);
    }

    std::string MainForm::ConvertToStdStringg(System::String^ input) {
        return msclr::interop::marshal_as<std::string>(input);
    }


    System::String^ MainForm::ConvertToSystemString(const std::string& input) {
        return gcnew System::String(input.c_str());
    }