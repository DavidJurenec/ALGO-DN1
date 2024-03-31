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

    std::ofstream outputFile("out.txt");
    if (!outputFile) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    for (size_t i = 0; i < A.size(); i++) {
        outputFile << static_cast<int>(A[i]) << (i < A.size() - 1 ? ' ' : '\n');
    }

    outputFile.close();

    return 0;
}