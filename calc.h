#ifndef CALC_H
#define CALC_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* char type:
 * -1 = blank
 * 0 = number
 * 1 = +
 * 2 = -
 * 3 = *
 * 4 = /
 * 5 = ^
 * 6 = sin
 * 7 = cos
 * 8 = tan
 * 9 = (
 * 10 = )
 * 11 = x (variable)
 */
typedef struct {
   char type; //see list above for types
   double value; //if type is number, this holds the value of the number
   double compValue; //if type is complex, this holds the imaginary component
} CItem;

typedef struct {
   CItem items[128];
   char len;
} Func;

void initFunc(Func *f);
double calc(Func func, double x);

#endif
