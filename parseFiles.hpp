#pragma once
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define BOOST_NO_CXX11_SCOPED_ENUMS
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <dirent.h>
#define GOOD_FILE_CRITERION temp_name != ".." && temp_name != "."

void moveToAverageTable(int numberOfPolychedralAtoms,
                        double **&meltingLine,
                        int file_id,
                        double **&averaged_correlation);

int parseInputFilenames(std::string *&filenames);

void AverageOverFiles(int n_files,
                      int n_rows,
                      double ***&data,
                      double **&mean);

double **readFile(const std::string &fileName, int numberOfAtomsInFile);
