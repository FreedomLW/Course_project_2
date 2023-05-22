#pragma once

#include <bitset>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

const int BIT_SET = 7;
const int MAX_BIT_SET = 12;
const int SETS_NUMBER = (1 << BIT_SET);

#define SET bitset<MAX_BIT_SET> 

auto cmp = [](const SET& a, const SET& b) 
    { return a.to_ullong() < b.to_ullong(); };

//#define SET_OF_SETS set<SET, decltype(cmp)>
#define SET_OF_SETS vector<SET>

#define FAMILY bitset<SETS_NUMBER>

SET calculate_K(int k);

class Family {
public:
    FAMILY family_in_bits;
    int other_elements_count = 0;
    vector<int> bits;

    Family();

    Family(FAMILY vec);

    Family(FAMILY vec, int other_el);

    Family(const vector<int>& vec);

    Family(const vector<int>& vec, int other_el);

    int set_count();

    void close();
    

    void calculate_bits();

    Family get_closed() const;
};

ostream& operator<< (ostream &out, const Family &s);

Family merge(const Family& s1, const Family& s2);

Family merge_plus(const Family& s1, const Family& s2);

SET universum(const Family& fam);