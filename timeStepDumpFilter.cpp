#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>

using namespace std;

int main(int argc, char* argv[])
{

	ifstream infile;
	ofstream outfile;

	int currentTimestep = 0;

	std::ostringstream oss;
	string inname, outname, filename;
	int i;
	for(int temp = 600; temp <= 1250; temp+=50){
        for(i = 0; i <= 500000; i+=50000){
            oss.str("");
            oss << "./AlSi_" << temp << "/" << i << "_AlSi.lammpstrj";

            currentTimestep = i;
            outname = oss.str();

            cout << outname << endl;

            stringstream namestream, linestream;

            namestream << "../../AlSi_4ML/dump_log_sample/AlSi_" << temp << ".lammpstrj";

            filename = namestream.str();
            infile.open(filename.c_str());

            if(!infile){
                cout << "File not exist!" << "\n";
                return 1;
            }

            outfile.open(outname.c_str());

            bool start_push = false;
            int timestep = 0;
            int linecounter = 0;
            int numbofatoms = 0;
            int allatoms = 0;

            string type = "";
            string id = "";
            string x_c = "";
            string y_c = "";
            string z_c = "";
            string line, oldline;

                while(!infile.eof()){
                    getline(infile, line);
                    if(line == "ITEM: TIMESTEP" && linecounter > 0){break;}

                    if(linecounter > 8){
                        start_push = true;
                        linestream.str(line);

                        allatoms++;
                        numbofatoms++;

                        linestream.clear();
                        linestream.str("");
                    }

                    if(start_push == false){oldline = line;}

                    linecounter++;
                }

        infile.close();
        infile.clear();

        infile.open(filename.c_str());

        bool atoms_found = false;
        int atom_counter = 0;
        int all_atoms_counter = 0;
        linecounter = 0;

        while(!infile.eof()){
            getline(infile, line);
            linestream.str(line);

            if(line == "ITEM: TIMESTEP"){
                getline(infile, line);
                linestream.str(line);
                linestream >> timestep;

                if(currentTimestep == timestep){
                    outfile << "ITEM: TIMESTEP" << '\n';
                }
            }

            if(currentTimestep == timestep){
                if(line == "ITEM: TIMESTEP"){
                    linecounter = 0;
                }

                if(oldline == "ITEM: NUMBER OF ATOMS"){
                    outfile << numbofatoms << '\n';
                } else {
                    if(!atoms_found){
                        outfile << line << "\n";
                        linecounter++;
                    }

                    if(atoms_found){
                        string coordinates = "";
                        linestream >> id;
                        linestream >> type;
                        linestream >> x_c;
                        linestream >> y_c;
                        linestream >> z_c;

                        if(atom_counter < numbofatoms){
                            int position = id.length()+type.length()+2;
                            outfile << atom_counter+1 << " " << type << " " << line.substr(position) << "\n";
                            atom_counter++;
                        }

                        all_atoms_counter++;

                        if(all_atoms_counter == allatoms){
                            all_atoms_counter = 0;
                            atoms_found = false;
                        }
                    }

                if( atoms_found == false && line == "ITEM: ATOMS id type x y z vx vy vz "){
                    atom_counter = 0;
                    atoms_found = true;
                }
            }
        }

        oldline = line;
        linestream.clear();
        linestream.str("");
    }

    infile.close();
    infile.clear();

    outfile.close();
    }
}
    return 0;
}
