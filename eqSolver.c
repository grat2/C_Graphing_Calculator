#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int isInt(double num) {
   int temp = (int)num;
   //printf("%d, %f\n", temp, num);
   if(num-(double)temp == 0) {
      return 1;
   }
   return 0;
}

void main() {
   double a, b, c, d;
   for(a = -30; a <= 30; a += 0.01) {
      for(b = -30; b <= 30; b += 0.01) {
         for(c = -30; c <= 30; c += 0.01) {
            for(d = -30; d <= 30; d += 0.01) {
               /* if(isInt(d) && (int)d % 10 == 0)
                  printf("d = %f\n", d); */
            }
            if(isInt(c) && (int)c % 10 == 0)
               printf("c = %f\n", c);
         }
         if(isInt(b) && (int)b % 10 == 0)
            printf("b = %f\n", b);
      }
      if(isInt(a) && (int)a % 10 == 0)
         printf("a = %f\n", a);
   }
}
