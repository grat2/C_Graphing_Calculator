#ifndef INTEDERI_H
#define INTEDERI_H

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "calc.h"

double integ(Func func, double l, double u);
double simpsons_rule(Func func, double l, double u);
double recursive_asr(Func func, double l, double u, double whole, double error);

#endif
