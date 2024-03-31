#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

int main(int argc, char* argv[]) {
     if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    std::vector<unsigned char> A;
    unsigned int temp;
    while (inputFile >> temp) {
        A.push_back(static_cast<unsigned char>(temp));
    }

    inputFile.close();

    return 0;
}