#include <vector>
#include "Addition_Functions.h"
#include "Backtracking.h"
#include "Fi.h"
#include "Family_checker.h"
#include "Timer.h"

using namespace std;

void backtracking(int i, const vector<pair<int,int>>& N, int k, 
                vector<int> b, int l, 
                vector<vector<int>>& d, int& timer) {
    timer += 1;
    if (timer % 1000000 == 0) {
        cout << "\n....................................\ntimer=" << timer << "\n";
    }
    if (b.empty()) {
        if (N.size() <= l) {
            return;
        }
        if (v_dop(Family(), N, l, i, k) < d[k][0]) {
            b.push_back(l);
            backtracking(i, N,k, b, l+1, d, timer);
            b.pop_back();
            backtracking(i, N,k, b, l+1, d, timer);
        }
        return;
    }
    Family G = merge_plus(takeNb(N, b, l), Fi[i].closed_f);
    G.other_elements_count = k;
    if (!checkNotFC(G, i)) return;
    if (!checkNotPrevious(G, i)) return;

    d[k][b[0] == 0] = min(fam_value(G, Fi[i].weight, Fi[i].t), 
                          d[k][b[0] == 0]);
    if (v_dop(G, N, l, i, k) < d[k][b[0] == 0] && (l+1) < N.size()) {
        b.push_back(l);
        backtracking(i, N,k, b, l+1, d, timer);
        if (G.family_in_bits.test(N[l].first)) {
            return;
        }
        b.pop_back();
        backtracking(i, N,k, b, l+1, d, timer);
    }
}

void fake_backtracking(int i, const vector<pair<int,int>>& N, int k, 
                vector<int> b, int l, int& num, 
                bool check_FC, bool check_Fi) {
    if (b.empty()) {
        if (N.size( ) <= l) {
            return;
        }
        if (v_dop(Family(), N, l, i, k) <= num) {
            b.push_back(l);
            fake_backtracking(i, N, k, b, l+1, num, check_FC, check_Fi);
            b.pop_back();
            fake_backtracking(i, N,k, b, l+1, num, check_FC, check_Fi);
        }
        return;
    }
    Family G = merge_plus(takeNb(N, b, l), Fi[i].closed_f);
    G.other_elements_count = k;
    if (check_FC && !checkNotFC(G, i)) return; 
    if (check_Fi && !checkNotPrevious(G, i)) return;
    if (fam_value(G, Fi[i].weight, Fi[i].t) == num) {
        cout << "Found it: ";
        for (auto el : G.bits) {
            SET tmp(el);
            tmp |= calculate_K(G.other_elements_count);
            cout << tmp.to_string() << " " << set_value(SET(el), Fi[i].weight, Fi[i].t, G.other_elements_count) << '\n';
        }
        num = -10000;
        for (auto el : b) {
            cout << el << '\n';
        }
    }
    if (v_dop(G, N, l, i, k) <= num && (l+1) < N.size()) {
        b.push_back(l);
        fake_backtracking(i, N,k, b, l+1, num, check_FC, check_Fi);
        if (G.family_in_bits.test(N[l].first)) {
            return;
        }
        b.pop_back();
        fake_backtracking(i, N,k, b, l+1, num, check_FC, check_Fi);
    }
}