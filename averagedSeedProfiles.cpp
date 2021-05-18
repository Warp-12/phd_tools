#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    ifstream infile;
    ofstream outfile;

    stringstream inname, outname;
    string line;
    stringstream linestream;
    double in_prof[20][4][300][10];
    double tmp_prof[20][6][10];
    double tmp_ave[20][6];
    double ave_prof[20][3];
    int check[300][3];

    int blockcounter = 0;
    int linecounter = 0;
    int blocklines = 0;
    int seed_index = 0;

    for (int s = 0; s < 10; s++) {
        seed_index = s + 1;

        inname << "./profile_" << seed_index << ".xz";
        infile.open(inname.str().c_str());

        while (!infile.eof()) {
            getline(infile, line);

            if (linecounter >= 3) {
                linestream.str(line);

                int truecounter = linecounter - 3;

                if (blocklines == 20) {
                    blockcounter++;
                    blocklines = 0;
                }
                if (truecounter % 21 == 0) {
                    for (int col = 0; col < 3; col++) {
                        linestream >> check[blockcounter][col];
                    }
                }

                if (truecounter % 21 != 0) {
                    for (int col = 0; col < 4; col++) {
                        linestream >> in_prof[blocklines][col][blockcounter][s];
                    }
                    blocklines++;
                }

                linestream.clear();
                linestream.str("");
            }

            linecounter++;
        }

        infile.close();
        infile.clear();

        inname.clear();
        inname.str("");
        blocklines = 0;
        blockcounter = 0;
        linecounter = 0;
    }

    for (int s = 0; s < 10; s++) {
        for (int i = 0; i < 300; i++) {
            for (int k = 0; k < 20; k++) {
                for (int j = 0; j < 4; j++) {
                    tmp_prof[k][j][s] += in_prof[k][j][i][s];
                }
                tmp_prof[k][4][s] += in_prof[k][3][i][s] * in_prof[k][3][i][s];
            }
        }
    }

    for (int s = 0; s < 10; s++) {
        for (int k = 0; k < 20; k++) {
            for (int j = 0; j < 5; j++) {
                tmp_prof[k][j][s] = tmp_prof[k][j][s] / 300;
                tmp_ave[k][j] += tmp_prof[k][j][s];
            }
        }
    }
    for (int k = 0; k < 20; k++) {
        for (int j = 0; j < 5; j++) {
            tmp_ave[k][j] /= 10;
        }
    }

    double var[1];
    outname << "./profile.ave";
    outfile.open(outname.str().c_str());

    for (int i = 0; i < 20; i++) {
        ave_prof[i][0] = tmp_ave[i][1];
        ave_prof[i][1] = tmp_ave[i][3];
        var[0] = tmp_ave[i][4] - tmp_ave[i][2] * tmp_ave[i][2];

        ave_prof[i][2] = sqrt(abs(var[0]));
        for (int j = 0; j < 3; j++) {
            outfile << ave_prof[i][j] << " ";
        }
        outfile << '\n';
    }

    outfile.close();
    outfile.clear();
    outname.clear();
    outname.str("");

    for (int s = 0; s < 10; s++) {
        for (int k = 0; k < 20; k++) {
            for (int j = 0; j < 5; j++) {
                tmp_prof[k][j][s] = 0;
                tmp_ave[k][j] = 0;
            }
        }
    }

    for (int s = 0; s < 10; s++) {
        for (int k = 0; k < 300; k++) {
            for (int o = 0; o < 3; o++) {
                cout << check[k][o] << " ";
            }
            cout << "\n";
            for (int i = 0; i < 20; i++) {
                cout << "  ";
                for (int j = 0; j < 4; j++) {
                    cout << in_prof[i][j][k][s] << " ";
                }
                cout << "\n";
            }
        }
    }
    return 0;
}
