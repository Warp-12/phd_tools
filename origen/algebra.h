#ifndef ALGEBRA_H
#define ALGEBRA_H

void computeRotationMatrix(double **initial, double **rotated, double **rot_mat);
int invertMatrix(double **matrix, double **inverse);
void vectorTimesMatrix(double vector[], double **matrix, double result[], int size);
double vectorNorm(int *vector);
void thirdAxis(int **indices);

#endif /* ALGEBRA_H */
