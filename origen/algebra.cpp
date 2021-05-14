#include "algebra.h"
#include <cmath>
#include <iostream>

using namespace std;

void thirdAxis(int **indices){

  indices[1][0] = indices[2][1]*indices[0][2]-indices[2][2]*indices[0][1];
  indices[1][1]=-(indices[2][0]*indices[0][2]-indices[2][2]*indices[0][0]);
  indices[1][2]=indices[2][0]*indices[0][1]-indices[2][1]*indices[0][0];

}
void computeRotationMatrix(double **initial, double **rotated, double **rot_mat){

  rot_mat[0][0] = initial[0][0]*rotated[0][0]+initial[0][1]*rotated[0][1]+initial[0][2]*rotated[0][2];
  rot_mat[0][1] = initial[0][0]*rotated[1][0]+initial[0][1]*rotated[1][1]+initial[0][2]*rotated[1][2];
  rot_mat[0][2] = initial[0][0]*rotated[2][0]+initial[0][1]*rotated[2][1]+initial[0][2]*rotated[2][2];

  rot_mat[1][0] = initial[1][0]*rotated[0][0]+initial[1][1]*rotated[0][1]+initial[1][2]*rotated[0][2];
  rot_mat[1][1] = initial[1][0]*rotated[1][0]+initial[1][1]*rotated[1][1]+initial[1][2]*rotated[1][2];
  rot_mat[1][2] = initial[1][0]*rotated[2][0]+initial[1][1]*rotated[2][1]+initial[1][2]*rotated[2][2];

  rot_mat[2][0] = initial[2][0]*rotated[0][0]+initial[2][1]*rotated[0][1]+initial[2][2]*rotated[0][2];
  rot_mat[2][1] = initial[2][0]*rotated[1][0]+initial[2][1]*rotated[1][1]+initial[2][2]*rotated[1][2];
  rot_mat[2][2] = initial[2][0]*rotated[2][0]+initial[2][1]*rotated[2][1]+initial[2][2]*rotated[2][2];

}

int invertMatrix(double **matrix, double **inverse){

  double determinant = abs((matrix[0][0]*matrix[1][1]*matrix[2][2])+(matrix[0][1]*matrix[1][2]*matrix[2][0])+(matrix[0][2]*matrix[1][0]*matrix[2][1]))-((matrix[0][2]*matrix[1][1]*matrix[2][0])+(matrix[0][1]*matrix[1][0]*matrix[2][2])+(matrix[1][2]*matrix[2][1]*matrix[0][0]));

  if(determinant==0){return 1;}
  if(determinant!=0){

    inverse[0][0] = (matrix[1][1]*matrix[2][2]-matrix[1][2]*matrix[2][1])/determinant;
    inverse[0][1] = (matrix[0][2]*matrix[2][1]-matrix[0][1]*matrix[2][2])/determinant;
    inverse[0][2] = (matrix[0][1]*matrix[1][2]-matrix[0][2]*matrix[1][1])/determinant;

    inverse[1][0] = (matrix[1][2]*matrix[2][0]-matrix[1][0]*matrix[2][2])/determinant;
    inverse[1][1] = (matrix[0][0]*matrix[2][2]-matrix[0][2]*matrix[2][0])/determinant;
    inverse[1][2] = (matrix[0][2]*matrix[1][0]-matrix[0][0]*matrix[1][2])/determinant;

    inverse[2][0] = (matrix[1][0]*matrix[2][1]-matrix[1][1]*matrix[2][0])/determinant;
    inverse[2][1] = (matrix[0][1]*matrix[2][0]-matrix[0][0]*matrix[2][1])/determinant;
    inverse[2][2] = (matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0])/determinant;

    return 0;

  }

}
void vectorTimesMatrix(double vector[], double **matrix, double result[], int size){

    double rightside;

    for(int i = 0; i < size; i++){

	rightside = 0;

	for(int j = 0; j < size; j++){

		rightside += matrix[i][j]*vector[j];

	}

	result[i] = rightside;

    }

}
double vectorNorm(int *vector){

    double norm;

    norm = sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);

    return norm;

}
