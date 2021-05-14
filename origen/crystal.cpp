#include <iostream>
#include <fstream>
#include <string>
#include <cfloat>
#include <sstream>
#include <cmath>

using namespace std;

double precision = 1.0e-12; 

int bravaisLatticePopulation(int base_counter, double *min, double *max){

  int atom_count = 0;

  for (int atom = 0; atom < base_counter; atom++){
    for (int i = min[0]-2; i < max[0]+2; i++) {
      for (int j = min[1]-2; j < max[1]+2; j++) {
        for (int k = min[2]-2; k < max[2]+2; k++) {

              atom_count++;

        }
      }
    }
  }

  return atom_count;

}
void createBravaisLattice(int base_counter, double *min, double *max, double **basis, double **atoms){

  int atomcounter = 0;

  for (int atom = 0; atom < base_counter; atom++){
    for (int i = min[0]-2; i < max[0]+2; i++) {
      for (int j = min[1]-2; j < max[1]+2; j++) {
        for (int k = min[2]-2; k < max[2]+2; k++) {

              atoms[atomcounter][0] = basis[atom][0] + i;
              atoms[atomcounter][1] = basis[atom][2] + j;
              atoms[atomcounter][2] = basis[atom][1] + k;
		
	      atomcounter++;

        }
      }
    }
  }
}
int cutElementaryCell(double *edges, double **atoms, int n_atoms, double ** &elemcell){

  double delta[6];

  for(int i = 0; i < 3; i++){

  	delta[i] = -precision*edges[i];
	delta[i+3] = (1.000-precision)*edges[i];

  }

  bool x_in, y_in, z_in;
  int in_atoms = 0;

  for(int i = 0; i < n_atoms; i++){

	x_in = false;
	y_in = false;
	z_in = false;

	if(atoms[i][0] < delta[3] && atoms[i][0] > delta[0]){x_in = true;}
	if(atoms[i][1] < delta[4] && atoms[i][1] > delta[1]){y_in = true;}
	if(atoms[i][2] < delta[5] && atoms[i][2] > delta[2]){z_in = true;}

	if(x_in == true && y_in == true && z_in == true){in_atoms++;}

  }

  elemcell = new double *[in_atoms];
  for (int i = 0; i < in_atoms; i++) { elemcell[i] = new double [3]; }

  in_atoms = 0;

  for(int i = 0; i < n_atoms; i++){

	x_in = false;
	y_in = false;
	z_in = false;

	if(atoms[i][0] < delta[3] && atoms[i][0] > delta[0]){x_in = true;}
	if(atoms[i][1] < delta[4] && atoms[i][1] > delta[1]){y_in = true;}
	if(atoms[i][2] < delta[5] && atoms[i][2] > delta[2]){z_in = true;}

	if(x_in == true && y_in == true && z_in == true){

	    elemcell[in_atoms][0] = atoms[i][0];
    	    elemcell[in_atoms][1] = atoms[i][1];
   	    elemcell[in_atoms][2] = atoms[i][2];
            in_atoms++;
        
	 }

  }
  
  return in_atoms;

}
int measureCrystal(int n, int *repetitions){

    int count = 0;

    for (int atom = 0; atom < n; atom++){
      for (int i = 0; i < repetitions[0]; i++){
        for (int j = 0; j < repetitions[1]; j++){
          for (int k = 0; k < repetitions[2]; k++){

	           count++;

       }
      }
     }
    }

    return count;

}
void growCrystal(int n, double **grain, double a, double b, double c, int *repetitions, double *zero, double **grown){

    int count = 0;

    for (int atom = 0; atom < n; atom++){
      for (int i = 0; i < repetitions[0]; i++){
        for (int j = 0; j < repetitions[1]; j++){
          for (int k = 0; k < repetitions[2]; k++){

             grown[count][0] = grain[atom][0]+i*a+zero[0];
             grown[count][1] = grain[atom][1]+j*b+zero[1];
             grown[count][2] = grain[atom][2]+k*c+zero[2];

	     count++;

       }
      }
     }
    }

}
void measureFinalStructure(int *rep, double *&zero, double a, double b, double c, double * &measured){
  
  measured[0] = zero[0]; 
  measured[1] = zero[1]; 
  measured[2] = zero[2]; 

  measured[3] = measured[0]+rep[0]*a; 
  measured[4] = measured[1]+rep[1]*b; 
  measured[5] = measured[2]+rep[2]*c; 

  zero[0] = measured[3];
  zero[1] = measured[4];
  zero[2] = measured[5];
 
}
