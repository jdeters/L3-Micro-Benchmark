#include <stdlib.h>
#include <stdio.h>

#ifdef LIKWID_PERFMON
#include <likwid.h>
#else
#define LIKWID_MARKER_INIT
#define LIKWID_MARKER_THREADINIT
#define LIKWID_MARKER_SWITCH
#define LIKWID_MARKER_REGISTER(regionTag)
#define LIKWID_MARKER_START(regionTag)
#define LIKWID_MARKER_STOP(regionTag)
#define LIKWID_MARKER_CLOSE
#define LIKWID_MARKER_GET(regionTag, nevents, events, time, count)
#endif

#define L3CACHE_SIZE (16*1024*1024)

#define N 100000

long *data1;
long *data2;

void run() {
    LIKWID_MARKER_THREADINIT;
    
    int i;
    for(i = 0; i < 7 * L3CACHE_SIZE; i++) data2[i] = i;

    LIKWID_MARKER_START("foo");
    unsigned long index = 0;
    unsigned long count = 0;
    while(count != N){
        data1[index] = data2[index];
        index = (index + 8) % (7 * L3CACHE_SIZE);
        count++;
    } 
    LIKWID_MARKER_STOP("foo");
}

int main() {
    LIKWID_MARKER_INIT;
    printf("%d\n", sizeof(long));
    data1 = (long *) malloc(7 * L3CACHE_SIZE * sizeof(long));
    data2 = (long *) malloc(7 * L3CACHE_SIZE * sizeof(long));
    run(); 
    LIKWID_MARKER_CLOSE; 
    return 0;
}
