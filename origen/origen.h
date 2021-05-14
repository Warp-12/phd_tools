#ifndef ORIGEN_H
#define ORIGEN_H

#include <iostream>
#include <string>

using namespace std;

int origenStart(string input_filename, double **&oriented_crystal); // Origen z czytaniem i pisaniem pliku
int origenStart(int *&repetitions, double *&point_of_origin, int **orientation, double lattice_constants[3], string lattice_type, string basis_file, string output_file, string output_filetype, string atom_type,double *&simulation_cell, double **&oriented_crystal, string writefile); // Przeciążona funkcja do której jawnie podawane są parametry
int orientCrystal(int **miller, int *rep, double* origin, double &a, double &b, double &c, string lattice, string basefile, double ** &crystal);
void writeOutput(string outputfiletype, double **crys, double *box, int *reps, double *ori, string outfile, int n_at, string atomtyp);
void readParameters(string name, int **miller, int *rep, double *origin, double &a, double &b, double &c, string &lattice, string &basefile, string &writefile, string &outputfile, string &outputfiletype, string &atomtype);

#endif
