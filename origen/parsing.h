#ifndef PARSING_H
#define PARSING_H

#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int parseParametersFile(string paramsname, string &lattice, int **indices, double &a, double &b, double &c, string &basename, int *reps, double *zero, string &write, string &output, string &outtype, string &atype);
void determineAtomicBasis(string type, double **type_basis, string basefile);
void writeAtomsToFile(double **data, string filename, int rows, double a, double b, double c, string type, string atype);
void writeCrystalToXYZ(double **crystal, double *zero, string filename, int rows, string type, string atype);
void writeCrystalToLmpData(double **crystal, double *box, string filename, int rows, string type, string atype);
int countBasis(string basefile);
void loadBasis(double **basis, string basefile);

#endif /* PARSING_H */
