/* Closed-form solution for "A point loading on a surface of an elastic
   semi-infinite mass"
   Returns the value of the vertical boussinesq influence factor for a
   point load at the surface.
   The parameters passed to the function are:
   x = distance #1 in xy plane from point load to point of calculation
   y = distance #2 in xy plane from point load to point of calculation
   z = depth below ground surface
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi (3.14159265359)

double bouss_point(double x, double y, double z);
FILE * file_open(char name[], char access_mode[]);

int main()
{
   double x,y,z1,z2,dz,I0,sigmaz,p;
   FILE *outC;
   outC = file_open("bouss_point_out.dat", "w");

   printf("\n\n");
   printf("                                      POINT - ELASTIC                                            \n\n\n");
   printf(".................................................................................................\n");
   printf(". Program to calculate closed-form solution for point load over infinite elastic medium         .\n");
   printf(". Input should be in consistent units (i.e. SI or imperial)                                     .\n");
   printf(". Input location of load and x and y location of calculation point                              .\n");
   printf(". Input top, bottom, and vertical increment of calculation points                               .\n");
   printf(". Creates output file 'bouss_point_out.dat' with calculated I0 values at (x,y) from z1 to z2    .\n");
   printf(".................................................................................................\n\n\n");
   printf("Based on code from verification manual for Phase2 version 2.1 by Rocscience - 1999\n");
   printf("Modified by Doug Wahl, 2014\n\n\n");

   printf("Value of uniform strip load (load/unit area) - use consistent units:\n");
   scanf("%lf",&p);
   printf("X coordinate of calculation point:\n");
   scanf("%lf",&x);
   printf("Y coordinate of calculation point:\n");
   scanf("%lf",&y);
   printf("Top of calculation points:\n");
   scanf("%lf",&z1);
   printf("Bottom of calculation points:\n");
   scanf("%lf",&z2);
   printf("Vertical increment of calculation points:\n");
   scanf("%lf",&dz);

   while (z1 < z2)
    {
      z1 = z1 + dz;
      I0 = bouss_point(x,y,z1);
      sigmaz = I0*p;
      printf("%f %f %f %f %f %f\n",p,x,y,z1,I0,sigmaz);
      fprintf(outC,"%f %f %f %f %f %f\n",p,x,y,z1,I0,sigmaz);
    }
    fclose(outC);
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

/* function returning the vertial Boussinesq influence factor for a surficial point load */

double bouss_point(double x, double y, double z)
{
  double I_value = 1.0;
  double r,R;
  r = sqrt(x*x + y*y);
  R = sqrt(sqrt(r*r)+z*z);
  I_value = 3*z*z*z/(2*pi*R*R*R*R*R);

  return I_value;
}
