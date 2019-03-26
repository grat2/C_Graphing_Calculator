#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"
#include "parser.h"

void main() {
   char func[256];
   unsigned char i;
   double res = 0, x = 0, l= 0, r = 0;
   int cont = 1, calculus = 0, integr = 0;
   Func f;
   initFunc(&f);
   printf("Enter a function: ");
   fgets(func, 256, stdin);
   parse(func, &f);
   i = 0;
   while(f.items[i].type >= 0 || f.items[i+1].type >= 0) {
      printf("f[%d].type = %d\n", i, f.items[i].type);
      printf("f[%d].value = %f\n", i, f.items[i].value);
      i++;
   }
   while(cont) {
      printf("Calculus (1/0)? ");
      scanf("%d", &calculus);
      if(calculus) {
         printf("Integrate (1/0)?");
         scanf("%d", &integr);
         if(integr) {
            printf("Enter left bound: ");
            scanf("%lf", &l);
            printf("Enter right bound: ");
            scanf("%lf", &r);
            res = integ(f, l, r);
            printf("Integration result (%f, %f): %f", l, r, res);
         }
         else {

         }
      }
      else {
         printf("Enter x (if applicable): ");
         scanf("%lf", &x);
         printf("Result: %20g\n", calc(f, x));
      }
      printf("Continue (1/0)? ");
      scanf("%d", &cont);
   }
}