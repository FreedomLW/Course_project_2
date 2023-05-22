#pragma once

#include "Family.h"
#include <vector>

class F {
public:
    Family f;
    Family closed_f;
    vector<int> weight;
    vector<vector<vector<int>>> compare;
    int t;
    size_t s;

    F() {};

    F(const vector<int>& family, const vector<int>& weights);
};