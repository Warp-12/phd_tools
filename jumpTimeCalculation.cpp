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

using namespace std;

#define BP(string) std::cout << (string) << "\n";

int main(int argc, char *argv[]) {

    ifstream infile;
    ofstream outfile;

    string inname, outname, filename;
    stringstream namestream;
    stringstream linestream;
    string line;


    namestream << "./1_at_AuSi_675.out"; 

    infile.open(namestream.str().c_str());

    if (!infile) {
        cout << "File not exist!"
             << "\n";
        return 1;
    }

    int linecounter = 0;
    int n_atoms = 0;
    int timesteps = 0;

    while (getline(infile, line)) {
        linecounter++;
        if (linecounter == 4) {
            linestream.str(line);
            linestream >> n_atoms;
            linestream.str("");
            linestream.clear();
        }
        if (line.find("TIMESTEP") < line.length()) {
            timesteps++;
        }
    }

    infile.close();
    infile.clear();

    double **atoms = new double *[n_atoms]; 
    for (int atom_id = 0; atom_id < n_atoms; atom_id++)
        atoms[atom_id] = new double[4];

    double **time_distance = new double *[timesteps];
    for (int step = 0; step < timesteps; step++)
        time_distance[step] = new double[5];

    infile.open(namestream.str().c_str());

    int timestep_counter = 0;
    int atom_counter = 0;
    int step = 0;

    int atom_type = 0;
    double maximum = -DBL_MAX;
    double minimum = DBL_MAX;

    bool begin_timestep = false;
    bool begin_atoms = false;
    bool begin_analysis = false;

    string trashcan;
    
    while (getline(infile, line)) {
        if (begin_timestep) {
            if (begin_atoms) {
                linestream.str(line);
                linestream >> trashcan;
                linestream >> atom_type;

                for (int dimension = 0; dimension < 3; dimension++)
                    linestream >> atoms[atom_counter][dimension];

                atoms[atom_counter][3] = atom_type - 1;  

                atom_counter++;

                if (atom_counter == 1) 
                {
                    begin_timestep = false;  
                    begin_atoms = false;     
                    begin_analysis = true;  

                    timestep_counter++;  

                    atom_counter = 0;
                }
            }
        }
        
        if (begin_analysis) {
            double x = 0.0;
            double y = 0.0;
            double z = 0.0;

            x = atoms[0][0];
            y = atoms[0][1];
            z = atoms[0][2];

            time_distance[step][0] = x;
            time_distance[step][1] = y;
            time_distance[step][2] = z;

            begin_analysis = false;
            begin_timestep = false;
            begin_atoms = false;

            step++;
        }
        
        if (!begin_analysis)  
        {
            if (line.find("TIMESTEP") < line.length() && !begin_timestep) {
                atom_counter = 0;
                begin_timestep = true;
            }
            if (line.find("id type x y z") < line.length() && !begin_atoms) {
                begin_atoms = true;
            }
        }
    }
    infile.close();

    double r_t = 0.0;
    double r_to = 0.0;
    double msd = 0.0;

    r_to = time_distance[0][0] * time_distance[0][0] +
           time_distance[0][1] * time_distance[0][1] +
           time_distance[0][2] * time_distance[0][2];

    r_to = sqrt(r_to);

    for (int i = 0; i < step; i++) {
        r_t = time_distance[i][0] * time_distance[i][0] +
              time_distance[i][1] * time_distance[i][1] +
              time_distance[i][2] * time_distance[i][2];

        r_t = sqrt(r_t);
        msd = (r_t - r_to) * (r_t - r_to);

        time_distance[i][3] = r_t;
        time_distance[i][4] = msd;
    }

    stringstream vectorcomponent;
    vectorcomponent << "componet.out";

    outfile.open(vectorcomponent.str().c_str());

    for (int index = 0; index < step; index++) {
        outfile << index << "   " << time_distance[index][0] << "   " << time_distance[index][1] << "   " << time_distance[index][2] << "   " << time_distance[index][3] << "   " << time_distance[index][4] << "   "
                << "\n";
    }

    outfile.close();
    outfile.clear();
    vectorcomponent.str("");
    vectorcomponent.clear();

    int count = 0;

    vector<double> changes_x;
    vector<double> changes_y;
    vector<double> changes_z;
    vector<int> jump_time;

    double radius_before = 0.0;
    double radius = 0.0;
    double radius_after = 0.0;

    for (int i = 0; i < step - 1; i++) {
        if (i > 1) {
            radius_before = time_distance[i - 1][0] * time_distance[i - 1][0] +
                            time_distance[i - 1][1] * time_distance[i - 1][1] +
                            time_distance[i - 1][2] * time_distance[i - 1][2];

            radius = time_distance[i][0] * time_distance[i][0] +
                     time_distance[i][1] * time_distance[i][1] +
                     time_distance[i][2] * time_distance[i][2];

            radius_after = time_distance[i + 1][0] * time_distance[i + 1][0] +
                           time_distance[i + 1][1] * time_distance[i + 1][1] +
                           time_distance[i + 1][2] * time_distance[i + 1][2];

            radius_before = sqrt(radius_before);
            radius = sqrt(radius);
            radius_after = sqrt(radius_after);

            if (radius <= radius_before) {
                if (radius_after > radius) {
                    changes_x.push_back(time_distance[i][0]);
                    changes_y.push_back(time_distance[i][1]);
                    changes_z.push_back(time_distance[i][2]);
                    jump_time.push_back(i);

                    count++;
                }
            }
        }
    }
    
    int size_of_vector = jump_time.size();

    double **displacement = new double *[size_of_vector];
    for (int count_index = 0; count_index < size_of_vector; count_index++) {
        displacement[count_index] = new double[5];
    }

    for (int i = 0; i < size_of_vector; i++) {
        displacement[i][0] = 0;
        displacement[i][1] = jump_time[i];
        displacement[i][2] = changes_x[i];
        displacement[i][3] = changes_y[i];
        displacement[i][4] = changes_z[i];
    }

    double r_ij = 0.0;

    double x_i = 0.0;
    double y_i = 0.0;
    double z_i = 0.0;

    double x_j = 0.0;
    double y_j = 0.0;
    double z_j = 0.0;

    double xx = 0.0;
    double yy = 0.0;
    double zz = 0.0;

    int proved = 0;
    double sum = 0;
    int ave = 0;

    for (int shift_i = 0; shift_i < size_of_vector - 1; shift_i++) {
        int shift_j = shift_i + 1;

        x_i = displacement[shift_i][2];
        y_i = displacement[shift_i][3];
        z_i = displacement[shift_i][4];

        x_j = displacement[shift_j][2];
        y_j = displacement[shift_j][3];
        z_j = displacement[shift_j][4];

        xx = x_j - x_i;
        yy = y_j - y_i;
        zz = z_j - z_i;

        r_ij = xx * xx + yy * yy + zz * zz;
        r_ij = sqrt(r_ij);

        displacement[shift_i][0] = r_ij;
    }

    for (int shift_i = 0; shift_i < size_of_vector; shift_i++) {
        if (displacement[shift_i][0] >= 1.17) {
            if (shift_i > 1) {
                proved = displacement[shift_i][1] - displacement[shift_i - 1][1];
                sum += proved;
                ave++;
            }
        }
    }
    sum /= ave;

    stringstream timebefore;

    timebefore << "before_sorting.out";

    outfile.open(timebefore.str().c_str());

    for (int count_index = 0; count_index < count; count_index++) {
        if (displacement[count_index][0] > 0.1) {
            outfile << displacement[count_index][0] << "   " << displacement[count_index][1] << "   " << displacement[count_index][2] << "   " << displacement[count_index][3] << "   " << displacement[count_index][4] << "\n";
        }
    }

    outfile.close();
    outfile.clear();
    timebefore.str("");
    timebefore.clear();

    

    minimum = DBL_MAX;
    maximum = -DBL_MAX;

    for (int counter = 0; counter < count; counter++) {
        if (displacement[counter][0] > maximum) {
            maximum = displacement[counter][0];
        }
        if (displacement[counter][0] < minimum) {
            minimum = displacement[counter][0];
        }
    }

    cout << "Number of change sign:  " << count << "\n";
    cout << "Maximum:  " << maximum << "\n";
    cout << "Minimum:  " << minimum << "\n";


    double swapHolder = -1.0;
    double swapIndex = 1.0;
    int end = count;
    int length = count;

    for (int counter = length - 1; counter > 0; counter--) {
        for (int index = 0; index < end; index++) {
            if (index >= 1) {
                if (displacement[index - 1][0] > displacement[index][0]) {
                    swapHolder = displacement[index][0];
                    displacement[index][0] = displacement[index - 1][0];
                    displacement[index - 1][0] = swapHolder;

                    swapIndex = displacement[index][1];
                    displacement[index][1] = displacement[index - 1][1];
                    displacement[index - 1][1] = swapIndex;
                }
            }
        }
        end--;
    }


    int n_bins = 1000;

    double bin_width = maximum / n_bins;

    int *bins = new int[n_bins];
    for (int bin = 0; bin < n_bins; bin++) {
        bins[bin] = 0;
    }

    double **probability = new double *[n_bins];
    for (int bin = 0; bin < n_bins; bin++) {
        probability[bin] = new double[2];

        for (int i = 0; i < 2; i++) {
            probability[bin][i] = 0;
        }
    }

    for (int jump = 0; jump < count; jump++) {
        int bin_id = 0;

        for (int bin = 0; bin < n_bins; bin++) {
            double min = bin * bin_width;
            double max = (bin + 1) * bin_width;

            if (displacement[jump][0] >= min) {
                if (displacement[jump][0] < max) {
                    bin_id = bin;
                    probability[bin][0] = displacement[jump][0];
                }
            }
        }
        bins[bin_id]++;
    }

    for (int bin = 0; bin < n_bins; bin++) {
        probability[bin][1] = bins[bin];
        probability[bin][1] /= count;
        probability[bin][1] /= bin_width;
    }

    double maximum_p = -DBL_MAX;
    double maximum_probability_distance = 0.0;

    for (int bin = 0; bin < n_bins; bin++) {
        if (probability[bin][1] > maximum_p) {
            maximum_p = probability[bin][1];
            maximum_probability_distance = probability[bin][0];
        }
    }

    int time_counter = 0;
    double ave_jump_distance = 0.0;
    int jump_ave = 0;
    for (int i = 0; i < count; i++) {
        if (displacement[i][0] >= 2.88) 
        {
            if (displacement[i][0] > maximum_probability_distance) {
                time_counter++;
            }

            cout << displacement[i][0] << "     " << displacement[i][1] << "\n";
        }

        if (displacement[i][0] > 2.16)  // distanse equal 0,75*diameter of atom Si
        {
            ave_jump_distance += displacement[i][0];
            jump_ave++;
        }
    }
    ave_jump_distance /= jump_ave;

    cout << "Average time counter   :      " << sum << "\n";
    cout << "Time_counter           :      " << time_counter << "\n";
    cout << "Probability distance   :      " << maximum_probability_distance << "\n";
    cout << "Average jump distance  :      " << ave_jump_distance << "\n";

    stringstream probabilityname, timedistance;

    probabilityname << "probability.out";

    outfile.open(probabilityname.str().c_str());

    for (int bin = 0; bin < n_bins; bin++) {
        outfile << bins[bin] << "  " << probability[bin][0] << " " << probability[bin][1] << "\n";
    }

    outfile.close();
    outfile.clear();

    timedistance << "distance_after_sorting.out";

    outfile.open(timedistance.str().c_str());

    for (int count_index = 0; count_index < count; count_index++) {
        outfile << displacement[count_index][0] << "   " << displacement[count_index][1] << "\n";
    }

    outfile.close();
    outfile.clear();

    probabilityname.str("");
    probabilityname.clear();

    timedistance.str("");
    timedistance.clear();


    for (int atom_id = 0; atom_id < n_atoms; atom_id++) {
        delete[] atoms[atom_id];
    }
    delete[] atoms;

    for (int step = 0; step < timesteps; step++) {
        delete[] time_distance[step];
    }
    delete[] time_distance;

    for (int bin = 0; bin < n_bins; bin++) {
        delete[] probability[bin];
    }
    delete[] probability;

    for (int count_index = 0; count_index < size_of_vector; count_index++) {
        delete[] displacement[count_index];
    }
    delete[] displacement;

    delete[] bins;

    return 0;
}
