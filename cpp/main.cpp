#include<iostream>
#include<random>
#include<vector>
#include<algorithm>

#include "exetimer.h"

using namespace std;

long long loopMax;
long long loopCnt;


void loop() {
    vector<long long> v(loopMax);

    for ( long long i = 0; i < loopMax; i++ ) {
        v[loopMax-i-1] = i;
    }

    sort(v.begin(), v.end());
}

ExeTimer test () {
    const int seed = 0;

    ExeTimer timer = startTimer();
    for ( int i = 0; i < loopCnt; i++ ) {
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
    loopCnt = atoll(argv[2]);

    ExeTimer timer = test();

    printf("[Test1 CPP] End : loopMax: %lld, loopCnt: %lld , time : %ld\n", loopMax, loopCnt, timer.elapsedMilliseconds());
}