#include<iostream>
<<<<<<< HEAD
#include<random>
#include<vector>
#include<algorithm>

=======
#include<vector>
#include<algorithm>
>>>>>>> 73d89fa7205dab842a7116dbb3476ddee1696d9f
#include "exetimer.h"

using namespace std;

<<<<<<< HEAD
long long loopMax;
long long loopCnt;


void loop() {
    vector<long long> v(loopMax);

    for ( long long i = 0; i < loopMax; i++ ) {
=======
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
>>>>>>> 73d89fa7205dab842a7116dbb3476ddee1696d9f
        v[loopMax-i-1] = i;
    }

    sort(v.begin(), v.end());
}

<<<<<<< HEAD
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
=======
int main( int argc, char **argv ) {
    test1(argc, argv);
>>>>>>> 73d89fa7205dab842a7116dbb3476ddee1696d9f
}