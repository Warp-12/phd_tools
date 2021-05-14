#include <iostream>
#include "./origen/origen.h"
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <climits>
#include <float.h>

using namespace std;

int main(int argc, char *argv[]){
    (void)argc;
    int bottom_layers = 0;
    int top_layers    = 0;
    int top_Au_layers = 0;

    string element_1 = argv[1];
    string element_2 = argv[4];
    string latticetype_1;
    string latticetype_2;

    stringstream argstream;

    argstream << argv[2] << " " << argv[3] << " " << argv[5] ;
    argstream >> bottom_layers; argstream >> top_layers; argstream >> top_Au_layers;

    bottom_layers -= 1;

    int *repz    = new int [3];
    int *repz_Au = new int [3]; // ilosc powtórzeń w kierunku każdej osi dla Krzemu
    int **mill   = new int *[3];

    for(int i = 0; i < 3; i++){
        mill[i] = new int [3];
    }
    double *pointoforigin = new double [3];
    double **bottom_unfiltered;
    double *cell;
    double latticeconstants_1[3];
    double latticeconstants_2[3];

    repz[0]=10;         repz[1]=10;         repz[2]=10;
    mill[0][0]=1;       mill[0][1]=0;       mill[0][2]=0;
    mill[2][0]=0;       mill[2][1]=0;       mill[2][2]=1;
    pointoforigin[0]=0; pointoforigin[1]=0; pointoforigin[2]=0;

    latticeconstants_1[0]=5.4281; latticeconstants_1[1]=5.4281;	latticeconstants_1[2]=5.4281;
    latticetype_1="dia";

    latticeconstants_2[0]=4.0495; latticeconstants_2[1]=4.0495; latticeconstants_2[2]=4.0495;
    latticetype_2="fcc";


    int n_bottom=origenStart(repz, pointoforigin, mill, latticeconstants_1, latticetype_1, "", "", "lmpdata", "1", cell, bottom_unfiltered, "no");

    double *simulation_box = new double [4];
    simulation_box[0] = cell[0]; simulation_box[1] = cell[3];
    simulation_box[2] = cell[1]; simulation_box[3] = cell[4];

    double dx,dy,dz,dr;
    double spacing = DBL_MAX;
    double spacing_epsilon = 0.0001;
    double minimum = DBL_MAX;
    double minimum_epsilon = 0.0001;
    double old_spacing = 0.0;
    double old_minimum = 0.0;
    bool escape = false;

    for(int i = 0; i < n_bottom; i++){
        if(escape == true){break;}

        for(int j = 0; j < n_bottom; j++){
            dz = abs(bottom_unfiltered[j][2]-bottom_unfiltered[i][2]);

            if(escape == true) {break;}
            if(dz < spacing && dz > 0.0) {old_spacing = spacing; spacing = dz;}
            if(spacing-old_spacing == spacing_epsilon) {escape = true;}
        }
    }

    escape = false;

    for(int i = 0; i < n_bottom; i++){
        if(escape == true){break;}
        for(int j = 0; j < n_bottom; j++){
            dx = bottom_unfiltered[j][0]-bottom_unfiltered[i][0];
            dy = bottom_unfiltered[j][1]-bottom_unfiltered[i][1];
            dz = bottom_unfiltered[j][2]-bottom_unfiltered[i][2];
            dr=dx*dx+dy*dy+dz*dz; dr=sqrt(dr);

            if(escape == true) {break;}
            if(dr < minimum && dr > 0.0) {old_minimum = minimum; minimum = dr;}
            if(minimum-old_minimum == minimum_epsilon) {escape = true;}
        }
    }

    double **top_unfiltered;

    // TRZEBA RESETOWAC TABLICE PUNKTU (0,0,0)!!!!!

    pointoforigin[0]=0;
    pointoforigin[1]=0;
    pointoforigin[2]=0;
    repz[0]=10;
    repz[1]=10;
    repz[2]=10; // krzem górna warstwa ilość powilen
    int n_top=origenStart(repz, pointoforigin, mill, latticeconstants_1, latticetype_1, "", "", "lmpdata", "2", cell, top_unfiltered, "no");

    /*
    #ifdef DEBUG
        for(int i = 0; i < n_top; i++){
            cout << top_unfiltered[i][2] << "\n";
        }
    #endif
    */

    double **bottom_filtered, **top_filtered;

    int bot_counter = 0;
    int top_counter = 0;

    for(int i = 0; i < n_bottom ; i++){
        if( bottom_unfiltered[i][2] < (1+spacing_epsilon)*bottom_layers*spacing){
            bot_counter++;
        }
    }
    for(int i = 0; i < n_top ; i++){
        if( top_unfiltered[i][2] < (1+spacing_epsilon)*top_layers*spacing){
            top_counter++;
        }
    }

    bottom_filtered = new double *[bot_counter];
    top_filtered = new double *[top_counter];

    cout << bottom_layers*spacing << " " << top_layers*spacing << "\n";

    bot_counter = 0; top_counter = 0;

    for(int i = 0; i < n_bottom; i++){
        if( bottom_unfiltered[i][2] < (1+spacing_epsilon)*bottom_layers*spacing){
            bottom_filtered[bot_counter] = new double [3];
            for(int j = 0; j < 3; j++){bottom_filtered[bot_counter][j] = bottom_unfiltered[i][j];}
            bot_counter++;
        }
    }

    for(int i = 0; i < n_top; i++){
        if( top_unfiltered[i][2] < (1+spacing_epsilon)*top_layers*spacing){
            top_filtered[top_counter] = new double [3];
            for(int j = 0; j < 3; j++){top_filtered[top_counter][j] = top_unfiltered[i][j];}
            top_counter++;
        }
    }

    int all_counter = top_counter + bot_counter;

    double shift = (bottom_layers + 1) * spacing;

    for(int i = 0; i < top_counter; i++){
        top_filtered[i][2] += shift;
    }

    escape=false;
    int bad_counter = 0;

    for(int p = 0; p < 100; p++){

        if(escape == true){break;}
        bad_counter = 0;

        for(int i = 0; i < top_counter; i++){
            top_filtered[i][2] += 0.01;
        }
        for(int i = 0; i < top_counter; i++){

            for(int j = 0; j < top_counter; j++){

                if(i == j){continue;}

                dx=top_filtered[j][0]-top_filtered[i][0];
                dy=top_filtered[j][1]-top_filtered[i][1];
                dz=top_filtered[j][2]-top_filtered[i][2];
                dr=dx*dx+dy*dy+dz*dz; dr=sqrt(dr);

                if(dr<minimum){bad_counter++;}
            }
        }
        if(bad_counter == 0){escape = true;}
    }
    // Tablica  dla miedzi

    double **top_Au_unfiltered;

    // TRZEBA RESETOWAC TABLICE PUNKTU (0,0,0)!!!!!

    pointoforigin[0]=0; pointoforigin[1]=0; pointoforigin[2]=0;
    repz_Au[0]=13; repz_Au[1]=13; repz_Au[2]=13; //ilość powtórzen w kierunkach x,y,z
    int n_top_Au=origenStart(repz_Au, pointoforigin, mill, latticeconstants_2, latticetype_2, "", "", "lmpdata", "3", cell, top_Au_unfiltered, "no");
    double **top_Au_filtered;
    int top_Au_counter = 0;

    for(int i = 0; i < n_top_Au; i++){
        if( top_Au_unfiltered[i][2] < (1+spacing_epsilon)*top_Au_layers*spacing){
            top_Au_counter++;
        }
    }

    top_Au_filtered = new double *[top_Au_counter];

    cout << top_Au_layers << " " << top_Au_layers*spacing << "\n";

    top_Au_counter = 0;

    for(int i = 0; i < n_top_Au; i++){
        if( top_Au_unfiltered[i][2] < (1+spacing_epsilon)*top_Au_layers*spacing){
            top_Au_filtered[top_Au_counter] = new double [3];
            for(int j = 0; j < 3; j++){top_Au_filtered[top_Au_counter][j] = top_Au_unfiltered[i][j];}
            top_Au_counter++;
        }
    }
    //----------------------------------------------------------------------------------------------
        double **over_filtered = new double *[top_counter];
        int over_counter = 0;
        for(int i = 0; i < top_counter; i++){
            over_filtered[i] = new double [3];

            over_filtered[i][0] = top_filtered[i][0];
            over_filtered[i][1] = top_filtered[i][1];
            over_filtered[i][2] = top_filtered[i][2];

            over_counter++;
        }
           //     double shift_Si = ((bottom_layers + 1) * spacing) + (top_layers  * spacing + minimum) - 4.0;

        for(int i = 0; i < top_counter; i++){
            over_filtered[i][2] += 57.5;
        }

//        escape=false;
//        bad_counter = 0;

//        for(int p = 0; p < 100; p++){
//            if(escape == true){break;}
//            bad_counter = 0;

//            for(int i = 0; i < over_counter; i++){
//                over_filtered[i][2] += 0.01;
//            }
//            for(int i = 0; i < over_counter; i++){
//                for(int j = 0; j < over_counter; j++){

//                    if(i == j){continue;}

//                    dx=over_filtered[j][0]-over_filtered[i][0];
//                    dy=over_filtered[j][1]-over_filtered[i][1];
//                    dz=over_filtered[j][2]-over_filtered[i][2];
//                    dr=dx*dx+dy*dy+dz*dz; dr=sqrt(dr);

//                    if(dr<minimum){bad_counter++;}
//                }
//            }
//            if(bad_counter == 0){escape = true;}
//        }







    all_counter = top_counter + bot_counter + top_Au_counter /*+ over_counter*/;
    //--------------------------------------------------------------------------------------------
    // Potrzebna zmiana przy wielkich ilościach

    // old and bad but usefull
    //double shift_Au = ((bottom_layers + 1) * spacing) + (top_layers  * spacing + minimum) - 4.0;
        double shift_Au = 68.724 + minimum;


   for(int i = 0; i < top_Au_counter; i++){
        top_Au_filtered[i][2] += shift_Au;
    }

    escape=false;
    bad_counter = 0;

    for(int p = 0; p < 100; p++){
        if(escape == true){break;}
        bad_counter = 0;

        for(int i = 0; i < top_Au_counter; i++){
            top_Au_filtered[i][2] += 0.01;
        }
        for(int i = 0; i < top_Au_counter; i++){
            for(int j = 0; j < top_Au_counter; j++){

                if(i == j){continue;}

                dx=top_Au_filtered[j][0]-top_Au_filtered[i][0];
                dy=top_Au_filtered[j][1]-top_Au_filtered[i][1];
                dz=top_Au_filtered[j][2]-top_Au_filtered[i][2];
                dr=dx*dx+dy*dy+dz*dz; dr=sqrt(dr);

                if(dr<minimum){bad_counter++;}
            }
        }
        if(bad_counter == 0){escape = true;}
    }


    double **all_filtered = new double *[all_counter];
    for(int i = 0; i < all_counter; i++){
        all_filtered[i] = new double [4];
    }
    for(int i = 0; i < bot_counter; i++){
        all_filtered[i][3] = 1;
        for(int j = 0; j < 3; j++){
            all_filtered[i][j] = bottom_filtered[i][j];
        }
    }
    for(int i = 0; i < top_counter; i++){
        all_filtered[i+bot_counter][3] = 2;

        for(int j = 0; j < 3; j++){
            all_filtered[i+bot_counter][j] = top_filtered[i][j];
        }
    }
    for(int i = 0; i < top_Au_counter; i++){
        all_filtered[i+bot_counter+top_counter][3] = 3;
        for(int j = 0; j < 3; j++){
            all_filtered[i+bot_counter+top_counter][j] = top_Au_filtered[i][j];
        }
    }


//    for(int i = 0; i < over_counter; i++){
//            all_filtered[i+bot_counter+top_counter+top_Au_counter][0] = over_filtered[i][0];
//            all_filtered[i+bot_counter+top_counter+top_Au_counter][1] = over_filtered[i][1];
//            all_filtered[i+bot_counter+top_counter+top_Au_counter][2] = over_filtered[i][2];
//            all_filtered[i+bot_counter+top_counter+top_Au_counter][3] = 2.0;
//    }

    double min = DBL_MAX;
    double max = -DBL_MAX;

    for(int i = 0; i < all_counter; i++){
        if(all_filtered[i][2] < min){min = all_filtered[i][2];}
        if(all_filtered[i][2] > max){max = all_filtered[i][2];}
    }



    stringstream pipe;
    ofstream plik;
    pipe << element_1 << "_" << element_2 << "_combined.data";
    string outname = pipe.str();

    plik.open(outname.c_str());
    plik << "Oriented crystal file\n";
    plik << all_counter << " atoms \n";
    plik << "0 bonds\n";
    plik << "0 angles\n";
    plik << "0 dihedrals\n";
    plik << "0 impropers\n\n";
    plik << "3 atom types\n\n";

    plik << simulation_box[0] << " " << simulation_box[1] << " xlo xhi\n";
    plik << simulation_box[2] << " " << simulation_box[3] << " ylo yhi\n";
    plik << min << " " << max << " zlo zhi\n\n";

    plik << "Atoms\n\n";

    for(int i = 0; i < all_counter; i++){
        plik << i+1 << " " << int(all_filtered[i][3])
                    << " " << all_filtered[i][0]
                    << " " << all_filtered[i][1]
                    << " " << all_filtered[i][2] << "\n";
    }

    plik.close();
    plik.clear();
    pipe.clear();

#ifdef DEBUG
    cout << bottom_layers << " " <<  bot_counter << " " << top_layers << " "  << top_counter << " "  << top_Au_layers << " "  << top_Au_counter << " "<< spacing << " " << minimum << "\n";
#endif

    for(int i = 0; i < all_counter; i++){
        delete [] all_filtered[i];
    }
    delete [] all_filtered;
    delete [] cell;
    delete [] pointoforigin;
    for(int i = 0; i < bot_counter; i++){
        delete [] bottom_filtered[i];
        delete [] over_filtered[i];
    }
    for(int i = 0; i < top_counter; i++){
        delete [] top_filtered[i];
    }
    for(int i = 0; i < top_Au_counter; i++){
        delete [] top_Au_filtered[i];
    }
    delete [] bottom_filtered;
    delete [] over_filtered;
    delete [] top_filtered;
    delete [] top_Au_filtered;
    for(int i = 0; i < n_bottom; i++){
        delete [] bottom_unfiltered[i];
    }
    for(int i = 0; i < n_top; i++){
        delete [] top_unfiltered[i];
    }
    for(int i = 0; i < n_top_Au; i++){
        delete [] top_Au_unfiltered[i];
    }
    delete [] bottom_unfiltered;
    delete [] top_unfiltered;
    delete [] top_Au_unfiltered;
    delete [] simulation_box;

}

