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

ofstream logfile;

double scalarProduct(double *vector_a, double *vector_b) {
    double product = 0.0;

    for (int i = 0; i < 3; i++)
        product += vector_a[i] * vector_b[i];

    return product;
}
void calculateBoxBasisVectors(double **vertices, double **&vectors, double *&point_of_origin) {
    double **triclinic_parameters = new double *[3];
    for (int dimension = 0; dimension < 3; dimension++)
        triclinic_parameters[dimension] = new double[2];

    vector<double> values;

    values.push_back(0.0);
    values.push_back(vertices[0][2]);
    values.push_back(vertices[1][2]);
    values.push_back(vertices[0][2] + vertices[1][2]);

    triclinic_parameters[0][0] = vertices[0][0] - *min_element(values.begin(), values.end());
    triclinic_parameters[0][1] = vertices[0][1] - *max_element(values.begin(), values.end());

    triclinic_parameters[1][0] = vertices[1][0] - min(0.0, vertices[2][2]);
    triclinic_parameters[1][1] = vertices[1][1] - max(0.0, vertices[2][2]);

    triclinic_parameters[2][0] = vertices[2][0];
    triclinic_parameters[2][1] = vertices[2][1];

    point_of_origin[0] = triclinic_parameters[0][0];
    point_of_origin[1] = triclinic_parameters[1][0];
    point_of_origin[2] = triclinic_parameters[2][0];

    vectors[0][0] = triclinic_parameters[0][1] - triclinic_parameters[0][0];
    vectors[0][1] = 0.0;
    vectors[0][2] = vectors[0][1];

    vectors[1][0] = vertices[0][2];
    vectors[1][1] = triclinic_parameters[1][1] - triclinic_parameters[1][0];
    vectors[1][2] = 0.0;

    vectors[2][0] = vertices[1][2];
    vectors[2][1] = vertices[2][2];
    vectors[2][2] = triclinic_parameters[2][1] - triclinic_parameters[2][0];

    logfile << "\nTRICLINIC BOX VECTORS\n";

    for (int dimension = 0; dimension < 3; dimension++) {
        logfile << "Vector " << dimension + 1 << " : ( ";
        for (int component = 0; component < 3; component++) {
            logfile << vectors[dimension][component] << " ";
        }
        logfile << ")\n";
    }

    for (int dimension = 0; dimension < 3; dimension++)
        delete[] triclinic_parameters[dimension];
    delete[] triclinic_parameters;
}
double calculateBoxVolume(double **basis_vectors) {
    double volume = basis_vectors[0][0] * (basis_vectors[1][1] * basis_vectors[2][2] - basis_vectors[2][1] * basis_vectors[1][2]) - basis_vectors[0][1] * (basis_vectors[1][0] * basis_vectors[2][2] - basis_vectors[2][0] * basis_vectors[1][2]) + basis_vectors[0][2] * (basis_vectors[1][0] * basis_vectors[2][1] - basis_vectors[2][0] * basis_vectors[1][1]);
    logfile << "\nBOX VOLUME : " << volume << "\n";
    return volume;
}
void normalizeBasisVectors(double **&basis_vectors) {
    double norm = 0.0;

    for (int dimension = 0; dimension < 3; dimension++) {
        norm = scalarProduct(basis_vectors[dimension], basis_vectors[dimension]);
        norm = sqrt(norm);
        basis_vectors[dimension][3] = norm;
    }
}
void checkAtomWrapping(double *&atom_position, double **basis_vectors, double *point_of_origin) {
    for (int dimension = 0; dimension < 3; dimension++) {
        atom_position[dimension] -= point_of_origin[dimension];
        atom_position[dimension] = scalarProduct(atom_position, basis_vectors[dimension]);
        atom_position[dimension] /= basis_vectors[dimension][3] * basis_vectors[dimension][3];

        if (atom_position[dimension] < 0.0)
            atom_position[dimension] += 1.0;
        if (atom_position[dimension] > 1.0)
            atom_position[dimension] -= 1.0;
    }
}
bool checkPeriodicCoundaryConditions(double *position_i, double *position_j, double **box, double r_cut, double &dr) {
    double da = 0.0;
    double db = 0.0;
    double dc = 0.0;
    dr = 0.0;

    da = position_j[0] - position_i[0];
    db = position_j[1] - position_i[1];
    dc = position_j[2] - position_i[2];

    if (da > 0.5) da -= 1.0;
    if (da <= -0.5) da += 1.0;

    if (db > 0.5) db -= 1.0;
    if (db <= -0.5) db += 1.0;

    if (dc > 0.5) dc -= 1.0;
    if (dc <= -0.5) dc += 1.0;

    da *= box[0][3];
    db *= box[1][3];
    dc *= box[2][3];

    dr = (da * da) + (db * db) + (dc * dc);
    dr = sqrt(dr);

    bool final_check;

    if (dr <= r_cut) final_check = true;
    if (dr > r_cut) final_check = false;

    return final_check;
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
int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Input bin width!!!!\n";
        return 1;
    }
    if (argc < 3) {
        cout << "Input RDF cutoff radius!!!!\n";
        return 1;
    }

    stringstream argstream;
    argstream << argv[1] << " " << argv[2];

    std::ifstream infile;
    ofstream outfile;

    string inname, outname, filename;
    stringstream namestream;
    stringstream linestream;
    std::string line;

    namestream << "./alcu_100K.txt";

    //filename = namestream.str();

    infile.open(namestream.str().c_str());

    if (!infile) {
        cout << "File not exist!"
             << "\n";
        return 1;
    }

    int linecounter = 0;
    int n_atoms = 0;

    while (std::getline(infile, line)) {
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

    double r_max;
    double dr;

    argstream >> dr;
    argstream >> r_max;

    int n_bins = (int)r_max / dr + 10;

    int *bin_count = new int[n_bins];
    for (int bin = 0; bin < n_bins; bin++)
        bin_count[bin] = 0;

    int *timestep_bin_count = new int[n_bins];
    for (int bin = 0; bin < n_bins; bin++)
        timestep_bin_count[bin] = 0;

    double *gr = new double[n_bins];
    for (int bin = 0; bin < n_bins; bin++)
        gr[bin] = 0.0;

    double **box_vertices = new double *[3];
    for (int dimension = 0; dimension < 3; dimension++)
        box_vertices[dimension] = new double[3];

    double **box_vectors = new double *[3];
    for (int dimension = 0; dimension < 3; dimension++)
        box_vectors[dimension] = new double[4];

    double *origin = new double[3];

    double timestep_volume;

    double **atoms = new double *[n_atoms];
    for (int atom_id = 0; atom_id < n_atoms; atom_id++)
        atoms[atom_id] = new double[3];

    infile.open(namestream.str().c_str());
    logfile.open("./log.out");

    int timestep_counter = 0;
    int atom_counter = 0;

    bool begin_timestep = false;
    bool begin_volume = false;
    bool begin_atoms = false;
    bool begin_analysis = false;
    int dimension_counter = 0;

    string trashcan;
    //---------------------------------------------------------------------------------
    while (std::getline(infile, line)) {
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
                    calculateBoxBasisVectors(box_vertices, box_vectors, origin);
                    normalizeBasisVectors(box_vectors);
                    timestep_volume = calculateBoxVolume(box_vectors);
                    begin_volume = false;
                }

                linestream.str("");
                linestream.clear();
            }
            if (begin_atoms) {
                linestream.str(line);
                linestream >> trashcan;
                linestream >> trashcan;

                for (int dimension = 0; dimension < 3; dimension++)
                    linestream >> atoms[atom_counter][dimension];
                atom_counter++;

                if (atom_counter == n_atoms - 1) {
                    begin_timestep = false;
                    begin_atoms = false;
                    begin_volume = false;
                    begin_analysis = true;
                    timestep_counter++;
                }
            }
        }
        if (begin_analysis) {
            bool good_pair = false;
            int number_of_pairs = 0.5 * (n_atoms * (n_atoms - 1));
            int interval = 0;

            for (int bin = 0; bin < n_bins; bin++) {
                timestep_bin_count[bin] = 0;
            }

            for (int atom_id = 0; atom_id < n_atoms; atom_id++) {
                checkAtomWrapping(atoms[atom_id], box_vectors, origin);
            }

            double r_ij = 0.0;
            double *r_i = new double[3];
            double *r_j = new double[3];

            for (int atom_i = 0; atom_i < n_atoms; atom_i++) {
                for (int atom_j = atom_i + 1; atom_j < n_atoms; atom_j++) {
                    r_ij = 0.0;

                    for (int dimension = 0; dimension < 3; dimension++) {
                        r_i[dimension] = atoms[atom_i][dimension];
                        r_j[dimension] = atoms[atom_j][dimension];
                    }

                    good_pair = checkPeriodicCoundaryConditions(r_i, r_j, box_vectors, r_max, r_ij);

                    if (good_pair) {
                        double ratio = r_ij / dr;
                        interval = checkInterval(ratio, dr);
                        timestep_bin_count[interval]++;
                    }
                }
            }

            delete[] r_i;
            delete[] r_j;

            for (int bin = 0; bin < n_bins; bin++) {
                bin_count[bin] += timestep_bin_count[bin];
                gr[bin] += (timestep_bin_count[bin] * timestep_volume) / (number_of_pairs * 4 * M_PI * (bin * dr) * (bin * dr) * dr);
            }

            begin_analysis = false;
            begin_timestep = false;
            begin_atoms = false;
            begin_volume = false;
        }
        if (!begin_analysis) {
            if (line.find("TIMESTEP") < line.length() && !begin_timestep) {
                for (int dimension = 0; dimension < 3; dimension++)
                    for (int bound = 0; bound < 3; bound++)
                        box_vertices[dimension][bound] = 0.0;

                timestep_volume = 1.0;
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
    outfile.open("./histogram.out");

    for (int bin = 0; bin < n_bins; bin++) {
        outfile << bin * dr << " " << bin_count[bin] / timestep_counter << "\n";
    }

    outfile.close();
    outfile.clear();

    outfile.open("./rdf.out");

    for (int bin = 0; bin < n_bins; bin++) {
        outfile << bin * dr << " " << gr[bin] / timestep_counter << "\n";
    }

    outfile.close();
    outfile.clear();

    //===============================================================================

    delete[] gr;
    delete[] timestep_bin_count;
    delete[] bin_count;
    delete[] origin;

    for (int atom_id = 0; atom_id < n_atoms; atom_id++)
        delete[] atoms[atom_id];
    delete[] atoms;

    for (int dimension = 0; dimension < 3; dimension++)
        delete[] box_vectors[dimension];
    delete[] box_vectors;

    for (int dimension = 0; dimension < 3; dimension++)
        delete[] box_vertices[dimension];
    delete[] box_vertices;

    //================================================================================
    return 0;

    logfile.close();
}
