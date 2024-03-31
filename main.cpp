#include <iostream>
#include <fstream>
#include <vector>

// Funkcija za branje vhodne datoteke
bool readFile(const char* filename, std::vector<unsigned char>& A) {
    std::ifstream inputFile(filename); // Vhodna datoteka
    // Preverjanje vhodne datoteke
    if (!inputFile) {
        std::cerr << "Error opening input file." << std::endl;
        return false;
    }

    unsigned int temp; // Začasna spremenljivka za branje števil

    // Branje števil iz datoteke
    while (inputFile >> temp) {
        A.push_back(static_cast<unsigned char>(temp)); // Pretvori v unsigned char in dodaj v vektor
    }
    inputFile.close(); // Zapri vhodno datoteko
    return true; 
}

// Funkcija za pisanje števil v datoteko
bool writeFile(const char* filename, const std::vector<unsigned char>& A) {
    std::ofstream outputFile(filename); // Izhodna datoteka
    // Preverjanje izhodne datoteke
    if (!outputFile) {
        std::cerr << "Error opening output file." << std::endl;
        return false;
    }

    // Zapiši sortirana števila v izhodno datoteko
    for (size_t i = 0; i < A.size(); i++) {
        // Izpiši števila ločena s presledki
        outputFile << static_cast<int>(A[i]) << (i < A.size() - 1 ? ' ' : '\n');
    }
    outputFile.close(); // Zapri izhodno datoteko
    return true;
}

// Funkcija za sortiranje glede na k-ti bit
void countingSort(std::vector<unsigned char>& A, int k) {
    int C[2] = {0}; // Polje za štetje kolikokrat se pojavi 0 in 1 na k-tem bitu
    std::vector<unsigned char> B(A.size()); // Začasni vektor za shranjevanje sortiranih elementov

    // Štetje pojavitve bitov
    for (size_t i = 0; i < A.size(); i++) {
        C[(A[i] >> k) & 1]++; // Izračunaj vrednost k-tega bita in povečaj števec
    }

    // Izračunaj kumulativno vsoto za določitev pozicij elementov
    C[1] += C[0];

    // Razporedi elemente v začasni vektor B glede na k-te bite
    for (int i = A.size() - 1; i >= 0; i--) {
        B[--C[(A[i] >> k) & 1]] = A[i]; // Dodeli element na pravilno mesto in zmanjšaj števec
    }

    // Kopiranje sortiranih elementov nazaj v originalni vektor A
    A = B;
}

int main(int argc, char* argv[]) {

    // Preverjanje argumentov
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    // Vektor za shranjevanje vhodnih števil
    std::vector<unsigned char> A; 

    // Uporabi funkcijo readFile za branje datoteke
    if (!readFile(argv[1], A)) { 
        return 1;
    }
    
    // Binarni radix sort za vsak bit
    for (int k = 0; k < 8; k++) {
        countingSort(A, k); // Sortiraj vektor A glede na k-ti bit
    }

    // Uporabi funkcijo writeFile za pisanje v datoteko
    if (!writeFile("out.txt", A)) { 
        return 1;
    }

    return 0;
}