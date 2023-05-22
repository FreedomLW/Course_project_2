#pragma once

#include <vector>
#include <string>

using namespace std;

void algorithm(int i, vector<vector<int>>& d, 
               int &timer, int threshold = 0);

void calc_all(vector<vector<vector<int>>>& d, int &timer, 
              bool without7 = true, int max_number = 28, 
              bool add_to_file = true, string file_name = "");

void algorithm_Fi(int i, int k, int num, bool check_FC = false, bool check_Fi = false);
