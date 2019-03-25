#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

int main() {
   Func f;
   double x;
   //x ^ ( 2 + ( x / 3 ) ) - 27
   f.items[0].type = 11;
   f.items[1].type = 5;
   f.items[2].type = 9;
   f.items[3].type = 0;
   f.items[3].value = 2.0;
   f.items[4].type = 1;
   f.items[5].type = 9;
   f.items[6].type = 11;
   f.items[7].type = 4;
   f.items[8].type = 0;
   f.items[8].value = 3;
   f.items[9].type = 10;
   f.items[10].type = 10;
   f.items[11].type = 2;
   f.items[12].type = 0;
   f.items[12].value = 27;
   f.len = 13;
   printf("Enter x: ");
   scanf("%lf", &x);
   printf("Calc: ");
   printf("%g\n", calc(f, x));
   return 0;
}
