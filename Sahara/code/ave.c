#include <stdio.h>
#include <math.h>
#define N 100
//#define TEN_AVE
int main()
{
    // double a[10]={};
    double a[N] = {
        0.541242,0.544943,0.540230,0.545547,0.543768,0.523510,0.543972,0.543710,0.544420,0.538902,0.541038,0.542666,0.542328,0.541563,0.542509,0.539781,0.544552,0.542618,0.542147,0.540885,0.540576,0.525949,0.542051,0.543043,0.543281,0.542379,0.539246,0.545355,0.543005,0.543644,0.539141,0.538361,0.537701,0.544546,0.542935,0.538000,0.537841,0.544005,0.540713,0.541621,0.543029,0.544930,0.543723,0.544851,0.543193,0.542473,0.547753,0.541700,0.532722,0.542858,0.544211,0.535961,0.539151,0.545162,0.527021,0.544412,0.528906,0.565536,0.545354,0.540477,0.544521,0.544144,0.546305,0.540188,0.542436,0.551845,0.546603,0.550434,0.546190,0.547576,0.545274,0.543838,0.546124,0.541724,0.545201,0.544955,0.546387,0.543691,0.535068,0.526747,0.527024,0.547880,0.547048,0.547020,0.542021,0.542740,0.538373,0.523011,0.543904,0.549519,0.539144,0.545486,0.545819,0.543880,0.550445,0.573750,0.530524,0.543684,0.592520,0.538688,

    };
#ifdef TEN_AVE
    double b[N] = {
    };
    double c[N] = {
    };
    double d[N] = {
    };
    double e[N] = {
    };
    double f[N] = {
    };
    double g[N] = {
    };
    double h[N] = {
    };
    double ii[N] = {
    };
    double j[N] = {
    };
#endif
    double ave_a = 0.0;
#ifdef TEN_AVE
    double ave_b = 0.0;
    double ave_c = 0.0;
    double ave_d = 0.0;
    double ave_e = 0.0;
    double ave_f = 0.0;
    double ave_g = 0.0;
    double ave_h = 0.0;
    double ave_i = 0.0;
    double ave_j = 0.0;
#endif

    int i;
    for (i = 0; i < N; i++)
    {
        ave_a += a[i];
        //printf("i=%d,%lf\n", i,a[i]);
#ifdef TEN_AVE
        ave_b += b[i];
        ave_c += c[i];
        ave_d += d[i];
        ave_e += e[i];
        ave_f += f[i];
        ave_g += g[i];
        ave_h += h[i];
        ave_i += ii[i];
        ave_j += j[i];

#endif
    }
    
    ave_a = ave_a / N;
    printf("%lf\n", ave_a);
    #ifdef TEN_AVE
    ave_b = ave_b / N;
    printf("%lf\n", ave_b);
    ave_c = ave_c / N;
    printf("%lf\n", ave_c);
    ave_d = ave_d / N;
    printf("%lf\n", ave_d);
    ave_e = ave_e / N;
    printf("%lf\n", ave_e);
    ave_f = ave_f / N;
    printf("%lf\n", ave_f);
    ave_g = ave_g / N;
    printf("%lf\n", ave_g);
    ave_h = ave_h / N;
    printf("%lf\n", ave_h);
    ave_i = ave_i / N;
    printf("%lf\n", ave_i);
    ave_j = ave_j / N;
    printf("%lf\n", ave_j);
    #endif
    
}