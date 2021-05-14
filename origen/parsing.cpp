#include <iostream>
#include "parsing.h"

using namespace std;

int parseParametersFile(string paramsname, string &lattice, int **indices, double &a, double &b, double &c, string &basename, int *reps, double *zero, string &write, string &output, string &outtype, string &atype){

  string line,keyword;
  stringstream linestream;
  ifstream params;

  params.open(paramsname.c_str(), ios::in );

  if(!params.good()){cout << "\nERROR: File specified doesn't exist!\n"; return 1;}
  if(params.good()){

    while(!params.eof()){

          getline(params,line);

          linestream.str(line);

          linestream >> keyword;
          if(keyword == "write"){linestream >> write;}
          if(keyword == "lattice"){

                  linestream >> lattice;
                  if(lattice == "fcc" || lattice == "bcc" || lattice == "sc" || lattice == "dia"){linestream >> a; b = a; c = a;}
                  if(lattice == "custom"){

                    linestream >> basename;
                    linestream >> a;
                    linestream >> b;
                    linestream >> c;


                  }

          }
          if(keyword == "a"){

                  linestream >> indices[0][0];
                  linestream >> indices[0][1];
                  linestream >> indices[0][2];

          }
          if(keyword == "c"){

                  linestream >> indices[2][0];
                  linestream >> indices[2][1];
                  linestream >> indices[2][2];

          }
          if(keyword == "rep"){

                  for (int i = 0; i < 3; i++) {

                      linestream >> reps[i];

                  }

          }
          if(keyword == "origin"){

                  for (int i = 0; i < 3; i++) {

                      linestream >> zero[i];

                  }

          }
          if(keyword == "output"){

                linestream >> output;
                linestream >> outtype;

          }
          if(keyword == "atomtype"){

                linestream >> atype;

          }


          linestream.clear();
          linestream.str("");
    }

    params.close();

    if(atype == ""){atype = "Si";}
    if(lattice != "fcc" && lattice != "bcc" && lattice != "sc" && lattice != "custom"){cout << "ERROR: Wrong lattice type specified!\n"; return 1;}
    if(a <= 0 || b <= 0 || c <= 0){cout << "ERROR: Invalid lattice constants!\n"; return 1;}
    if(output == ""){cout << "ERROR: No output filename specified!\n"; return 1;}
    if(outtype != "xyz" && outtype != "lmpdata"){cout << "ERROR: No output filetype specified!\n"; return 1;}
    if(reps[0] == 0 && reps[1] == 0 && reps[2] == 0){cout << "WARNING: Elementary cell will not be duplicated!\n";}

    bool wrong_miller = false;

    if(indices[0][0] == 0 && indices[0][1] == 0 && indices[0][2] == 0){wrong_miller = true;}
    if(indices[2][0] == 0 && indices[2][0] == 0 && indices[2][0] == 0){wrong_miller = true;}
    if(wrong_miller == true){cout << "ERROR: Invalid Miller indices!\n"; return 1;}

    return 0;

  }

}

void determineAtomicBasis(string type, double **type_basis, string basefile){

  if(type == "custom"){

    loadBasis(type_basis, basefile);

  }

  if(type == "fcc"){

  type_basis[0][0] = 0;
  type_basis[0][1] = 0;
  type_basis[0][2] = 0;

  type_basis[1][0] = 0;
  type_basis[1][1] = 0.5;
  type_basis[1][2] = 0.5;

  type_basis[2][0] = 0.5;
  type_basis[2][1] = 0.5;
  type_basis[2][2] = 0;

  type_basis[3][0] = 0.5;
  type_basis[3][1] = 0;
  type_basis[3][2] = 0.5;

  }

  if(type == "bcc"){

  type_basis[0][0] = 0;
  type_basis[0][1] = 0;
  type_basis[0][2] = 0;

  type_basis[1][0] = 0.5;
  type_basis[1][1] = 0.5;
  type_basis[1][2] = 0.5;

  }

  if(type == "sc"){

  type_basis[0][0] = 0;
  type_basis[0][1] = 0;
  type_basis[0][2] = 0;

  }
  if(type == "dia"){

  type_basis[0][0] = 0;
  type_basis[0][1] = 0;
  type_basis[0][2] = 0;

  type_basis[1][0] = 0;
  type_basis[1][1] = 0.5;
  type_basis[1][2] = 0.5;

  type_basis[2][0] = 0.5;
  type_basis[2][1] = 0.5;
  type_basis[2][2] = 0;

  type_basis[3][0] = 0.5;
  type_basis[3][1] = 0;
  type_basis[3][2] = 0.5;

  type_basis[4][0] = 0.75;
  type_basis[4][1] = 0.25;
  type_basis[4][2] = 0.25;

  type_basis[5][0] = 0.75;
  type_basis[5][1] = 0.75;
  type_basis[5][2] = 0.75;

  type_basis[6][0] = 0.25;
  type_basis[6][1] = 0.75;
  type_basis[6][2] = 0.25;

  type_basis[7][0] = 0.25;
  type_basis[7][1] = 0.25;
  type_basis[7][2] = 0.75;


  }

}
void writeAtomsToFile(double **data, string filename, int rows, double a, double b, double c, string type, string atype){

  ofstream file;

  file.open(filename.c_str());

  file << rows << "\n";
  file << "Type: " << type << "\n";

  for(int i = 0; i < rows-1; i++){

    data[i][0] = data[i][0]*a;
    data[i][1] = data[i][1]*b;
    data[i][2] = data[i][2]*c;

    file << atype << " " << data[i][0] << " " << data[i][1] << " " << data[i][2] << "\n";

  }

  data[rows-1][0] = data[rows-1][0]*a;
  data[rows-1][1] = data[rows-1][1]*b;
  data[rows-1][2] = data[rows-1][2]*c;

  file << atype << " " << data[rows-1][0] << " " << data[rows-1][1] << " " << data[rows-1][2] << "\n";

  file.close();

}
int countBasis(string basefile){

    ifstream basis_file;
    string line;
    int linecounter = -1;

    basis_file.open(basefile.c_str());

    while(!basis_file.eof()){

      getline(basis_file, line);
      linecounter++;

    }

    basis_file.close();
    return linecounter;

}
void loadBasis(double **basis, string basefile){

    ifstream basis_file;
    string line;
    stringstream liness;
    int linecounter = 0;

    basis_file.open(basefile.c_str());

    while(!basis_file.eof()){

      getline(basis_file, line);
      liness.str(line);

      for (int i = 0; i < 3; i++) {

        liness >> basis[linecounter][i];

      }

      liness.clear();
      liness.str("");

      linecounter++;

    }

    basis_file.close();

}
void writeCrystalToXYZ(double **crystal, double *zero, string filename, int rows, string type, string atype){

  stringstream namestream;

  namestream << filename << ".xyz";

  ofstream file;

  file.open(namestream.str().c_str());

  file << rows << "\n";
  file << "Type: " << type << "\n";

  for(int i = 0; i < rows; i++){

    for(int j = 0; j < 3; j++){

	crystal[i][j] = crystal[i][j] + zero[j];

    }

    file << atype << " " << crystal[i][0] << " " << crystal[i][1] << " " << crystal[i][2] << "\n";

  }

  file.close();
  namestream.clear();
  namestream.str("");

}
void writeCrystalToLmpData(double **crystal, double *box, string filename, int rows, string type, string atype){

  stringstream namestream;

  namestream << filename << ".data";

  ofstream file;

  file.open(namestream.str().c_str());

  file << "Oriented crystal file\n\n";
  file << rows << " atoms \n";
  file << "0 bonds\n";
  file << "0 angles\n";
  file << "0 dihedrals\n";
  file << "0 impropers\n\n";

  file << "1 atom types\n\n";

  file << box[0] << " " << box[3] << " xlo xhi\n";
  file << box[1] << " " << box[4] << " ylo yhi\n";
  file << box[2] << " " << box[5] << " zlo zhi\n\n";

  file << "Atoms\n\n";

  for(int i = 0; i < rows; i++){

   	file << i+1 << " " << atype << " " << crystal[i][0] << " " << crystal[i][1] << " " << crystal[i][2] << "\n";

  }

  file.close();
  namestream.clear();
  namestream.str("");

}
