#include "InteDeri.h"

/* takes in function as an array of items, lower bound, and upper bound and
 * calculates integral using simpson's rule
 */
double integ(Func func, double l, double u) {
   return recursive_asr(func, l, u, simpsons_rule(func, l, u), 0.00000000001);
}

/* Simpsons rule function for integral approximation
 * input: function, lower & upper bounds
 * output: double
 */
double simpsons_rule(Func func, double l, double u) {
   double mid, h;
   mid = (l+u)/2.0;
   h = (u-l)/6.0;
   return h*(calc(func, l) + 4*calc(func, mid) + calc(func, u));
}

/* Recursive adaptive simpsons rule function for integral approximation
 * input: function, lower & upper bounds, simpsons rule approximation across
 *    entire interval (upper - lower)
 * output: double
 */
double recursive_asr(Func func, double l, double u, double whole, double error) {
   double mid, left, right;
   mid = (l+u)/2.0;
   left = simpsons_rule(func, l, mid);
   right = simpsons_rule(func, mid, u);
   if(abs(left+right-whole) <= 15*error)
      return (left+right+(left+right-whole)/15);
   else
      return recursive_asr(func, l, mid, left, error) +
         recursive_asr(func, mid, u, right, error);
}

/* takes in function as an array of items and x value and calculates derivative
 * using approximation */
double deriv(Func func, double x) {
   double res = (calc(func, x+0.0000000001) - calc(func, x-0.0000000001));
   return res/0.0000000002;
}

/* void main() {
   char func[256];
   unsigned char i;
   int id = 0;
   double res = 0, l = 0, r = 0;
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
   while(l != -1 || r != -1) {
      printf("Integrate/derive (0/1)? ");
      scanf("%d", &id);
      if(id) {
         printf("Derivation: \n");
         printf("Enter x: ");
         scanf("%lf", &l);
         res = deriv(f, l);
         printf("Result from x=%f: %f\n", l, res);
      }
      else {
         printf("Integration: \n");
         printf("Enter left bound: ");
         scanf("%lf", &l);
         printf("Enter right bound: ");
         scanf("%lf", &r);
         res = integ(f, l, r);
         printf("Result from (%f, %f): %f\n", l, r, res);
      }
   }
} */
