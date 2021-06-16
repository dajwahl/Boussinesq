/* Closed-form solution for " A rectangular loading on a surface of an elastic
   semi-infinite mass"
   Output: A file, "bouss_out.txt" containing the stresses
   The following data should be input by user:
   p = Value of uniform rectangular load (load/unit area)
   b = Length of the side along x-axis of rectangular footing
   l = Length of the side along y-axis of rectangular footing
   z1 = Starting depth of calculations
   z2 = Ending depth of calculations
   dz = Increment for depth calculations
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi (3.14159265359)

double bouss_rect (double, double, double, double);
FILE * file_open(char name[], char access_mode[]);

int main()
{
  FILE *outC;
  outC = file_open("bouss_out.txt", "w");
  
   printf("\n\n");
   printf("                                      RECT - ELASTIC                                                   \n\n\n");
   printf(".......................................................................................................\n");
   printf(". Program to calculate closed-form solution for uniform rectangular load over infinite elastic medium .\n");
   printf(". Input should be in consistent units (i.e. SI or imperial)                                           .\n");
   printf(". Calculations will start from initial depth below corner of rectangle and proceed incrementally down .\n");
   printf(". to ending depth                                                                                     .\n");
   printf(".......................................................................................................\n\n\n");
   printf("Based on code from verification manual for Phase2 version 2.1 by Rocscience - 1999\n");
   printf("Modified by Doug Wahl, 2014\n\n\n");

  double p,z1,z2,dz,b,l,m,n,v,v1,I0,sigmaz;
  printf("Value of uniform rectangular load (load/unit area) - use consistent units: ");
  scanf("%lf",&p);
  printf("Starting depth of calculations: ");
  scanf("%lf",&z1);
  printf("Ending depth of calculations: ");
  scanf("%lf",&z2);
  printf("Increment for depth calculations: ");
  scanf("%lf",&dz);
  printf("Width of footing: ");
  scanf("%lf",&b);
  printf("Width of footing: ");
  scanf("%lf",&l);
  
  while (z1 < z2)
  {
    z1 = z1 + dz;
    m = b/z1;
    n = l/z1;
    v = m*m+n*n+1;
    v1 = m*m*n*n;
    I0 = bouss_rect(m,n,v,v1);
    sigmaz = I0*p;
    printf("%f %f %f %f %f %f %f %f %f %f\n",p,z1,b,l,m,n,v,v1,I0,sigmaz);
    fprintf(outC,"%f %f %f %f %f %f %f %f %f %f\n",p,z1,b,l,m,n,v,v1,I0,sigmaz);
  }
  return 0;
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

/* function returning the Boussinesq influence factor for point beneath corner of uniform rectangular load */

double bouss_rect(double m, double n, double v, double v1)
{
  double I_value = 1.0;
  double A,B,C,D,E;
  
  A = 1/(4*pi);
  B = (2*m*n*sqrt(v))/(v+v1);
  C = (v+1)/v;
  D = atan((2*m*n*sqrt(v))/(v-v1))+pi;
  E = atan((2*m*n*sqrt(v))/(v-v1));
      
  if (v < v1)
    I_value = A*(B*C+D);
  else
    I_value = A*(B*C+E);
  
  return I_value;
}
