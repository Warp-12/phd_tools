#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<string>

using namespace std;

int main(int argc, char* argv[]){
//Reading from files

	
	ifstream parametrfile;
	ofstream outfile;

	string line;
	stringstream inname_exp, inname_fit, outname;
	stringstream linestream;
	int temp_index   = 0;
	int index = 0;
	int line_counter = 0;
	double parameters_exp[600][2][28];
	double parameters_fit[340][2][28];
	double par_out[340][2][28];
//==========================================================================================================
	for(int i = 1; i < 29; i++)
	{
		temp_index = i;
		if(temp_index<10){inname_exp << "./gnudata/" << temp_index << "KK_exp.GNU";}
		else if(temp_index>=10){inname_exp << "./gnudata/" << temp_index << "K_exp.GNU";}

	parametrfile.open(inname_exp.str().c_str());
	while(!parametrfile.eof())
	{
		 getline(parametrfile, line);
		 linestream.str(line);

		 linestream >> parameters_exp[line_counter][0][i] >> parameters_exp[line_counter][1][i];
					line_counter++;                                                                            
																												 
		linestream.clear();                                                                                   
		linestream.str("");              

	}

	parametrfile.close();
	parametrfile.clear();
	inname_exp.clear();
	inname_exp.str("");
	line_counter=0;
	}
//==========================================================================================================
	for(int i = 1; i < 29; i++)
	{
		temp_index = i;
		if(temp_index<10){inname_fit << "./gnudata/" << temp_index << "KK_fit.GNU";}
		else if(temp_index>=10){inname_fit << "./gnudata/" << temp_index << "K_fit.GNU";}

	parametrfile.open(inname_fit.str().c_str());
	while(!parametrfile.eof())
	{
		 getline(parametrfile, line);
		 linestream.str(line);

		 linestream >> parameters_fit[line_counter][0][i] >> parameters_fit[line_counter][1][i];
					line_counter++;                                                                            
																												 
		linestream.clear();                                                                                   
		linestream.str("");              

	}

	parametrfile.close();
	parametrfile.clear();
	inname_fit.clear();
	inname_fit.str("");
	line_counter=0;
	}
//==========================================================================================================
	for(int q = 1; q < 29; q++)
	{
		index = q;
		if(index<10){outname << "./diffrdf/" << index << "KK_dif.GNU";}
		else if(index>=10){outname << "./diffrdf/" << index << "K_dif.GNU";}

	outfile.open(outname.str().c_str());
	for(int i =0; i < 340; i++)
	{
		
		par_out[i][0][q] = parameters_exp[i][0][q];
		par_out[i][1][q] = parameters_fit[i][1][q]-parameters_exp[i][1][q];
		for(int j = 0; j < 2; j++){outfile << par_out[i][j][q] << "    ";}

		outfile << '\n';

	}

	outfile.close();
	outfile.clear();
	outname.clear();
	outname.str("");

	for(int i = 0; i < 340; i++)
	{
		for(int j =0; j < 2; j++)
		{
			par_out[i][j][q] = 0;
		}
	}
	}
/*
for(int i = 0; i < 340; i++)
{  cout << "\n";
	for(int j = 0; j < 2; j++)
	{   cout << "\n";
		for(int k = 1; k < 29; k++)
		{
			cout << "\t" << parameters_fit[i][j][k] << "  " << "\t\n";
		}
	}
}
*/
	return 0;
}
