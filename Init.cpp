#include "Init.h"

#include <vector>

using namespace std;

F::F(const vector<int>& family, const vector<int>& weights) {
    f = family;
    f.family_in_bits.set(0);
    closed_f = f.get_closed();
    f.bits.reserve(100);
    closed_f.bits.reserve(100);
    for (int i = 0; i < SETS_NUMBER; ++i) {
        if (f.family_in_bits.test(i)) {
            f.bits.push_back(i);
        }
        if (closed_f.family_in_bits.test(i)) {
            closed_f.bits.push_back(i);
        }
    }

    s = universum(f).count();
    compare.resize(f.bits.size());
    int p = 1;
    for (int l = 3; l < (1<<(f.bits.size()-1)); ++l) {
    
        SET el(l);
        if (l >= (1<<p)) {
            compare[p].reserve((1<<(p)));
            p += 1;
        }
        if (el.count() < 2) continue;
        vector<int> new_vec;
        new_vec.reserve(el.size()+1);
        SET res((1<<s)-1); 
        for (int bit = 0; bit < el.size(); ++bit) { 
            if (el.test(bit)) {
                new_vec.push_back(bit+1);
                res &= f.bits[bit+1];
            }
        }
        new_vec.push_back(res.count());
        compare[p].push_back(new_vec);
    
    }

    weight = weights;
    weight.reserve(MAX_BIT_SET);
    while (weight.size() != MAX_BIT_SET) {
        weight.push_back(weight[weight.size() - 1]);
    }
    t = 0;
    for (auto el : weight) {
        t += el;
    }
    t /= 2;
}