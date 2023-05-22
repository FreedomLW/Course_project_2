#include "Addition_Functions.h"
#include "Family_checker.h"
#include "Family.h"
#include "Fi.h"
#include "Timer.h"

#include <string>
#include <fstream>

static int duration_fam_value = 0;
static int duration_take_n_b = 0;
static int duration_vdop = 0;
static int timer_fam_value = 0;
static int timer_take_n_b = 0;
static int timer_vdop = 0;

static bool print = false;

int set_value(const SET &s, const vector<int> &weight, int t, int k) {
    int res = -t + k * weight[MAX_BIT_SET - 1];
    for (int i = 0; i < s.size(); ++i) {
        if (s.test(i)) {
            res += weight[i];
        }
    }
    return res;
}

int fam_value(const Family &fam, const vector<int> &weight, int t) {
    int res = 0;
    if (fam.bits.empty()) {
        return 0;
    } else {
        for (auto bit : fam.bits) {
            res += set_value(bit, weight, t, fam.other_elements_count);
        }
    }
    return res;
}

vector<pair<int, int>> calculateN(int i, int k, int threshold, 
                bool check_FC, bool check_Fi) {
    vector<pair<int, int>> res;
    res.reserve(100);
    res.push_back(make_pair(0, set_value(SET(0), Fi[i].weight, Fi[i].t, k)));
    for (int j = 1; j < (1 << Fi[i].s); ++j) {
        Family fam_tmp = Family(vector<int>{j}, k); 
        fam_tmp.bits.push_back(j);
        fam_tmp.other_elements_count = k;
        //if (check_FC && !checkNotFC(fam_tmp, i)) continue;
        //if (check_Fi && !checkNotPrevious(fam_tmp, i)) continue;
        if (set_value(SET(j), Fi[i].weight, Fi[i].t, k) < threshold) {
            res.push_back(make_pair(j, set_value(SET(j), Fi[i].weight, Fi[i].t, k)));
        }
    }
    sort(res.begin(), res.end(), 
        [i, k](pair<int, int> a, pair<int,int> b)
        {return set_value(SET(a.first), Fi[i].weight, Fi[i].t, k) < set_value(SET(b.first), Fi[i].weight, Fi[i].t, k);});
    return res;
}

int v_dop(const Family& G, const vector<pair<int,int>> &N, int l, int i, int k) {
    int res = fam_value(G, Fi[i].weight, Fi[i].t);
    for (int j = l; j < N.size(); ++j) {
        if (G.family_in_bits.test(N[j].first)) continue;
        if (N[j].second >= 0) {
            break;
        }
        res += N[j].second;
    }
    return res;
}

Family takeNb(const vector<pair<int,int>> &N, const vector<int> &b, int l) {
    if (print) {
        Timer time(&duration_take_n_b);
        ++timer_vdop;
        if (timer_vdop % 100000 == 0) {
            cout << "Duration takeNb: " << (duration_take_n_b /1e6) << "s\n";
            duration_take_n_b = 0;
        }
    }
    Family res;
    res.bits.reserve(100);
    for (const auto el : b) {
        res.family_in_bits.set(N[el].first);
        res.bits.push_back(N[el].first);
    }
    res.close();
    return res;
}

void print_d(const vector<vector<int>> &d_i, int i, bool header) {
    if (header) {
        cout << "k=\t0\t1\t2\t3\t3\t4\t4\t5\t5\t6\t6\t7\t7\n";
        cout << "d=\t1\t0\t0\t1\t0\t1\t0\t1\t0\t1\t0\t1\t0\n";
    }
    cout <<"i=" <<  i << '\t' << d_i[0][1] << '\t' << d_i[1][0] << '\t' 
                                                   << d_i[2][0] << '\t';
    for (int j = 3; j < d_i.size(); ++j) {
            if (j > 4 && d_i[j][1] == 1000 && d_i[j][0] == 1000) break;  
            cout << d_i[j][1] << "\t" << d_i[j][0] << '\t';
    }
    cout << '\n';
}

void print_di_to_file(string file_name, const vector<vector<int>>& d, int i, bool header, bool add_to_file) {

    std::ofstream out;
    if (add_to_file)
        out.open(file_name + ".txt", std::ios::app);
    else
        out.open(file_name + ".txt");

    if (header) { 
        out << "k=\t0\t1\t2\t3\t3\t4\t4\t5\t5\t6\t6\t7\t7\n";
        out << "d=\t1\t0\t0\t1\t0\t1\t0\t1\t0\t1\t0\t1\t0\n";
    }
    out << "i=" <<  i << '\t' << d[0][1] << '\t' << d[1][0] << '\t' << d[2][0] << '\t';
    for (int j = 3; j < d.size(); ++j) {
        if (j > 4 && d[j][1] == 1000 && d[j][0] == 1000) break;  
        out <<  d[j][1] << "\t" << d[j][0] << '\t';
    }
    out << '\n';
    out.close();
}

void print_d_to_file(string file_name, const vector<vector<vector<int>>>& d) {
    int i = 1; 
    while (d[i][0][1] != d[i][0][0]) {
        if (i == 1) {
            print_di_to_file(file_name, d[i], i, true);
        } else {
            print_di_to_file(file_name, d[i], i, false, true);
        }
        ++i;
    }
}

void print_compare(int t) {
    for (int i = 0; i < Fi[t].compare.size(); ++i) {
        cout << "i = " << i << '\n';
        for (int j = 0; j < Fi[t].compare[i].size(); ++j) {
            for (int k = 0; k < Fi[t].compare[i][j].size(); ++k) {
                if (k == 0) {
                    cout << SET(Fi[t].f.bits[Fi[t].compare[i][j][k]]) << " ";
                    continue;
                }
                if (k != Fi[t].compare[i][j].size() - 1) {
                    cout << "+ " << SET(Fi[t].f.bits[Fi[t].compare[i][j][k]]) << " ";
                } else {
                    cout << "= " << Fi[t].compare[i][j][k] << '\n';
                }
            }
        }
        cout << '\n';
    }
}

void print_Fi(int t) {
    cout << "{";
    for (int bit : Fi[t].f.bits) {
        cout << SET(bit) << '\n';
    }
    cout << "}\n";
}