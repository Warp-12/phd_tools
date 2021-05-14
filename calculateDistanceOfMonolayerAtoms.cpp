#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>
#include<climits>
#include<iostream>
#include<cfloat>
#include<vector>
#include<algorithm>
#include "rawstate/rawstate.h"
using namespace std;
using namespace RawState;
using namespace RawStateLAMMPSTools;

int main(int argc, char* argv[])
{
//---------------------------------------------------------------------------
    (void)argc;
    (void)argv;

    ofstream outfile;

    std::string dumpfile = "./4_at/925_34.lammpstrj";

    RawState::setStateTimestep(0);
    RawState::setStateTimestepDelta(1);
    int number_of_readings = RawStateLAMMPSTools::getNumberOfReadings(dumpfile);

    double **atoms_i = new double *[number_of_readings];
    for(int step_id = 0; step_id < number_of_readings; step_id++)
        atoms_i[step_id] = new double [5];

    double **atoms_j = new double *[number_of_readings];
    for(int step_id = 0; step_id < number_of_readings; step_id++)
        atoms_j[step_id] = new double [5];

    double **atoms_ij = new double *[number_of_readings];
    for(int step_id = 0; step_id < number_of_readings; step_id++)
        atoms_ij[step_id] = new double [2];


    Atom **timestep_atoms  = new Atom *[number_of_readings];
//---------------------------------------------------------------------------
    for(int step_id = 0; step_id < number_of_readings; step_id++){

        System *auAtoms = new System;
        auAtoms->_readNextLAMMPSTimestep(dumpfile);
        timestep_atoms[step_id] = new Atom [auAtoms->_n_atoms];

        for(int atom_i =0; atom_i < auAtoms->_n_atoms; atom_i++){

            timestep_atoms[step_id][atom_i]._createPositionsTable();

            timestep_atoms[step_id][atom_i]._position[0] = auAtoms->_particles[atom_i]._position[0];
            timestep_atoms[step_id][atom_i]._position[1] = auAtoms->_particles[atom_i]._position[1];
            timestep_atoms[step_id][atom_i]._position[2] = auAtoms->_particles[atom_i]._position[2];

            if(atom_i == 0){
                atoms_i[step_id][0] = timestep_atoms[step_id][atom_i]._position[0];
                atoms_i[step_id][1] = timestep_atoms[step_id][atom_i]._position[1];
                atoms_i[step_id][2] = timestep_atoms[step_id][atom_i]._position[2];
            }
            if(atom_i == 1){
                atoms_j[step_id][0] = timestep_atoms[step_id][atom_i]._position[0];
                atoms_j[step_id][1] = timestep_atoms[step_id][atom_i]._position[1];
                atoms_j[step_id][2] = timestep_atoms[step_id][atom_i]._position[2];
            }
        }
        delete auAtoms;
    }
//---------------------------------------------------------------------------

    double r_t_i  = 0.0;
    double r_to_i = 0.0;
    double msd_i  = 0.0;

    double r_t_j  = 0.0;
    double r_to_j = 0.0;
    double msd_j  = 0.0;

    double r_atom_ij  = 0.0;

    r_to_i   = atoms_i[0][0] * atoms_i[0][0] + atoms_i[0][1] * atoms_i[0][1] + atoms_i[0][2] * atoms_i[0][2];
    r_to_i   = sqrt(r_to_i);

    r_to_j   = atoms_j[0][0] * atoms_j[0][0] + atoms_j[0][1] * atoms_j[0][1] + atoms_j[0][2] * atoms_j[0][2];
    r_to_j   = sqrt(r_to_j);

    for(int i = 0; i < number_of_readings; i++) {

            r_t_i   = atoms_i[i][0] * atoms_i[i][0] + atoms_i[i][1] * atoms_i[i][1] + atoms_i[i][2] * atoms_i[i][2];
            r_t_i   = sqrt(r_t_i);
            msd_i   = (r_t_i - r_to_i)*(r_t_i-r_to_i);

            r_t_j   = atoms_j[i][0] * atoms_j[i][0] + atoms_j[i][1] * atoms_j[i][1] + atoms_j[i][2] * atoms_j[i][2];
            r_t_j   = sqrt(r_t_j);
            msd_j   = (r_t_j - r_to_j)*(r_t_j - r_to_j);


            r_atom_ij   = pow((atoms_j[i][0] - atoms_i[i][0]),2) + pow((atoms_j[i][1] - atoms_i[i][1]),2) + pow((atoms_j[i][2] - atoms_i[i][2]),2);
            r_atom_ij   = sqrt(r_atom_ij);

            atoms_ij[i][0] = r_atom_ij;

            atoms_i[i][3] = r_t_i;
            atoms_i[i][4] = msd_i;

            atoms_j[i][3] = r_t_j;
            atoms_j[i][4] = msd_j;
    }
//--------------------------------------------------------------------------------------------------
   double sum_ij = 0.0;

   for(int i = 0; i < number_of_readings; i++) {
       sum_ij+=atoms_ij[i][0];

   }
   sum_ij/=number_of_readings;
   cout << "AVERAGE DISTANCE OF ATOM_I AND ATOM_J: " << sum_ij << "\n";



//--------------------------------------------------------------------------------------------------
    int count_i = 0;
    int count_j = 0;

    vector <double> changes_x_i;
    vector <double> changes_y_i;
    vector <double> changes_z_i;
    vector <int> jump_time_i;

    vector <double> changes_x_j;
    vector <double> changes_y_j;
    vector <double> changes_z_j;
    vector <int> jump_time_j;

    double radius_before_i = 0.0;
    double radius_i        = 0.0;
    double radius_after_i  = 0.0;

    double radius_before_j = 0.0;
    double radius_j        = 0.0;
    double radius_after_j  = 0.0;

    for(int i = 0; i < number_of_readings - 1; i++){
        if(i>1){

            radius_before_i = atoms_i[i-1][0] * atoms_i[i-1][0] + atoms_i[i-1][1] * atoms_i[i-1][1] + atoms_i[i-1][2] * atoms_i[i-1][2];
            radius_i        = atoms_i[i][0]   * atoms_i[i][0]   + atoms_i[i][1]   * atoms_i[i][1]   + atoms_i[i][2]   * atoms_i[i][2];
            radius_after_i  = atoms_i[i+1][0] * atoms_i[i+1][0] + atoms_i[i+1][1] * atoms_i[i+1][1] + atoms_i[i+1][2] * atoms_i[i+1][2];

            radius_before_j = atoms_j[i-1][0] * atoms_j[i-1][0] + atoms_j[i-1][1] * atoms_j[i-1][1] + atoms_j[i-1][2] * atoms_j[i-1][2];
            radius_j        = atoms_j[i][0]   * atoms_j[i][0]   + atoms_j[i][1]   * atoms_j[i][1]   + atoms_j[i][2]   * atoms_j[i][2];
            radius_after_j  = atoms_j[i+1][0] * atoms_j[i+1][0] + atoms_j[i+1][1] * atoms_j[i+1][1] + atoms_j[i+1][2] * atoms_j[i+1][2];

            radius_before_i = sqrt(radius_before_i);
            radius_i        = sqrt(radius_i);
            radius_after_i  = sqrt(radius_after_i);

            radius_before_j = sqrt(radius_before_j);
            radius_j        = sqrt(radius_j);
            radius_after_j  = sqrt(radius_after_j);

            if(radius_i <= radius_before_i){
                if(radius_after_i > radius_i){
                    changes_x_i.push_back(atoms_i[i][0]);
                    changes_y_i.push_back(atoms_i[i][1]);
                    changes_z_i.push_back(atoms_i[i][2]);
                    jump_time_i.push_back(i);

                    count_i++;
                }
            }

            if(radius_j <= radius_before_j){
                if(radius_after_j > radius_j){
                    changes_x_j.push_back(atoms_j[i][0]);
                    changes_y_j.push_back(atoms_j[i][1]);
                    changes_z_j.push_back(atoms_j[i][2]);
                    jump_time_j.push_back(i);

                    count_j++;
                }
            }
        }
    }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Zmiany!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        int size_of_vector_i = jump_time_i.size();
        int size_of_vector_j = jump_time_j.size();

        double **displacement_i = new double *[size_of_vector_i];
        for(int count_index = 0; count_index < size_of_vector_i; count_index++)
            displacement_i[count_index] = new double [5];

        double **displacement_j = new double *[size_of_vector_j];
        for(int count_index = 0; count_index < size_of_vector_j; count_index++)
            displacement_j[count_index] = new double [5];


        for(int i = 0; i < size_of_vector_i; i++){
            displacement_i[i][0] = 0;
            displacement_i[i][1] = jump_time_i[i];
            displacement_i[i][2] = changes_x_i[i];
            displacement_i[i][3] = changes_y_i[i];
            displacement_i[i][4] = changes_z_i[i];
        }
        for(int i = 0; i < size_of_vector_j; i++){
            displacement_j[i][0] = 0;
            displacement_j[i][1] = jump_time_j[i];
            displacement_j[i][2] = changes_x_j[i];
            displacement_j[i][3] = changes_y_j[i];
            displacement_j[i][4] = changes_z_j[i];
        }
    //-----------------------> Calculate distant <---------------------------

        double r_ij_i= 0.0;
        double x_i_i = 0.0;
        double y_i_i = 0.0;
        double z_i_i = 0.0;
        double x_j_i = 0.0;
        double y_j_i = 0.0;
        double z_j_i = 0.0;
        double xx_i = 0.0;
        double yy_i = 0.0;
        double zz_i = 0.0;
        int proved_i = 0;
        double sum_i = 0;
        int ave_i = 0;

        double r_ij_j= 0.0;
        double x_i_j = 0.0;
        double y_i_j = 0.0;
        double z_i_j = 0.0;
        double x_j_j = 0.0;
        double y_j_j = 0.0;
        double z_j_j = 0.0;
        double xx_j = 0.0;
        double yy_j = 0.0;
        double zz_j = 0.0;
        int proved_j = 0;
        double sum_j = 0;
        int ave_j = 0;

        for(int shift_i = 0; shift_i < size_of_vector_i-1; shift_i++){

            int shift_j = shift_i + 1;

            x_i_i = displacement_i[shift_i][2];
            y_i_i = displacement_i[shift_i][3];
            z_i_i = displacement_i[shift_i][4];

            x_j_i = displacement_i[shift_j][2];
            y_j_i = displacement_i[shift_j][3];
            z_j_i = displacement_i[shift_j][4];

            xx_i = x_j_i - x_i_i;
            yy_i = y_j_i - y_i_i;
            zz_i = z_j_i - z_i_i;

            r_ij_i = xx_i*xx_i + yy_i*yy_i + zz_i*zz_i;
            r_ij_i = sqrt(r_ij_i);

            displacement_i[shift_i][0] = r_ij_i;

        }

        for(int shift_i = 0; shift_i < size_of_vector_i; shift_i++){
            if(displacement_i[shift_i][0] >= 1.17){
                if(shift_i>1){
                    proved_i = displacement_i[shift_i][1]- displacement_i[shift_i-1][1];
                    sum_i+=proved_i;
                    ave_i++;
                }
            }
        }
        sum_i/=ave_i;

        for(int shift_i = 0; shift_i < size_of_vector_j-1; shift_i++){

            int shift_j = shift_i + 1;

            x_i_j = displacement_j[shift_i][2];
            y_i_j = displacement_j[shift_i][3];
            z_i_j = displacement_j[shift_i][4];

            x_j_j = displacement_j[shift_j][2];
            y_j_j = displacement_j[shift_j][3];
            z_j_j = displacement_j[shift_j][4];

            xx_j = x_j_j - x_i_j;
            yy_j = y_j_j - y_i_j;
            zz_j = z_j_j - z_i_j;

            r_ij_j = xx_j*xx_j + yy_j*yy_j + zz_j*zz_j;
            r_ij_j = sqrt(r_ij_j);

            displacement_j[shift_i][0] = r_ij_j;

        }

        for(int shift_i = 0; shift_i < size_of_vector_j; shift_i++){
            if(displacement_j[shift_i][0] >= 1.17){
                if(shift_i>1){
                    proved_j = displacement_j[shift_i][1]- displacement_j[shift_i-1][1];
                    sum_j+=proved_j;
                    ave_j++;
                }
            }
        }
        sum_j/=ave_j;



//--------------------------------------------------------------------------------------
    double maximum_i = -DBL_MAX;
    double minimum_i = DBL_MAX;
    double maximum_j = -DBL_MAX;
    double minimum_j = DBL_MAX;


    for(int counter = 0; counter < count_i; counter++){
            if(displacement_i[counter][0] > maximum_i){
                maximum_i = displacement_i[counter][0];
            }
            if(displacement_i[counter][0] < minimum_i){
                minimum_i = displacement_i[counter][0];
            }
    }
    for(int counter = 0; counter < count_j; counter++){
            if(displacement_j[counter][0] > maximum_j){
                maximum_j = displacement_j[counter][0];
            }
            if(displacement_j[counter][0] < minimum_j){
                minimum_j = displacement_j[counter][0];
            }
    }

    cout << "Number of change sign:  " << "Au1 : " << count_i << "  " << "Au2 : " << count_j << "\n";
    cout << "Maximum: " << "Au1 : " << maximum_i << " " << "Au2 : " << maximum_j << "\n";
//----------------------------------------------------------------------------------------

    double swapHolder = -1.0;
    double swapIndex = 1.0;
    int    end        = count_i;
    int    length     = count_i;

    for(int counter = length - 1; counter > 0; counter--){
        for(int index = 0; index < end; index++){
            if(index >= 1){
                if(displacement_i[index-1][0] > displacement_i[index][0]){
                    swapHolder = displacement_i[index][0];
                    displacement_i[index][0] = displacement_i[index-1][0];
                    displacement_i[index-1][0] = swapHolder;

                    swapIndex = displacement_i[index][1];
                    displacement_i[index][1] = displacement_i[index-1][1];
                    displacement_i[index-1][1] = swapIndex;
                }
            }
        }
        end--;
    }

    swapHolder = -1.0;
    swapIndex = 1.0;
    end        = count_j;
    length     = count_j;

    for(int counter = length - 1; counter > 0; counter--){
        for(int index = 0; index < end; index++){
            if(index >= 1){
                if(displacement_j[index-1][0] > displacement_j[index][0]){
                    swapHolder = displacement_j[index][0];
                    displacement_j[index][0] = displacement_j[index-1][0];
                    displacement_j[index-1][0] = swapHolder;

                    swapIndex = displacement_j[index][1];
                    displacement_j[index][1] = displacement_j[index-1][1];
                    displacement_j[index-1][1] = swapIndex;
                }
            }
        }
        end--;
    }
   //----------------------------------------------------------------------
    int n_bins = 1000;

        double bin_width_i = maximum_i/n_bins;
        double bin_width_j = maximum_j/n_bins;

        int *bins_i = new int [n_bins];
        for(int bin = 0; bin < n_bins; bin++){
            bins_i[bin] = 0;
        }

        int *bins_j = new int [n_bins];
        for(int bin = 0; bin < n_bins; bin++){
            bins_j[bin] = 0;
        }

        double **probability_i = new double *[n_bins];
        for(int bin = 0; bin < n_bins; bin++){
            probability_i[bin] = new double [2];

            for(int i = 0; i < 2 ; i++){
                probability_i[bin][i] = 0;
            }
        }
        double **probability_j = new double *[n_bins];
        for(int bin = 0; bin < n_bins; bin++){
            probability_j[bin] = new double [2];

            for(int i = 0; i < 2 ; i++){
                probability_j[bin][i] = 0;
            }
        }

        for(int jump = 0; jump < count_i; jump++){
            int bin_id = 0;

            for(int bin = 0; bin < n_bins; bin++){
                double min = bin * bin_width_i;
                double max = (bin + 1) * bin_width_i;

                if(displacement_i[jump][0] >= min){
                    if(displacement_i[jump][0] < max){
                        bin_id = bin;
                        probability_i[bin][0] = displacement_i[jump][0];
                    }
                }
            }
            bins_i[bin_id]++;
        }
        for(int jump = 0; jump < count_j; jump++){
            int bin_id = 0;

            for(int bin = 0; bin < n_bins; bin++){
                double min = bin * bin_width_j;
                double max = (bin + 1) * bin_width_j;

                if(displacement_j[jump][0] >= min){
                    if(displacement_j[jump][0] < max){
                        bin_id = bin;
                        probability_j[bin][0] = displacement_j[jump][0];
                    }
                }
            }
            bins_j[bin_id]++;
        }
        for(int bin = 0; bin < n_bins; bin++){
            probability_i[bin][1] = bins_i[bin];
            probability_i[bin][1] /= count_i;
            probability_i[bin][1] /= bin_width_i;
        }

        for(int bin = 0; bin < n_bins; bin++){
            probability_j[bin][1] = bins_j[bin];
            probability_j[bin][1] /= count_j;
            probability_j[bin][1] /= bin_width_j;
        }
//-----------------------------------------------------------------------------
//---------------------Max probability ----------------------------------------
double 	maximum_p_i = -DBL_MAX;
double maximum_probability_distance_i = 0.0;
double 	maximum_p_j = -DBL_MAX;
double maximum_probability_distance_j = 0.0;

        for(int bin = 0; bin < n_bins; bin++){
            if(probability_i[bin][1] > maximum_p_i){
                maximum_p_i = probability_i[bin][1];
                maximum_probability_distance_i = probability_i[bin][0];
            }
        }

        for(int bin = 0; bin < n_bins; bin++){
            if(probability_j[bin][1] > maximum_p_j){
                maximum_p_j = probability_j[bin][1];
                maximum_probability_distance_j = probability_j[bin][0];
            }
        }


        int time_counter_i = 0;
        double ave_jump_distance_i = 0.0;
        int jump_ave_i = 0;

        int time_counter_j = 0;
        double ave_jump_distance_j = 0.0;
        int jump_ave_j = 0;

        for(int i = 0; i < count_i; i++){
            if(displacement_i[i][0] >= 2.88){
                if(displacement_i[i][0] > maximum_probability_distance_i){
                        time_counter_i++;
                }
            }

            if(displacement_i[i][0] > 2.16){
                    ave_jump_distance_i+=displacement_i[i][0];
                    jump_ave_i++;
            }
        }
            ave_jump_distance_i/=jump_ave_i;

            for(int i = 0; i < count_j; i++){
                if(displacement_j[i][0] >= 2.88){
                    if(displacement_j[i][0] > maximum_probability_distance_j){
                            time_counter_j++;
                    }
                }

                if(displacement_j[i][0] > 2.16){
                        ave_jump_distance_j+=displacement_j[i][0];
                        jump_ave_j++;
                }
            }
                ave_jump_distance_j/=jump_ave_j;



       cout << "Average time counter   : " << "Atom_i: " << sum_i << " | " << "Atom_j: " << sum_j << "\n";
       cout << "Time_counter           : " << "Atom_i: " << time_counter_i << " | " << "Atom_j: " << time_counter_j << "\n";
       cout << "Probability distance   : " << "Atom_i: " << maximum_probability_distance_i << " | " << "Atom_j: " << maximum_probability_distance_j << "\n";
       cout << "Average jump distance  : " << "Atom_i: " << ave_jump_distance_i  << " | " << "Atom_j: " <<  ave_jump_distance_j  << "\n";
//----------------------------------------------------------------------------------------




    stringstream timedistance_i;
    timedistance_i << "distance_after_sorting_i.out";

    outfile.open(timedistance_i.str().c_str());

    for(int count_index = 0; count_index < count_i; count_index++){
        outfile << displacement_i[count_index][0] << "   " <<
                   displacement_i[count_index][1] << "\n";
    }

    outfile.close();
    outfile.clear();

    timedistance_i.str("");
    timedistance_i.clear();


    stringstream timedistance_j;
    timedistance_j << "distance_after_sorting_j.out";

    outfile.open(timedistance_j.str().c_str());

    for(int count_index = 0; count_index < count_j; count_index++){
        outfile << displacement_j[count_index][0] << "   " <<
                   displacement_j[count_index][1] << "\n";
    }

    outfile.close();
    outfile.clear();

    timedistance_j.str("");
    timedistance_j.clear();

//---------------------------------------------------------------------------
    for(int step_id = 0; step_id <number_of_readings; step_id++){delete [] atoms_i[step_id];}
    delete [] atoms_i;

    for(int step_id = 0; step_id <number_of_readings; step_id++){delete [] atoms_j[step_id];}
    delete [] atoms_j;

    for(int step_id = 0; step_id <number_of_readings; step_id++){delete [] atoms_ij[step_id];}
    delete [] atoms_ij;

    for(int count_index = 0; count_index < size_of_vector_i; count_index++){delete [] displacement_i[count_index];}
      delete [] displacement_i;

    for(int count_index = 0; count_index < size_of_vector_j; count_index++){delete [] displacement_j[count_index];}
      delete [] displacement_j;

    for(int bin = 0; bin < n_bins; bin++){delete [] probability_i[bin];}
      delete [] probability_i;

    for(int bin = 0; bin < n_bins; bin++){delete [] probability_j[bin];}
      delete [] probability_j;

    delete [] bins_i;
    delete [] bins_j;

}
