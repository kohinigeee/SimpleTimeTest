#include<iostream>
#include<random>
#include<vector>
#include<algorithm>

#include "exetimer.h"

using namespace std;
using ele_t = long long;

long long loopMax = 0;
long long loopCount = 0;

void loop();


void test1( int argc, char **argv ) {
    if ( argc < 3 ) {
        cout << "Usage: " << argv[0] << " <loopMax> <loopCount>" << endl;
        return;
    }

    loopMax = atoll(argv[1]);
    loopCount = atoll(argv[2]);

    ExeTimer timer = startTimer();
    for ( ele_t i = 0; i < loopCount; i++ ) {
        loop();
        printf("Loop %lld was done\n", i);
    }
    timer.stop();

    cout << "--------------------------------" << endl;
    cout << endl;

    printf("Process was done , loopMax: %lld, loopCount: %lld\n", loopMax, loopCount);
    cout << "Elapsed time: " << timer.elapsedMilliseconds() << "ms" << endl;
}


void loop() {
    vector<ele_t> v(loopMax);

    for ( ele_t i = 0; i < 1000000; i++ ) {
        v[loopMax-i-1] = i;
    }

    sort(v.begin(), v.end());
}

ExeTimer test () {
    const int seed = 0;

    ExeTimer timer = startTimer();
    for ( int i = 0; i < loopCount; i++ ) {
        loop();
        // printf("[Test1 CPP] loop done %d\n", i);
    }
    timer.stop();

    printf("[Test1 CPP] All loop was done : elapsed time: %lld ms\n", timer.elapsedMilliseconds());

    return timer;
}


int main(int argc, char** argv) {
    if ( argc < 3 ) {
        printf("Usage: %s <loopMax> <loopCnt>\n", argv[0]);
        return 1;
    }

    loopMax = atoll(argv[1]);
    loopCount = atoll(argv[2]);

    ExeTimer timer = test();

    printf("[Test1 CPP] End : loopMax: %lld, loopCnt: %lld , time : %ld\n", loopMax, loopCount, timer.elapsedMilliseconds());
}