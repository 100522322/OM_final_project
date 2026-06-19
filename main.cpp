#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include <ctime>
#include <chrono>
#include <vector>
#include <string>
#include "Graph.h"
#include "SA.h"
#include "ABC.h"
#include "DHS.h"

using namespace std;

const int RUNS = 10;
const int ITERATIONS = 10000;

struct Results {
    int best;
    int worst;
    float avg;
    float std;
    float time_mean;
};

struct InstanceConfig {
    string file;
    string name;
    int colors;
};

bool load_graph(Graph& graph, const string& file) {
    if (graph.load_from_file("./instances/" + file)) return true;
    if (graph.load_from_file("../instances/" + file)) return true;
    return false;
}

Results runABC(Graph& graph, int colors, int colony_size, int limit) {
    int best = INT_MAX;
    int worst = -1;
    float avg = 0;
    float std = 0;
    float time_sum = 0;
    vector<int> fitnesses;

    for (int run = 0; run < RUNS; run++) {
        srand(time(0) + run);
        ABC abc(graph, colors, colony_size, limit, ITERATIONS);

        auto start = chrono::steady_clock::now();
        vector<int> result = abc.run();
        auto end = chrono::steady_clock::now();

        int best_run = result[0];
        time_sum += chrono::duration<double>(end - start).count();

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

    cout << "ABC Best: " << best << " Worst: " << worst << " Avg: " << avg
         << " Std: " << std << " Time: " << time_sum / RUNS << "s" << endl;
    return {best, worst, avg, std, time_sum / RUNS};
}

Results runDHS(Graph& graph, int colors, int hms, double hmcr, double par) {
    int best = INT_MAX;
    int worst = -1;
    float avg = 0;
    float std = 0;
    float time_sum = 0;
    vector<int> fitnesses;

    for (int run = 0; run < RUNS; run++) {
        srand(time(0) + run);
        DHS dhs(graph, colors, hms, hmcr, par, ITERATIONS);

        auto start = chrono::steady_clock::now();
        vector<int> result = dhs.run();
        auto end = chrono::steady_clock::now();

        int best_run = result[0];
        time_sum += chrono::duration<double>(end - start).count();

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

    cout << "DHS Best: " << best << " Worst: " << worst << " Avg: " << avg
         << " Std: " << std << " Time: " << time_sum / RUNS << "s" << endl;
    return {best, worst, avg, std, time_sum / RUNS};
}

Results runSA(Graph& graph, int colors, float temperature, float alpha) {
    int best = INT_MAX;
    int worst = -1;
    float avg = 0;
    float std = 0;
    float time_sum = 0;
    vector<int> fitnesses;

    for (int run = 0; run < RUNS; run++) {
        srand(time(0) + run);
        SA sa(colors, graph, ITERATIONS, temperature, alpha);

        auto start = chrono::steady_clock::now();
        vector<int> result = sa.run();
        auto end = chrono::steady_clock::now();

        int best_run = result[0];
        time_sum += chrono::duration<double>(end - start).count();

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

    cout << "SA Best: " << best << " Worst: " << worst << " Avg: " << avg
         << " Std: " << std << " Time: " << time_sum / RUNS << "s" << endl;
    return {best, worst, avg, std, time_sum / RUNS};
}

int main() {
    vector<InstanceConfig> instances = {
        {"queen6_6.col.txt", "queen6_6", 7},
        {"queen8_8.col.txt", "queen8_8", 9},
        {"queen12_12.col.txt", "queen12_12", 13},
        {"le450_15b.col.txt", "le450_15b", 15},
        {"le450_25a.col.txt", "le450_25a", 25},
        {"DSJC125.1.col", "DSJC125.1", 8},
        {"DSJC250.5.col", "DSJC250.5", 28},
        {"DSJC500.5.col", "DSJC500.5", 48},
    };

    const int colony_size = 50;
    const int limit = 200;
    const int hms = 5;
    const double hmcr = 0.95;
    const double par = 0.2;
    const float temperature = 100.0f;
    const float alpha = 0.99f;

    ofstream csv("./results/results.csv");
    csv << "algorithm,instance,best,worst,avg,std,time_mean" << endl;

    for (const InstanceConfig& config : instances) {
        Graph graph;
        if (!load_graph(graph, config.file)) {
            cerr << "Error: can't load " << config.file << endl;
            return 1;
        }

        cout << "Instance: " << config.name << " (k=" << config.colors << ")" << endl;

        Results r_sa = runSA(graph, config.colors, temperature, alpha);
        csv << "SA," << config.name << "," << r_sa.best << "," << r_sa.worst << ","
            << r_sa.avg << "," << r_sa.std << "," << r_sa.time_mean << endl;

        Results r_abc = runABC(graph, config.colors, colony_size, limit);
        csv << "ABC," << config.name << "," << r_abc.best << "," << r_abc.worst << ","
            << r_abc.avg << "," << r_abc.std << "," << r_abc.time_mean << endl;

        Results r_dhs = runDHS(graph, config.colors, hms, hmcr, par);
        csv << "DHS," << config.name << "," << r_dhs.best << "," << r_dhs.worst << ","
            << r_dhs.avg << "," << r_dhs.std << "," << r_dhs.time_mean << endl;

        cout << "------------------------------------------------------" << endl;
    }

    csv.close();
    return 0;
}
