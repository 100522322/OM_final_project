#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <ctime>
#include <vector>
#include "Graph.h"
#include "ABC.h"
#include "DHS.h"

using namespace std;

const int RUNS = 3;
const int ITERATIONS = 10000;
const int K = 8;

struct Results {
    int best;
    int worst;
    float avg;
    float std;
};

Results runABC(Graph& graph, int colony_size, int limit) {
    int best = INT_MAX;
    int worst = -1;
    float avg = 0;
    float std = 0;
    vector<int> fitnesses;

    for (int run = 0; run < RUNS; run++) {
        srand(time(0) + run);
        ABC abc(graph, K, colony_size, limit, ITERATIONS);
        vector<int> result = abc.run();
        int best_run = result[0];

        if (best_run < best) best = best_run;
        if (best_run > worst) worst = best_run;
        avg += best_run;
        fitnesses.push_back(best_run);
    }

    avg /= RUNS;
    for (int i = 0; i < (int)fitnesses.size(); i++) {
        std += (fitnesses[i] - avg) * (fitnesses[i] - avg);
    }
    std = sqrt(std / RUNS);

    cout << "Best: " << best << " Worst: " << worst << " Avg: " << avg << " Std: " << std << endl;
    return {best, worst, avg, std};
}

Results runDHS(Graph& graph, int hms, double hmcr, double par) {
    int best = INT_MAX;
    int worst = -1;
    float avg = 0;
    float std = 0;
    vector<int> fitnesses;

    for (int run = 0; run < RUNS; run++) {
        srand(time(0) + run);
        DHS dhs(graph, K, hms, hmcr, par, ITERATIONS);
        vector<int> result = dhs.run();
        int best_run = result[0];

        if (best_run < best) best = best_run;
        if (best_run > worst) worst = best_run;
        avg += best_run;
        fitnesses.push_back(best_run);
    }

    avg /= RUNS;
    for (int i = 0; i < (int)fitnesses.size(); i++) {
        std += (fitnesses[i] - avg) * (fitnesses[i] - avg);
    }
    std = sqrt(std / RUNS);

    cout << "Best: " << best << " Worst: " << worst << " Avg: " << avg << " Std: " << std << endl;
    return {best, worst, avg, std};
}

void tuningABC(Graph& graph) {
    ofstream csv("./results/tuning_abc.csv");
    csv << "parameter,value,best,worst,avg,std" << endl;

    cout << "\n--- Tuning ABC: Colony Size (limit=50) ---" << endl;
    vector<int> colony_sizes = {5, 10, 20, 50, 100};
    for (int colony_size : colony_sizes) {
        cout << "colony_size=" << colony_size << ": ";
        Results r = runABC(graph, colony_size, 50);
        csv << "colony_size," << colony_size << "," << r.best << "," << r.worst << "," << r.avg << "," << r.std << endl;
    }

    cout << "\n--- Tuning ABC: Abandonment Limit (colony_size=20) ---" << endl;
    vector<int> limits = {10, 25, 50, 100, 200};
    for (int limit : limits) {
        cout << "limit=" << limit << ": ";
        Results r = runABC(graph, 20, limit);
        csv << "limit," << limit << "," << r.best << "," << r.worst << "," << r.avg << "," << r.std << endl;
    }

    csv.close();
}

void tuningDHS(Graph& graph) {
    ofstream csv("./results/tuning_dhs.csv");
    csv << "parameter,value,best,worst,avg,std" << endl;

    cout << "\n--- Tuning DHS: Harmony Memory Size (HMCR=0.9, PAR=0.3) ---" << endl;
    vector<int> hms_values = {5, 10, 20, 50};
    for (int hms : hms_values) {
        cout << "HMS=" << hms << ": ";
        Results r = runDHS(graph, hms, 0.9, 0.3);
        csv << "HMS," << hms << "," << r.best << "," << r.worst << "," << r.avg << "," << r.std << endl;
    }

    cout << "\n--- Tuning DHS: HMCR (HMS=20, PAR=0.3) ---" << endl;
    vector<double> hmcr_values = {0.5, 0.7, 0.9, 0.95};
    for (double hmcr : hmcr_values) {
        cout << "HMCR=" << hmcr << ": ";
        Results r = runDHS(graph, 20, hmcr, 0.3);
        csv << "HMCR," << hmcr << "," << r.best << "," << r.worst << "," << r.avg << "," << r.std << endl;
    }

    cout << "\n--- Tuning DHS: PAR (HMS=20, HMCR=0.9) ---" << endl;
    vector<double> par_values = {0.1, 0.2, 0.3, 0.5, 0.7};
    for (double par : par_values) {
        cout << "PAR=" << par << ": ";
        Results r = runDHS(graph, 20, 0.9, par);
        csv << "PAR," << par << "," << r.best << "," << r.worst << "," << r.avg << "," << r.std << endl;
    }

    csv.close();
}

int main() {
    Graph graph;
    if (!graph.load_from_file("./instances/DSJC125.1.col")) {
        if (!graph.load_from_file("../instances/DSJC125.1.col")) {
            cerr << "Error: can't load DSJC125.1.col" << endl;
            return 1;
        }
    }

    cout << "Tuning on DSJC125.1 (k=" << K << ", iterations=" << ITERATIONS << ", runs=" << RUNS << ")" << endl;

    tuningABC(graph);
    tuningDHS(graph);

    return 0;
}
