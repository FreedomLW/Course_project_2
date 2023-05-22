#pragma once

#include "Family.h"

const int N_NUMBER = 200;

int set_value(const SET &s, const vector<int> &weight, int t, int k);

int fam_value(const Family &fam, const vector<int> &weight, int t);

vector<pair<int, int>> calculateN(int i, int k, int threshold = 0, 
                bool check_FC = true, bool check_Fi = true);

int v_dop(const Family& G, const vector<pair<int,int>> &N, int l, int i, int k);

Family takeNb(const vector<pair<int,int>> &N, const vector<int> &b, int l);

void print_d(const vector<vector<int>> &d_i, int i, bool header = true);

void print_compare(int t);

void print_Fi(int t);

void print_d_to_file(string file_name, const vector<vector<vector<int>>>& d);

void print_di_to_file(string file_name, const vector<vector<int>>& d, int i, bool header = true, bool add_to_file = false);