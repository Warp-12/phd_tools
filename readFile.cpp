#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string fileName = "./testOrigin.txt";
    std::ifstream inFile(fileName);
    std::string line;
    std::stringstream lineStream;

    if (!inFile) {
        std::cout << "Cannot open file!" << '\n';
        return 1;
    }
    std::string trash;
    int lineCounter = 0;
    int numberOfAtomsInFile = std::count(std::istreambuf_iterator<char>(inFile),
                                         std::istreambuf_iterator<char>(), '\n') -
                              9;
    inFile.close();
    inFile.open(fileName);

    double **table = new double *[numberOfAtomsInFile];
    for (int i = 0; i < numberOfAtomsInFile; i++) {
        table[i] = new double[4];
    }

    std::cout << "Number of atoms in file: " << numberOfAtomsInFile << '\n';

    int atomCounter = 0;

    while (std::getline(inFile, line)) {
        lineStream.str(line);

        if (lineCounter >= 9) {
            lineStream >> trash;
            lineStream >> trash;
            table[lineCounter - 9][0] = atomCounter + 1;
            lineStream >> table[lineCounter - 9][1];
            lineStream >> table[lineCounter - 9][2];
            lineStream >> table[lineCounter - 9][3];

            atomCounter++;
        }
        lineStream.clear();
        lineCounter++;
    }
    inFile.close();

    for (int i = 0; i < numberOfAtomsInFile; i++) {
        std::cout << "Count atoms: " << table[i][0] << '\n';
    }

    for (int i = 0; i < numberOfAtomsInFile; i++) {
        delete[] table[i];
    }

    delete[] table;
}