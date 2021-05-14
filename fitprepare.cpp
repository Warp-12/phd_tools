#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

#define INCREMENT 25

string outheader = "        N         R        sigma**2     beta ";
string inputfiles = "./groutput/";
string outputfiles = "./grinput/";

int main(int argc, char* argv[])
{
	
	if(argc < 2)
	{
		cout << "ERROR!: No temperature value passed to program!!\n";
		return 1;
	}
	if(argc < 3)
	{
		cout << "ERROR!: No ansamble type passed to program!!\n";
		return 1;
	}

	cout << "STARTING FitPrepare!\n";

	int step = 0;	
	string ansamble;
	string direct;

	stringstream arguments;

	arguments << argv[1] << " " << argv[2] << " " << argv[3];
	arguments >> step;
	arguments >> ansamble;
	arguments >> direct;

	arguments.clear();
	arguments.str("");

	stringstream namestream;
	string inname, outname;
	
	double **parameters = new double *[4];

	for(int i = 0; i < 4; i++)
	{
		parameters[i] = new double [4];
	}

	double a = 3.980281e-12;
   	double b = -1.514274e-8;
   	double c = 2.125616e-5;
   	double d = -0.01430541790652;
   	double e = 13.6876399668339;
   	double next_temperature = 550+INCREMENT*step;
   	double density = (a*next_temperature*next_temperature*next_temperature*next_temperature+b*next_temperature*next_temperature*next_temperature+c*next_temperature*next_temperature+d*next_temperature+e)/346.9068;	
	stringstream gaussstream;
        string gauss[4];

       	for(int i=0; i < 4; i++)
	{
		gaussstream << "'G'," << 4*i+1 << "," << 4*i+3 << "," << 4*i+2 << "," << 4*i+4 << "\n";
		gauss[i]=gaussstream.str();
		gaussstream.clear();
		gaussstream.str("");
	}

	string other[6];
	other[0]="2.5,3.8\n";
	other[1]="2.,5.0\n";

	stringstream tempstream;
	if(step < 10)
	{
		tempstream << step << "KK";
	}
	if(step >= 10)
	{
		tempstream << step << "K";
	}
	other[2]= tempstream.str();
	tempstream.str("");

	other[3]="\nSET ERRDEF  0.00000000001\n";
	other[4]="SIMPLEX     4000 \n";
	if(direct=="up")
	{
		if(step >= 10)
		{
			if(step == 10)
			{
				namestream << inputfiles << "9KK.OUT";
			}
			if(step > 10)
			{
				namestream << inputfiles << step-1 << "K.OUT";
			}
		}
		if(step < 10)
		{
			namestream << inputfiles << step-1 << "KK.OUT";
		}
	}
    if(direct=="down")
	{
		if(step >= 9)
		{
			if(step == 9)
			{
				namestream << inputfiles << "10K.OUT";
			}
			if(step > 9)
			{
				namestream << inputfiles << step+1 << "K.OUT";
			}
		}
		if(step < 9)
		{
			namestream << inputfiles << step+1 << "KK.OUT";
		}
	}
	inname = namestream.str();
	namestream.clear();
	namestream.str("");
	
	ifstream parameterfile;
	parameterfile.open(inname.c_str());

	// READING OF LAST TEMPERATURE PARAMETERS FOR FITTING
	
	string line;
	stringstream linestream;
	int start_push = 0;
	int line_counter =0;
	
	// ==================================================
	
	while(!parameterfile.eof())
	{
		getline(parameterfile, line);
		linestream.str(line);
		
		if(line=="  =========================================== " && start_push==1) {start_push=0;}
		if(start_push==1)
		{
			linestream >> parameters[line_counter][0] >> parameters[line_counter][1] >> parameters[line_counter][2] >> parameters[line_counter][3];       
			line_counter++;
		}
        	if(line==outheader){start_push=1;}

		linestream.clear();
		linestream.str("");
	}

	// ==================================================
	
	parameterfile.close();

	namestream << outputfiles << step << ".IN";
	outname = namestream.str();
	namestream.clear();
	namestream.str("");

	ofstream scriptfile;
	scriptfile.open(outname.c_str());

	scriptfile << fixed << setprecision(5);
     	

	// WRITING OF GRFIT INPUT SCRIPT FOR NEXT TEMPERATURE
	
	// =================================================

	string blankspace = "";
	int parametercounter = 1;

	scriptfile << "---------|---------|---------|---------|---------|---------|\n";

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			double min,max;

			if( j != 1  && j != 0)
			{
				min = 0.5*parameters[i][j];
				max = 1.2*parameters[i][j];
			}
			if( j == 0 )
			{
				min = 0.5*parameters[i][j];
				max = 2.0*parameters[i][j];
			}
			if( j == 1 )
			{
				min = parameters[i][j]-0.1;
				max = parameters[i][j]+0.1;
			}

			if(parametercounter < 10)
			{
				scriptfile << "    " << parametercounter << "    ";
			}
			if(parametercounter >= 10)
			{
				scriptfile << "   " << parametercounter << "    ";
			}
			
			if(j == 0){ scriptfile << "  N_" << i+1 << "      ";}
			if(j == 1){ scriptfile << "  R_" << i+1 << "      ";}
			if(j == 2){ scriptfile << "  V_" << i+1 << "      ";}
			if(j == 3){ scriptfile << "  B_" << i+1 << "      ";}

			if(parameters[i][j] > 10.0)
			{
				scriptfile << parameters[i][j] << "  "; 
			}	
			if(parameters[i][j] < 10.0)
			{
				scriptfile << parameters[i][j] << "   "; 
			}
			if(i == 0)
			{	
				if(j == 0){ scriptfile << " 0.1      ";}
				if(j == 1){ scriptfile << " 0.01     ";}
				if(j == 2){ scriptfile << " 0.0001   ";}
				if(j == 3){ scriptfile << " 0.01     ";}
			}
			if(i == 1)
			{	
				if(j == 0){ scriptfile << " 0.1      ";}
				if(j == 1){ scriptfile << " 0.01     ";}
				if(j == 2){ scriptfile << " 0.001    ";}
				if(j == 3){ scriptfile << " 0.01     ";}
			}
			if(i == 2)
			{	
				if(j == 0){ scriptfile << " 0.1      ";}
				if(j == 1){ scriptfile << " 0.01     ";}
				if(j == 2){ scriptfile << " 0.001    ";}
				if(j == 3){ scriptfile << " 0.1      ";}
			}
/*			if(i == 3)
			{	
				if(j == 0){ scriptfile << " 0.01     ";}
				if(j == 1){ scriptfile << " 0.01     ";}
				if(j == 2){ scriptfile << " 0.001    ";}
				if(j == 3){ scriptfile << " 0.01     ";}
			}
*/			if(min > 10.0)
			{
				scriptfile << min << "  "; 
			}	
			if(min < 10.0)
			{
				scriptfile << min << "   "; 
			}
			if(max > 10.0)
			{
				scriptfile << max << "  "; 
			}	
			if(max < 10.0)
			{
				scriptfile << max << "   "; 
			}
			scriptfile << "\n";
			parametercounter++;
		}
	}

	scriptfile << setprecision(0);
	scriptfile << "\n";
	scriptfile << "./rdfdata/averdf_" << next_temperature << "_" << ansamble << ".txt.rdf\n";
	scriptfile << setprecision(10) << density << "\n";
	scriptfile << 3 << "\n";

	for(int i = 0; i < 3; i++)
	{
		scriptfile << gauss[i];	
	}
	for(int i = 0; i < 5; i++)
	{
		scriptfile << other[i];	
	}

	scriptfile << "EXIT\n";

	// =================================================
	
	scriptfile.close();

	for(int i = 0; i < 4; i++)
	{
		delete [] parameters[i];
	}
	delete [] parameters;

	return 0;
}
