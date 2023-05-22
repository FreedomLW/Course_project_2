#include "Addition_Functions.h"
#include "Backtracking.h"
#include "Fi.h"

#include <string>
#include <vector>

using namespace std;

void algorithm(int i, vector<vector<int>>& d, 
               int &timer, int threshold) {
    for (int k = 0; k < (13 - Fi[i].s); ++k) {
        vector<pair<int, int>> N = calculateN(i, k, threshold);
        if (N.size() == 0) continue;
        backtracking(i, N, k, vector<int>{0}, 1, d, timer);
        if (k > 0) {
            backtracking(i, N, k, vector<int>{}, 1, d, timer);
        }
    }
}


void calc_all(vector<vector<vector<int>>>& d, int &timer, 
              bool without7 = true, int max_number = 28, 
              bool add_to_file = true, string file_name = "") {
    for (int i = 1; i < max_number; ++i){
        if (without7) {
            if (Fi[i].s > 6) continue;
        }
        algorithm(i, d[i], timer, 400);
        if (i == 1) print_d(d[i], i, true);
        else print_d(d[i], i, false);
        if (add_to_file) {
            print_di_to_file(file_name + "_" + to_string(i), d[i], true);
        }
    }
    if (add_to_file){
        print_d_to_file(file_name, d);
    }
    cout << "k=\t0\t1\t2\t3\t3\t4\t4\t5\t5\t6\t6\t7\t7\n";
    cout << "d=\t1\t0\t0\t1\t0\t1\t0\t1\t0\t1\t0\t1\t0\n";
    for (int i = 1; i < max_number; ++i) {
        cout <<"i=" <<  i << '\t' << d[i][0][1] << '\t' << d[i][1][0] << '\t' << d[i][2][0] << '\t';
        for (int j = 3; j < d[i].size(); ++j) {
            if (j > 4 && d[i][j][1] == 1000 && d[i][j][0] == 1000) break;   
            cout << d[i][j][1] << "\t" << d[i][j][0] << '\t';
        }
        cout << '\n';
    }
}

void algorithm_Fi(int i, int k, int num, bool check_FC = false, bool check_Fi = false) {
    int ans = 1000;
    int timer = 0;
    vector<pair<int, int>> N = calculateN(i, k, max(0, num+1), check_FC, check_Fi);
    for (auto& el : N) {
        cout << SET(el.first) << " " << el.second << '\n';
    }
    if (N.size() == 0) return;
    fake_backtracking(i, N, k, vector<int>{0}, 1, num, check_FC, check_Fi);
    if (k > 0) {
        fake_backtracking(i, N, k, vector<int>{}, 1, num, check_FC, check_Fi);
    }
}