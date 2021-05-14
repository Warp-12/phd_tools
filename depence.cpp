#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<string>

using namespace std;

string outheader = "        N         R        sigma**2     beta ";

int main(int argc, char* argv[]){
//Reading from files

	
	ifstream parametrfile;
	ofstream outfile;

	string line;
	stringstream inname, outname;
	stringstream linestream;
	int start_push   = 0;
	int stop_push    = 0;
	int temp_index   = 0;
	int line_counter = 0;
	double parameters[4][3][29];
	double par_out[29][14];
//==========================================================================================================
	for(int i = 0; i < 29; i++)
	{
		temp_index = i;
		if(temp_index<10){inname << "./groutput/" << temp_index << "KK.OUT";}
		else if(temp_index>=10){inname << "./groutput/" << temp_index << "K.OUT";}

	parametrfile.open(inname.str().c_str());
	while(!parametrfile.eof())
	{
		 getline(parametrfile, line);
		 linestream.str(line);

		 if(line=="  =========================================== " && start_push==1) {start_push=0;}           
		 if(start_push==1)
		 {                                                                                                     
						linestream >> parameters[line_counter][0][i] >> parameters[line_counter][1][i] >> 
							          parameters[line_counter][2][i] >> parameters[line_counter][3][i];
						line_counter++;                                                                            
		 }                                                                                                     
		                if(line==outheader){start_push=1;}                                                                
																												 
		linestream.clear();                                                                                   
		linestream.str("");              

	}

	parametrfile.close();
	parametrfile.clear();
	inname.clear();
	inname.str("");
	line_counter=0;
	}
//==========================================================================================================

	outname << "./gnudata/depen_plot.txt";
	outfile.open(outname.str().c_str());
	for(int i =0; i < 29; i++)
	{
		par_out[i][0] = 550+i*25;
		par_out[i][1] = parameters[0][0][i];
		par_out[i][2] = parameters[1][0][i];
		par_out[i][3] = parameters[2][0][i];
		par_out[i][4] = parameters[0][1][i];
		par_out[i][5] = parameters[1][1][i];
		par_out[i][6] = parameters[2][1][i];
		par_out[i][7] = parameters[0][2][i];
		par_out[i][8]= parameters[1][2][i];
		par_out[i][9]= parameters[2][2][i];
		par_out[i][10]= parameters[0][3][i];
		par_out[i][11]= parameters[1][3][i];
		par_out[i][12]= parameters[2][3][i];
        par_out[i][13]= parameters[0][0][i]+parameters[1][0][i]+parameters[2][0][i];
		for(int j = 0; j < 14; j++){outfile << par_out[i][j] << "  ";}

		outfile << '\n';

	}

	outfile.close();
	outfile.clear();
	outname.clear();
	outname.str("");

	for(int i =0; i <29; i++)
	{
		for(int j =0; j < 14; j++)
		{
			par_out[i][j]=0;
		}
	}

for(int i=0; i< 4; i++)
{  cout << "\n";
	for(int j =0; j<4; j++)
	{   cout << "\n";
		for(int k =0; k < 29; k++)
		{
			cout << "\t" << parameters[i][j][k] << "  " << "\t\n";
		}
	}
}
	return 0;
}
