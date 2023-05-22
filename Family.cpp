#include "Family.h"

#include <bitset>
#include <iostream>
#include <set>
#include <vector>
#include "Timer.h"

static int duration_close = 0;
static int duration_murge_plus = 0;
static int timer_close = 0;
static int timer_murge_plus = 0;

static bool print = false;

SET calculate_K(int k) {
    SET res(0);
    for (int j = 0; j < k; ++j) {
        res.set(MAX_BIT_SET - 1 - j);
    }
    return res;
}

Family::Family() {
    family_in_bits = FAMILY(0);
}

Family::Family(FAMILY vec) {
    family_in_bits = vec;
}

Family::Family(const vector<int>& vec) {
    for (auto el : vec) {
        family_in_bits.set(el);
    }
}

Family::Family(FAMILY vec, int other_el = 0) {
    family_in_bits = vec;
    other_elements_count = other_el;
}

Family::Family(const vector<int>& vec, int other_el = 0) {
    for (auto el : vec) {
        family_in_bits.set(el);
    }
    other_elements_count = other_el;
}

int Family::set_count() {
    return family_in_bits.count(); 
}
void Family::close() {
    if (bits.empty()) {
        for (int i1 = 1; i1 < SETS_NUMBER; ++i1) {
            if (!family_in_bits.test(i1)) continue;
            for (int i2 = i1 + 1; i2 < SETS_NUMBER; ++i2) {
                if (!family_in_bits.test(i2)) continue; 
                family_in_bits.set(i1 | i2);
            }
        }
    } else {
        int size = bits.size();
        for (int i1 = 0; i1 < size; ++i1) {
            int size2 = bits.size();
            for (int i2 = i1+1; i2 < size2; ++i2) {
                if (family_in_bits.test(bits[i1] | bits[i2])) continue;
                family_in_bits.set(bits[i1] | bits[i2]);
                bits.push_back(bits[i1] | bits[i2]);
            }
        }
    }
}

void Family::calculate_bits() {
    bits.reserve(100);
    for (int i = 0; i < SETS_NUMBER; ++i) {
        if (family_in_bits.test(i)) {
            bits.push_back(i);
        }
    }
}
Family Family::get_closed() const {
    Family new_fam;
    new_fam.family_in_bits = family_in_bits;
    new_fam.other_elements_count = other_elements_count;
    new_fam.close();
    return new_fam;
};


ostream& operator<< (ostream &out, const Family &s) {
    if (s.family_in_bits.none()) {
        out << string("{}");
        return out;
    }
    out << string("{\n");
    for (int i = 0; i < s.family_in_bits.size(); ++i) {
        if (s.family_in_bits.test(i)) {
            SET tmp(i);
            tmp |= calculate_K(s.other_elements_count);
            out << tmp << '\n';
        }
    }
    out << string("}");
    return out;
};

Family merge(const Family& s1, const Family& s2) {
    if (s1.other_elements_count != s2.other_elements_count) {
        if (s1.other_elements_count != 0 || s2.other_elements_count != 0) {
            exception;
        }   
    }
    Family new_family;
    new_family.family_in_bits = s1.family_in_bits | s2.family_in_bits;
    return new_family;

}

Family merge_plus(const Family& s1, const Family& s2) {
    if (s1.other_elements_count != s2.other_elements_count) {
        if (s1.other_elements_count != 0 || s2.other_elements_count != 0) {
            exception;
        }   
    }
    if (print) {
        Timer time(&duration_murge_plus);
        ++timer_murge_plus;
        if (timer_murge_plus % 100000 == 0) {
            cout << "Duration merge plus: " << (duration_murge_plus / 1e6) << "s\n";
            duration_murge_plus = 0;
        }
    }
    Family new_family;
    new_family.other_elements_count = max(s1.other_elements_count, s2.other_elements_count);
    if (s1.bits.empty() || s2.bits.empty()) {
        exception;
    } else {
        new_family.bits.reserve(100);
        for (int i1 = 0; i1 < s1.bits.size(); ++i1) {
            for (int i2 = 0; i2 < s2.bits.size(); ++i2) {
                if (new_family.family_in_bits.test(s1.bits[i1] | s2.bits[i2])) continue;
                new_family.family_in_bits.set(s1.bits[i1] | s2.bits[i2]);
                new_family.bits.push_back(s1.bits[i1] | s2.bits[i2]);
            }
        }
    }
    return new_family;
}

SET universum(const Family& fam) {
    SET univ(0);
    for (int i = 0; i < SETS_NUMBER; ++i) {
        if (fam.family_in_bits.test(i))
            univ |= SET(i);
    }
    return univ;
}