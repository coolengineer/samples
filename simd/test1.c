#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <xmmintrin.h>

#define timer_start(fmt, ...) struct timeval _t1, _t2, _t3; gettimeofday(&_t1,NULL); \
    printf(fmt,##__VA_ARGS__)
#define timer_end() gettimeofday(&_t2,NULL); timersub(&_t2,&_t1,&_t3);\
    printf("Elapsed: %ld.%06ld secs.\n\n", _t3.tv_sec, _t3.tv_usec)

#define items (250 * 1024 * 1024 / sizeof(float))
__attribute__((aligned(16))) float orig[items];
__attribute__((aligned(16))) float dst1[items];
__attribute__((aligned(16))) float dst2[items];

void init() {
    timer_start("Init... %ld items, %ld bytes * 3\n", items, sizeof(orig));
    for( int i=0; i<items; i++ ) {
        orig[i] = ((float) rand()) * powf(10.f, (float) (rand() % 20));
    }
    memset(dst1, sizeof dst1, 0);
    memset(dst2, sizeof dst1, 0);
    timer_end();
}

void compare(const char *title) {
    printf("%s Compare... ", title);
    if (!memcmp(dst1, dst2, sizeof dst1)) { printf("OK\n\n"); } else { printf("Failed\n\n"); }
}

void prepare() {
    timer_start("Calc with math lib...\n");
    int i;
    for(i=0; i<items; i++) {
        dst1[i] = sqrtf(orig[i]);
    }
    timer_end();
}

void test1() {
    timer_start("Calc with math SSE (take1)...\n");
    int i;
    for (i=0; i<items; i+= sizeof(__m128)/sizeof(float)) {
        *(__m128 *) &dst2[i] = _mm_sqrt_ps( *(__m128 *) &orig[i] );
    }
    timer_end();
    compare("SSE (take1)");
}

void test2() {
    timer_start("Calc with math SSE (take2)...\n");
    int i;
    for (i=0; i<items; i+= sizeof(__m128)/sizeof(float)) {
        _mm_stream_ps(&dst2[i], _mm_sqrt_ps( *(__m128 *) &orig[i] ));
    }
    timer_end();
    compare("SSE (take2)");
}

int main() {
    init();
    prepare();
    test1();
    test2();
    return 0;
}

