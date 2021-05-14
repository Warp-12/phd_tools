#ifndef CRYSTAL_H
#define CRYSTAL_H

void createBravaisLattice(int base_counter, double *min, double *max, double **basis, double **atoms);
int bravaisLatticePopulation(int base_counter, double *min, double *max);
int cutElementaryCell(double *edges, double **atoms, int n_atoms, double ** &elemcell);
void createElementaryCell(double **cell, int counter);
int measureCrystal(int n, int *repetitions);
void growCrystal(int n, double **grain, double a, double b, double c, int *repetitions, double *zero, double **grown);
void measureFinalStructure(int *rep, double *&zero, double a, double b, double c, double * &measured);

#endif /* CRYSTAL_H */
