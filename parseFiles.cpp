#include "parseFiles.hpp"

void moveToAverageTable(int numberOfBins,
                        double **&meltingLine,
                        int file_id,
                        double **&averaged_correlation) {
    std::stringstream filename;

    filename << "./output/files/polychedralLine_" << file_id + 1 << ".out";
    std::ofstream avecor;
    avecor.open(filename.str().c_str());

    averaged_correlation = new double *[numberOfBins];

    for (int i = 0; i < numberOfBins; i++) {
        averaged_correlation[i] = new double[2];

        averaged_correlation[i][0] = 0.0;
        averaged_correlation[i][1] = 0.0;

        averaged_correlation[i][0] = meltingLine[i][0];
        averaged_correlation[i][1] = meltingLine[i][1];

        avecor << i
               << " " << averaged_correlation[i][0]
               << " " << averaged_correlation[i][1]
               << "\n";
    }

    avecor.close();
}

int parseInputFilenames(std::string *&filenames) {
    int n_files = 0;
    DIR *input_files_directory;
    struct dirent *input_file;

    if ((input_files_directory = opendir("./sample/")) != NULL) {
        while ((input_file = readdir(input_files_directory)) != NULL) {
            std::string temp_name = input_file->d_name;
            if (GOOD_FILE_CRITERION) {
                int file_extension_trj = 0;

                file_extension_trj = temp_name.find(".sample");

                if (file_extension_trj != -1) {
                    n_files++;
                }
            }
        }

        closedir(input_files_directory);

        filenames = new std::string[n_files];

        input_files_directory = opendir("./sample/");

        int counter = 0;
        std::stringstream namestream;

        while ((input_file = readdir(input_files_directory)) != NULL) {
            std::string temp_name = input_file->d_name;
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

void AverageOverFiles(int n_files, int n_rows, double ***&data, double **&mean) {
    std::ofstream averaged;

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

double **readFile(const std::string &fileName, int numberOfAtomsInFile) {
    std::ifstream inFile(fileName);
    std::string line;
    std::stringstream lineStream;

    if (!inFile) {
        std::cout << "Cannot open file!" << '\n';
    }
    std::string trash;
    int lineCounter = 0;

    inFile.close();
    inFile.open(fileName);

    double **table = new double *[numberOfAtomsInFile];
    for (int i = 0; i < numberOfAtomsInFile; i++) {
        table[i] = new double[4];
    }

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

    // for (int i = 0; i < numberOfAtomsInFile; i++) {
    //     std::cout << "Count atoms: " << table[i][0] << '\n';
    // }

    // for (int i = 0; i < numberOfAtomsInFile; i++) {
    //     delete[] table[i];
    // }
    // delete[] table;

    return table;
}