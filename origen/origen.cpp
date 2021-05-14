#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
#include <string>
#include "parsing.h"
#include "algebra.h"
#include "crystal.h"
#include "origen.h"

using namespace std;

int origenStart(int *&repetitions, double *&point_of_origin, int **orientation, double lattice_constants[3], string lattice_type, string basis_file, string output_file, string output_filetype, string atom_type, double *&simulation_cell,  double **&oriented_crystal, string writefile){

    int rows;
    simulation_cell = new double [6];

    rows = orientCrystal(orientation, repetitions, point_of_origin, lattice_constants[0], lattice_constants[1], lattice_constants[2], lattice_type, basis_file, oriented_crystal);
    measureFinalStructure(repetitions, point_of_origin, lattice_constants[0], lattice_constants[1], lattice_constants[2], simulation_cell);
    if(writefile == "yes"){writeOutput(output_filetype, oriented_crystal, simulation_cell, repetitions, point_of_origin, output_file, rows, atom_type);}

    return rows;

}
int origenStart(string input_filename, double **&oriented_crystal){

    string writefile;

    int rows;

    int *repetitions = new int [3];

    int **orientation = new int *[3];

    for(int i = 0; i < 3; i++){

	orientation[i] = new int [3];

    }

    double *point_of_origin = new double [3];
    double *simulation_cell = new double [6];

    double lattice_constants[3];

    string lattice_type;
    string basis_file;
    string output_file;
    string output_filetype;
    string atom_type;

    readParameters(input_filename, orientation, repetitions, point_of_origin, lattice_constants[0], lattice_constants[1], lattice_constants[2], lattice_type, basis_file, writefile, output_file, output_filetype, atom_type);
    rows = orientCrystal(orientation, repetitions, point_of_origin, lattice_constants[0], lattice_constants[1], lattice_constants[2], lattice_type, basis_file, oriented_crystal);
    measureFinalStructure(repetitions, point_of_origin, lattice_constants[0], lattice_constants[1], lattice_constants[2], simulation_cell);
    if(writefile == "yes"){writeOutput(output_filetype, oriented_crystal, simulation_cell, repetitions, point_of_origin, output_file, rows, atom_type);}

    return rows;

}
int orientCrystal(int **miller, int *rep, double *origin, double &a, double &b, double &c, string lattice, string basefile, double ** &crystal){

  if(miller[2][0]*miller[0][0]+miller[2][1]*miller[0][1]+miller[2][2]*miller[0][2] != 0){

    cout << "\nNon-orthogonal basis!\n";

  }

  thirdAxis(miller);

  double **e = new double *[3];

  for(int i = 0; i < 3; i++){

	e[i] = new double [3];

  }

  e[0][0] = 1; e[0][1] = 0; e[0][2] = 0;
  e[1][0] = 0; e[1][1] = 1; e[1][2] = 0;
  e[2][0] = 0; e[2][1] = 0; e[2][2] = 1;

  double **p = new double *[3];

  for(int i = 0; i < 3; i++){

	p[i] = new double [3];

  }

  double x_norm,y_norm,z_norm;

  x_norm = sqrt(miller[0][0]*miller[0][0]+miller[0][1]*miller[0][1]+miller[0][2]*miller[0][2]);
  y_norm = sqrt(miller[1][0]*miller[1][0]+miller[1][1]*miller[1][1]+miller[1][2]*miller[1][2]);
  z_norm = sqrt(miller[2][0]*miller[2][0]+miller[2][1]*miller[2][1]+miller[2][2]*miller[2][2]);

  p[0][0] = miller[0][0]/x_norm;
  p[0][1] = miller[0][1]/x_norm;
  p[0][2] = miller[0][2]/x_norm;

  p[1][0] = miller[1][0]/y_norm;
  p[1][1] = miller[1][1]/y_norm;
  p[1][2] = miller[1][2]/y_norm;

  p[2][0] = miller[2][0]/z_norm;
  p[2][1] = miller[2][1]/z_norm;
  p[2][2] = miller[2][2]/z_norm;

  double **rotation_matrix = new double *[3];

  for(int i = 0; i < 3; i++){

	rotation_matrix[i] = new double [3];

  }

  computeRotationMatrix(e,p,rotation_matrix);

  double **inverse_rotation = new double *[3];

  for(int i = 0; i < 3; i++){

	   inverse_rotation[i] = new double [3];

  }

  int exitcode = invertMatrix(rotation_matrix, inverse_rotation);

  if(exitcode == 1){cout << "Unable to invert rotation matrix!\n";}

  double *minimum = new double [3];
  double *maximum = new double [3];

  for(int i = 0; i < 3; i++){

    minimum[i] = INT_MAX;
    maximum[i] = -INT_MAX;

  }

  for(int i = 0; i < 3; i++){

    for(int j = 0; j < 3; j++){

      if(miller[j][i] > maximum[i]){maximum[i]=miller[j][i];}
      if(miller[j][i] < minimum[i]){minimum[i]=miller[j][i];}

    }

  }

  int n_basis;
  double **basis;

  if(lattice == "custom"){n_basis = countBasis(basefile);}
  if(lattice == "fcc"){n_basis = 4;}
  if(lattice == "dia"){n_basis = 8;}
  if(lattice == "bcc"){n_basis = 2;}
  if(lattice == "sc"){n_basis = 1;}

  basis = new double *[n_basis];

  for(int i = 0; i < n_basis; i++){

	basis[i] = new double [3];

  }

  determineAtomicBasis(lattice, basis, basefile);

  double **atoms;

  int n_atoms;
  n_atoms = bravaisLatticePopulation(n_basis, minimum, maximum);

  atoms = new double *[n_atoms];

  for(int i = 0; i < n_atoms; i++){

	atoms[i] = new double [3];

  }

  createBravaisLattice(n_basis, minimum, maximum, basis, atoms);

  double **rotated_atoms = new double *[n_atoms];

  for(int i = 0; i < n_atoms; i++){

	rotated_atoms[i] = new double [3];

  }

  for(int i = 0; i < n_atoms; i++){

  	vectorTimesMatrix(atoms[i],inverse_rotation,rotated_atoms[i],3);

  }

  for(int i = 0; i < n_atoms; i++){

	rotated_atoms[i][0] = rotated_atoms[i][0]*a;
	rotated_atoms[i][1] = rotated_atoms[i][1]*b;
	rotated_atoms[i][2] = rotated_atoms[i][2]*c;

  }

  double *norms = new double [3];

  norms[0] = a*vectorNorm(miller[0]);
  norms[1] = b*vectorNorm(miller[1]);
  norms[2] = c*vectorNorm(miller[2]);

  a = norms[0];
  b = norms[1];
  c = norms[2];

  double **elementary;

  int n_cut = cutElementaryCell(norms,rotated_atoms,n_atoms,elementary);



  int n_cryst = measureCrystal(n_cut, rep);

  crystal = new double *[n_cryst];

  for (int i = 0; i < n_cryst; i++) {

    crystal[i] = new double [3];

  }

  growCrystal(n_cut, elementary, a, b, c, rep, origin, crystal);

  for(int i = 0; i < n_atoms; i++){

	if(i < 3){ delete [] e[i]; delete [] p[i]; }
	if(i < n_basis){ delete [] basis[i];  }
	if(i < n_cut){ delete [] elementary[i]; }
	delete [] rotated_atoms[i];
	delete [] atoms[i];

  }

  delete [] rotated_atoms;
  delete [] atoms;
  delete [] elementary;
  delete [] norms;
  delete [] basis;
  delete [] e;
  delete [] p;

  return n_cryst;

}
void readParameters(string name, int **miller, int *rep, double *origin, double &a, double &b, double &c, string &lattice, string &basefile, string &writefile, string &outputfile, string &outputfiletype, string &atomtype){

  int exitparse = 0;

  exitparse = parseParametersFile(name,lattice,miller,a,b,c,basefile,rep,origin, writefile, outputfile, outputfiletype, atomtype);
  if(exitparse == 1){cout << "UNABLE TO READ PARAMETERS FILE!\n\n";}


}
void writeOutput(string outputfiletype, double **crys, double *box, int *reps, double *ori, string outfile, int n_at, string atomtyp){

  if(outputfiletype == "xyz"){

    writeCrystalToXYZ(crys, ori, outfile, n_at, "Crystal", atomtyp);

  }
  if(outputfiletype == "lmpdata"){

    writeCrystalToLmpData(crys, box, outfile, n_at, "Crystal (LAMMPS DATA FILE)", atomtyp);

  }
  if(outputfiletype == ""){cout << "\nWARNING: No final output file format specified!\nCanceling writing data to file...";}


}
