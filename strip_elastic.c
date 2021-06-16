/* Closed-form solution for " A strip loading on a surface of an elastic
   semi-infinite mass"
   Output: A file, "strip_elas_out.dat" containing the stresses
   The following data should be input by user
   p = Value of uniform strip load (load/unit area)
   b = Half length of the strip footing
   rx0= X coordinate of Initial point
   ry0= Y coordinate of Initial point
   rx = Length of stress grid in X Direction from initial point
   ry = Length of stress grid in Y Direction from initial point
   nx = Number of points in X direction where the values should be calculated
   ny = Number of points in Y direction where the values should be calculated
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi (3.14159265359)
FILE * file_open(char name[], char access_mode[]);
main()
{
   int nx,ny,i,j;
   double b,p,ppi,rx,ry,d1,d2,d3,d4,d5,rx0,ry0,x,y,x1,x2,thta1;
   double alpha,delta,sigmax,sigmay,tauxy,sigma3,sigma1,sigma2,tau,I1,I2,I3;
   FILE *outC;
   outC = file_open("strip_elas_out.dat", "w");

   printf("\n\n");
   printf("                                      STRIP - ELASTIC                                            \n\n\n");
   printf(".................................................................................................\n");
   printf(". Program to calculate closed-form solution for uniform strip load over infinite elastic medium .\n");
   printf(". Input should be in consistent units (i.e. SI or imperial)                                     .\n");
   printf(". X points will start from initial point and divide grid into equal intervals                   .\n");
   printf(". Y points will start from initial point plus one equal grid interval                           .\n");
   printf(".................................................................................................\n\n\n");
   printf("Based on code from verification manual for Phase2 version 2.1 by Rocscience - 1999\n");
   printf("Modified by Doug Wahl, 2014\n\n\n");
   
   printf("Value of uniform strip load (load/unit area) - use consistent units:\n");
   scanf("%lf",&p);
   printf("Half length of the strip footing:\n");
   scanf("%lf",&b);
   printf("X coordinate of Initial point:\n");
   scanf("%lf",&rx0);
   printf("Y coordinate of Initial point:\n");
   scanf("%lf",&ry0);
   printf("Length of stress grid in X Direction:\n");
   scanf("%lf",&rx);
   printf("Length of stress grid in Y Direction:\n");
   scanf("%lf",&ry);
   printf("Number of points in X direction:\n");
   scanf("%d",&nx);
   printf("Number of points in Y direction:\n");
   scanf("%d",&ny);
/*
   p = 1.0;
   b = 1.0;
   rx0= 0.0;
   ry0= 0.0;
   rx = 0.0;
   ry = 5.0;
   nx = 1;
   ny = 100;
*/
   fprintf(outC," Uniform strip load : %14.7e\n",p);
   fprintf(outC," Half length of the strip : %14.7e\n",b);
   fprintf(outC," X coordinate of Initial point : %14.7e\n",rx0);
   fprintf(outC," Y coordinate of Initial point : %14.7e\n",ry0);
   fprintf(outC," Length of stress grid in X Dir: %14.7e\n",rx);
   fprintf(outC," Length of stress grid in Y Dir: %14.7e\n",ry);
   fprintf(outC," Number of points in X Dir : %5d\n",nx);
   fprintf(outC," Number of points in Y Dir : %5d\n\n",ny);
   fprintf(outC," Ni Nj x y sigma1");
   fprintf(outC," sigma3 taumax sigma1/p sigma3/p tau/p \n\n");
   d4=0.0;
   d5=0.0;
   ppi=-p/pi;
   if(nx>1)d4=rx/(nx-1);
   if(ny>1)d5=ry/(ny);
for(i=0; i<nx; i++)
  { x=rx0+d4*(i);
    for(j=0; j<ny; j++)
      { y=ry0+d5*(j+1);
        x1=x+b;
        x2=x-b;
        thta1=atan2(y,x1);
        delta=atan2(y,x2);
        alpha=thta1-delta;
        d1=sin(alpha);
        d2=cos(alpha+2.*delta);
        d3=sin(alpha+2.*delta);
        sigmax=ppi*(alpha-d1*d2);
        sigmay=ppi*(alpha+d1*d2);
        tauxy=ppi*d1*d3;
        sigma1=ppi*(alpha+d1);
        sigma3=ppi*(alpha-d1);
        tau=ppi*d1;
        I1=sigma1/p;
        I2=sigma3/p;
        I3=tau/p;
  fprintf(outC,"%4d%4d %11.4e %11.4e %11.4e %11.4e %11.4e %11.4e %11.4e %11.4e\n",
               (i+1),(j+1),x,y,sigma1,sigma3,tau,I1,I2,I3);
      }
    }
     fclose(outC);
  }
FILE * file_open (char name[], char access_mode[])
{
FILE * f;
    f = fopen (name, access_mode);
    if (f == NULL) { /* error? */
    perror ("Cannot open file");
    exit (1);
    }
    return f;
}
