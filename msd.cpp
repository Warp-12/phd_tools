#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>
#include <string>
#include "./trajectory.h"
#include "datastructures.h"

using namespace std;

int main(int argc, char* argv[])
{
    string *filenames;

    if(argc == 1)
    {
        cout << "ERROR: No number of windows specified!\n";
        return 1;
    }
    if(argc == 2)
    {
	cout << "ERROR: No starting point specified!\n";
        return 1;
    }	
    if(argc == 3)
    {
	cout << "ERROR: No ending point specified!\n";
        return 1;
    }	

    int number_of_files = parseInputFilenames(filenames);
    int n_windows = 0;
    int time_start = 0;
    int time_end = 0;

    double *diffusion_coefficients = new double [number_of_files];

    stringstream argstream;
    
    argstream << argv[1] << " " << argv[2] << " " << argv[3];
    argstream >> n_windows;
    argstream >> time_start;
    argstream >> time_end;

    argstream.clear();

    for(int file = 0; file < number_of_files; file++)
    {
        parseTrajectoryFile(filenames[file], time_start, time_end, n_windows, file);
    }

    return 0;
}
