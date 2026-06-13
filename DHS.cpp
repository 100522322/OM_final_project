#include "DHS.h"

#include <cstdlib>

DHS::DHS(Graph& graph, int num_colors, int harmony_size, double HMCR, double PAR, int iterations)
    : graph(graph),
    num_colors(num_colors),
    harmony_size(harmony_size),
    HMCR(HMCR),
    PAR(PAR),
    iterations(iterations) {}


vector<int> DHS::run() {
    initialize();

    for (int i = 0; i < iterations; i++) {
        vector<int> new_sol = new_solution();
        int new_fitness = graph.fitness(new_sol);

        int indx = worst_index();

        if (new_fitness < harmony_mem[indx].fitness) {
            harmony_mem[indx].individual = new_sol;
            harmony_mem[indx].fitness = new_fitness;
        }

        update();

        if (best.fitness == 0) {
            break;
        }
    }

    vector<int> res;
    res.push_back(best.fitness);
    res.push_back(worst.fitness);
    return res;
}

void DHS::initialize() {
    harmony_mem.clear();

    for (int i = 0; i < harmony_size; i++) {
        Harmony h;
        h.individual = graph.random_color_graph(num_colors);
        h.fitness = graph.fitness(h.individual);

        harmony_mem.push_back(h);
    }

    best = harmony_mem[0];
    worst = harmony_mem[0];
    update();
}

vector<int> DHS::new_solution() {
    vector<int> new_sol(graph.num_nodes);

    for (int i = 0; i < graph.num_nodes; i++) {
        double r1 = (double) rand() / RAND_MAX;

        if (r1 < HMCR) {
            int rand_harmony = rand() % harmony_mem.size();
            new_sol[i] = harmony_mem[rand_harmony].individual[i];
        } else {
            new_sol[i] = rand() % num_colors;
        }

        double r2 = (double) rand() / RAND_MAX;

        if (r2 < PAR) {
            new_sol[i] = best_color(i, new_sol);
        }
    }
    return new_sol;
}

int DHS::best_color(int node, vector<int> individual) {
    int best_color = individual[node];
    int best_fitness = graph.fitness(individual);

    for (int c = 0; c < num_colors; c++) {
        if (c == individual[node]) continue;

        vector<int> temp = individual;
        temp[node] = c;

        int temp_fitness = graph.fitness(temp);

        if (temp_fitness < best_fitness) {
            best_fitness = temp_fitness;
            best_color = c;
        }
    }
    return best_color;
}

void DHS::update() {
    best = harmony_mem[0];
    worst = harmony_mem[0];
    
    for (const auto& h : harmony_mem) {
        if (h.fitness < best.fitness) {
            best = h;
        }

        if (h.fitness > worst.fitness) {
            worst = h;
        }
    }
}

int DHS::worst_index() const {
    int indx = 0;

    for (int i = 1; i < harmony_mem.size(); i++) {
        if (harmony_mem[i].fitness > harmony_mem[indx].fitness) {
            indx = i;
        }
    }

    return indx;
}