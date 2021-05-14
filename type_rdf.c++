#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

#define BP(string) std::cout << (string) << "\n";

ofstream logfile;

//-------------------------------------------------------------------------------
double scalarProduct(double *vector_a, double *vector_b)
{
	double product = 0.0;

	for(int i = 0; i < 3; i++)
		product += vector_a[i] * vector_b[i];

	return product;
}
void calculateBoxBasisVectors(double **vertices, double **&vectors, double *&point_of_origin)
{
	double **triclinic_parameters = new double *[3];
	for(int dimension = 0; dimension < 3; dimension++)
		triclinic_parameters[dimension] = new double [2];

	vector<double> values;

	values.push_back(0.0);
	values.push_back(vertices[0][2]);
	values.push_back(vertices[1][2]);
	values.push_back(vertices[0][2]+vertices[1][2]);

	triclinic_parameters[0][0] = vertices[0][0] - *min_element(values.begin(),values.end());
	triclinic_parameters[0][1] = vertices[0][1] - *max_element(values.begin(),values.end());
	
	triclinic_parameters[1][0] = vertices[1][0] - min(0.0, vertices[2][2]);
	triclinic_parameters[1][1] = vertices[1][1] - max(0.0, vertices[2][2]);
	
	triclinic_parameters[2][0] = vertices[2][0];
	triclinic_parameters[2][1] = vertices[2][1];

  point_of_origin[0] = triclinic_parameters[0][0];
  point_of_origin[1] = triclinic_parameters[1][0];
  point_of_origin[2] = triclinic_parameters[2][0];

	vectors[0][0] = triclinic_parameters[0][1] - triclinic_parameters[0][0];
	vectors[0][1] = 0.0;
	vectors[0][2] = vectors[0][1];

	vectors[1][0] = vertices[0][2];
	vectors[1][1] = triclinic_parameters[1][1] - triclinic_parameters[1][0];
	vectors[1][2] = 0.0;

	vectors[2][0] = vertices[1][2];
	vectors[2][1] = vertices[2][2];
	vectors[2][2] = triclinic_parameters[2][1] - triclinic_parameters[2][0];

  logfile << "\nTRICLINIC BOX VECTORS\n";

	for(int dimension = 0; dimension < 3; dimension++)
	{
    logfile << "Vector " << dimension+1  << " : ( ";
    for(int component = 0; component < 3; component++)
    {
      logfile << vectors[dimension][component] << " ";
    }
    logfile << ")\n";
  }   

	for(int dimension = 0; dimension < 3; dimension++)
		delete[] triclinic_parameters[dimension];
	delete [] triclinic_parameters;
}
double calculateBoxVolume(double **basis_vectors)
{
	double volume = basis_vectors[0][0] * (basis_vectors[1][1] * basis_vectors[2][2] 
										 - basis_vectors[2][1] * basis_vectors[1][2])
				  - basis_vectors[0][1] * (basis_vectors[1][0] * basis_vectors[2][2]
										 - basis_vectors[2][0] * basis_vectors[1][2])
				  + basis_vectors[0][2] * (basis_vectors[1][0] * basis_vectors[2][1]
										 - basis_vectors[2][0] * basis_vectors[1][1]);
  logfile << "\nBOX VOLUME : " << volume << "\n";
  return volume;
}
void normalizeBasisVectors(double **&basis_vectors)
{
  double norm = 0.0;

	for(int dimension = 0; dimension < 3; dimension++)
	{
		norm = scalarProduct( basis_vectors[dimension], basis_vectors[dimension] );	
		norm = sqrt(norm);
		basis_vectors[dimension][3] = norm;
	}	

}
void checkAtomWrapping(double *&atom_position, double **basis_vectors, double *point_of_origin)
{
	for(int dimension = 0; dimension < 3; dimension++)
	{
    atom_position[dimension] -= point_of_origin[dimension];
    atom_position[dimension] = scalarProduct(atom_position,basis_vectors[dimension]);
    atom_position[dimension] /= basis_vectors[dimension][3] * basis_vectors[dimension][3];
 //   pudla nie jest potrzebne

		if( atom_position[dimension] < 0.0 )
			atom_position[dimension] += 1.0;
		if( atom_position[dimension] > 1.0 )
			atom_position[dimension] -= 1.0;
	}	
}
bool checkPeriodicCoundaryConditions(double *position_i, double *position_j, double **box, double r_cut, double &dr, bool yes_x, bool yes_y, bool yes_z)
{
	double da = 0.0;
	double db = 0.0;
	double dc = 0.0;
	dr = 0.0;

	da = position_j[0] - position_i[0];
  db = position_j[1] - position_i[1];
  dc = position_j[2] - position_i[2];

  if(yes_x == true)
  {
	  if(da > 0.5) da -= 1.0;   
	  if(da <= -0.5) da += 1.0;   
  } 
  if(yes_y == true)
  {
	  if(db > 0.5) db -= 1.0;   
	  if(db <= -0.5) db += 1.0;   
  }
  if(yes_z == true)
  {
	  if(dc > 0.5) dc -= 1.0;   
	  if(dc <= -0.5) dc += 1.0;   
  }

  da *= box[0][3];
  db *= box[1][3];
  dc *= box[2][3];

  dr = (da * da) + (db * db) + (dc * dc);
  dr = sqrt(dr);

	bool final_check;

	if(dr <= r_cut) final_check = true;
	if(dr > r_cut) final_check = false;

	return final_check;
}
void createPairMap(int n_types,vector<string> &pair_map)
{
  stringstream keystring;

  for (int type_i = 0; type_i < n_types; type_i++) 
    for (int type_j = 0; type_j < n_types; type_j++)
    {
      keystring << type_i << type_j;
      pair_map.push_back(keystring.str());
      keystring.str("");
      keystring.clear();
    }

  int map_size = pair_map.size();

  stringstream key_i;
  stringstream key_j;
  string comparison_element = "";

  std::vector<string> good_elements;
  
  for (int map_element = 0; map_element < map_size; map_element++)
    if( pair_map[map_element] != "D" ) good_elements.push_back(pair_map[map_element]);

  pair_map.clear();

  map_size = good_elements.size();
  
  for (int map_element = 0; map_element < map_size; map_element++)
  {
    pair_map.push_back(good_elements[map_element]);
  }

  map_size = pair_map.size();
}
int whichTableRow(int i_type,int j_type, vector<string> type_map)
{
  int result = 0;

  stringstream typekeystream;
  string typekey;
  stringstream typecode;
  string typecodeelement;

  typekeystream << i_type << j_type;
  typekey = typekeystream.str();

  int map_size = type_map.size();

  for (int map_element = 0; map_element < map_size; map_element++)
  {
    typecode << type_map[map_element];
    typecode >> typecodeelement;
    
    if( typekey == typecodeelement )
    {
      result = map_element;
    }
    
    typecode >> typecodeelement;
    if( typekey == typecodeelement )
    {
      result = map_element;
    }
    typecode.str("");
    typecode.clear();
    
    if(result != 0) break;
  }

  typekeystream.str("");

  return result;
}
int checkInterval(double number, double range)
{
	int floored_number = (int) number;

	double lower_bound = range * floored_number;
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
int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "Input bin width!!!!\n";
		return 1;
	}
	if(argc < 3)
	{
		cout << "Input RDF cutoff radius!!!!\n";
		return 1;
	}
	if(argc < 6)
	{
		cout << "Input PBC settings (p for periodic, n for non periodic)!!!!\n";
		return 1;
	}
	if(argc < 8)
	{
		cout << "Input z_max and z_min range for RDF calculation\n";
		return 1;
	}

	
	stringstream argstream;
	argstream << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << " " << argv[5] << " " << argv[6] << " " << argv[7];

//---------------------------------------------------------------------------------
//Initialise stream

	std::ifstream infile;
	ofstream outfile;

	string inname, outname, filename;
	stringstream namestream;
	stringstream linestream;
	std::string line;
	
//---------------------------------------------------------------------------------
	
	namestream << "./test.dump"; 

	infile.open(namestream.str().c_str());

	if(!infile)
	{
		cout << "File not exist!" << "\n";
		return 1;
	}
	
	int linecounter = 0;
	int n_atoms = 0;

	while( std::getline(infile,line) )
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
 
	double r_max;
	double dr;
  double z_max;
  double z_min;

	argstream >> dr;
	argstream >> r_max;

  bool pbx = false;
  bool pby = false;
  bool pbz = false;

  std::string container;
  argstream >> container;
  
  if(container == "p") pbx = true;
  argstream >> container;
  if(container == "p") pby = true;
  argstream >> container;
  if(container == "p") pbz = true;

  argstream >> z_max;
  argstream >> z_min;

	int n_bins = r_max/dr + 10;
//================================
  int n_atom_types = 3;
  double height_of_vacum = 150.0;
//================================
  
  int n_pair_types = 0;

  for (int i = 0; i < n_atom_types; i++)
  {
    for (int j = 0; j < n_atom_types; j++)
    {
      n_pair_types++; 
    }
  }

  std::vector<string> pair_map;

  // Tworzenie mapy par
  
  createPairMap(n_atom_types, pair_map);

  int **bin_count = new int *[n_pair_types];
  for (int type = 0; type < n_pair_types; type++) 
  {
    bin_count[type] = new int [n_bins];
    for(int bin = 0; bin < n_bins; bin++)
      bin_count[type][bin] = 0;
  }
	
  int **timestep_bin_count = new int *[n_pair_types];
  for (int type = 0; type < n_pair_types; type++) 
  {
    timestep_bin_count[type] = new int [n_bins];
    for(int bin = 0; bin < n_bins; bin++)
      timestep_bin_count[type][bin] = 0;
  }
	
  double **gr = new double *[n_pair_types];
  for (int type = 0; type < n_pair_types; type++) 
  {
    gr[type] = new double [n_bins];
    for(int bin = 0; bin < n_bins; bin++)
      gr[type][bin] = 0;
  }

	double **box_vertices = new double *[3];
	for(int dimension = 0; dimension < 3; dimension++)
		box_vertices[dimension] = new double [3];

	double **box_vectors = new double *[3];
	for(int dimension = 0; dimension < 3; dimension++)
		box_vectors[dimension] = new double [4];

  double *origin = new double [3];

	double timestep_volume;
  
  double *coordinates = new double [4];
  std::vector<double*> atoms;


	infile.open(namestream.str().c_str());
  logfile.open("./log.out");

	int timestep_counter = 0;
	int atom_counter = 0;

	bool begin_timestep = false;
	bool begin_volume = false;
	bool begin_atoms = false;
	bool begin_analysis = false;
  int dimension_counter = 0;

	string trashcan;
    
  int *number_of_pairs = new int [n_pair_types];
  int counter = 0;

//---------------------------------------------------------------------------------
	while( std::getline(infile, line) )
	{
    if(begin_timestep)
    {
      if(begin_volume)
      {
        linestream.str(line);
        linestream >> box_vertices[dimension_counter][0];
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
          calculateBoxBasisVectors(box_vertices, box_vectors, origin);
          normalizeBasisVectors(box_vectors);
          timestep_volume = calculateBoxVolume(box_vectors);
          begin_volume = false;
        }
        
        linestream.str("");
        linestream.clear();
      }
      if(begin_atoms)
      {			
        int atom_type = 0;

        double height = box_vertices[2][1] - box_vertices[2][0] - height_of_vacum;
        
		linestream.str(line);
        linestream >> trashcan;
        linestream >> atom_type;

        for(int dimension = 0; dimension < 3; dimension++)
          linestream >> coordinates[dimension];
        coordinates[3] = atom_type - 1;
        
        if(coordinates[2]/height >= z_min)
        {
          if(coordinates[2]/height <= z_max)
          {
            atoms.push_back(new double [4]);
            atoms[counter][0] = coordinates[0]/box_vectors[0][3];
            atoms[counter][1] = coordinates[1]/box_vectors[1][3];
            atoms[counter][2] = coordinates[2]/box_vectors[2][3];
            atoms[counter][3] = coordinates[3];
            counter++;
          }
        }
        
        atom_counter++;
        
        if(atom_counter == n_atoms - 1)
        {
          begin_timestep = false;
          begin_atoms = false;
          begin_volume = false;
          begin_analysis = true;
          counter = 0;
          timestep_counter++;
		      cout << "Timestep : " << timestep_counter << '\n';
        }
      }
    }
		if(begin_analysis)
		{
      for (int type = 0; type < n_pair_types; type++) {
        number_of_pairs[type] = 0;
      }
		int sizeoftable = atoms.size();
      for(int atom_i = 0; atom_i < sizeoftable; atom_i++)
			{
				for(int atom_j = atom_i + 1; atom_j < sizeoftable; atom_j++)
				{
          for(int type_i = 0; type_i < n_atom_types; type_i++)
          {
            for(int type_j = 0; type_j < n_atom_types; type_j++)
            {
                int pair_type = whichTableRow(type_i, type_j, pair_map);
                number_of_pairs[pair_type]++;
            }
          }
        }
      }

			bool good_pair = false;
			int interval = 0;

      for(int pair_type = 0; pair_type < n_pair_types; pair_type++)
      {
        for(int bin = 0; bin < n_bins; bin++)
        {
          timestep_bin_count[pair_type][bin] = 0;
        }
      }

      if( z_max > 1.0 )
      {
        for(int atom_id = 0; atom_id < sizeoftable; atom_id++)
        {
          checkAtomWrapping(atoms[atom_id], box_vectors, origin);
        }
      }

			double r_ij = 0.0;
      double *r_i = new double [3];
      double *r_j = new double [3];
      
      for(int atom_i = 0; atom_i < sizeoftable; atom_i++)
			{
				for(int atom_j = atom_i + 1; atom_j < sizeoftable; atom_j++)
				{
          for(int type_i = 0; type_i < n_atom_types; type_i++)
          {
            for(int type_j = 0; type_j < n_atom_types; type_j++)
            {
              r_ij = 0.0;

              for(int dimension = 0; dimension < 3; dimension++)
              {
                r_i[dimension] = atoms[atom_i][dimension];
                r_j[dimension] = atoms[atom_j][dimension];
              }

              if( ( (int) atoms[atom_i][3] == type_i && (int) atoms[atom_j][3] == type_j ) )
              {
                int pair_type = whichTableRow(type_i, type_j, pair_map);
                good_pair = checkPeriodicCoundaryConditions(r_i, r_j, box_vectors, r_max, r_ij, pbx, pby, pbz);

                if(good_pair)
                {
                  double ratio = r_ij/dr; 
                  interval = checkInterval(ratio, dr);	
                  timestep_bin_count[pair_type][interval]++;
                }
              }
            }
          }
				}
			}
      
      delete [] r_i;
      delete [] r_j;

      for(int pair_type = 0; pair_type < n_pair_types; pair_type++)
      {
        for(int bin = 0; bin < n_bins; bin++)
        {
          bin_count[pair_type][bin] += timestep_bin_count[pair_type][bin];
          gr[pair_type][bin] += (timestep_bin_count[pair_type][bin] * timestep_volume ) 
              / (number_of_pairs[pair_type] * 4 * M_PI * ( bin * dr ) * ( bin * dr ) * dr ); 
        }
      }

			begin_analysis = false;
      begin_timestep = false;
      begin_atoms = false;
      begin_volume = false;
      atoms.clear();
		}
    if(!begin_analysis)
    {
      if(line.find("TIMESTEP") < line.length() && !begin_timestep)
      {
        for(int dimension = 0; dimension < 3; dimension++)
          for(int bound = 0; bound < 3; bound++)
            box_vertices[dimension][bound] = 0.0;
        
        timestep_volume = 1.0;
        dimension_counter = 0;
        atom_counter = 0;
        begin_timestep = true;
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

  stringstream histname, rdfname, rdftotal;
  stringstream mappart;
  string type_id;

  for (int type = 0; type < n_pair_types; type++)
  {
    mappart << pair_map[type];
    mappart >> type_id;

    histname << "./results/hist_" << type_id << ".out";
    rdfname << "./results/rdf_" << type_id << ".out";
    rdftotal << "./results/rdf_total.out";

    outfile.open(histname.str().c_str());

    for(int bin = 0; bin < n_bins; bin++)
    {
      outfile << bin * dr << " " << bin_count[type][bin] / timestep_counter << "\n";
    }

    outfile.close();
    outfile.clear();

    outfile.open(rdfname.str().c_str());

    for(int bin = 0; bin < n_bins; bin++)
    {
      outfile << bin * dr << " " << gr[type][bin] / timestep_counter << "\n";
    }

    outfile.close();
    outfile.clear();

    outfile.open(rdftotal.str().c_str());

    for(int bin = 0; bin < n_bins; bin++)
    {
      outfile << bin * dr << " " << (gr[0][bin] + gr[1][bin] + gr[2][bin]) / timestep_counter << "\n";
    }
   
	  outfile.close();
    outfile.clear();

    histname.str("");
    rdfname.str("");
  	rdftotal.str("");
    histname.clear();
    rdfname.clear();
	  rdftotal.clear();
    mappart.str("");
    mappart.clear();
  }

//===============================================================================

  delete [] coordinates;
  delete [] number_of_pairs;
  delete [] origin;

  for (int type = 0; type < n_pair_types; type++)
  {
    delete [] timestep_bin_count[type];
    delete [] gr[type];
    delete [] bin_count[type];
  }

	delete [] timestep_bin_count;
	delete [] gr;
	delete [] bin_count;
	

	for(int dimension = 0; dimension < 3; dimension++)
		delete [] box_vectors[dimension];
	delete [] box_vectors;

	for(int dimension = 0; dimension < 3; dimension++)
		delete [] box_vertices[dimension];
	delete [] box_vertices;

//================================================================================

  return 0;
  
  logfile.close();
}
