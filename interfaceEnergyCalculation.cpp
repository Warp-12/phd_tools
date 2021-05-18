#include <algorithm>
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
#include "parseFiles.hpp"
#include "rawstate/rawstate.h"

using namespace std;
using namespace alglib;
using namespace RawState;
using namespace RawStateLAMMPSTools;

#define REAL 0
#define IMAG 1

int main()
{

    std::string *names;
    int number_of_files = parseInputFilenames(names);

    cout << "NUMBER OF FILES READ: " << number_of_files << "\n";
    
    double x_length = 0.0;
    double y_length = 0.0;
    double z_length = 0.0;
    ofstream outfile;
    double ***averaged = new double **[number_of_files];
    int width = INT_MAX;

    double r_max = 2.82;
    double max_x = DBL_MIN;
    double min_x = DBL_MAX;
    double max_y = DBL_MIN;
    double min_y = DBL_MAX;
    double max_z = DBL_MIN;
    double min_z = DBL_MAX;

    int cluster_atoms = 0;

    int nx_bins = 0;
    int ny_bins = 0;
    int nz_bins = 0;
    int position = 0;
    int counter = 0;

    double average_bin_z = 0.0;
    long unsigned int numberOfAtomsInFile = 0;

    double epsilon = 0.001;

    vector<double> atomInside_z;

    for (int file = 0; file < number_of_files; file++)
    {
        
        std::string dumpFile = names[file]; 
        std::ifstream inFile(dumpFile);
        numberOfAtomsInFile = std::count(std::istreambuf_iterator<char>(inFile),
                                         std::istreambuf_iterator<char>(), '\n');
        numberOfAtomsInFile -= 9;

        inFile.clear();
        inFile.close();

        double **atomSystemTable = readFile(dumpFile, (int)numberOfAtomsInFile);

        Atom *currentAtom = new Atom[numberOfAtomsInFile];

        for (size_t i = 0; i < numberOfAtomsInFile; i++)
        {
            currentAtom[i]._createPositionsTable();

            currentAtom[i]._position[0] = atomSystemTable[i][1];
            currentAtom[i]._position[1] = atomSystemTable[i][2];
            currentAtom[i]._position[2] = atomSystemTable[i][3];
        }

        for (int i = 0; i < numberOfAtomsInFile; i++)
        {
            delete[] atomSystemTable[i];
        }
        delete[] atomSystemTable;

        cluster_atoms = 0;

        for (size_t i = 0; i < numberOfAtomsInFile; i++)
        {
            if (i > 1)
            {
                if (i < numberOfAtomsInFile - 1)
                {
                    double neighbourDistance = sqrt(pow(currentAtom[i + 1]._position[0] - currentAtom[i]._position[0], 2) +
                                                    pow(currentAtom[i + 1]._position[1] - currentAtom[i]._position[1], 2) +
                                                    pow(currentAtom[i + 1]._position[2] - currentAtom[i]._position[2], 2));

                    max_x = std::max(max_x, currentAtom[i]._position[0]);
                    min_x = std::min(min_x, currentAtom[i]._position[0]);
                    max_y = std::max(max_y, currentAtom[i]._position[1]);
                    min_y = std::min(min_y, currentAtom[i]._position[1]);
                    max_z = std::max(max_z, currentAtom[i]._position[2]);
                    min_z = std::min(min_z, currentAtom[i]._position[2]);
                }
            }
        }

        x_length = max_x - min_x;
        y_length = max_y - min_y;
        z_length = max_z - min_z;

        nx_bins = static_cast<int>(x_length / r_max);
        ny_bins = static_cast<int>(y_length / r_max);
        nz_bins = static_cast<int>(z_length / r_max);

        double **table = new double *[static_cast<long unsigned int>(nx_bins)];
        for (int i = 0; i < nx_bins; i++)
        {
            table[i] = new double[2];
        }

        for (size_t j = 0; j < static_cast<long unsigned int>(nx_bins); j++)
        {
            for (size_t k = 0; k < static_cast<long unsigned int>(ny_bins); k++)
            {
                for (size_t i = 0; i < numberOfAtomsInFile; i++)
                {
                    if (currentAtom[i]._position[0] > j * r_max and currentAtom[i]._position[0] <= ((j + 1) * r_max + epsilon) and
                        currentAtom[i]._position[1] > k * r_max and currentAtom[i]._position[1] <= ((k + 1) * r_max + epsilon))
                    {
                        atomInside_z.push_back(currentAtom[i]._position[2]);

                        cluster_atoms++;
                    }
                }
            }

            max_z = DBL_MIN;
            position = 0;
            counter = 0;
            average_bin_z = 0.0;

            for (size_t k = 0; k < atomInside_z.size(); k++)
            {
                if (atomInside_z[k] > max_z)
                {
                    max_z = atomInside_z[k];
                    position = k;
                }
                average_bin_z += atomInside_z[k];
            }

            average_bin_z /= atomInside_z.size();

            table[j][0] = ((2 * j + 1) * r_max) / 2;
            table[j][1] = average_bin_z;

            atomInside_z.clear();
        }

        width = std::min(width, nx_bins);

        moveToAverageTable(width, table, file, averaged[file]);

        for (int i = 0; i < nx_bins; i++)
        {
            delete[] table[i];
        }
        delete[] table;
    }
    
    double **averageProfileTable = new double *[width];
    AverageOverFiles(number_of_files, width, averaged, averageProfileTable);

    for (int i = 0; i < width; i++)
    {
        delete[] averageProfileTable[i];
    }
    delete[] averageProfileTable;

    // Begin FTT transform

    ifstream infile;
    string inname, outname, filename, line, trashcan;
    stringstream namestream, linestream;

    namestream << "./output/mean_profile.out";

    infile.open(namestream.str().c_str());

    int linecounter = 0;

    if (!infile)
    {
        cout << "File not exist!"
             << "\n";
    }

    while (getline(infile, line))
    {
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
    while (getline(infile, line))
    {
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

    for (int i = 0; i < linecounter; i++)
    {
        magnitude[i] = new double[3];
    }

    double max_magnitude = -INT_MAX;

    for (int i = 0; i < linecounter; i++)
    {
        magnitude[i][0] = i * ((2 * 3.14159265359) / x_length);
        magnitude[i][1] = f[i].x * f[i].x + f[i].y * f[i].y;
    }

    int max_index = 0;
    for (int i = 0; i < linecounter; i++)
    {
        if (magnitude[i][1] > max_magnitude)
        {
            max_magnitude = magnitude[i][1];
            max_index = i;
        }
    }

    double k_b = 1.380649;
    double T_m = 1687.0;

    double interfacialEnergy = 0.0;
    for (size_t i = 0; i < linecounter; i++)
    {
         interfacialEnergy = (k_b * T_m / x_length * averageMagnitude) * (1 / (magnitude[i][0] * magnitude[i][0]));
         magnitude[i][2] = interfacialEnergy;
         cout << "INTERFACIAL ENERGY :    " << interfacialEnergy << '\n';
    }

    cout << "MAX MAGNITUDE :    " << max_magnitude << '\n';
    double freq = max_index * max_magnitude / linecounter;
    cout << "FREQUANCY :    " << freq << '\n';
    //-------------------------------------------------------------------------------
    outname = "./result_fft.out";

    outfile.open(outname.c_str());

    for (int i = 0; i < linecounter; i++)
    {
        outfile << magnitude[i][0] << "   " << magnitude[i][1] << "    " << magnitude[i][2] << endl;
    }

    outfile.close();
    //-------------------------------------------------------------------------------

    for (int i = 0; i < linecounter; i++)
    {
        delete[] magnitude[i];
    }
    delete[] magnitude;

    for (int atom_id = 0; atom_id < linecounter; atom_id++)
    {
        delete[] atomIn[atom_id];
    }
    delete[] atomIn;

    delete[] dataArgument;

    //---------------------------------------------------------

    for (int file = 0; file < number_of_files; file++)
    {
        for (int row = 0; row < width; row++)
        {
            delete[] averaged[file][row];
        }

        delete[] averaged[file];
    }

    delete[] averaged;
}
