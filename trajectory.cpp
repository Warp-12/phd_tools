#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <dirent.h>
#include "datastructures.h"

using namespace std;

#define HEADER_COUNT 9
#define GOOD_FILE_CRITERION temp_name != ".." && temp_name != "."

int parseInputFilenames(std::string *&filenames)
{
	int n_files = 0;	
	DIR *input_files_directory;
	struct dirent *input_file;

	if ((input_files_directory = opendir ("./input/")) != NULL){

 		while ((input_file = readdir (input_files_directory)) != NULL){
		
			string temp_name = input_file->d_name;	
			if(GOOD_FILE_CRITERION){
				
				int file_extension_trj = 0;

				file_extension_trj = temp_name.find(".lammpstrj");
				
				if(file_extension_trj != -1){n_files++;}

			}

  		}

		closedir (input_files_directory);

		filenames = new string [n_files];

  		input_files_directory = opendir ("./input/");

		int counter = 0;
		stringstream namestream;

 		while ((input_file = readdir (input_files_directory)) != NULL){
					
			string temp_name = input_file->d_name;	
			if(GOOD_FILE_CRITERION){

					int file_extension_trj = 0;

					file_extension_trj = temp_name.find(".lammpstrj");

					if(file_extension_trj != -1){

					namestream << "./input/" << temp_name;

					filenames[counter] = namestream.str();

					namestream.clear();
					namestream.str("");
					cout << filenames[counter] << "\n";
					counter++;
				
				}				

			}

  		}
  		closedir (input_files_directory);
	} 
	else{return 0;}	

	return n_files;

}
void parseTrajectoryFile(string filename, int start, int end, int n_windows, int id)
{
    ifstream trajectory;

    msd_snapshot *snapshot = new msd_snapshot [n_windows];  

    trajectory.open(filename.c_str());

    string line, oldline;
    stringstream linestream;

    int n_atoms = 0;

    while( n_atoms == 0 )
    {
        getline(trajectory, line);

        if( oldline == "ITEM: NUMBER OF ATOMS")
        {
            linestream.str(line);
            linestream >> n_atoms;
            linestream.clear();
            linestream.str("");
        }

        oldline = line;
    }

    trajectory.close();
    trajectory.clear();

    int timestep_lines = 9+n_atoms;

    trajectory.open(filename.c_str());

    int window_lines = (end-start)*timestep_lines/n_windows;
    int window_timesteps = (end-start)/n_windows; 
    int line_counter = 0;
    
    bool start_time = false;
    bool start_dimensions = false;
    bool start_timestep = false;

    int time_label = 0;
    int dim_counter = 0;
    
    int timestep_counter = 0;
    int window_counter = 0;
    int atom_counter = 0;
    bool tables_allocated = false;

    string trash;
    stringstream windataname, avedataname;

    ofstream windows_data;
    ofstream averaged_data;

    windataname << "./output/windows_" << id+1 << ".out"; 
    avedataname << "./output/average_" << id+1 << ".out"; 

    windows_data.open(windataname.str().c_str());
    averaged_data.open(avedataname.str().c_str());

    while( window_counter != n_windows )
    {
        if( tables_allocated == false )
        {
            snapshot[window_counter]._n_atoms = n_atoms;
            snapshot[window_counter].createAtomTables();    
            tables_allocated = true;
        }

        getline(trajectory, line);
        
        if( oldline == "ITEM: TIMESTEP" && start_time == false )
        {
            linestream.str(line);
            linestream >> time_label;

            if( time_label == start )
            {
                start_time = true;
            }

            linestream.clear();
            linestream.str("");
        }
        if( start_time == true )
        {
            if( oldline == "ITEM: TIMESTEP")
            {
                linestream.str(line);
                linestream >> time_label;

                if( time_label == end )
                {
                    start_time = false;
                }

                linestream.clear();
                linestream.str("");
            }
            if( oldline == "ITEM: BOX BOUNDS pp pp ff" )
            {
                start_dimensions = true;
            }
            if( start_dimensions == true )
            {
                linestream.str(line);

                linestream >> snapshot[window_counter]._box_limits[dim_counter][0];
                linestream >> snapshot[window_counter]._box_limits[dim_counter][1];

                linestream.clear();
                linestream.str("");

                snapshot[window_counter]._box_dimensions[dim_counter] =
                snapshot[window_counter]._box_limits[dim_counter][1] - snapshot[window_counter]._box_limits[dim_counter][0];

                dim_counter++;

                if( dim_counter == 3 )
                {
                    dim_counter = 0;
                    start_dimensions = false;
                }
            }
            if( oldline == "ITEM: ATOMS id type x y z vx vy vz " )
            {
                start_timestep = true;
            }
            if( start_timestep == true )
            {
                linestream.str(line);

                int atom_id = 0;
                linestream >> atom_id;
                atom_id -= 1;
                linestream >> trash;

                if( timestep_counter == 0 )
                {
                    for( int col = 0; col < 3; col++ )
                    {
                        double value;
                        linestream >> value;
                        snapshot[window_counter]._reference[atom_id][col] = value;
                        snapshot[window_counter]._positions[atom_id][col] = value;
                        snapshot[window_counter]._old_positions[atom_id][col] = value;
                    }
                }
                else
                {
                    for( int col = 0; col < 3; col++ )
                    {
                        double value;
                        linestream >> value;
                        snapshot[window_counter]._positions[atom_id][col] = value;
                    }
                }

                linestream.clear();
                linestream.str("");
                atom_counter++;
                
                if( atom_counter == n_atoms )
                {
                    snapshot[window_counter].computeMSD();
                    
                    windows_data << window_counter+1 << " " << timestep_counter << " " << snapshot[window_counter]._msd[0] << " " << snapshot[window_counter]._msd[1] << " " << snapshot[window_counter]._msd[2] << " " << snapshot[window_counter]._msd[3] << "\n";
                    
                    snapshot[window_counter].updateOldPositions();
                    
                    timestep_counter++;
                    start_timestep = false;
                    atom_counter = 0;
                }
            }

            line_counter++;

            if(line_counter == window_lines)
            {
                window_counter++;
                tables_allocated = false;
                timestep_counter = 0;
                line_counter = 0;
            }
        }
        oldline = line;
    }

    windows_data.close();
    windows_data.clear();

    double *ave_msd = new double [window_timesteps]; 
    
    for(int time = 0; time < window_timesteps; time++)
    {
        ave_msd[time] = 0;
    }

    ifstream to_average;

    to_average.open(windataname.str().c_str());

    double time_value;

    while(getline(to_average,line))
    {
        int timestep = 0; 
        linestream.str(line);
        
        linestream >> trash;
        linestream >> timestep;
        linestream >> time_value;

        ave_msd[timestep] += time_value;

        linestream.clear();
        linestream.str("");
    }

    to_average.close();

    for(int time = 0; time < window_timesteps; time++)
    {
        ave_msd[time] /= n_windows;
        averaged_data << time << " " << ave_msd[time] << "\n";
    }

    averaged_data.close();

    trajectory.close();
    trajectory.clear();

    delete [] ave_msd;
    delete [] snapshot;
}
