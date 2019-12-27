#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <xmmintrin.h>

#define timer_start() struct timeval _t1, _t2, _t3; gettimeofday(&_t1,NULL)
#define timer_end() gettimeofday(&_t2,NULL); timersub(&_t2,&_t1,&_t3);\
    printf("Elapsed: %ld.%06ld secs.\n\n", _t3.tv_sec, _t3.tv_usec)

#define items (250 * 1024 * 1024 / sizeof(float))
__attribute__((aligned(16))) float orig[items];
__attribute__((aligned(16))) float dst1[items];
__attribute__((aligned(16))) float dst2[items];

void init()
{
    timer_start();
    printf("Init... %ld items\n", items);
    for( int i=0; i<items; i++ ) {
        orig[i] = ((float) rand()) * powf(10.f, (float) (rand() % 20));
    }
    memset(dst1, sizeof dst1, 0);
    memset(dst2, sizeof dst1, 0);
    timer_end();
}

void test1()
{
    timer_start();
    printf("Calc with math lib...\n");
    int i;
    for(i=0; i<items; i++) {
        dst1[i] = sqrtf(orig[i]);
    }
    timer_end();
}

void test2()
{
    timer_start();
    printf("Calc with math SSE (take1)...\n");
    int i;
    for (i=0; i<items; i+= sizeof(__m128)/sizeof(float)) {
        *(__m128 *) &dst2[i] = _mm_sqrt_ps( *(__m128 *) &orig[i] );
    }
    timer_end();
}

void compare()
{
    timer_start();
    printf("Compare... ");
    if (!memcmp(dst1, dst2, sizeof dst1)) {
        printf("OK\n");
    } else {
        printf("Failed\n");
    }
    timer_end();
}

int main()
{
    init();
    test1();
    test2();
    compare();
    return 0;
}

