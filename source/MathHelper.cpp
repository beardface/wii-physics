#include "MathHelper.h"

MathHelper::MathHelper(){}

MathHelper::~MathHelper(){}
/* ------------------------------------------------------------------------ */
/*  splakima                                                                */
/*      Calculation of a smooth curve, addopted from:                       */
/*      H. Akima, Interpolation and smooth curve fitting based on local     */
/*      procedures (algorithm 433), Communications of the ACM 15 (1972),    */
/*      no. 10, 914 -918                                                    */
/*                                                                          */
/*      Call: int splakima (mode,l,x,y,m,n,u,v)                             */
/*                                                                          */
/*      int mode    input:   1  x coordinates must be strictly ascending    */
/*                           2  arbitrary points allowed                    */
/*      int l       input:  number of data points, l >= 2                   */
/*      double *x   input:  array x(i), i = 1,l  with x coordinates         */
/*                  output: unchanged                                       */
/*      double *y   input:  array y(i), i = 1,l  with y coordinates         */
/*                  output: unchanged                                       */
/*      int m       input:  number of subintervals, m >= 2                  */
/*      int n       input:  length of the arrays u and v with               */
/*                          n = (l - 1) * m + 1                             */
/*      double *u   input:  array u(i) of length n                          */
/*                  output: contains the x coordinates of the smooth curve  */
/*      double *v   input:  array v[i] of length n                          */
/*                  output: contains the y coordinates of the smooth curve  */
/*                                                                          */
/*      Return:     0  successful                                           */
/*                 -1  error in input parameters                            */
/*                 -2  if x coordinates not increasing                      */
/*                 -3  if identical points                                  */

int MathHelper::splakima (int mode,int l,double *x,double *y,int m,int n,double *u,double *v)
{
    int i,j,md0,mdm1,l0,m0,mm1,n0,lm1,k,k5;
    double a1,a2,a3,a4,m1,m2,m3,m4,sw,w2,w3;
    double t2,t3,x2,x3,x4,x5,y2,y3,y4,y5,sin2,sin3,cos2,cos3,p1,rm;

    x5 = y5 = t3 = sin3 = cos3 = 0.0;
    md0 = mode;
    mdm1 = md0 - 1;
    l0 = l;
    lm1 = l0 - 1;
    m0 = m;
    mm1 = m0 - 1;
    n0 = n;

    if (md0 <= 0 || md0 >= 3 || lm1 <= 0 || mm1 <= 0 || n0 != (lm1 * m0 + 1))
        return(-1);

    if (md0 == 1) {
        i = 2;

        if (x[1] < x[2]) {
            for (i = 3; i <= l0; ++i) {
                if (x[i] <= x[i - 1])
                    return(-2);
            }
        }
        else if (x[1] > x[2]) {
            for (i = 3; i <= l0; ++i) {
                if (x[i] >= x[i - 1])
                    return(-2);
            }
        }
        else
            return(-2);
    }
    else {
        for (i = 2; i <= l0; ++i) {
            if (x[i - 1] == x[i] && y[i - 1] == y[i])
                return(-3);
        }
    }
    k = n0 + m0;
    i = l0 + 1;

    for (j=1; j<=l0; ++j) {
        k -= m0;
        i--;
        u[k] = x[i];
        v[k] = y[i];
    }
    rm = m0;
    rm = 1.0 / rm;
    k5 = m0 + 1;

    for (i = 1; i <= l0; ++i) {

        if (i > 1)
            goto Lab40;

        x3 = u[1];
        y3 = v[1];
        x4 = u[m0 + 1];
        y4 = v[m0 + 1];
        a3 = x4 - x3;
        m3 = y4 - y3;

        if (mdm1 == 0)
            m3 /= a3;

        if ( l0 != 2)
            goto Lab41;

        a4 = a3;
        m4 = m3;

Lab31:
        if (md0 == 2) {
            a2 = a3 + a3 - a4;
            a1 = a2 + a2 - a3;
        }
        m2 = m3 + m3 - m4;
        m1 = m2 + m2 - m3;

        if (md0 == 1)
            goto Lab51;
        else
            goto Lab56;

Lab40:
        x2 = x3;
        y2 = y3;
        x3 = x4;
        y3 = y4;
        x4 = x5;
        y4 = y5;

        a1 = a2;
        m1 = m2;
        a2 = a3;
        m2 = m3;
        a3 = a4;
        m3 = m4;

        if (i >= lm1)
            goto Lab42;

Lab41:
        k5 = k5 + m0;
        x5 = u[k5];
        y5 = v[k5];
        a4 = x5 - x4;
        m4 = y5 - y4;

        if (mdm1 == 0)
            m4 /= a4;
        goto Lab43;

Lab42:
        if (mdm1 != 0)
            a4 = a3 + a3 - a2;
        m4 = m3 + m3 - m2;

Lab43:
        if (i == 1)
            goto Lab31;
        if (md0 == 1)
            goto Lab50;
        else
            goto Lab55;

Lab50:
        t2 = t3;

Lab51:
        w2 = fabs(m4 - m3);
        w3 = fabs(m2 - m1);
        sw = w2 + w3;

        if (sw == 0.0) {
            w2 = w3 = 0.5;
            sw = 1.0;
        }
        t3 = (w2 * m2 + w3 * m3) / sw;

        if (i > 1)
            goto Lab60;
        else
            goto Lab80;

Lab55:
        cos2 = cos3;
        sin2 = sin3;

Lab56:
        w2 = fabs(a3 * m4 - a4 * m3);
        w3 = fabs(a1 * m2 - a2 * m1);

        if ((w2 + w3) != 0.0)
            goto Lab57;

        w2 = sqrt(a3 * a3 + m3 * m3);
        w3 = sqrt(a2 * a2 + m2 * m2);

Lab57:
        cos3 = w2 * a2 + w3 * a3;
        sin3 = w2 * m2 + w3 * m3;
        sw = cos3 * cos3 + sin3 * sin3;
        if (sw == 0.0)
            goto Lab58;

        sw = sqrt(sw);
        cos3 /= sw;
        sin3 /= sw;

Lab58:
        if (i > 1)
            goto Lab65;
        else
            goto Lab80;

Lab60:
        w2 = (2.0 * (m2 - t2) + m2 - t3) / a2;
        w3 = (-m2 - m2 + t2 + t3) / (a2 * a2);
        goto Lab70;

Lab65:
        sw = sqrt(a2 * a2 + m2 * m2);
        p1 = sw * cos2;
        a1 = 3.0 * a2 - sw * (cos2 + cos2 + cos3);
        m1 = a2 - p1 - a1;

        t2 = sw * sin2;
        w2 = 3.0 * m2 - sw * (sin2 + sin2 + sin3);
        w3 = m2 - t2 - w2;

        goto Lab75;

Lab70:
        a2 = a2 * rm;
        sw = 0.0;

        for (j = 1; j <= mm1; ++j) {
            k++;
            sw += a2;
            u[k] = x2 + sw;
            v[k] = y2 + sw * (t2 + sw * (w2 + sw * w3));
        }
        goto Lab79;

Lab75:
        sw = 0.0;

        for (j = 1; j <= mm1; ++j) {
            k++;
            sw += rm;
            u[k] = x2 + sw * (p1 + sw * (a1 + sw * m1));
            v[k] = y2 + sw * (t2 + sw * (w2 + sw * w3));
        }

Lab79:
        k++;
Lab80: ;
    }
    return(0);
}
