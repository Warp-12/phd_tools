#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include"./neighbour_list.h"

using namespace std;

#define BP(string) std::cout << (string) << "\n";
int checkInterval(double number, double range)
{
    int floored_number = (int) number;

    double lower_bound  = range * floored_number;
    double higher_bound = range * ( floored_number + 1 );

    int result;

    if( number >= lower_bound && number < higher_bound )
        result =  floored_number;
    if( number < lower_bound )
        result = floored_number - 1;
    if( number >= higher_bound )
        result = floored_number + 1;
  return result;
}

//-------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "Input cutoff radius!!!\n";
		return 1;
	}

	stringstream argstream;
	argstream << argv[1];
//---------------------------------------------------------------------------------
//Initialise stream

	ifstream infile;
	ofstream outfile;

	string inname, outname, filename;
	stringstream namestream;
	stringstream linestream;
	string line;
	
//---------------------------------------------------------------------------------
	
	namestream << "./dump_2w/AuSi_425.lammpstrj"; //zmiana nazwy  pliku dumpa

	infile.open(namestream.str().c_str());

	if(!infile)
	{
		cout << "File not exist!" << "\n";
		return 1;
	}
	
	int linecounter = 0;
	int n_atoms = 0;

	while( getline(infile,line) )
	{
		linecounter++;
		if(linecounter == 4)
		{
			linestream.str(line);
			linestream >> n_atoms;
			linestream.str("");
			linestream.clear();
		}
	}

	infile.close();
	infile.clear();

//--------------------------------------------------------------------------------
//-------------------------------Structure of cod---------------------------------
 

	double **box_vertices = new double *[3];   // tablica na x_min x_maxx .... pudlo symulacyjne
	for(int dimension = 0; dimension < 3; dimension++)
	{
		box_vertices[dimension] = new double [3];
	}

	double **atoms = new double *[n_atoms]; // tablica na koordynaty dla atomów
	for(int atom_id = 0; atom_id < n_atoms; atom_id++)
	{
		atoms[atom_id] = new double [4];
	}
	infile.open(namestream.str().c_str());


	int timestep_counter  = 0;
	int atom_counter      = 0;
    int dimension_counter = 0;

	bool begin_timestep = false;
	bool begin_volume   = false;
	bool begin_atoms    = false;
	bool begin_analysis = false;
 
	double timestep_area;
	double rcut;
	
	argstream >> rcut;

	string trashcan;

//---------------------------------------------------------------------------------
//-------------------------------> Neighbour list creation <-----------------------

	int *numberofneighbours ;
	int     **neighbourlist ;
	double         **lenght ;


//---------------------------------------------------------------------------------
	while( getline(infile, line) )
	{
    if(begin_timestep)
    {
      if(begin_volume)
      {
        linestream.str(line);
        
        linestream >> box_vertices[dimension_counter][0] ; 
        linestream >> box_vertices[dimension_counter][1];
       
		
		if( !linestream.eof() )
        {
          linestream >> box_vertices[dimension_counter][2];
        }
        else
        {
          box_vertices[dimension_counter][2] = 0.0;
        }

        dimension_counter++;
        if(dimension_counter > 2)
        {
          begin_volume  = false;
		  dimension_counter = 0;
        }

        linestream.str("");
        linestream.clear();
  
      }

//======================Atoms coord reading========================
      if(begin_atoms)
      {			
        int atom_type = 0;

        timestep_area = calculateArea(box_vertices);
		height = calculateHeight(box_vertices);
        
		linestream.str(line);
        linestream >> trashcan;
        linestream >> atom_type;

        for(int dimension = 0; dimension < 3; dimension++)
          linestream >> atoms[atom_counter][dimension];
        
        atoms[atom_counter][3] = atom_type-1; // atom type sie zmienia dla elementu tablicy
        atom_counter++;
        
        if(atom_counter == n_atoms - 1) // kiedy dojedzie do przedostatniego atomu zaczna analiza
        {
          begin_timestep = false; // nie zaczyna zczytywac timestepu
          begin_atoms = false;   // nie zaczyna zczytywac coords atomów 
          begin_volume = false; // -//- objetosci
          
          begin_analysis = true; // nie zaczu=yna analizy na najbliszczy sasiadów
		  atom_counter = 0;
          timestep_counter++; // podnosi licznik dla nastepnego timestepu
        }
      }
    }
    if(begin_analysis)
    {
						
	verletList(atoms, box_vertices, numbofatoms, numbwindow, rcut, numberofneighbours, neighbourslist, lenght);
//----------------------------------------------------------------------------
//------------------------------------------------------------
      begin_analysis = false;
      begin_timestep = false;
      begin_atoms    = false;
      begin_volume   = false;
	  
	}
    if(!begin_analysis) //gdy nie bylo analizy to zczytuje do tablic poz naliezieniu odpowiednich nazw w pliku
    {
      if(line.find("TIMESTEP") < line.length() && !begin_timestep)
      {
        for(int dimension = 0; dimension < 3; dimension++)
		{
          for(int bound = 0; bound < 3; bound++)
		  {
			  box_vertices[dimension][bound] = 0.0;
		  }
		}
        timestep_area     = 1.0;
        dimension_counter = 0;
        atom_counter      = 0;
        begin_timestep    = true;
      }
      if(line.find("BOUNDS") < line.length() && !begin_volume)
      {
        begin_volume = true;
      }
      if(line.find("id type x y z") < line.length() && !begin_atoms)
      {
        begin_atoms = true;
      }
    }
  }

  infile.close();
//-----------------------------------------------------------------------------------------------------
  
//----------------------------------------------------------------------------------------------------
//wypisywanie do pliku na końcu
/*
  stringstream denname;
	
  denname << "profile_density.out";
    outfile.open(denname.str().c_str());

    //for(int bin = 0; bin < density.size(); bin++)
	for(int i = 0; i < max; i++)
    {
		if(density_profile[i][0] != 0)
		{
		  outfile << i*dz/height << "  " << i*dz << "   " << density_profile[i][0] 
						  << "   " << density_profile[i][1]/timestep_counter
						  << "   " << density_profile[i][2]/density_profile[i][0]
						  << "   " << density_profile[i][3]/density_profile[i][0] << "\n";
		}
	}

    outfile.close();
    outfile.clear();

    denname.str("");
    denname.clear();
*/
//===============================================================================
//------> Czyszczenie pamięci po tablicach <------------
	
  for(int atom_id = 0; atom_id < n_atoms; atom_id++)
		delete [] atoms[atom_id]; 
	delete [] atoms;
  
	for(int count = 0; count < elements; count++)
		delete [] density_profile[count]; 
	delete [] density_profile;
	
	for(int dimension = 0; dimension < 3; dimension++)
		delete [] box_vertices[dimension];
	delete [] box_vertices;

	delete [] neighbourslist;
	delete [] lenght;


//================================================================================

  return 0;

}
