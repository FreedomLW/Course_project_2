#include "Addition_Functions.h"
#include "Family_checker.h"
#include "Algorithm.h"
#include "Fi.h"

#include <vector>
#include <chrono>

int main() {
    auto start = chrono::system_clock::now();
    int timer = 0;
    vector<vector<vector<int>>> d(40, vector<vector<int>>(
                                  14, vector<int>(2, 1000)));
    for (int i = 1; i < 6; ++i) {
        for (int k = 0; k < 13 - Fi[i].s; ++k) {
            if (k != 0) d[i][k][0] = set_value(universum(Fi[i].f), Fi[i].weight, Fi[i].t, k);
            if (k != 1 && k != 2) d[i][k][1] = fam_value(Fi[i].closed_f, Fi[i].weight, Fi[i].t) + k * Fi[i].closed_f.bits.size();
        }
    }
    //algorithm(1, d[1], timer, 60);
    algorithm_Fi(7, 0, 24, true, true);
    calc_all(d, timer, true, 8, true, "to_work/f_Fi");
    //print_d(d[1], 1);
    auto end = chrono::system_clock::now();
    cout << "iterations: " << timer << '\n';
    cout << chrono::duration_cast<chrono::seconds>(end - start).count() << "s" << endl;
}