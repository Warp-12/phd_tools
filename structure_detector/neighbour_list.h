#ifndef NEIGHBOUR_LIST_H
#define NEIGHBOUR_LIST_H

void verletList(double ***atom_positions, double ***simulation_box, int num_of_atoms, int numb_window,  double r_cut, int **&number_of_neighbours, int ***&neighbours_list, double ***&lenghts);

#endif /* NEIGHBOUR_LIST_H  */
