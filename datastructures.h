#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <iostream>

struct msd_snapshot
{
    int _n_atoms;
    double **_reference;
    double **_positions;
    double **_old_positions;
    double *_msd;

    double **_box_limits;
    double *_box_dimensions;

    msd_snapshot()
    {
        this->_n_atoms = 0;
        this->_msd = new double [4];
        this->_box_limits = new double *[3];
        this->_box_dimensions = new double [3];

        for(int i = 0; i < 3; i++)
        {
            this->_box_limits[i] = new double [2];
        }
    }
    void createAtomTables()
    {
        int rows = this->_n_atoms;

        this->_positions = new double *[rows];
        this->_old_positions = new double *[rows];
        this->_reference = new double *[rows];
        
        for(int row = 0; row < rows; row++)
        {
            this->_positions[row] = new double [3];
            this->_old_positions[row] = new double [3];
            this->_reference[row] = new double [3];
        }
    }
    void deleteAtomTables()
    {
        int rows = this->_n_atoms;

        for(int row = 0; row < rows; row++)
        {
            delete [] this->_positions[row];
            delete [] this->_old_positions[row];
            delete [] this->_reference[row];
        }
        
        delete [] this->_positions;
        delete [] this->_old_positions;
        delete [] this->_reference;
    }
    void updateOldPositions()
    {
        int rows = this->_n_atoms;
        
        for(int row = 0; row < rows; row++)
        {
            for ( int dim = 0; dim < 3; dim++ )
            {
                this->_old_positions[row][dim] = this->_positions[row][dim];
            }
        }
    }
    void computeMSD()
    {
        int rows = this->_n_atoms;

        double *displacement = new double [4];

        for ( int dim = 0; dim < 3; dim++ )
        {
            this->_msd[dim] = 0.0;
        }
        
        for ( int row = 0; row < rows; row++ )
        {
            double sum = 0;

            for ( int dim = 0; dim < 3; dim++ )
            {
                displacement[dim] = this->_positions[row][dim]-this->_old_positions[row][dim];

                if( displacement[dim] > 0.5 * this->_box_dimensions[dim] )
                {
                    this->_reference[row][dim] += this->_box_dimensions[dim];   
                }
                if( displacement[dim] <= -0.5 * this->_box_dimensions[dim] )
                {
                    this->_reference[row][dim] -= this->_box_dimensions[dim];   
                }
                
                displacement[dim] = this->_positions[row][dim]-this->_reference[row][dim];
                sum += displacement[dim]*displacement[dim];
                this->_msd[dim] += displacement[dim]*displacement[dim];
            }

        }
        for ( int dim = 0; dim < 4; dim++ )
        {
            this->_msd[dim] /= rows;
        }
        
        this->_msd[3] = sqrt(this->_msd[0]*this->_msd[0] +
                             this->_msd[1]*this->_msd[1] +
                             this->_msd[2]*this->_msd[2] );

        delete [] displacement;
    }
    ~msd_snapshot()
    {
        this->deleteAtomTables();

        for(int i = 0; i < 3; i++)
        {
            delete [] this->_box_limits[i];
        }

        delete [] this->_msd;
        delete [] this->_box_dimensions;
        delete [] this->_box_limits;
    }
};

#endif /* DATASTRUCTURES_H */
