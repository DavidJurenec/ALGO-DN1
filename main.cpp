#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

// Funkcija za sortiranje glede na k-ti bit
void countingSort(std::vector<unsigned char>& A, int k) {
    int C[2] = {0}; // Polje za štetje kolikokrat se pojavi 0 in 1 na k-tem bitu
    std::vector<unsigned char> B(A.size()); // Začasni vektor za shranjevanje sortiranih elementov

    // Štetj pojavitev bitov
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

    // Vhodna datoteka
    std::ifstream inputFile(argv[1]); 

    // Preverjanje vhodne datoteke
    if (!inputFile) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }
    
    std::vector<unsigned char> A; // Vektor za shranjevanje vhodnih števil
    unsigned int temp; // Začasna spremenljivka za branje števil
    while (inputFile >> temp) { // Branje števil iz datoteke
        A.push_back(static_cast<unsigned char>(temp)); // Pretvori v unsigned char in dodaj v vektor
    }

    // Zapri vhodno datoteko
    inputFile.close(); 

    // Izvedi Binarni Radix Sort za vsak bit
    for (int k = 0; k < 8; k++) {
        countingSort(A, k); // Sortiraj vektor A glede na k-ti bit
    }

    // Izhodna datoteka
    std::ofstream outputFile("out.txt");

    // Preverjanje izhodne datoteke
    if (!outputFile) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    // Zapiši sortirana števila v izhodno datoteko
    for (size_t i = 0; i < A.size(); i++) {
        outputFile << static_cast<int>(A[i]) << (i < A.size() - 1 ? ' ' : '\n'); // Izpiši števila ločena s presledki
    }

    // Zapri izhodno datoteko
    outputFile.close(); 

    return 0;
}