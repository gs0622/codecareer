/*gcc -Wl,--no-as-needed,-lrt Fibonacci.c*/
#include <stdio.h>
#include <time.h>
/*exponential time, bad*/
unsigned long long fib1(int n)
{
    if (n==0) return 0;
    if (n==1) return 1;
    return fib1(n-2)+fib1(n-1);
}
/*O(n) time, O(1) space, good*/
unsigned long long fib2(int n)
{
    int i;
    unsigned long long f, fm1, fm2; /*f(n), f(n-1), f(n-2)*/
    if (n==0) return 0;
    if (n==1) return 1;
    for (i=2,fm1=1,fm2=0;i<=n;i++) { /*bottom-up*/
        f = fm1+fm2, fm2=fm1, fm1=f;
    }
    return f;
}
/*O(n) time, O(1) space, good*/
unsigned long long fib3(int n)
{
    int i;
    unsigned long long f[2] = {0, 1}, tmp;
    if (n<2) return f[n];
    for (i=2;i<=n;i++) { /*bottom-up*/
        tmp = f[1], f[1]=f[0]+f[1], f[0]=tmp;
    }
    return f[1];
}
struct matrix2x2 {
    unsigned long long d[2][2];
};
static struct matrix2x2 matrix2x2mul(struct matrix2x2 m, struct matrix2x2 n)
{
    struct matrix2x2 r;
    r.d[0][0] = m.d[0][0] * n.d[0][0] + m.d[0][1] * n.d[1][0];
    r.d[0][1] = m.d[0][0] * n.d[0][1] + m.d[0][1] * n.d[1][1];
    r.d[1][0] = m.d[1][0] * n.d[0][0] + m.d[1][1] * n.d[1][0];
    r.d[1][1] = m.d[1][0] * n.d[0][1] + m.d[1][1] * n.d[1][1];
    return r;
}
static struct matrix2x2 fibpow(int n)
{
    static struct matrix2x2 u = {.d[0][0]=1, .d[0][1]=1, .d[1][0]=1, .d[1][1]=0};
    struct matrix2x2 r;
    if (1==n) return u;
    if (n%2==0) {
        r = fibpow(n/2);
        r = matrix2x2mul(r, r);
    } else {
        r = fibpow((n-1)/2);
        r = matrix2x2mul(r, r);
        r = matrix2x2mul(r, u);
    }
    return r;
}
/*O(lgn) time, O(1) space, best*/
unsigned long long fib4(int n)
{
    struct matrix2x2 r;
    unsigned long long f[2] = {0, 1};
    if (n<2) return f[n];
    r = fibpow(n-1);
    return r.d[0][0];
}
void m2x2mul_avx(struct matrix2x2 *r, struct matrix2x2 const * const m, struct matrix2x2 const * const n)
{
    /*AVX by YT*/
    __asm__ volatile (
        "movdqu     (%rdx), %xmm0\r\n"
        "movddup    (%rsi), %xmm4\r\n"
        "movdqu     16(%rdx), %xmm2\r\n"
        "movddup    8(%rsi), %xmm6\r\n"
        "movddup    16(%rsi), %xmm8\r\n"
        "movddup    24(%rsi), %xmm10\r\n"
        "vpsrldq    $4, %xmm0, %xmm1\r\n"
        "vpsrldq    $4, %xmm4, %xmm5\r\n"
        "vpmuludq   %xmm4, %xmm1, %xmm12\r\n"
        "vpsrldq    $4, %xmm2, %xmm3\r\n"
        "vpsrldq    $4, %xmm6, %xmm7\r\n"
        "vpmuludq   %xmm5, %xmm0, %xmm5\r\n"
        "vpsrldq    $4, %xmm8, %xmm9\r\n"
        "vpsrldq    $4, %xmm10, %xmm11\r\n"
        "vpmuludq   %xmm6, %xmm3, %xmm13\r\n"
        "vpmuludq   %xmm7, %xmm2, %xmm7\r\n"
        "vpmuludq   %xmm8, %xmm1, %xmm14\r\n"
        "vpmuludq   %xmm9, %xmm0, %xmm9\r\n"
        "vpmuludq   %xmm10, %xmm3, %xmm15\r\n"
        "vpaddq     %xmm12, %xmm5, %xmm12\r\n"
        "vpmuludq   %xmm11, %xmm2, %xmm11\r\n"
        "vpmuludq   %xmm4, %xmm0, %xmm4\r\n"
        "vpaddq     %xmm13, %xmm7, %xmm13\r\n"
        "vpmuludq   %xmm6, %xmm2, %xmm6\r\n"
        "vpmuludq   %xmm8, %xmm0, %xmm8\r\n"
        "vpaddq     %xmm14, %xmm9, %xmm14\r\n"
        "vpmuludq   %xmm10, %xmm2, %xmm10\r\n"
        "vpsllq     $32, %xmm12, %xmm5\r\n"
        "vpsllq     $32, %xmm13, %xmm7\r\n"
        "vpaddq     %xmm15, %xmm11, %xmm15\r\n"
        "vpsllq     $32, %xmm14, %xmm9\r\n"
        "vpsllq     $32, %xmm15, %xmm11\r\n"
        "vpaddq     %xmm4, %xmm5, %xmm0\r\n"
        "vpaddq     %xmm6, %xmm7, %xmm1\r\n"
        "vpaddq     %xmm8, %xmm9, %xmm2\r\n"
        "vpaddq     %xmm10, %xmm11, %xmm3\r\n"
        "vpaddq     %xmm0, %xmm1, %xmm0\r\n"
        "vpaddq     %xmm2, %xmm3, %xmm1\r\n"
        "movdqu     %xmm0, (%rdi)\r\n"
        "movdqu     %xmm1, 16(%rdi)\r\n"
    );
}

static struct matrix2x2 fibpow2(int n)
{
    static struct matrix2x2 u = {.d[0][0]=1, .d[0][1]=1, .d[1][0]=1, .d[1][1]=0};
    struct matrix2x2 r;
    if (1==n) return u;
    if (n%2==0) {
        r = fibpow2(n/2);
        m2x2mul_avx(&r, &r, &r);
    } else {
        r = fibpow2((n-1)/2);
        m2x2mul_avx(&r, &r, &r);
        m2x2mul_avx(&r, &r, &u);
    }
    return r;
}
/*O(lgn) time, O(1) space, best*/
unsigned long long fib5(int n)
{
    struct matrix2x2 r;
    unsigned long long f[2] = {0, 1};
    if (n<2) return f[n];
    r = fibpow2(n-1);
    return r.d[0][0];
}
void m2x2mul_avx2(struct matrix2x2 *r, struct matrix2x2 const * const m, struct matrix2x2 const * const n)
{
    /*AVX2 by YT*/
    __asm__ volatile (
        "vmovdqu    (%rsi), %ymm14\r\n"
        "mov        $1, %rax\r\n"
        "test       %rdx, %rdx\r\n"
        "movq       %rax, %xmm15\r\n"
        "vpermq     $0b01000001, %ymm15, %ymm15\r\n"
        "je         0f\r\n"
        "1:\r\n"
        "shr        $1, %rdx\r\n"
        "jae        2f\r\n"
        "vpermq     $0b01000100, %ymm15, %ymm0\r\n"
        "vpermq     $0b10001000, %ymm14, %ymm1\r\n"
        "vpermq     $0b11101110, %ymm15, %ymm2\r\n"
        "vpermq     $0b11011101, %ymm14, %ymm3\r\n"
        "vpsrldq    $4, %ymm0, %ymm4\r\n"
        "vpsrldq    $4, %ymm1, %ymm5\r\n"
        "vpmuludq   %ymm1, %ymm4, %ymm8\r\n"
        "vpsrldq    $4, %ymm2, %ymm6\r\n"
        "vpsrldq    $4, %ymm3, %ymm7\r\n"
        "vpmuludq   %ymm0, %ymm5, %ymm9\r\n"
        "vpmuludq   %ymm3, %ymm6, %ymm10\r\n"
        "vpmuludq   %ymm2, %ymm7, %ymm11\r\n"
        "vpmuludq   %ymm0, %ymm1, %ymm0\r\n"
        "vpmuludq   %ymm2, %ymm3, %ymm2\r\n"
        "vpaddq     %ymm8, %ymm9, %ymm8\r\n"
        "vpaddq     %ymm10, %ymm11, %ymm10\r\n"
        "vpaddq     %ymm8, %ymm10, %ymm8\r\n"
        "vpsllq     $32, %ymm8, %ymm1\r\n"
        "vpaddq     %ymm0, %ymm2, %ymm0\r\n"
        "vpaddq     %ymm0, %ymm1, %ymm15\r\n"
        "je         0f\r\n"
        "2:\r\n"
        "vpermq     $0b01000100, %ymm14, %ymm0\r\n"
        "vpermq     $0b10001000, %ymm14, %ymm1\r\n"
        "vpermq     $0b11101110, %ymm14, %ymm2\r\n"
        "vpermq     $0b11011101, %ymm14, %ymm3\r\n"
        "vpsrldq    $4, %ymm0, %ymm4\r\n"
        "vpsrldq    $4, %ymm1, %ymm5\r\n"
        "vpmuludq   %ymm1, %ymm4, %ymm8\r\n"
        "vpsrldq    $4, %ymm2, %ymm6\r\n"
        "vpsrldq    $4, %ymm3, %ymm7\r\n"
        "vpmuludq   %ymm0, %ymm5, %ymm9\r\n"
        "vpmuludq   %ymm3, %ymm6, %ymm10\r\n"
        "vpmuludq   %ymm2, %ymm7, %ymm11\r\n"
        "vpmuludq   %ymm0, %ymm1, %ymm0\r\n"
        "vpmuludq   %ymm2, %ymm3, %ymm2\r\n"
        "vpaddq     %ymm8, %ymm9, %ymm8\r\n"
        "vpaddq     %ymm10, %ymm11, %ymm10\r\n"
        "vpaddq     %ymm8, %ymm10, %ymm8\r\n"
        "vpsllq     $32, %ymm8, %ymm1\r\n"
        "vpaddq     %ymm0, %ymm2, %ymm0\r\n"
        "vpaddq     %ymm0, %ymm1, %ymm14\r\n"
        "jmp        1b\r\n"
        "0:\r\n"
        "vmovdqu    %ymm15, (%rdi)\r\n"
    );
}
static struct matrix2x2 fibpow3(int n)
{
    static struct matrix2x2 u = {.d[0][0]=1, .d[0][1]=1, .d[1][0]=1, .d[1][1]=0};
    struct matrix2x2 r;
    if (1==n) return u;
    if (n%2==0) {
        r = fibpow3(n/2);
        m2x2mul_avx2(&r, &r, &r);
    } else {
        r = fibpow3((n-1)/2);
        m2x2mul_avx2(&r, &r, &r);
        m2x2mul_avx2(&r, &r, &u);
    }
    return r;
}
/*O(lgn) time, O(1) space, best*/
unsigned long long fib6(int n)
{
    struct matrix2x2 r;
    unsigned long long f[2] = {0, 1};
    if (n<2) return f[n];
    r = fibpow3(n-1);
    return r.d[0][0];
}
void m2x2pow_avx2(struct matrix2x2 *r, struct matrix2x2 const * const m, const unsigned long long powN)
{
    __asm__ volatile (
        "vmovdqu    (%rsi), %ymm14\r\n"         /*	src	*/
        "mov        $1, %rax\r\n"
        "test       %rdx, %rdx\r\n"
        "movq       %rax, %xmm15\r\n"
        "vpermq     $0b01000001, %ymm15, %ymm15\r\n"    /*	identity matrix	*/
        "je         0f\r\n"
        "1:\r\n"
        "shr        $1, %rdx\r\n"
        "jae        2f\r\n"                     /*	not required to update result with current src^n	*/
        "vpermq     $0b01000100, %ymm15, %ymm0\r\n" /*	{y, x, y, x}	*/
        "vpermq     $0b10001000, %ymm14, %ymm1\r\n" /*	{c, c, a, a}	*/
        "vpermq     $0b11101110, %ymm15, %ymm2\r\n" /*	{w, z, w, z}	*/
        "vpermq     $0b11011101, %ymm14, %ymm3\r\n" /*	{d, d, b, b}	*/
        "vpsrldq    $4, %ymm0, %ymm4\r\n"       /*	{y>>32, x>>32, y>>32, x>>32}	*/
        "vpsrldq    $4, %ymm1, %ymm5\r\n"       /*	{c>>32, c>>32, a>>32, a>>32}	*/
        "vpmuludq   %ymm1, %ymm4, %ymm8\r\n"    /*	{cy>>32, cx>>32, ay>>32, ax>>32}	*/
        "vpsrldq    $4, %ymm2, %ymm6\r\n"       /*	{w>>32, z>>32, w>>32, z>>32}	*/
        "vpsrldq    $4, %ymm3, %ymm7\r\n"       /*	{d>>32, d>>32, b>>32, b>>32}	*/
        "vpmuludq   %ymm0, %ymm5, %ymm9\r\n"    /*	{(c>>32)y, (c>>32)x, (a>>32)y, (a>>32)x}	*/
        "vpmuludq   %ymm3, %ymm6, %ymm10\r\n"   /*	{dw>>32, dz>>32, bw>>32, bz>>32}	*/
        "vpmuludq   %ymm2, %ymm7, %ymm11\r\n"   /*	{(d>>32)w, (d>>32)z, (b>>32)w, (b>>32)z}	*/
        "vpmuludq   %ymm0, %ymm1, %ymm0\r\n"    /*	low 64bit {cy, cx, ay, ax}	*/
        "vpmuludq   %ymm2, %ymm3, %ymm2\r\n"    /*	low 64bit {dw, dz, bw, bz}	*/
        "vpaddq     %ymm8, %ymm9, %ymm8\r\n"    /*	middle 64bit {cy, cx, ay, ax}	*/
        "vpaddq     %ymm10, %ymm11, %ymm10\r\n" /*	middle 64bit {dw, dz, bw, bz}	*/
        "vpaddq     %ymm8, %ymm10, %ymm8\r\n"   /*	middle 64bit {cy+dw, cx+dz, ay+bw, ax+bz}	*/
        "vpsllq     $32, %ymm8, %ymm1\r\n"  /*	low part of middle 64bit {cy+dw, cx+dz, ay+bw, ax+bz}	*/
        "vpaddq     %ymm0, %ymm2, %ymm0\r\n"    /*	low 64bit {cy+dw, cx+dz, ay+bw, ax+bz}	*/
        "vpaddq     %ymm0, %ymm1, %ymm15\r\n"
        "je         0f\r\n"                     /*	no more power to do	*/
        "2:\r\n"
        "vpermq     $0b01000100, %ymm14, %ymm0\r\n" /*	{y, x, y, x}	*/
        "vpermq     $0b10001000, %ymm14, %ymm1\r\n" /*	{c, c, a, a}	*/
        "vpermq     $0b11101110, %ymm14, %ymm2\r\n" /*	{w, z, w, z}	*/
        "vpermq     $0b11011101, %ymm14, %ymm3\r\n" /*	{d, d, b, b}	*/
        "vpsrldq    $4, %ymm0, %ymm4\r\n"   /*	{y>>32, x>>32, y>>32, x>>32}	*/
        "vpsrldq    $4, %ymm1, %ymm5\r\n"       /*	{c>>32, c>>32, a>>32, a>>32}	*/
        "vpmuludq   %ymm1, %ymm4, %ymm8\r\n"    /*	{cy>>32, cx>>32, ay>>32, ax>>32}	*/
        "vpsrldq    $4, %ymm2, %ymm6\r\n"       /*	{w>>32, z>>32, w>>32, z>>32}	*/
        "vpsrldq    $4, %ymm3, %ymm7\r\n"       /*	{d>>32, d>>32, b>>32, b>>32}	*/
        "vpmuludq   %ymm0, %ymm5, %ymm9\r\n"    /*	{(c>>32)y, (c>>32)x, (a>>32)y, (a>>32)x}	*/
        "vpmuludq   %ymm3, %ymm6, %ymm10\r\n"   /*	{dw>>32, dz>>32, bw>>32, bz>>32}	*/
        "vpmuludq   %ymm2, %ymm7, %ymm11\r\n"   /*	{(d>>32)w, (d>>32)z, (b>>32)w, (b>>32)z}	*/
        "vpmuludq   %ymm0, %ymm1, %ymm0\r\n"    /*	low 64bit {cy, cx, ay, ax}	*/
        "vpmuludq   %ymm2, %ymm3, %ymm2\r\n"    /*	low 64bit {dw, dz, bw, bz}	*/
        "vpaddq     %ymm8, %ymm9, %ymm8\r\n"    /*	middle 64bit {cy, cx, ay, ax}	*/
        "vpaddq     %ymm10, %ymm11, %ymm10\r\n" /*	middle 64bit {dw, dz, bw, bz}	*/
        "vpaddq     %ymm8, %ymm10, %ymm8\r\n"   /*	middle 64bit {cy+dw, cx+dz, ay+bw, ax+bz}	*/
        "vpsllq     $32, %ymm8, %ymm1\r\n"      /*	low part of middle 64bit {cy+dw, cx+dz, ay+bw, ax+bz}	*/
        "vpaddq     %ymm0, %ymm2, %ymm0\r\n"    /*	low 64bit {cy+dw, cx+dz, ay+bw, ax+bz}	*/
        "vpaddq     %ymm0, %ymm1, %ymm14\r\n"
        "jmp        1b\r\n"
        "0:\r\n"
        "vmovdqu    %ymm15, (%rdi)\r\n"
        "retq\r\n"
    );
}
static struct matrix2x2 fibpow4(int n)
{
    static struct matrix2x2 u = {.d[0][0]=1, .d[0][1]=1, .d[1][0]=1, .d[1][1]=0};
    struct matrix2x2 r;
    if (1==n) return u;
    m2x2pow_avx2(&r, &u, (unsigned long long)n);
    return r;
}
/*O(lgn) time, O(1) space, best*/
unsigned long long fib7(int n)
{
    struct matrix2x2 r;
    unsigned long long f[2] = {0, 1};
    if (n<2) return f[n];
    r = fibpow4(n-1);
    return r.d[0][0];
}
int main(void)
{
    int n;
    struct timespec t1, t2;
    unsigned long long r;
    printf("Fibonacci? ");
    while (scanf("%d", &n)==1) {
        printf("\n");
        clock_gettime(CLOCK_MONOTONIC, &t1);
        r = fib6(n);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        printf("fib6(%d)=%llu t=%lus %luns\n", n, r, (t2.tv_sec-t1.tv_sec), (t2.tv_nsec-t1.tv_nsec));
        clock_gettime(CLOCK_MONOTONIC, &t1);
        r = fib5(n);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        printf("fib5(%d)=%llu t=%lus %luns\n", n, r, (t2.tv_sec-t1.tv_sec), (t2.tv_nsec-t1.tv_nsec));
        clock_gettime(CLOCK_MONOTONIC, &t1);
        r = fib4(n);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        printf("fib4(%d)=%llu t=%lus %luns\n", n, r, (t2.tv_sec-t1.tv_sec), (t2.tv_nsec-t1.tv_nsec));
        clock_gettime(CLOCK_MONOTONIC, &t1);
        r = fib3(n);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        printf("fib3(%d)=%llu t=%lus %luns\n", n, r, (t2.tv_sec-t1.tv_sec), (t2.tv_nsec-t1.tv_nsec));
        clock_gettime(CLOCK_MONOTONIC, &t1);
        r = fib2(n);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        printf("fib2(%d)=%llu t=%lus %luns\n", n, r, (t2.tv_sec-t1.tv_sec), (t2.tv_nsec-t1.tv_nsec));
        /*clock_gettime(CLOCK_MONOTONIC, &t1);
        r = fib1(n);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        printf("fib1(%d)=%llu t=%lus %luns\n", n, r, (t2.tv_sec-t1.tv_sec), (t2.tv_nsec-t1.tv_nsec));*/
        printf("\nFibonacci? ");
    }
    return 0;
}
