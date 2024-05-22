#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

struct Symbol {
    std::string name;
    int address;
    bool defined;
    int fileIndex;
};

struct Relocation {
    std::string symbol;
    int offset;
    int fileIndex;
};

struct ObjectFile {
    std::vector<int> code;              // Code section
    std::unordered_map<std::string, int> symbols; // Defined symbols
    std::vector<Relocation> relocations; // Relocation entries
};

void readObjectFile(const std::string& filename, ObjectFile& objFile, int fileIndex) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    int codeSize;
    file >> codeSize;
    objFile.code.resize(codeSize);
    for (int i = 0; i < codeSize; ++i) {
        file >> objFile.code[i];
    }

    int numSymbols;
    file >> numSymbols;
    for (int i = 0; i < numSymbols; ++i) {
        std::string name;
        int address;
        file >> name >> address;
        objFile.symbols[name] = address;
    }

    int numRelocations;
    file >> numRelocations;
    for (int i = 0; i < numRelocations; ++i) {
        Relocation reloc;
        file >> reloc.symbol >> reloc.offset;
        reloc.fileIndex = fileIndex;
        objFile.relocations.push_back(reloc);
    }

    file.close();
}

void link(const std::vector<std::string>& filenames, const std::string& outputFilename) {
    std::vector<ObjectFile> objectFiles(filenames.size());
    std::unordered_map<std::string, Symbol> globalSymbols;

    // Step 1: Read all object files and collect symbols
    for (int i = 0; i < filenames.size(); ++i) {
        readObjectFile(filenames[i], objectFiles[i], i);
        for (const auto& sym : objectFiles[i].symbols) {
            if (globalSymbols.find(sym.first) != globalSymbols.end()) {
                std::cerr << "Symbol redefinition: " << sym.first << std::endl;
                exit(1);
            }
            globalSymbols[sym.first] = { sym.first, sym.second, true, i };
        }
    }

    // Step 2: Resolve relocations
    for (const auto& objFile : objectFiles) {
        for (const auto& reloc : objFile.relocations) {
            if (globalSymbols.find(reloc.symbol) == globalSymbols.end()) {
                std::cerr << "Undefined symbol: " << reloc.symbol << std::endl;
                exit(1);
            }
        }
    }

    // Step 3: Generate the final executable
    std::vector<int> finalCode;
    for (const auto& objFile : objectFiles) {
        finalCode.insert(finalCode.end(), objFile.code.begin(), objFile.code.end());
    }

    for (const auto& objFile : objectFiles) {
        for (const auto& reloc : objFile.relocations) {
            Symbol sym = globalSymbols[reloc.symbol];
            finalCode[reloc.offset] += sym.address;
        }
    }

    // Step 4: Write the output executable
    std::ofstream outputFile(outputFilename, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error opening output file: " << outputFilename << std::endl;
        exit(1);
    }

    for (int code : finalCode) {
        outputFile.write(reinterpret_cast<const char*>(&code), sizeof(code));
    }

    outputFile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " output_file obj_files..." << std::endl;
        return 1;
    }

    std::string outputFilename = argv[1];
    std::vector<std::string> inputFilenames;
    for (int i = 2; i < argc; ++i) {
        inputFilenames.push_back(argv[i]);
    }

    link(inputFilenames, outputFilename);

    std::cout << "Linking completed. Output file: " << outputFilename << std::endl;

    return 0;
}
