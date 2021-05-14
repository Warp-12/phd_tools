#include "atom_system.h"

/*
struct Atom
{
	bool _is_present;
	int _type_id;
	double *_position;
	double *_velocities;
	double *_forces;
	double _mass;
};
*/

void Atom::Atom()
{
	this->_is_present = true;
	this->_position = nullptr;
	this->_velocities = nullptr;
	this->_forces = nullptr;
}
void Atom::~Atom()
{
	delete [] this->_position;
	if(this->_velocities != nullptr) delete [] this->_velocities;
	if(this->_forces != nullptr) delete [] this->_forces;
}
void Atom::_setExistance(bool is_present)
{
	this->_is_present = is_present;
}
void Atom::_setMass(double mass)
{
	this->_mass = mass;
}
void Atom::_setTypeId(int type_id)
{
	this->_type_id = type_id;
}
void Atom::_createPositionsTable()
{
	this->_position = new double [3]; 
}
void Atom::_createVelocitiesTable()
{
	this->_velocities = new double [3];
}
void Atom::_createForcesTable()
{
	this->_forces = new double [3];
}

/*
struct NeighbourList
{
	int _max_neighbours;
	double _r_cutoff;

	// Verlet list tables
	
	int _n_atoms;
	int *_n_neighbours;
	int **_neighbours_ids;
	double **_bond_lenghts;
};
*/

void NeighbourList::NeighbourList()
{
	this->_n_neighbours   = nullptr;
	this->_neighbours_ids = nullptr;
	this->_bond_lenghts   = nullptr;
    
}
void NeighbourList::~NeighbourList()
{
}
void NeighbourList::_setMaxNeighbours(int max_neighbours)
{
	this->_max_neighbours = max_neighbours;
}
void NeighbourList::_setCutoff(double r_cutoff)
{
	this->_r_cutoff = r_cutoff;
}
void NeighbourList::_prepareNeighboursList()
{
	this->_n_neighbours = new int [this->_n_atoms];
	this->_neighbours_ids = new int *[this->_n_atoms];
	this->_bond_lenghts = new double *[this->_n_atoms];
	
    for(int i = 0; i < this->_n_atoms; i++){
	
		_n_neighbours[i] = 0;
		_neighbours_ids[i] = new int [this->_n_neighbours];	
		_bond_lenghts[i] = new double [this->_n_neighbours];	

	} 
}
void NeighbourList::_buildNeighboursList(double **box_matrix)
{

}

/*
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
};
*/

void System::System()
{
	this->_particles    = nullptr;
	this->_neighbours   = nullptr;
	this->_periodic = new bool [3];

	this->_box_matrix = new double *[3];
	for(int i = 0; i < 3; i++)
		this->_box_matrix[i] = new double [3];
}
void System::~System()
{
	if(this->_neighbours != nullptr) delete [] this->_neighbours;
	delete [] this->_periodic;
	delete [] this->_particles;
	this->_neighbours.~NeighbourList();
	
	for(int i = 0; i < 3; i++)
		delete [] this->_box_matrix[i];
	delete [] this->_box_matrix;
}
void System::_setCutoff(double r_cutoff)
{
	this->_r_cutoff = r_cutoff;
}
void System::_setNAtoms(int n_atoms)
{
	this->_n_atoms = n_atoms;
}
void System::_setPeriodicity(bool px, bool py, bool pz)
{
	this->_periodic[0] = px;
	this->_periodic[1] = py;
	this->_periodic[2] = pz;
}
void System::_createParticlesTable()
{
	this->_particles = new Atom [this->_n_atoms];
}
void System::_createNeighboursList()
{
	this->_neighbours = new NeighbourList;	
}

#endif /* ATOM_SYSTEM_H */
