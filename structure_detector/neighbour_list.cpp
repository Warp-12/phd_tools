#include <iostream>
#include <cstdlib>
#include <cmath>
#include "neighbour_list.h"

void verletList(double **atom_positions, double **simulation_box, int num_of_atoms, double r_cut, int *&number_of_neighbours, int **&neighbours_list, double **&lenghts)
{
	int MAX_NEIGHBOURS = 4*num_of_atoms;

	// Neighbour list creation

    number_of_neighbours = new int [num_of_atoms];
	neighbours_list = new int *[num_of_atoms];
	lenghts = new double *[num_of_atoms];
	
    for(int i = 0; i < num_of_atoms; i++){
	
		number_of_neighbours[i] = 0;
		neighbours_list[i] = new int [MAX_NEIGHBOURS];	
		lenghts[i] = new double [MAX_NEIGHBOURS];	

	} 

//	register int i_type;
	double sq_r_cut;

    double *d_ij = new double [3];
    double *box_dimensions = new double [3];
    double sum_of_squares;

    for(int dim = 0; dim < 3; dim++)
    {
        box_dimensions[dim] = simulation_box[dim][1] - simulation_box[dim][0];
    }

    int atom_i, atom_j;

    std::cout << "Creating Verlet list for cutoff radius: " << r_cut << "\n";

	for(atom_i = 0; atom_i < num_of_atoms; atom_i++)
	{
		for(atom_j = atom_i + 1; atom_j < num_of_atoms; atom_j++)
		{
			sq_r_cut = r_cut*r_cut;	

			d_ij[0] = atom_positions[atom_j][0] - atom_positions[atom_i][0]; 
			
            if(d_ij[0] < -0.5*box_dimensions[0])
			{
				d_ij[0] += box_dimensions[0];
			}
			if(d_ij[0] > 0.5*box_dimensions[0])
			{
				d_ij[0] -= box_dimensions[0];
			}
			
            sum_of_squares = d_ij[0]*d_ij[0];
			
            if(sum_of_squares < sq_r_cut)
			{
			    d_ij[1] = atom_positions[atom_j][1] - atom_positions[atom_i][1]; 
				
                if(d_ij[1] < -0.5*box_dimensions[1])
				{
					d_ij[1] += box_dimensions[1];
				}
				if(d_ij[1] > 0.5*box_dimensions[1])
				{
					d_ij[1] -= box_dimensions[1];
				}
				sum_of_squares += d_ij[1]*d_ij[1];

				if(sum_of_squares < sq_r_cut)
				{
			        d_ij[2] = atom_positions[atom_j][2] - atom_positions[atom_i][2]; 
					
                    if(d_ij[2] < -0.5*box_dimensions[2])
					{
						d_ij[2] += box_dimensions[2];
					}
					if(d_ij[2] > 0.5*box_dimensions[2])
					{
						d_ij[2] -= box_dimensions[2];
					}
					
                    sum_of_squares += d_ij[2]*d_ij[2];

                    double r_ij = sqrt(sum_of_squares);					

                    if( r_ij < r_cut )
					{
						if(number_of_neighbours[atom_j] == MAX_NEIGHBOURS ||
						   number_of_neighbours[atom_i] == MAX_NEIGHBOURS)
						{
                            std::cout << "Too many neighbours!\n";
							exit(0);
						}
						
                        neighbours_list[atom_i][number_of_neighbours[atom_i]] = atom_j;
						neighbours_list[atom_j][number_of_neighbours[atom_j]] = atom_i;
						
                        lenghts[atom_i][number_of_neighbours[atom_i]] = r_ij;
						lenghts[atom_j][number_of_neighbours[atom_j]] = r_ij;
						
                        number_of_neighbours[atom_i]++;
						number_of_neighbours[atom_j]++;
					}
				}
			} 
		}
	}

    delete [] box_dimensions;
    delete [] d_ij;
}
