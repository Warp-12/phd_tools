#include <algorithm>
#include <boost/filesystem.hpp>
#include <cfloat>
#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "/usr/include/libalglib/ap.h"
#include "/usr/include/libalglib/fasttransforms.h"
#include "/usr/include/libalglib/stdafx.h"
#include "rawstate/rawstate.h" #define BOOST_NO_CXX11_SCOPED_ENUMS
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <dirent.h>
#define GOOD_FILE_CRITERION temp_name != ".." && temp_name != "."

using namespace std;
using namespace alglib;
using namespace RawState;
using namespace RawStateLAMMPSTools;

#define REAL 0
#define IMAG 1

int parseInputFilenames(string *&filenames) {
    int n_files = 0;
    DIR *input_files_directory;
    struct dirent *input_file;

    if ((input_files_directory = opendir("./sample/")) != NULL) {
        while ((input_file = readdir(input_files_directory)) != NULL) {
            string temp_name = input_file->d_name;
            if (GOOD_FILE_CRITERION) {
                int file_extension_trj = 0;

                file_extension_trj = temp_name.find(".sample");

                if (file_extension_trj != -1) {
                    n_files++;
                }
            }
        }

        closedir(input_files_directory);

        filenames = new string[n_files];

        input_files_directory = opendir("./sample/");

        int counter = 0;
        stringstream namestream;

        while ((input_file = readdir(input_files_directory)) != NULL) {
            string temp_name = input_file->d_name;
            if (GOOD_FILE_CRITERION) {
                int file_extension_trj = 0;

                file_extension_trj = temp_name.find(".sample");

                if (file_extension_trj != -1) {
                    namestream << "./sample/" << temp_name;

                    filenames[counter] = namestream.str();

                    namestream.clear();
                    namestream.str("");

                    counter++;
                }
            }
        }

        closedir(input_files_directory);

    } else {
        return 0;
    }

    return n_files;
}

void readFile(const std::string &fileName) {
    std::ifstream inFile(fileName);
    std::string line;
    std::stringstream lineStream;

    if (!inFile) {
        std::cout << "Cannot open file!" << '\n';
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

int main() {
    ofstream outfile;

    std::string dumpfile = "./testExport.txt";

    RawState::setStateTimestep(0);
    RawState::setStateTimestepDelta(1);
    int number_of_readings = RawStateLAMMPSTools::getNumberOfReadings(dumpfile);

    System *atomSystem = new System;
    atomSystem->_readNextLAMMPSTimestep(dumpfile);

    Atom *currentAtom = new Atom[atomSystem->_n_atoms];

    for (size_t i = 0; i < atomSystem->_n_atoms; i++) {
        currentAtom[i]._createPositionsTable();

        currentAtom[i]._position[0] = atomSystem->_particles[i]._position[0];
        currentAtom[i]._position[1] = atomSystem->_particles[i]._position[1];
        currentAtom[i]._position[2] = atomSystem->_particles[i]._position[2];
    }

    double r_max = 2.82;

    double max_x = DBL_MIN;
    double min_x = DBL_MAX;
    double max_y = DBL_MIN;
    double min_y = DBL_MAX;
    double max_z = DBL_MIN;
    double min_z = DBL_MAX;

    int cluster_atoms = 0;
    for (size_t i = 0; i < atomSystem->_n_atoms - 1; i++) {
        if (i > 1) {
            double neighbourDistance = sqrt(pow(currentAtom[i + 1]._position[0] - currentAtom[i]._position[0], 2) +
                                            pow(currentAtom[i + 1]._position[1] - currentAtom[i]._position[1], 2) +
                                            pow(currentAtom[i + 1]._position[2] - currentAtom[i]._position[2], 2));

            if (neighbourDistance < r_max) {
                if (max_x < currentAtom[i]._position[0]) {
                    max_x = currentAtom[i]._position[0];
                }

                if (min_x > currentAtom[i]._position[0]) {
                    min_x = currentAtom[i]._position[0];
                }

                if (max_y < currentAtom[i]._position[1]) {
                    max_y = currentAtom[i]._position[1];
                }

                if (min_y > currentAtom[i]._position[1]) {
                    min_y = currentAtom[i]._position[1];
                }

                if (max_z < currentAtom[i]._position[2]) {
                    max_z = currentAtom[i]._position[2];
                }

                if (min_z > currentAtom[i]._position[2]) {
                    min_z = currentAtom[i]._position[2];
                }
            }
        }
    }

    double x_length = max_x - min_x;
    double y_length = max_y - min_y;
    double z_length = max_z - min_z;

    int nx_bins = x_length / r_max;
    int ny_bins = y_length / r_max;
    int nz_bins = z_length / r_max;

    double epsilon = 0.001;
    vector<double> atomInside_x;
    vector<double> atomInside_y;
    vector<double> atomInside_z;

    outfile.open("./histogram.txt");
    for (size_t j = 0; j < nx_bins; j++) {
        for (size_t k = 0; k < ny_bins; k++) {
            for (size_t i = 0; i < atomSystem->_n_atoms; i++) {
                if (currentAtom[i]._position[0] > j * r_max and currentAtom[i]._position[0] <= ((j + 1) * r_max + epsilon) and
                    currentAtom[i]._position[1] > k * r_max and currentAtom[i]._position[1] <= ((k + 1) * r_max + epsilon)) {
                    atomInside_x.push_back(currentAtom[i]._position[0]);
                    atomInside_y.push_back(currentAtom[i]._position[1]);
                    atomInside_z.push_back(currentAtom[i]._position[2]);

                    cluster_atoms++;
                }
            }
        }

        max_z = -100.0;
        int position = 0;
        int counter = 0;

        double average_bin_z = 0.0;

        for (size_t k = 0; k < atomInside_z.size(); k++) {
            if (atomInside_z[k] > max_z) {
                max_z = atomInside_z[k];
                position = k;
            }
            average_bin_z += atomInside_z[k];
        }
        average_bin_z /= atomInside_z.size();

        outfile << atomInside_x[position] << " "
                << atomInside_z[position] << " "
                << average_bin_z << "\n";

        atomInside_x.clear();
        atomInside_y.clear();
        atomInside_z.clear();
    }
    outfile.close();
    outfile.clear();

    ifstream infile;
    string inname, outname, filename;
    stringstream namestream;
    stringstream linestream;
    string line;
    string trashcan;

    namestream << "./histogram.txt";

    infile.open(namestream.str().c_str());

    int linecounter = 0;

    if (!infile) {
        cout << "File not exist!"
             << "\n";
    }

    while (getline(infile, line)) {
        linecounter++;

        linestream.str("");
        linestream.clear();
    }

    infile.close();
    infile.clear();

    double *dataArgument = new double[linecounter];

    double **atomIn = new double *[linecounter];
    for (int atom_id = 0; atom_id < linecounter; atom_id++)
        atomIn[atom_id] = new double[4];

    infile.open(namestream.str().c_str());

    linecounter = 0;
    string tmp;
    while (getline(infile, line)) {
        linestream.str(line);

        linestream >> atomIn[linecounter][0];
        linestream >> atomIn[linecounter][1];
        linestream >> atomIn[linecounter][2];

        dataArgument[linecounter] = atomIn[linecounter][2];

        linestream.str("");
        linestream.clear();
        linecounter++;
    }

    infile.close();
    infile.clear();

    alglib::real_1d_array x1;
    x1.setcontent(linecounter, dataArgument);

    alglib::complex_1d_array f;
    alglib::real_1d_array x2;
    fftr1d(x1, f);

    double **magnitude = new double *[linecounter];

    for (int i = 0; i < linecounter; i++) {
        magnitude[i] = new double[3];
    }

    double max_magnitude = -INT_MAX;

    for (int i = 0; i < linecounter; i++) {
        magnitude[i][0] = i * ((2 * 3.14159265359) / x_length);
        magnitude[i][1] = f[i].x * f[i].x + f[i].y * f[i].y;
    }

    int max_index = 0;
    for (int i = 0; i < linecounter; i++) {
        if (magnitude[i][1] > max_magnitude) {
            max_magnitude = magnitude[i][1];
            max_index = i;
        }
    }

    // double k_b = 1.380649;
    // double T_m = 1687.0;

    // double interfacialEnergy = 0.0;
    // for (size_t i = 0; i < linecounter; i++)
    // {
    //     interfacialEnergy = (k_b * T_m / x_length * averageMagnitude) * (1 / (magnitude[i][0] * magnitude[i][0]));
    //     magnitude[i][2] = interfacialEnergy;
    //     cout << "INTERFACIAL ENERGY :    " << interfacialEnergy << '\n';
    // }

    cout << "MAX MAGNITUDE :    " << max_magnitude << '\n';
    double freq = max_index * max_magnitude / linecounter;
    cout << "FREQUANCY :    " << freq << '\n';
    //-------------------------------------------------------------------------------
    outname = "./result_fft.out";

    outfile.open(outname.c_str());

    for (int i = 0; i < linecounter; i++) {
        outfile << magnitude[i][0] << "   " << magnitude[i][1] << "    " << magnitude[i][2] << endl;
    }

    outfile.close();
    //-------------------------------------------------------------------------------

    for (int i = 0; i < linecounter; i++) {
        delete[] magnitude[i];
    }
    delete[] magnitude;

    for (int atom_id = 0; atom_id < linecounter; atom_id++) {
        delete[] atomIn[atom_id];
    }
    delete[] atomIn;

    delete[] dataArgument;
}