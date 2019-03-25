#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"
#include "parser.h"

void main() {
   char func[256];
   unsigned char i;
   double res = 0, x = 0;
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
   while(x != -1.0) {
      printf("Enter x (if applicable): ");
      scanf("%lf", &x);
      printf("Result: %20g\n", calc(f, x));
   }
}