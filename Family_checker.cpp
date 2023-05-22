#include "Family_checker.h"
#include "Init.h"
#include "Fi.h"
#include "Timer.h"
#include <unordered_map>

static int duration_FC = 0;
static int duration_FC7 = 0;
static int duration_Prev = 0;
static int timer_FC = 0;
static int timer_FC7 = 0;
static int timer_Prev = 0;

static bool print = false;

bool checkNotFC(const Family &fam, int i) {
    if (print){
        Timer time(&duration_FC);
        ++timer_FC;
        if (timer_FC % 100000 == 0) {
            cout << "Duration Check FC: " << (duration_FC / 1e6) << "s\n";
            duration_FC = 0;
        }
    }
    SET_OF_SETS mas3;
    int k = fam.other_elements_count;
    SET K = calculate_K(k);
    if (fam.bits.empty()) {
        cout << "Error\n";
        exception;
    } else {
        for (int j = 0; j < fam.bits.size(); ++j) {
            SET el(fam.bits[j]);
            el |= K;
            if (el.count() < 3 && el.count() != 0) {
                return false;
            }
            if (el.count() == 3) {
                if (find(mas3.begin(), mas3.end(), el) == mas3.end())
                    mas3.push_back(el);
            }
        }
    }

    if (fam.other_elements_count > 3) {
        return true;
    }

    for (int j = 0; j < Fi[i].closed_f.bits.size(); ++j) {
        SET el(Fi[i].closed_f.bits[j]);
        if (el.count() < 3 && el.count() != 0) {
            return false;
        }
        if (el.count() == 3 && find(mas3.begin(), mas3.end(), el) 
                                == mas3.end()) {
            mas3.push_back(el);
        }
        if (mas3.size() > 8) {
            return false;
        }
    }

    if (mas3.size() < 3) {
        return true;
    }

    
    for (auto el : mas3) {
        for (auto el2 : mas3){
            if (el == el2) continue;
            for (auto el3 : mas3) {
                if (el == el3 || el2 == el3) continue;
                if ((el | el2 | el3).count() < 6) {
                    return false;
                }
                for (auto el4 : mas3) {
                    if (el == el4 || el2 == el4 || el3 == el4) continue;
                    if ((el | el2 | el3 | el4).count() < 8) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

SET_OF_SETS calculate_mass(const Family& G, int i, int num, bool add_Fi = true) {
    int k = G.other_elements_count;
    SET K = calculate_K(k);

    SET_OF_SETS mas;

    if (G.bits.empty()) {
        cout << "Error\n";
        exception;
    } else {
        for (int j = 0; j < G.bits.size(); ++j) {
            SET el(G.bits[j]);
            el |= K;
            if (el.count() == num) {
                if (find(mas.begin(), mas.end(), el) == mas.end())
                    mas.push_back(el);
            }
        }
    }

    if (add_Fi) {
        for (int j = 0; j < Fi[i].closed_f.bits.size(); ++j) {
            SET el(Fi[i].closed_f.bits[j]);
            if (el.count() == num) {
                if (find(mas.begin(), mas.end(), el) == mas.end())
                    mas.push_back(el);
            }
        }
    }
    return mas;
}

bool checkNotFC1(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4) {

    for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
        for (auto it2 = mas3.begin(); it2 != mas3.end(); ++it2) {
            if (*it1 == *it2) continue;
            if  (((*it1) & (*it2)).count() != 2) continue;
            for (auto it3 = mas4.begin(); it3 != mas4.end(); ++it3) {
                if ((*it3 & *it1).count() != 3 or
                    (*it3 & *it2).count() != 2) continue;
                return false;
            }
        }
    }
    return true;
}

bool checkNotFC2(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4) {
    for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
        for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
            if  (((*it1) & (*it2)).count() != 1) continue;
            for (auto it3 = mas4.begin(); it3 != mas4.end(); ++it3) {
                if ((*it3 & *it1).count() != 1 or
                    (*it3 & *it2).count() != 3 or
                    (*it3 & *it2 & *it1).count() != 0) continue;
                for (auto it4 = mas4.begin(); it4 != mas4.end(); ++it4) {
                    if ((*it4 & *it1).count() != 1 or
                        (*it4 & *it2).count() != 3 or
                        (*it4 & *it3).count() != 3 or
                        (*it4 & *it2 & *it3).count() != 3) continue;
                    return false;
                }
            }
        }
    }
    return true;
}

bool checkNotFC3(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4) {

        for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas3.begin(); it2 != mas3.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 0) continue;
                for (auto it3  = mas4.begin(); it3 != mas4.end(); ++it3) {
                    if ((*it3 & *it1).count() != 3 or
                        (*it3 & *it2).count() != 1) continue;
                    for (auto it4 = mas4.begin(); it4 != mas4.end(); ++it4) {
                        if ((*it4 & *it1).count() != 3 or
                            (*it4 & *it2).count() != 1 or 
                            (*it3 == *it4)) continue;
                        return false;
                    }
                }
            }
    }
    return true;
}

bool checkNotFC4(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4) {

       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas3.begin(); it2 != mas3.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 1) continue; 
                return false;
        }
    }
    return true;
}

bool checkNotFC5(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4) {

    for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
        for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
            if  (((*it1) & (*it2)).count() != 1) continue;
            for (auto it3  = mas4.begin(); it3 != mas4.end(); ++it3) {
                if ((*it3 & *it1).count() != 1 or
                    (*it3 & *it2).count() != 3 or 
                    (*it1 & *it2 & *it3).count() != 0) continue;
                return false;
            }
        }
    }
    return true;
}

bool checkNotFC6(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4) {
       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 3) continue;
                for (auto it3 = mas4.begin(); it3 != mas4.end(); ++it3) {
                    if (*it3 == *it2) continue;
                    if ((*it3 & *it1).count() != 3) continue;
                    for (auto it4 = mas4.begin(); it4 != mas4.end(); ++it4) {
                        if (*it4 == *it2 or *it4 == *it3) continue;
                        if ((*it4 & *it1).count() != 3) continue;
                        for (auto it5 = mas4.begin(); it5 != mas4.end(); ++it5) {
                            if (*it5 == *it2 or *it5 == *it3 or *it5 == *it4) continue;
                            if ((*it5 & *it1).count() != 3) continue;    
                            return false;
                        }
                    }
                }
            }
    }

    return true;
}

bool checkNotFC7(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4){
    if (print) {
        Timer time(&duration_FC7);
        ++timer_FC7;
        if (timer_FC7 % 100000 == 0) {
            cout << "Duration Check FC7: " << (duration_FC7 / 1e6) << "s\n";
            duration_FC7 = 0;
        }
    }
    if (mas4.size() < 6) return true;
    unordered_map<int, std::vector<int>> m;
    for (int i = 0; i < MAX_BIT_SET; ++i) {
        m[i].reserve(40);
    }
    for (int it = 0; it < mas4.size(); ++it) {
        for (int i = 0; i < MAX_BIT_SET; ++i) {
            if (mas4[it].test(i)) {
                m[i].push_back(it);
            }
        }
    }
    for (auto it1 = m.begin(); it1 != m.end(); ++it1) {
        auto it2 = next(it1);
        for (; it2 != m.end(); ++it2) {
            std::vector<int> intersection;
            std::set_intersection(it1->second.begin(), it1->second.end(), it2->second.begin(), it2->second.end(), std::back_inserter(intersection));
            if (intersection.size() < 6) continue;
            for (int i1 = 0; i1 < intersection.size() - 5; ++i1) {
                for (int i2 = i1 + 1; i2 < intersection.size() - 4; ++i2) {
                    for (int i3 = i2 + 1; i3 < intersection.size() - 3; ++i3) {
                        if (((mas4[intersection[i3]]) | (mas4[intersection[i2]]) | (mas4[intersection[i1]])).count() > 6) continue;
                        for (int i4 = i3 + 1; i4 < intersection.size() - 2; ++i4) {
                            if (((mas4[intersection[i4]]) | (mas4[intersection[i3]]) | (mas4[intersection[i2]]) | (mas4[intersection[i1]])).count() > 6) continue;
                            for (int i5 = i4 + 1; i5 < intersection.size() - 1; ++i5) {
                                if (((mas4[intersection[i5]]) | (mas4[intersection[i4]]) | (mas4[intersection[i3]]) | (mas4[intersection[i2]]) | (mas4[intersection[i1]])).count() > 6) continue;
                                for (int i6 = i5 + 1; i6 < intersection.size(); ++i6) {
                                    if (((mas4[intersection[i6]]) | (mas4[intersection[i5]]) | (mas4[intersection[i4]]) | (mas4[intersection[i3]]) | (mas4[intersection[i2]]) | (mas4[intersection[i1]])).count() != 6) continue;
                                        return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return true;
}

bool checkNotFC8(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4) {

        for (auto it1 = mas4.begin(); it1 != mas4.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 3) continue;
                for (auto it3 = mas4.begin(); it3 != mas4.end(); ++it3) {
                    if (*it3 == *it2 or *it3 == *it1) continue;
                    if ((*it3 & *it2 & *it1).count() != 3) continue;
                    for (auto it4 = mas4.begin(); it4 != mas4.end(); ++it4) {
                        if (*it4 == *it2 or *it4 == *it1 or *it4 == *it3) continue;
                        if ((*it4 & *it3 & *it1).count() != 3) continue;
                        return false;
                    }
                }
            }
    }
    return true;
}

bool checkNotFC9(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4) {

       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 3) continue;
                for (auto it3 = mas4.begin(); it3 != mas4.end(); ++it3) {
                    if (*it2 == *it3) continue;
                    if ((*it3 & *it2 & *it1).count() != 3) continue;
                    for (auto it4 = mas4.begin(); it4 != mas4.end(); ++it4) {
                        if (*it4 == *it3 or *it4 == *it2) continue;
                        if ((*it4 & *it2 & *it3 & *it1).count() != 3) continue;
                        return false;
                    }
                }
            }
    }
    return true;
}
bool checkNotFC10(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4) {
 

       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas3.begin(); it2 != mas3.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 0) continue;
                for (auto it3 = mas4.begin(); it3 != mas4.end(); ++it3) {
                    if ((*it3 & *it1).count() != 3 or
                        (*it3 & *it2).count() != 1) continue;
                    for (auto it4 = mas4.begin(); it4 != mas4.end(); ++it4) {
                        if (*it3 == *it4) continue;
                        if ((*it4 & *it1).count() != 3 or
                            (*it4 & *it2).count() != 0) continue;
                        return false;
                    }
                }
        }
    }
    return true;
}
bool checkNotFC11(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4) {

       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas3.begin(); it2 != mas3.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 0) continue;
                for (auto it3 = mas4.begin(); it3 != mas4.end(); ++it3) {
                    if ((*it3 & *it1).count() != 3 or
                        (*it3 & *it2).count() != 1) continue;
                    return false;
                }
        }
    }
    return true;
}

bool checkNotFC12(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4) {

       for (auto it1 = mas4.begin(); it1 != mas4.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 3) continue;
                for (auto it3 = mas4.begin(); it3 != mas4.end(); ++it3) {
                    if ((*it3 & *it1).count() != 3 or
                        (*it3 & *it2).count() != 3 or 
                        (*it3 & *it2 & *it1).count() != 3) continue;
                    return false;
                }
        }
    }
    return true;
}

bool checkNotFC13(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4) {

       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 2) continue;
                for (auto it3 = mas4.begin(); it3 != mas4.end(); ++it3) {
                    if ((*it3 & *it1).count() != 2 or
                        (*it3 & *it2).count() != 3 or
                        (*it3 & *it2 & *it1).count() != 1) continue;                 
                        return false;   
                }
            }
        }
    return true;
}

bool checkNotFC14(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {

       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas5.begin(); it2 != mas5.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 1) continue;
                for (auto it3 = mas5.begin(); it3 != mas5.end(); ++it3) {
                    if ((*it3 & *it1).count() != 1 or
                        (*it3 & *it2).count() != 4 or 
                        (*it3 & *it2 & *it1).count() != 0) continue;
                    for (auto it4 = mas5.begin(); it4 != mas5.end(); ++it4) {
                        if (*it4 == *it3 or *it4 == *it2) continue;
                        if ((*it4 & *it1).count() != 1 or
                            (*it4 & *it3 & *it2).count() != 4) continue;
                        return false;
                    }
                }
        }
    }
    return true;
}

bool checkNotFC15(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 1) continue;
                for (auto it3 = mas5.begin(); it3 != mas5.end(); ++it3) {
                    if ((*it3 & *it1).count() != 2 or
                        (*it3 & *it2).count() != 4 or 
                        (*it3 & *it2 & *it1).count() != 1) continue;
                    return false;
                }
            }
        }
    return true;
}

bool checkNotFC16(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas4.begin(); it1 != mas4.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 3) continue;
                for (auto it3 = mas4.begin(); it3 != mas4.end(); ++it3) {
                    if ((*it3 & *it1).count() != 3 or
                        (*it3 & *it2).count() != 3 or 
                        (*it3 & *it2 & *it1).count() != 2) continue;
                    return false;
                }
            }
        }
    return true;
}

bool checkNotFC17(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas3.begin(); it2 != mas3.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 0) continue;
                return false;
            }
        }
    return true;
}

bool checkNotFC18(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas3.begin(); it2 != mas3.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 2) continue;
                return false;
            }
        }
    return true;
}

bool checkNotFC19(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas5.begin(); it2 != mas5.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 2) continue;
                for (auto it3 = mas5.begin(); it3 != mas5.end(); ++it3) {
                    if ((*it3 & *it1).count() != 2 or
                        (*it3 & *it2).count() != 4 or 
                        (*it3 & *it2 & *it1).count() !=1) continue;
                    return false;
                }
            }
        }
    return true;
}

bool checkNotFC20(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 1) continue;
                return false;
            }
        }
    return true;
}

bool checkNotFC21(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 3) continue;
                for (auto it3 = mas4.begin(); it3 != mas4.end(); ++it3) {
                    if (*it3 == *it2) continue;
                    if ((*it3 & *it1).count() != 3) continue;
                    return false;
                }
            }
        }
    return true;
}

bool checkNotFC22(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 2) continue;
                return false;
            }
        }
    return true;
}

bool checkNotFC23(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas5.begin(); it2 != mas5.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 2) continue;
                return false;
            }
        }
    return true;
}

bool checkNotFC24(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 0) continue;
                return false;
            }
        }
    return true;
}

bool checkNotFC25(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas3.begin(); it1 != mas3.end(); ++it1) {
            return false;
        }
    return true;
}

bool checkNotFC26(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas4.begin(); it1 != mas4.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 3) continue;
                for (auto it3 = mas5.begin(); it3 != mas5.end(); ++it3) {
                    if ((*it3 & *it1).count() != 4 or 
                        (*it3 & *it2).count() != 3) continue;
                    return false;
                }
            }
        }
    return true;
}

bool checkNotFC27(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas4.begin(); it1 != mas4.end(); ++it1) {
            for (auto it2 = mas5.begin(); it2 != mas5.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 4) continue;
                for (auto it3 = next(it2); it3 != mas5.end(); ++it3) {
                    if ((*it3 & *it1).count() != 4) continue;
                    return false;
                }
            }
        }
    return true;
}

bool checkNotFC28(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas4.begin(); it1 != mas4.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 3) continue;
                return false;
            }
        }
    return true;
}

bool checkNotFC29(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas5.begin(); it1 != mas5.end(); ++it1) {
            for (auto it2 = mas5.begin(); it2 != mas5.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 4) continue;
                return false;
            }
        }
    return true;
}

bool checkNotFC30(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas4.begin(); it1 != mas4.end(); ++it1) {
            for (auto it2 = mas5.begin(); it2 != mas5.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 4) continue;
                return false;
            }
        }
    return true;
}

bool checkNotFC31(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas4.begin(); it1 != mas4.end(); ++it1) {
            for (auto it2 = mas4.begin(); it2 != mas4.end(); ++it2) {
                if  (((*it1) & (*it2)).count() != 2) continue;
                return false;
            }
        }
    return true;
}

bool checkNotFC32(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas4.begin(); it1 != mas4.end(); ++it1) {
            return false;
        }
    return true;
}

bool checkNotFC33(const SET_OF_SETS& mas3, const SET_OF_SETS& mas4, const SET_OF_SETS& mas5) {
       for (auto it1 = mas5.begin(); it1 != mas5.end(); ++it1) {
            return false;
        }
    return true;
}

bool checkNotPrevious(const Family& fam, int i){
    if (print) {
        Timer time(&duration_Prev);
        ++timer_Prev;
        if (timer_Prev % 100000 == 0) {
            cout << "Duration Check Prev: " << (duration_Prev / 1e6) << "s\n";
            duration_Prev = 0;
        }
    }
    if (i == 1) return true;
    SET_OF_SETS mas3 = calculate_mass(fam, i, 3);
    SET_OF_SETS mas4 = calculate_mass(fam, i, 4);
    
    if (i <= 18 && !checkNotFC1(mas3, mas4)) return false;
    if (i == 2) return true;
    
    if (i <= 5 && !checkNotFC2(mas3, mas4)) return false;
    if (i == 3) return true;
    
    if (i <= 5 && !checkNotFC3(mas3, mas4)) return false;
    if (i == 4) return true;
    
    if (i <= 25 && !checkNotFC4(mas3, mas4)) return false;
    if (i == 5) return true;

    if (i <= 20 && !checkNotFC5(mas3, mas4)) return false;
    if (i == 6) return true;

    if (i <= 8 && !checkNotFC6(mas3, mas4)) return false;
    if (i == 7) return true;

    if (fam.other_elements_count < 3) {
        if (i <= 12 && !checkNotFC7(mas3, mas4)) return false;
    }
    if (i == 8) return true;

    if (i <= 12 && !checkNotFC8(mas3, mas4)) return false;
    if (i == 9) return true;

    if (i <= 12 && !checkNotFC9(mas3, mas4)) return false;
    if (i == 10) return true;

    if (i <= 11 && !checkNotFC10(mas3, mas4)) return false;
    if (i == 11) return true;

    if (i <= 17 && !checkNotFC11(mas3, mas4)) return false;
    if (i == 12) return true;

    if (!checkNotFC12(mas3, mas4)) return false;
    if (i == 13) return true;
    
    if ( i<= 22 && !checkNotFC13(mas3, mas4)) return false;
    if (i == 14) return true;
    
    SET_OF_SETS mas5 = calculate_mass(fam, i, 5);

    if (i <= 25 && !checkNotFC14(mas3, mas4, mas5)) return false;
    if (i == 15) return true;

    if (i<= 20 && !checkNotFC15(mas3, mas4, mas5)) return false;
    if (i == 16) return true;

    if (i <= 28 && !checkNotFC16(mas3, mas4, mas5)) return false;
    if (i == 17) return true;

    if (i <= 25 && !checkNotFC17(mas3, mas4, mas5)) return false;
    if (i == 18) return true;

    if (i <= 25 && !checkNotFC18(mas3, mas4, mas5)) return false;
    if (i == 19) return true;

    if (!checkNotFC19(mas3, mas4, mas5)) return false;
    if (i == 20) return true;

    if (!checkNotFC20(mas3, mas4, mas5)) return false;
    if (i == 21) return true;

    if (!checkNotFC21(mas3, mas4, mas5)) return false;
    if (i == 22) return true;

    if (!checkNotFC22(mas3, mas4, mas5)) return false;
    if (i == 23) return true;

    if (!checkNotFC23(mas3, mas4, mas5)) return false;
    if (i == 24) return true;

    if (!checkNotFC24(mas3, mas4, mas5)) return false;
    if (i == 25) return true;

    if (!checkNotFC25(mas3, mas4, mas5)) return false;
    if (i == 26) return true;

    if (!checkNotFC26(mas3, mas4, mas5)) return false;
    if (i == 27) return true;

    if (!checkNotFC27(mas3, mas4, mas5)) return false;
    if (i == 28) return true;

    if (!checkNotFC28(mas3, mas4, mas5)) return false;
    if (i == 29) return true;

    if (!checkNotFC29(mas3, mas4, mas5)) return false;
    if (i == 30) return true;

    if (!checkNotFC30(mas3, mas4, mas5)) return false;
    if (i == 31) return true;

    if (!checkNotFC31(mas3, mas4, mas5)) return false;
    if (i == 32) return true;

    if (!checkNotFC32(mas3, mas4, mas5)) return false;
    if (i == 33) return true;
    return true;
}