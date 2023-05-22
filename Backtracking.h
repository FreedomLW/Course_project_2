#pragma once

#include <vector>

void backtracking(int i, const vector<pair<int,int>>& N, 
                int k, vector<int> b, int l,  
                vector<vector<int>>& d, int& timer);

void fake_backtracking(int i, const vector<pair<int,int>>& N, int k, 
                vector<int> b, int l, int& num, bool check_FC = false, bool check_Fi = false);