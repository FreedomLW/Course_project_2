#pragma once

#include "Init.h"
#include <vector>

using namespace std;

const vector<F> Fi = {
    F(),
    F(vector<int>{0b0000111, 0b0001011, 0b0010111, }, // 1
      vector<int>{24, 24, 18, 18, 12, 2, }),
    F(vector<int>{0b0000111, 0b0111001, 0b0111010, 0b0111100, }, // 2
      vector<int>{24, 24, 24, 10, 10, 10, 2, }),
    F(vector<int>{0b0000111, 0b0001111, 0b0010111, 0b0111000, }, // 3
      vector<int>{6, 6, 6, 9, 9, 6, 1, }),
    F(vector<int>{0b0000111, 0b0011001, }, // 4
      vector<int>{11, 7, 7, 7, 7, 1, }),
    F(vector<int>{0b0000111, 0b0111001, 0b0111010, }, // 5
      vector<int>{6, 6, 4, 4, 4, 4, 1, }),
    F(vector<int>{0b0000111, 0b0001111, 0b0010111, 0b0100111, 0b1000111, }, // 6
      vector<int>{8, 8, 8, 8, 8, 8, 8, 2, }),
    F(vector<int>{0b0001111, 0b0010111, 0b0011011, 0b0100111, 0b0101011, 0b0110011, }, // 7
      vector<int>{5, 5, 4, 4, 4, 4, 1, 1, }),
    F(vector<int>{0b0001111, 0b0010111, 0b0100111, 0b1000111, }, // 8
      vector<int>{8, 8, 8, 6, 6, 6, 6, 2, }),
    F(vector<int>{0b0000111, 0b0001111, 0b0010111, 0b0100111, }, // 9
      vector<int>{10, 10, 10, 8, 8, 8, 2, }),
    F(vector<int>{0b0000111, 0b0001111, 0b0010111, 0b1101000, }, // 10
      vector<int>{3, 3, 3, 3, 3, 3, 3, 1, }),
    F(vector<int>{0b0000111, 0b0001111, 0b0111000, }, // 11
      vector<int>{8, 8, 8, 14, 6, 6, 2, 2, }),
    F(vector<int>{0b0001111, 0b0010111, 0b0100111, }, // 12 
      vector<int>{10, 10, 10, 8, 8, 8, 2, 2, }),
    F(vector<int>{0b0000111, 0b0011011, 0b0011101, }, // 13
      vector<int>{12, 12, 12, 8, 8, 2, }),
    F(vector<int>{0b0000111, 0b1111001, 0b1111010, 0b1111100, }, // 14
      vector<int>{3, 3, 3, 3, 3, 3, 3, 1, }),
    F(vector<int>{0b0000111, 0b0111001, 0b0111011, }, // 15
      vector<int>{7, 7, 4, 4, 4, 4, 1, }),
    F(vector<int>{0b0001111, 0b0010111, 0b0011011, }, // 16
      vector<int>{9, 9, 8, 8, 8, 2, 2, 2, }),
    F(vector<int>{0b0000111, 0b0111000, }, // 17
      vector<int>{3, 3, 3, 3, 3, 3, 1, }),
    F(vector<int>{0b0000111, 0b0001011, }, // 18
      vector<int>{4, 4, 4, 4, 1, 1, 1, 1, }),
    F(vector<int>{0b0000111, 0b0111011, 0b0111101, }, //19
      vector<int>{8, 8, 8, 6, 6, 6, 2, }),
    F(vector<int>{0b0000111, 0b0111001, }, //20
      vector<int>{6, 6, 6, 4, 4, 4, 2, }),
    F(vector<int>{0b0000111, 0b01111, 0b010111, },//21
      vector<int>{3, 3, 3, 3, 3, 1, }),
    F(vector<int>{0b0000111, 0b0011011, }, //22
      vector<int>{10, 10, 8, 6, 6, 2, }),
    F(vector<int>{0b0000111, 0b0111011, }, //23
      vector<int>{4, 4, 4, 2, 2, 2, 1, }),
    F(vector<int>{0b0000111, 0b1111000, }, //24
      vector<int>{3, 3, 3, 2, 2, 2, 2, 1, }),
    F(vector<int>{0b0000111, }, //25
      vector<int>{3, 3, 3, 1, }), 
    F(vector<int>{0b0001111, 0b0010111, 0b0101111, }, // 26
      vector<int>{6, 6, 6, 6, 6, 4, 2, }),
    F(vector<int>{0b0001111, 0b0011111, 0b0101111, }, //27
      vector<int>{2, 2, 2, 2, 2, 2, 1, }),
    F(vector<int>{0b0001111, 0b0010111, }, //28
      vector<int>{3, 3, 3, 2, 2, 1, }),
    F(vector<int>{0b0011111, 0b0101111, },
      vector<int>{3, 3, 3, 3, 3, 3, 1, }),
    F(vector<int>{0b0001111, 0b0011111, },
      vector<int>{3, 3, 3, 3, 3, 1, }),
    F(vector<int>{0b0001111, 0b0110011, },
      vector<int>{3, 3, 3, 3, 3, 3, 1, }),
    F(vector<int>{0b0001111, },
      vector<int>{5, 5, 5, 5, 2, 2, 2, }),
    F(vector<int>{0b0011111, },
      vector<int>{4, 4, 4, 4, 4, 2, }),
};