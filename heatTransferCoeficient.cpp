#include <float.h>
#include <stdlib.h>

#include <boost/filesystem.hpp>
#include <vector>

#include "elastic.h"
#include "includes.h"
#include "interface.h"
#include "rawstate.h"
#include "simple.h"

using std::cout;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;
using namespace LAMMPS_NS;
using namespace RawState;
using namespace RawStateLAMMPSTools;

#define DEFAULT_THERMO "thermo_style custom elapsed fnorm pe etotal lx ly lz yz xz xy pxx pyy pzz pyz pxz pxy"

double timestep = 0.001;
int run_length = 10000;
int z_grid = 100;

double skipVoid(System *&input, int file_id) {
    double void_skip = 0.0;

    double n_atoms = input->_n_atoms;

    double lx = input->_box_data[0][1] - input->_box_data[0][0];
    double ly = input->_box_data[1][1] - input->_box_data[1][0];
    double lz = input->_box_data[2][1] - input->_box_data[2][0];

    double dz = (0.5 * lz) / z_grid;

    vector<double> density;

    ofstream density_log;
    density_log.open("./02_joined/density.log");

    for (int layer = 0; layer < z_grid; ++layer) {
        int atom_counter = 0;
        double min_z = input->_box_data[2][0] + dz * layer;
        double volume = lx * ly * (input->_box_data[2][1] - min_z);

        for (int atom_i = 0; atom_i < n_atoms; ++atom_i) {
            double z_pos = input->_particles[atom_i]._position[2];
            if (z_pos >= min_z) atom_counter++;
        }

        double layer_density = atom_counter / volume;
        density_log << min_z << " " << layer_density << "\n";
        density.push_back(layer_density);
    }

    density_log.close();

    return void_skip;
}
void repairBoundary(System *&input, int file_id) {
    int n_pop = input->_n_atoms;
    double r_cut = input->_neighbours->_r_cutoff;

    int atom_i, atom_j, atom_k;

    double *i_pos = new double[3];
    double *d_ij = new double[3];
    double sum_of_squares;
    double r_ij;

    double *badness_histogram = new double[n_pop];

    cout << "1) Starting distance check at intherphase boundary...\n";

    register int i_type, j_type;
    double sq_r_cut;

    cout << "\t1a) Preparing repair conditions ...\n";

    double imperfection_meter;
    int n_neigh;
    int diff_counter = 0;

    for (atom_i = 0; atom_i < n_pop; atom_i++) {
        imperfection_meter = 0.0;
        if (input->_particles[atom_i]._is_present == 0) continue;

        i_type = input->_particles[atom_i]._type_id;

        if (input->_neighbours->_n_neighbours[atom_i] != 0) {
            for (atom_j = 0; atom_j < input->_neighbours->_n_neighbours[atom_i]; atom_j++) {
                int neighbour_id = input->_neighbours->_neighbours_ids[atom_i][atom_j];
                j_type = input->_particles[neighbour_id]._type_id;

                if (i_type != j_type) {
                    imperfection_meter += abs(r_cut - input->_neighbours->_bond_lengths[atom_i][atom_j]) / input->_neighbours->_n_neighbours[atom_i];
                }
            }
        }
        badness_histogram[atom_i] = imperfection_meter;
    }

    double BIN_WIDTH = 0.01;
    int MAX_BINS = int(2.0 / BIN_WIDTH);
    int *bins = new int[MAX_BINS];

    double highest_bin_count = -DBL_MAX;
    double primary_bin = 0.0;

    for (int i = 0; i < MAX_BINS; i++)
        bins[i] = 0;

    ofstream histogram;

    for (atom_i = 0; atom_i < n_pop; atom_i++)
        for (int bin = 0; bin < MAX_BINS; bin++)
            if (badness_histogram[atom_i] >= bin * BIN_WIDTH && badness_histogram[atom_i] < (bin + 1) * BIN_WIDTH) bins[bin]++;

    stringstream namestream;
    string group_name;

    group_name = "./02_joined/before_";

    namestream << group_name << file_id + 1 << ".hist";
    histogram.open(namestream.str().c_str());

    for (int bin = 0; bin < MAX_BINS; bin++) {
        histogram << (bin + 1) * BIN_WIDTH << " " << double(bins[bin]) / n_pop << "\n";
        if (double(bins[bin]) / n_pop > highest_bin_count) {
            highest_bin_count = double(bins[bin]) / n_pop;
            primary_bin = (bin + 1) * BIN_WIDTH;
        }
    }

    histogram.close();
    namestream.clear();
    namestream.str("");

    int sum = 0;

    for (int bin = 0; bin < MAX_BINS; bin++) {
        sum += bins[bin];
    }

    delete[] bins;

    cout << "\t1b) Starting repair sequence ...\n";
    bool repaired;

    int saved = 0;

    do {
        repaired = true;
        double max = primary_bin;
        int worst_atom = 0;
        imperfection_meter = 0.0;

        for (atom_i = 0; atom_i < n_pop; atom_i++) {
            imperfection_meter = 0.0;
            if (input->_particles[atom_i]._is_present == 0) continue;

            i_type = input->_particles[atom_i]._type_id;

            if (input->_neighbours->_n_neighbours[atom_i] != 0) {
                for (atom_j = 0; atom_j < input->_neighbours->_n_neighbours[atom_i]; atom_j++) {
                    int neighbour_id = input->_neighbours->_neighbours_ids[atom_i][atom_j];
                    j_type = input->_particles[neighbour_id]._type_id;

                    if (i_type != j_type) {
                        imperfection_meter += abs(r_cut - input->_neighbours->_bond_lengths[atom_i][atom_j]) / input->_neighbours->_n_neighbours[atom_i];
                    }
                }

                if (imperfection_meter > max) {
                    worst_atom = atom_i;
                    repaired = false;
                }
            }
        }

        int position = 0;

        for (atom_j = 0; atom_j < input->_neighbours->_n_neighbours[worst_atom]; atom_j++) {
            int atom_j_id = input->_neighbours->_neighbours_ids[worst_atom][atom_j];

            for (int atom_k = 0; atom_k < input->_neighbours->_n_neighbours[atom_j_id]; atom_k++) {
                int atom_k_id = input->_neighbours->_neighbours_ids[atom_j_id][atom_k];
                if (atom_k_id == worst_atom) {
                    position = atom_k;
                    break;
                }
            }
            for (int atom_k = position + 1; atom_k < input->_neighbours->_n_neighbours[atom_j_id]; atom_k++) {
                input->_neighbours->_neighbours_ids[atom_j_id][atom_k - 1] = input->_neighbours->_neighbours_ids[atom_j_id][atom_k];
                input->_neighbours->_bond_lengths[atom_j_id][atom_k - 1] = input->_neighbours->_bond_lengths[atom_j_id][atom_k];
            }
            input->_neighbours->_n_neighbours[atom_j_id]--;
        }

        input->_particles[worst_atom]._is_present = 0;
        saved = worst_atom;
        n_pop--;

    } while (repaired == false);

    cout << "\n\t ## MEMBER DECREASE AFTER REPAIR: " << input->_n_atoms - n_pop << " ##\n\n";

    delete[] badness_histogram;
    badness_histogram = NULL;
    badness_histogram = new double[n_pop];

    for (atom_i = 0; atom_i < n_pop; atom_i++) {
        imperfection_meter = 0.0;
        if (input->_particles[atom_i]._is_present == 0) continue;

        i_type = input->_particles[atom_i]._type_id;

        if (input->_neighbours->_n_neighbours[atom_i] != 0) {
            for (atom_j = 0; atom_j < input->_neighbours->_n_neighbours[atom_i]; atom_j++) {
                int neighbour_id = input->_neighbours->_neighbours_ids[atom_i][atom_j];
                j_type = input->_particles[neighbour_id]._type_id;

                if (i_type == j_type)
                    continue;
                else {
                    imperfection_meter += abs(r_cut - input->_neighbours->_bond_lengths[atom_i][atom_j]);
                }
            }
        }
        badness_histogram[atom_i] = imperfection_meter;
    }

    bins = new int[MAX_BINS];
    for (int bin = 0; bin < MAX_BINS; bin++)
        bins[bin] = 0;

    for (atom_i = 0; atom_i < n_pop; atom_i++)
        for (int bin = 0; bin < MAX_BINS; bin++)
            if (badness_histogram[atom_i] >= bin * BIN_WIDTH && badness_histogram[atom_i] < (bin + 1) * BIN_WIDTH) bins[bin]++;

    group_name = "./02_joined/after_";

    namestream << group_name << file_id + 1 << ".hist";
    histogram.open(namestream.str().c_str());

    for (int bin = 0; bin < MAX_BINS; bin++) {
        histogram << (bin + 1) * BIN_WIDTH << " " << double(bins[bin]) / n_pop << "\n";
    }

    histogram.close();
    namestream.clear();
    namestream.str("");

    delete[] bins;
    delete[] badness_histogram;
    delete[] d_ij;
    delete[] i_pos;

    cout << "\tEND) Boundary checked! \n";
}
vector<string> get_file_list(const std::string &path) {
    vector<string> m_file_list;

    if (!path.empty()) {
        namespace fs = boost::filesystem;

        fs::path apk_path(path);
        fs::recursive_directory_iterator end;

        for (fs::recursive_directory_iterator i(apk_path); i != end; ++i) {
            const fs::path cp = (*i);
            m_file_list.push_back(cp.string());
        }
    }
    return m_file_list;
}
int main(int argc, char *argv[]) {
    string workmode = argv[1];

    int *temperature_seeds = new int[5];

    temperature_seeds[0] = 507137;
    temperature_seeds[1] = 105199;
    temperature_seeds[2] = 16823;
    temperature_seeds[3] = 115061;
    temperature_seeds[4] = 294347;

    if (workmode.compare("PREP") == 0) {
        MPI_Init(&argc, &argv);

        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        LAMMPS *lammps;
        void **lmp_addr = (void **)&lammps;

        char **lmp_args = new char *[2];

        lmp_args[0] = (char *)"-e log";
        lmp_args[1] = (char *)"-sc none";

        lammps_open_no_mpi(0, lmp_args, lmp_addr);

        system("rm ./01_half/*");
        system("rm ./01_half/sample_logs/*");
        system("rm ./01_half/sample_dumps/*");

        double cold_temperature = atof(argv[2]);
        double temperature_diff = atof(argv[3]);

        // General settings

        COMMAND("units metal");
        COMMAND("atom_style atomic");
        COMMAND("dimension 3");
        COMMAND("boundary p p p");

        string timestep_command = "timestep ";
        timestep_command += std::to_string(timestep);

        COMMAND(timestep_command);

        // Simulation box preparation

        double lattice_constant = 4.0782;
        double *bounds = new double[6];

        bounds[0] = -0.01;
        bounds[1] = -0.01 + 5.0 * lattice_constant;

        bounds[2] = -0.01;
        bounds[3] = -0.01 + 5.0 * lattice_constant;

        bounds[4] = -0.01;
        bounds[5] = -0.01 + 20.0 * lattice_constant;

        stringstream region_command;
        region_command << "region half prism ";
        region_command << bounds[0] << " " << bounds[1] << " ";
        region_command << bounds[2] << " " << bounds[3] << " ";
        region_command << bounds[4] << " " << bounds[5] << " ";
        region_command << "0.0 0.0 0.0 units box";

        string lattice_command;
        lattice_command = "lattice fcc ";
        lattice_command += std::to_string(lattice_constant);

        COMMAND(region_command.str());
        COMMAND(lattice_command);

        COMMAND("create_box      1 half");
        COMMAND("create_atoms    1 region half");
        COMMAND("mass            1 196.967");  // GOLD

        // Potential set up - MEAM-Jelinek
	// << "pair_coeff    * * ./potentials/meam_jelinek/library.meam 'AlS' 'SiS' 'MgS' 'CuS' 'FeS' ./potentials/meam_jelinek/jelinek.meam 'SiS'\n";
	// Potential set up - MEAM-Ruy-Cai
        stringstream meam_command;
        meam_command << "pair_style meam\n"
                     << "pair_coeff   * * ./potentials/meam_ryu_cai/AuSi_library.meam Au Si ./potentials/meam_ryu_cai/AuSi_ryu_cai.meam Au\n";
 
        string potential_command = meam_command.str();

        COMMAND(potential_command);

        // Saving initial state of the system

        COMMAND("thermo 1");
        COMMAND("run 0");
        COMMAND("write_restart ./01_half/initial_half.restart");
        COMMAND("write_data ./01_half/initial_half.data");

        // Minimization

        COMMAND("dump min_dump all custom 1 ./01_half/minimize.lammpstrj id type x y z fx fy fz");
        COMMAND("log ./01_half/minimize.log");

        COMMAND("thermo_style custom elapsed fmax fnorm pe pxx pyy pzz pyz pxz pxy");

        COMMAND("minimize 0.0 1.0e-08 25000 50000");

        COMMAND("change_box all boundary p p f");
        COMMAND("write_restart ./01_half/minimized_half.restart");
        COMMAND("write_data ./01_half/minimized_half.data");

        COMMAND("undump min_dump");
        COMMAND("reset_timestep 0");

        // Colder conditions

        stringstream velocity_command;
        stringstream thermostat_command;
        stringstream dump_command;
        stringstream log_command;
        stringstream run_command;

        run_command << "run " << run_length;

        for (int seed = 0; seed < 1; seed++) {
            COMMAND("clear");
            COMMAND("read_restart ./01_half/minimized_half.restart");
            COMMAND(potential_command);
            COMMAND("fix hardwalls all wall/reflect zlo EDGE zhi EDGE");

            dump_command << "dump my_dump all custom " << run_length / 10 << " ./01_half/sample_dumps/sample_cold_" << seed + 1 << ".lammpstrj id type x y z vx vy vz";
            log_command << "log ./01_half/sample_logs/sample_cold_" << seed + 1 << ".log";
            velocity_command << "velocity all create " << cold_temperature << " " << temperature_seeds[seed];
            thermostat_command << "fix my_nvt all nvt temp " << cold_temperature << " " << cold_temperature << " " << 100 * timestep;

            COMMAND(velocity_command.str());
            COMMAND(thermostat_command.str());
            COMMAND(dump_command.str());
            COMMAND(log_command.str());

            COMMAND("thermo 1");
            COMMAND(run_command.str());
            COMMAND("undump my_dump");
            COMMAND("unfix my_nvt");

            velocity_command.str("");
            thermostat_command.str("");
            dump_command.str("");
            log_command.str("");
            velocity_command.clear();
            thermostat_command.clear();
            dump_command.clear();
            log_command.clear();
        }

        // Hotter conditions

        for (int seed = 0; seed < 1; seed++) {
            COMMAND("clear");
            COMMAND("reset_timestep 0");
            COMMAND("read_restart ./01_half/minimized_half.restart");
            COMMAND(potential_command);
            COMMAND("fix hardwalls all wall/reflect zlo EDGE zhi EDGE");

            dump_command << "dump my_dump all custom " << run_length / 10 << " ./01_half/sample_dumps/sample_hot_" << seed + 1 << ".lammpstrj id type x y z vx vy vz";
            log_command << "log ./01_half/sample_logs/sample_hot_" << seed + 1 << ".log";
            velocity_command << "velocity all create " << cold_temperature + temperature_diff << " " << temperature_seeds[seed];
            thermostat_command << "fix my_nvt all nvt temp " << cold_temperature + temperature_diff << " " << cold_temperature + temperature_diff << " " << 100 * timestep;

            COMMAND(velocity_command.str());
            COMMAND(thermostat_command.str());
            COMMAND(dump_command.str());
            COMMAND(log_command.str());

            COMMAND("thermo 1");
            COMMAND(run_command.str());
            COMMAND("undump my_dump");
            COMMAND("unfix my_nvt");

            velocity_command.str("");
            thermostat_command.str("");
            dump_command.str("");
            log_command.str("");
            velocity_command.clear();
            thermostat_command.clear();
            dump_command.clear();
            log_command.clear();
        }
        delete[] bounds;
        lammps_close(lammps);
        MPI_Finalize();
    }
    if (workmode.compare("JOIN") == 0) {
        vector<string> dumpfiles = get_file_list("./01_half/sample_dumps/");
        vector<string> cold_files, hot_files;

        for (int file = 0; file < dumpfiles.size(); ++file) {
            if (dumpfiles[file].find("hot") != std::string::npos) hot_files.push_back(dumpfiles[file]);
            if (dumpfiles[file].find("cold") != std::string::npos) cold_files.push_back(dumpfiles[file]);
        }

        std::sort(hot_files.begin(), hot_files.end());
        std::sort(cold_files.begin(), cold_files.end());

        int n_files = hot_files.size();
        for (int file = 0; file < n_files; ++file) {
            System *hot_half = new System;
            System *cold_half = new System;

            std::string hot_filename = hot_files[file];
            std::string cold_filename = cold_files[file];
            //------------------------------------------------------------------------------------------------------
            int n_timesteps = 10;  //getNumberOfReadings(cold_filename);

            RawState::setStateTimestep(n_timesteps - 1);
            RawState::setStateTimestepDelta(1);

            hot_half->_readNextLAMMPSTimestep(hot_filename);

            RawState::setStateTimestep(n_timesteps - 1);
            RawState::setStateTimestepDelta(1);

            cold_half->_readNextLAMMPSTimestep(cold_filename);

            double cold_x = cold_half->_box_data[0][1] - cold_half->_box_data[0][0];
            double cold_y = cold_half->_box_data[1][1] - cold_half->_box_data[1][0];
            double cold_z = cold_half->_box_data[2][1] - cold_half->_box_data[2][0];
            double hot_z = hot_half->_box_data[2][1] - hot_half->_box_data[2][0];

            for (int atom_i = 0; atom_i < hot_half->_n_atoms; ++atom_i)
                hot_half->_particles[atom_i]._position[2] += cold_z;

            int all_atoms = cold_half->_n_atoms + hot_half->_n_atoms;

            System *all = new System;

            all->_setNAtoms(all_atoms);
            all->_createParticlesTable();

            all->_periodic[0] = true;
            all->_periodic[1] = true;
            all->_periodic[2] = false;

            all->_box_data[0][0] = cold_half->_box_data[0][0];
            all->_box_data[0][1] = cold_half->_box_data[0][1];
            all->_box_data[0][2] = cold_half->_box_data[0][2];

            all->_box_data[1][0] = cold_half->_box_data[1][0];
            all->_box_data[1][1] = cold_half->_box_data[1][1];
            all->_box_data[1][2] = cold_half->_box_data[1][2];

            all->_box_data[2][0] = cold_half->_box_data[0][0];
            all->_box_data[2][1] = cold_z + hot_z;
            all->_box_data[2][2] = cold_half->_box_data[0][2];

            for (int atom_i = 0; atom_i < all_atoms; ++atom_i) {
                all->_particles[atom_i]._createPositionsTable();
                all->_particles[atom_i]._createVelocitiesTable();
            }

            for (int atom_i = 0; atom_i < cold_half->_n_atoms; ++atom_i) {
                all->_particles[atom_i]._setTypeId(1);
                all->_particles[atom_i]._setMass(196.967);
                for (int dimension = 0; dimension < 3; ++dimension)
                    all->_particles[atom_i]._position[dimension] = cold_half->_particles[atom_i]._position[dimension];
                for (int dimension = 0; dimension < 3; ++dimension)
                    all->_particles[atom_i]._velocity[dimension] = hot_half->_particles[atom_i]._velocity[dimension];
            }
            for (int atom_i = cold_half->_n_atoms; atom_i < all_atoms; ++atom_i) {
                all->_particles[atom_i]._setTypeId(2);
                all->_particles[atom_i]._setMass(196.967);
                for (int dimension = 0; dimension < 3; ++dimension)
                    all->_particles[atom_i]._position[dimension] = hot_half->_particles[atom_i - cold_half->_n_atoms]._position[dimension];
                for (int dimension = 0; dimension < 3; ++dimension)
                    all->_particles[atom_i]._velocity[dimension] = hot_half->_particles[atom_i - cold_half->_n_atoms]._velocity[dimension];
            }

            double r_cutoff = DBL_MAX;

            for (int atom_i = 0; atom_i < cold_half->_n_atoms; ++atom_i) {
                for (int atom_j = atom_i + 1; atom_j < cold_half->_n_atoms; ++atom_j) {
                    double dx = cold_half->_particles[atom_j]._position[0] - cold_half->_particles[atom_i]._position[0];
                    double dy = cold_half->_particles[atom_j]._position[1] - cold_half->_particles[atom_i]._position[1];
                    double dz = cold_half->_particles[atom_j]._position[2] - cold_half->_particles[atom_i]._position[2];

                    if (dx >= 0.5 * cold_x) dx -= cold_x;
                    if (dy >= 0.5 * cold_y) dy -= cold_y;

                    double dr = sqrt(dx * dx + dy * dy + dz * dz);
                    if (dr < r_cutoff) r_cutoff = dr;
                }
            }

            cout << "\n Beginning analysis for temperature seed No. " << file + 1 << "\n";
            cout << "\n -- CREATING VERLET LIST FOR CUTOFF: " << r_cutoff << " --\n";
            all->_createNeighboursList(r_cutoff, 30, 1);
            cout << "\n -- REPAIRING THE HARDWALL BOUNDARY --\n\n";

            stringstream joined_file;

            joined_file << "./02_joined/broken_" << file + 1 << ".data";
            writeTimestepDataToFile(joined_file.str(), all, "vel");
            joined_file.str("");
            joined_file.clear();

            repairBoundary(all, file);

            joined_file << "./02_joined/all_" << file + 1 << ".data";

            cout << "\n -- WRITING THE OUTPUT FILE --\n\n";
            writeTimestepDataToFile(joined_file.str(), all, "vel");

            joined_file.str("");
            joined_file.clear();
            delete all;
            delete hot_half;
            delete cold_half;
        }
    }
    if (workmode.compare("EQUIL") == 0) {
        LAMMPS *lammps;
        void **lmp_addr = (void **)&lammps;

        char **lmp_args = new char *[2];

        lmp_args[0] = (char *)"-e log";
        lmp_args[1] = (char *)"-sc none";

        lammps_open_no_mpi(0, lmp_args, lmp_addr);

        vector<string> all_files = get_file_list("./02_joined/");
        vector<string> joined_files;

        for (int file = 0; file < all_files.size(); ++file)
            if (all_files[file].find("all_") != std::string::npos) joined_files.push_back(all_files[file]);

        // Potential setup

        std::ifstream parameters("./.lj_params");
        string line;
        getline(parameters, line);
        stringstream linestream;
        linestream.str(line);

        double lj_epsilon, lj_sigma;

        linestream >> lj_epsilon;
        linestream >> lj_sigma;

        parameters.close();

        stringstream meam_command;
// << "pair_coeff    * * ./potentials/meam_jelinek/library.meam 'AlS' 'SiS' 'MgS' 'CuS' 'FeS' ./potentials/meam_jelinek/jelinek.meam 'SiS' 'SiS' \n";
        meam_command << "pair_style meam\n"      
                     << "pair_coeff   * * ./potentials/meam_ryu_cai/AuSi_library.meam Au Si ./potentials/meam_ryu_cai/AuSi_ryu_cai.meam Au Au\n";
        string potential_command = meam_command.str();

        // Equlibration

        for (int file = 0; file < joined_files.size(); ++file) {
            string datacommand = "read_data ";
            string run_command = "run ";
            string log_command = "log ./03_equil/logs/";
            string dump_command = "dump my_nve_dump all custom 1 ./03_equil/dumps/";

            datacommand += joined_files[file];
            run_command += std::to_string(2 * run_length);

            log_command += "equil_";
            log_command += std::to_string(file + 1);
            log_command += ".log";
            dump_command += "equil_";
            dump_command += std::to_string(file + 1);
            dump_command += ".lammpstrj";
            dump_command += " id type x y z vx vy vz";

            string profile_command = "fix profile all ave/chunk 10 100 1000 layers v_temp ave running file ./03_equil/profiles/";
            profile_command += "profile_";
            profile_command += std::to_string(file + 1);
            profile_command += ".profile";

            COMMAND("clear");
            COMMAND("units metal");
            COMMAND("atom_style atomic");
            COMMAND("dimension 3");
            COMMAND("reset_timestep 0");

            COMMAND(datacommand);
            COMMAND("change_box all boundary p p f");
            COMMAND(potential_command);

            // Temperature profile
            // thermal conductivity calculation

            COMMAND("compute  ke  all ke/atom");
            COMMAND("variable temp atom (c_ke/1.5/1.160452166)*10000");
            COMMAND("compute layers all chunk/atom bin/1d z lower 0.05 units reduced");
            COMMAND(profile_command);

            // Hard walls at zlo and zhi
            COMMAND("fix hardwalls all wall/reflect zlo EDGE zhi EDGE");

            // NVE run

            COMMAND("fix my_nve all nve");

            COMMAND("thermo_style custom elapsed fmax fnorm pe pxx pyy pzz pyz pxz pxy");
            COMMAND("thermo 1");

            COMMAND(log_command);
            COMMAND(dump_command);
            COMMAND(run_command);
        }

        lammps_close(lammps);
        MPI_Finalize();
    }

    delete[] temperature_seeds;

    return 0;
}
