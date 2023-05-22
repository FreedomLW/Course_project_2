#include <chrono>

using namespace std;

class Timer {
public:

    int *timer; 
    chrono::system_clock::time_point start;

    Timer(int *new_timer) {
        timer = new_timer;
        start = chrono::system_clock::now();
    };

    ~Timer() {
        chrono::system_clock::time_point end = chrono::system_clock::now();
        *timer += chrono::duration_cast<chrono::microseconds>(end - start).count();
    };
};