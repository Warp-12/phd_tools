#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define BP(string) std::cout << (string) << "\n";
double calculateArea(double **basis_vectors) {
    double area = (basis_vectors[0][1] - basis_vectors[0][0]) *
                  (basis_vectors[1][1] - basis_vectors[1][0]);

    return area;
}
double calculateHeight(double **basis_vectors) {
    double high = basis_vectors[2][1] - basis_vectors[2][0];

    return high;
}
int checkInterval(double number, double range) {
    int floored_number = (int)number;

    double lower_bound = range * floored_number;
    double higher_bound = range * (floored_number + 1);

    int result;

    if (number >= lower_bound && number < higher_bound)
        result = floored_number;
    if (number < lower_bound)
        result = floored_number - 1;
    if (number >= higher_bound)
        result = floored_number + 1;
    return result;
}

//-------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    //---------------------------------------------------------------------------------
    //Initialise stream

    ifstream infile;
    ofstream outfile;

    string inname, outname, filename;
    stringstream namestream;
    stringstream linestream;
    string line;

    string inNameFile = argv[1];

    namestream << inNameFile; 

    infile.open(namestream.str().c_str());

    if (!infile) {
        cout << "File not exist!"
             << "\n";
        return 1;
    }

    int linecounter = 0;
    int n_atoms = 0;

    while (getline(infile, line)) {
        linecounter++;
        if (linecounter == 4) {
            linestream.str(line);
            linestream >> n_atoms;
            linestream.str("");
            linestream.clear();
        }
    }

    infile.close();
    infile.clear();


    double **box_vertices = new double *[3];  
    for (int dimension = 0; dimension < 3; dimension++) {
        box_vertices[dimension] = new double[3];
    }

    double **atoms = new double *[n_atoms];  
    for (int atom_id = 0; atom_id < n_atoms; atom_id++) {
        atoms[atom_id] = new double[4];
    }

    double height = 0.0;
    double dz = 1.0;

    int interval = 0;
    int elements = n_atoms;

    double **density_profile = new double *[elements]; 
    for (int count = 0; count < elements; count++) {
        density_profile[count] = new double[4];
    }

    infile.open(namestream.str().c_str());

    int timestep_counter = 0;
    int atom_counter = 0;
    int dimension_counter = 0;

    bool begin_timestep = false;
    bool begin_volume = false;
    bool begin_atoms = false;
    bool begin_analysis = false;

    double timestep_area;

    string trashcan;

    while (getline(infile, line)) {
        if (begin_timestep) {
            if (begin_volume) {
                linestream.str(line);

                linestream >> box_vertices[dimension_counter][0];
                linestream >> box_vertices[dimension_counter][1];

                if (!linestream.eof()) {
                    linestream >> box_vertices[dimension_counter][2];
                } else {
                    box_vertices[dimension_counter][2] = 0.0;
                }

                dimension_counter++;
                if (dimension_counter > 2) {
                    begin_volume = false;
                    dimension_counter = 0;
                }

                linestream.str("");
                linestream.clear();
            }

            if (begin_atoms) {
                int atom_type = 0;

                timestep_area = calculateArea(box_vertices);
                height = calculateHeight(box_vertices);

                linestream.str(line);
                linestream >> trashcan;
                linestream >> atom_type;

                for (int dimension = 0; dimension < 3; dimension++)
                    linestream >> atoms[atom_counter][dimension];

                atoms[atom_counter][3] = atom_type - 1;  
                atom_counter++;

                if (atom_counter == n_atoms - 1)  
                {
                    begin_timestep = false;  
                    begin_atoms = false;     
                    begin_volume = false;    

                    begin_analysis = true;  
                    atom_counter = 0;
                    timestep_counter++;  
                }
            }
        }
        if (begin_analysis) {
            double type_au = 1;
            double type_si = 0;

            for (double delta = 0.0; delta < height + 5.0; delta += dz) {
                for (int n = 0; n < n_atoms; n++) {
                    int ratio = delta / dz;
                    interval = checkInterval(ratio, dz);

                    if ((atoms[n][2] > delta - dz / 2) && (atoms[n][2] <= delta + dz / 2)) {
                        density_profile[interval][0]++;
                        double density_value = density_profile[interval][0] / timestep_area * dz;
                        density_profile[interval][1] = density_value;

                        if (atoms[n][3] == type_si) {
                            density_profile[interval][2]++;
                        }
                    }
                    if ((atoms[n][2] > delta - dz / 2) && (atoms[n][2] <= delta + dz / 2) && atoms[n][3] == type_au) {
                        density_profile[interval][3]++;
                    }
                }
            }

            begin_analysis = false;
            begin_timestep = false;
            begin_atoms = false;
            begin_volume = false;
        }
        if (!begin_analysis) 
        {
            if (line.find("TIMESTEP") < line.length() && !begin_timestep) {
                for (int dimension = 0; dimension < 3; dimension++) {
                    for (int bound = 0; bound < 3; bound++) {
                        box_vertices[dimension][bound] = 0.0;
                    }
                }
                timestep_area = 1.0;
                dimension_counter = 0;
                atom_counter = 0;
                begin_timestep = true;
            }
            if (line.find("BOUNDS") < line.length() && !begin_volume) {
                begin_volume = true;
            }
            if (line.find("id type x y z") < line.length() && !begin_atoms) {
                begin_atoms = true;
            }
        }
    }

    infile.close();

    int max = (height / dz) + 10;

    stringstream denname;

    denname << "profile_density.out";
    outfile.open(denname.str().c_str());

  
    for (int i = 0; i < max; i++) {
        if (density_profile[i][0] != 0) {
            outfile << i * dz / height << "  " << i * dz << "   " << density_profile[i][0]
                    << "   " << density_profile[i][1] / timestep_counter
                    << "   " << density_profile[i][2] / density_profile[i][0]
                    << "   " << density_profile[i][3] / density_profile[i][0] << "\n";
        }
    }

    outfile.close();
    outfile.clear();

    denname.str("");
    denname.clear();


    for (int atom_id = 0; atom_id < n_atoms; atom_id++)
        delete[] atoms[atom_id];
    delete[] atoms;

    for (int count = 0; count < elements; count++)
        delete[] density_profile[count];
    delete[] density_profile;

    for (int dimension = 0; dimension < 3; dimension++)
        delete[] box_vertices[dimension];
    delete[] box_vertices;

    return 0;
}
