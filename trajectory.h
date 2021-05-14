#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <dirent.h>
#include <string>
#include "datastructures.h"

int parseInputFilenames(std::string *&filenames);
void parseTrajectoryFile(std::string filename, int start, int end, int n_windows, int id);

#endif /* TRAJECTORY_H */
