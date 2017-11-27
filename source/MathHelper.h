#ifndef _MathHelper_H_
#define _MathHelper_H_

#include <math.h>

class MathHelper {
	public:
		MathHelper();
		~MathHelper();
		
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

		int splakima (int mode,int l,double *x,double *y,int m,int n,double *u,double *v);
};

#endif //_MathHelper_H_
