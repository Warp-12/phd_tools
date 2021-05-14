#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "ERROR!: No filename specified!\n";
        return 1;
    }
    
    string filename = argv[1];

    ifstream infile;
    ofstream exp_data, fit_data, first_data, second_data, third_data;

    string temperature;
    string initial_filename, first_filename, second_filename, third_filename, four_filename, five_filename;
    stringstream namestream;
//---------------------------------------------------------------------
    namestream << "./gnudata/" << filename << "_exp.GNU";

    first_filename = namestream.str();

    namestream.clear();
    namestream.str("");
//-----------------------------------------------------------------------
    namestream << "./gnudata/" << filename << "_fit.GNU";

    second_filename = namestream.str();

    namestream.clear();
    namestream.str("");
//-----------------------------------------------------------------------
    namestream << "./gnudata/" << filename << "_fp.GNU";

    third_filename = namestream.str();

    namestream.clear();
    namestream.str("");
//-----------------------------------------------------------------------
    namestream << "./gnudata/" << filename << "_sp.GNU";

    four_filename = namestream.str();

    namestream.clear();
    namestream.str("");
//-----------------------------------------------------------------------
    namestream << "./gnudata/" << filename << "_tp.GNU";

    five_filename = namestream.str();

    namestream.clear();
    namestream.str("");
//-----------------------------------------------------------------------
    namestream << "./input/" << filename << ".GRF";

    initial_filename = namestream.str();

    namestream.clear();
    namestream.str("");
//-----------------------------------------------------------------------    
    infile.open(initial_filename.c_str());
    exp_data.open(first_filename.c_str());
    fit_data.open(second_filename.c_str());
    first_data.open(third_filename.c_str());
    second_data.open(four_filename.c_str());
    third_data.open(five_filename.c_str());

    string line;
    int linecounter = 0;
    bool stop_first_data   = false;
    bool start_second_data = false;
    bool stop_second_data  = false;
    bool stop_third_data   = false;
    bool start_third_data  = false;
    bool stop_four_data    = false;
    bool start_four_data   = false;
    bool stop_five_data    = false;
    bool start_five_data   = false;
    

    while(!infile.eof())
    {
        getline(infile,line);
        if(linecounter >= 41 && stop_first_data == false)
        {
            if(line.find_first_of("PLOT") != -1)
            {
                stop_first_data = true;
                start_second_data = true;
                linecounter = 0;
            }
            if(stop_first_data == false)
            {
                exp_data << line << "\n"; 
            }
        }
//--------------------------------------------------------------------     
		if(start_second_data == true)
        {
            if(linecounter >= 2 && stop_second_data == false)
            {
                if(line.find_first_of("JOIN") != -1)
                {
                    stop_second_data = true;
					start_third_data = true;
					linecounter = 0;
                }
                if(stop_second_data == false)
                {
                    fit_data << line << "\n"; 
                }
            }
        }
//--------------------------------------------------------------------
        if(start_third_data == true)
        {
            if(linecounter >= 604 && stop_third_data == false)
            {
                if(line.find_first_of("join") != -1)
                {
                    stop_third_data = true;
					start_four_data = true;
					linecounter = 0;

                }
                if(stop_third_data == false)
                {
                    first_data << line << "\n"; 
                }
            }
        }
//-------------------------------------------------------------------
        if(start_four_data == true)
        {
            if(linecounter >= 1 && stop_four_data == false)
            {
                if(line.find_first_of("join") != -1)
                {
                    stop_four_data = true;
					start_five_data = true;
					linecounter = 0;

                }
                if(stop_four_data == false)
                {
                    second_data << line << "\n"; 
                }
            }
        }
//-------------------------------------------------------------------
        if(start_five_data == true)
        {
            if(linecounter >= 1 && stop_five_data == false)
            {
                if(line.find_first_of("join") != -1)
                {
                    stop_five_data = true;
                }
                if(stop_five_data == false)
                {
                    third_data << line << "\n"; 
                }
            }
        }
//-------------------------------------------------------------------
        linecounter++;
    }

    exp_data.close();
    fit_data.close();
    first_data.close();
    second_data.close();
    third_data.close();
    infile.close();

    return 0;
}
