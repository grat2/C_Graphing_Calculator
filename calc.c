#include "calc.h"
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
 * 12 = complex
 * 13 = !
 * 14 = asin
 * 15 = acos
 * 16 = atan
 * 17 = log
 * 18 = ln
 */

void initFunc(Func *f) {
   char i;
   for(i = 0; (i < 128 && i >= 0); i++) {
      f->items[i].type = -1;
      f->items[i].value = 0;
      f->items[i].compValue = 0;
   }
   f->len = 0;
}

Func setFuncX(Func func, double x);
Func doParCheck(Func func);
Func doFuncCheck(Func func, char t);
Func doOpCheck(Func func, char t);
char findOperand(Func func, char i, char lr);

/* takes in function as a Func structure and calculates result
 * returns double
 */
double calc(Func func, double x) {
   char i; //temp index for "for" loops

   //set x in function
   func = setFuncX(func, x);
   //carry out PEMDAS
   //check parentheses
   func = doParCheck(func);
   
   //check functions (sin, cos, factorial, etc.)
   for(i = 6; i <= 8; i++) { //sin, cos, tan
      func = doFuncCheck(func, i);
   }
   for(i = 13; i <= 18; i++) { //factorial, asin, acos, atan, log, ln
      func = doFuncCheck(func, i);
   }

   //check operations (exponent, multiplicaiton/division, etc.)
   for(i = 5; i > 0; i--) {
      //printf("i: %d\n", i);
      func = doOpCheck(func, i);
   }

   return func.items[0].value;
}

Func doFuncCalc(Func func, char i, char l, char r, char t);

Func doFuncCheck(Func func, char t) {
   char i, o, l, r; //temp index, operand index, left operand, right operand indices
   for(i = 0; i < func.len; i++) {
      if(func.items[i].type == t) {
         l = findOperand(func, i, 1);
         r = findOperand(func, i, 0);
         func = doFuncCalc(func, i, l, r, t);
      }
   }
   return func;
}

double factorial(double n);

Func doFuncCalc(Func func, char i, char l, char r, char t) {
   switch(t) {
      case 6: //sin
         func.items[i].type = 0;
         func.items[i].value = sin(func.items[r].value);
         func.items[r].type = -1;
         break;
      case 7: //cos
         func.items[i].type = 0;
         func.items[i].value = cos(func.items[r].value);
         func.items[r].type = -1;
         break;
      case 8: //tan
         func.items[i].type = 0;
         func.items[i].value = tan(func.items[r].value);
         func.items[r].type = -1;
         break;
      case 13: //factorial
         func.items[l].type = 0;
         func.items[l].value = factorial(func.items[l].value);
         func.items[i].type = -1;
         break;
      case 14: //asin
         func.items[i].type = 0;
         func.items[i].value = asin(func.items[r].value);
         func.items[r].type = -1;
         break;
      case 15: //acos
         func.items[i].type = 0;
         func.items[i].value = acos(func.items[r].value);
         func.items[r].type = -1;
         break;
      case 16: //atan
         func.items[i].type = 0;
         func.items[i].value = atan(func.items[r].value);
         func.items[r].type = -1;
         break;
      case 17: //log
         func.items[i].type = 0;
         func.items[i].value = log10(func.items[r].value);
         func.items[r].type = -1;
         break;
      case 18: //ln
         func.items[i].type = 0;
         func.items[i].value = log(func.items[r].value);
         func.items[r].type = -1;
         break;
   }
   return func;
}

double factorial(double n) {
   //this basically checks n to see if the numbers past the decimal point equal
   //zero since I use a double as the input lol
   if((n - (int)n) > 0 || n < 0) {
      return 0;
   }
   else if(n > 1) {
      return ((int)n * factorial((int)(n-1)));
   }
   return 1;
}

Func doOpCalc(Func func, char i, char l, char r, char t);
Func doExpCheck(Func func);
Func doMultCheck(Func func);

Func doOpCheck(Func func, char t) {
   char i, l, r; //temp index, left & right operand indices
   for(i = 0; i < func.len; i++) {
      //printf("type: %d\n", func.items[i].type);
      if(func.items[i].type == t) {
         l = findOperand(func, i, 1);
         r = findOperand(func, i, 0);
         func = doOpCalc(func, i, l, r, t);
      }
   }
   return func;
}

Func doOpCalc(Func func, char i, char l, char r, char t) {
   switch (t) {
      case 5: //exponent
         //printf("exponent\n");
         func.items[l].value = pow(func.items[l].value, func.items[r].value);
         break;
      case 4: //division
         //printf("division\n");
         func.items[l].value /= func.items[r].value;
         break;
      case 3: //multiplication
         //printf("multiplication\n");
         func.items[l].value *= func.items[r].value;
         break;
      case 2: //subtraction
         //printf("subtraction\n");
         func.items[l].value -= func.items[r].value;
         break;
      case 1: //addition
         //printf("addition\n");
         func.items[l].value += func.items[r].value;
         break;
   }
   func.items[i].type = -1;
   func.items[r].type = -1;
   return func;
}

char findOperand(Func func, char i, char lr) {
   char ret;
   (lr) ? (ret = i-1) : (ret = i+1);
   while(func.items[ret].type == -1 && ret >= 0 && ret < func.len) {
      (lr) ? (ret--) : (ret++);
   }
   if(func.items[ret].type != 0)
      return -1;
   else
      return ret;
}

Func setFuncX(Func func, double x) {
   char i;
   for(i = 0; i < func.len; i++) {
      if(func.items[i].type == 11) {
         func.items[i].value = x;
         func.items[i].type = 0;
      }
   }
   return func;
}

Func getTFunc(Func func, char lP, char rP);
Func setNewFunc(Func func, char lP, char rP, double res);

Func doParCheck(Func func) {
   char i, lP = -1, rP = -1, layer = 0;
   Func tFunc;
   double tRes;
   //find outermost parentheses groups
   for(i = 0; i < func.len; i++) {
      if(func.items[i].type == 9) { //left parenthesis found
         (lP >= 0) ? (lP = lP) : (lP = i); //set initial lP
         layer++;
         //printf("lP: %d\n", lP);
      }
      else if(func.items[i].type == 10) { //right parenthesis found
         layer--;
         (layer == 0) ? (rP = i) : (rP = rP); //found last right parenthesis
         //printf("rP: %d\n", rP);
      }
      if(rP > 0) { //found parentheses group, calculate inside
         tFunc = getTFunc(func, lP, rP);
         tRes = calc(tFunc, 0);
         //printf("Par res: %f\n", tRes);
         func = setNewFunc(func, lP, rP, tRes);
         lP = -1;
         rP = -1;
         i = 0;
      }
   } 
   return func;
}

Func getTFunc(Func func, char lP, char rP) {
   char i;
   for(i = lP+1; i < func.len; i++) {
      if(i < rP) {
         func.items[i-(lP+1)].type = func.items[i].type;
         func.items[i-(lP+1)].value = func.items[i].value;
      }
      func.items[i].type = -1;
   }
   func.len = rP-lP-1;
   return func;
}

Func setNewFunc(Func func, char lP, char rP, double res) {
   char i;
   func.items[lP].type = 0;
   func.items[lP].value = res;
   for(i = lP+1; i <= rP; i++) {
      func.items[i].type = -1;
   }
   for(i = 0; i < func.len; i++) {
      //printf("func.items[%d].type = %d\n", i, func.items[i].type);
   }
   return func;
}
