#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>


using namespace std;


map<string, int> symbolTable;


void firstPass(ifstream& inputFile) {
    string line;
    int locationCounter = 0;


    while (getline(inputFile, line)) {
        stringstream ss(line);
        string token;
        ss >> token;


        // Skip empty lines
        if (token.empty()) continue;


        // Check if it's a label
        if (token[token.length() - 1] == ':') {
            // Remove the colon from the label
            string label = token.substr(0, token.length() - 1);


            // Check if the label is already defined
            if (symbolTable.find(label) != symbolTable.end()) {
                cerr << "Error: Duplicate label '" << label << "'." << endl;
                exit(1);
            }


            // Add label to symbol table with its corresponding location
            symbolTable[label] = locationCounter;


            // Move to the next token, if there's any
            ss >> token;
        }


        // Check if it's a valid instruction
        if (token == "MOV" || token == "ADD" || token == "SUB" || token == "HLT" || token == "JNZ") {
            locationCounter++;
        } else if (!token.empty() && token[token.length() - 1] != ':') {
            // Report error for undefined instructions
            cerr << "Error: Undefined instruction or label '" << token << "'." << endl;
            exit(1);
        }
    }
}


int main() {
    ifstream inputFile("first_pass.asm");


    // Check if input file is open
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }


    // First pass: build symbol table
    firstPass(inputFile);


    // Close file
    inputFile.close();


    // Print the symbol table (for verification)
    cout << "Symbol Table:" << endl;
    for (const auto& pair : symbolTable) {
        cout << pair.first << " : " << pair.second << endl;
    }


    cout << "First pass complete." << endl;


    return 0;
}
