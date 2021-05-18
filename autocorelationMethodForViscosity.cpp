#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <dirent.h>
#define GOOD_FILE_CRITERION temp_name != ".." && temp_name != "."

using namespace std;

// wind shoud be n_sample -1, czyli ile ma kroków
//n_samples-ile ma danych
//
//
//------------------------------------------------------------------------------------------------------------------------------------------------------
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
//=======================================================================================================================================================
void Autocorrelation(double **&v, int n_samples, double ***&ac, int corr_window, int n_windows) {
    int window_width = n_samples / n_windows;
    int start_point = corr_window * window_width;

    for (int i = 0; i < window_width - 1; i++) {
        ac[corr_window][i][1] = 0.0;
        ac[corr_window][i][2] = 0.0;
        ac[corr_window][i][3] = 0.0;

        for (int j = 0; j < window_width - i; j++) {
            ac[corr_window][i][1] += v[j + start_point][1] * v[j + start_point + i][1];
            ac[corr_window][i][2] += v[j + start_point][2] * v[j + start_point + i][2];
            ac[corr_window][i][3] += v[j + start_point][3] * v[j + start_point + i][3];
        }

        ac[corr_window][i][1] /= window_width - (i + 1);
        ac[corr_window][i][2] /= window_width - (i + 1);
        ac[corr_window][i][3] /= window_width - (i + 1);
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------

void Average(int limit, double timestep, double ***&ac, int n_windows, int file_id, double **&averaged_correlation, int &width) {
    stringstream filename;

    filename << "./output/files/" << file_id + 1 << ".out";
    ofstream avecor;
    avecor.open(filename.str().c_str());

    int window_width = limit / n_windows;
    width = window_width;

    averaged_correlation = new double *[window_width];

    for (int i = 0; i < window_width; i++) {
        averaged_correlation[i] = new double[3];

        averaged_correlation[i][0] = 0.0;
        averaged_correlation[i][1] = 0.0;
        averaged_correlation[i][2] = 0.0;

        for (int j = 0; j < n_windows; j++) {
            averaged_correlation[i][0] += ac[j][i][1];
            averaged_correlation[i][1] += ac[j][i][2];
            averaged_correlation[i][2] += ac[j][i][3];
        }

        averaged_correlation[i][0] /= n_windows;
        averaged_correlation[i][1] /= n_windows;
        averaged_correlation[i][2] /= n_windows;

        avecor << i << " " << averaged_correlation[i][0] << " " << averaged_correlation[i][1] << " " << averaged_correlation[i][2] << " " << (averaged_correlation[i][0] + averaged_correlation[i][1] + averaged_correlation[i][2]) / 3.0 << "\n";
    }

    avecor.close();
}
void AverageOverFiles(int n_files, int n_rows, double ***&data, double **&mean) {
    ofstream averaged;

    averaged.open("./output/mean_corr.out");

    mean = new double *[n_rows];

    for (int row = 0; row < n_rows; row++) {
        mean[row] = new double[4];
        mean[row][0] = 0.0;
        mean[row][1] = 0.0;
        mean[row][2] = 0.0;
        mean[row][3] = 0.0;
    }

    for (int row = 0; row < n_rows; row++) {
        for (int file = 0; file < n_files; file++) {
            mean[row][0] += data[file][row][0];
            mean[row][1] += data[file][row][1];
            mean[row][2] += data[file][row][2];
        }

        mean[row][0] /= n_files;
        mean[row][1] /= n_files;
        mean[row][2] /= n_files;
        mean[row][3] += (mean[row][0] + mean[row][1] + mean[row][2]) / 3;

        averaged << row << " " << mean[row][0] << " " << mean[row][1] << " " << mean[row][2] << " " << mean[row][3] << "\n";
    }

    averaged.close();
}
double Integrate(int n_rows, int timestep, double **&averaged_correlation) {
    double *integral = new double[3];
    double averaged = 0.0;

    for (int i = 0; i < n_rows - 1; i++) {
        integral[0] += 0.5 * (averaged_correlation[i][0] + averaged_correlation[i + 1][0]) * timestep;
        integral[1] += 0.5 * (averaged_correlation[i][1] + averaged_correlation[i + 1][1]) * timestep;
        integral[2] += 0.5 * (averaged_correlation[i][2] + averaged_correlation[i + 1][2]) * timestep;
    }

    averaged = (integral[0] + integral[1] + integral[2]) / 3.0;

    for (int i = 0; i < n_rows; i++) {
        delete[] averaged_correlation[i];
    }

    delete[] averaged_correlation;
    delete[] integral;
    return averaged;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    double I = 0.0;
    double dt = 0.0;
    double kB = 1.38064852e-23;

    //=========================================================================

    double T = 1200.00365943241;

    double box_lenght = 33.5163726307217;

    int n_corrs = 1;
    //=========================================================================

    string *names;

    int number_of_files = parseInputFilenames(names);

    //=========================================================================
    ifstream infile;
    string line, first_word, second_word;
    stringstream inname, temp, keyword;
    int line_counter = 0;
    int start_push = 0;
    int rows = 0;
    double trash;
    //=========================================================================

    cout << "NUMBER OF FILES READ: " << number_of_files << "\n";

    double ***averaged = new double **[number_of_files];
    int width = 0;

    for (int file = 0; file < number_of_files; file++) {
        inname << names[file];

        cout << names[file] << "\n";

        infile.open(inname.str().c_str());

        while (!infile.eof()) {
            getline(infile, line);
            keyword.str(line);

            keyword >> first_word;
            keyword >> second_word;

            if (first_word == "Loop" && start_push == 1) {
                start_push = 0;
                rows = line_counter;
                line_counter = 0;
            }

            keyword.clear();
            keyword.str("");

            if (start_push == 1) {
                line_counter++;
            }

            if (second_word == "c_my_temp" && start_push == 0) {
                start_push = 1;
            }
        }
        infile.close();
        infile.clear();

        double **table = new double *[rows];

        for (int i = 0; i < rows; i++) {
            table[i] = new double[4];
        }

        infile.open(inname.str().c_str());

        while (!infile.eof()) {
            getline(infile, line);
            keyword.str(line);
            keyword >> first_word;
            keyword >> second_word;
            if (first_word == "Loop" && start_push == 1) {
                start_push = 0;
                line_counter = 0;
            }

            keyword.clear();
            keyword.str("");

            if (start_push == 1) {
                temp.str(line);
                temp >> table[line_counter][0];
                for (int i = 1; i < 12; i++) {
                    temp >> trash;
                }
                temp >> table[line_counter][1];
                temp >> table[line_counter][2];
                temp >> table[line_counter][3];
                temp.clear();
                line_counter++;
            }
            if (second_word == "c_my_temp" && start_push == 0) {
                start_push = 1;
            }
        }

        dt = table[1][0] - table[0][0];

        double ***correlation = new double **[n_corrs];

        width = rows / n_corrs;

        for (int window = 0; window < n_corrs; window++) {
            correlation[window] = new double *[width];

            for (int i = 0; i < width; i++) {
                correlation[window][i] = new double[4];
                correlation[window][i][0] = table[i][0];
            }
        }

        infile.close();
        infile.clear();
        inname.clear();
        inname.str("");

        //=====================================================================================================================================================

        for (int window = 0; window < n_corrs; window++) {
            Autocorrelation(table, rows, correlation, window, n_corrs);
        }
        Average(rows, dt, correlation, n_corrs, file, averaged[file], width);

        //=====================================================================================================================================================

        for (int i = 0; i < n_corrs; i++) {
            for (int j = 0; j < width; j++) {
                delete[] correlation[i][j];
            }

            delete[] correlation[i];
        }

        delete[] correlation;

        for (int i = 0; i < rows; i++) {
            delete[] table[i];
        }

        delete[] table;
    }

    double **mean_corr;
    AverageOverFiles(number_of_files, width, averaged, mean_corr);
    I = Integrate(width, dt, mean_corr);

    double conversion = ((box_lenght * box_lenght * box_lenght) / (kB * T)) * 1e-30 * 1e-15 * 1e10 * 1e3;
    double eta = I * conversion;

    cout << setw(22) << "#Integral " << setw(3) << " = " << setw(12) << I << '\n';
    cout << setw(22) << "#eta in mPa.s " << setw(3) << " = " << setw(12) << eta << '\n';

    for (int file = 0; file < number_of_files; file++) {
        for (int row = 0; row < width; row++) {
            delete[] averaged[file][row];
        }

        delete[] averaged[file];
    }

    delete[] averaged;
}
