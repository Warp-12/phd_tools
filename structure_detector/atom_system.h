#ifndef ATOM_SYSTEM_H
#define ATOM_SYSTEM_H

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <cfloat>
#include <climits>

struct Atom
{
	bool _is_present;
	int _type_id;
	double *_position;
	double *_velocities;
	double *_forces;
	double _mass;
	
	Atom();
	~Atom();

	_setExistance(bool is_present);
	_setMass(double mass);
	_setTypeId(int type_id);

	_createPositionsTable();
	_createVelocitiesTable();
	_createForcesTable();
};
struct NeighbourList
{
	int _max_neighbours;
	double _r_cutoff;

	// Verlet list tables
	
	int _n_atoms;
	int *_n_neighbours;
	int **_neighbours_ids;
	double **_bond_lenghts;

	NeighbourList();
	~NeighbourList();
	
	_setMaxNeighbours(int max_neighbours);
	_setCutoff(double r_cutoff);
	
	_buildNeighboursList(double **box_matrix);
};
struct System
{	
	// Information about atoms 

	int _n_atoms;
	Atom *_particles;
	NeighbourList *_neighbours;
	double _r_cutoff;

	// Information about box shape and size
	
	double **_box_matrix;
	bool *_periodic;

	System();
	~System();

	_setCutoff(double r_cutoff);
	_setNAtoms(int n_atoms);
	_setPeriodicity(bool px, bool py, bool pz);
	
	_createParticlesTable();
	_createNeighboursList();
};

#endif /* ATOM_SYSTEM_H */
