#include "parser.h"

//TODO:
// - add in parentheses check
// - do more testing to make sure it works

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

void doParseCheck(char *s, int *ind, char *prev, char i, Func *ret);
int checkMultAdjacent(char *s, int ind, char prev);

//inputs: string s, Func pointer f
//parses s to fill f's item list to be calculated
void parse(char *s, Func *f) {
   unsigned char i = 0;
   int ind = 0;
   char prev = -1;
   //i -> current char index in s
   //ind -> current item index in Func list
   while(i < 128 && ind < (int)strlen(s)) {
      if(checkMultAdjacent(s, ind, prev)) {
         f->items[i].type = 3;
         prev = 3;
         i++;
      }
      doParseCheck(s, &ind, &prev, i, f);
      i++;
   }
   printf("i: %d\nind: %d\n", i, ind);
   f->len = i;
}

int checkMultAdjacent(char *s, int ind, char prev) {
   if(s[ind] == '(' || s[ind] == 'x' || s[ind] == 'X') {
      if(prev == 0 || prev == 10 || prev == 11) {
         return 1;
      }
   }
   return 0;
}

void getNextNum(char *s, int *ind, char i, Func *f);

void doParseCheck(char *s, int *ind, char *prev, char i, Func *ret) {
   char sin[5] = "asin";
   char cos[5] = "acos";
   char tan[5] = "atan";
   char pi[3] = "pi";
   char log[4] = "log";
   char ln[3] = "ln";
   char decPlace = 0, neg = 0;
   //set current function item to correct type and set item type as
   //new previous type
   if(s[*ind] == 'x' || s[*ind] == 'X') { //variable
      ret->items[i].type = 11;
      *prev = 11;
   }
   else if(s[*ind] == '+') { //addition operator
      ret->items[i].type = 1;
      *prev = 1;
   }
   else if(s[*ind] == '-') { //subtract operator
      ret->items[i].type = 2;
      *prev = 2;
   }
   else if(s[*ind] == '*') { //multiply operator
      ret->items[i].type = 3;
      *prev = 3;
   }
   else if(s[*ind] == '/') { //divide operator
      ret->items[i].type = 4;
      *prev = 4;
   }
   else if(s[*ind] == '^') { //exponent operator
      ret->items[i].type = 5;
      *prev = 5;
   }
   else if(s[*ind] >= '0' && s[*ind] <= '9' || s[*ind] == '.') { //number
      *prev = 0;
      getNextNum(s, ind, i, ret);
   }
   else if(s[*ind] == '(') { //left parenthesis 
      ret->items[i].type = 9;
      *prev = 9;
   }
   else if(s[*ind] == ')') { //right parenthesis
      ret->items[i].type = 10;
      *prev = 10;
   }
   else if(strstr(&s[*ind], &sin[1]) == &s[*ind]) { //sin
      ret->items[i].type = 6;
      *prev = 6;
      *ind += 2;
   }
   else if(strstr(&s[*ind], &cos[1]) == &s[*ind]) { //cos
      ret->items[i].type = 7;
      *prev = 7;
      *ind += 2;
   }
   else if(strstr(&s[*ind], &tan[1]) == &s[*ind]) { //tan
      ret->items[i].type = 8;
      *prev = 8;
      *ind += 2;
   }
   else if(s[*ind] == '!') { //factorial operator
      ret->items[i].type = 13;
      *prev = 13;
   }
   else if(strstr(&s[*ind], sin) == &s[*ind]) { //asin
      ret->items[i].type = 14;
      *prev = 14;
      *ind += 3;
   }
   else if(strstr(&s[*ind], cos) == &s[*ind]) { //acos
      ret->items[i].type = 15;
      *prev = 15;
      *ind += 3;
   }
   else if(strstr(&s[*ind], tan) == &s[*ind]) { //atan
      ret->items[i].type = 16;
      *prev = 16;
      *ind += 3;
   }
   else if(s[*ind] == 'e') { //constant e
      ret->items[i].type = 0;
      ret->items[i].value = M_E;
      *prev = 0;
   }
   else if(strstr(&s[*ind], pi) == &s[*ind]) { //constant pi
      ret->items[i].type = 0;
      ret->items[i].value = M_PI;
      *prev = 0;
      *ind += 1;
   }
   else if(strstr(&s[*ind], log) == &s[*ind]) { //log
      ret->items[i].type = 17;
      *prev = 17;
      *ind += 2;
   }
   else if(strstr(&s[*ind], ln) == &s[*ind]) { //ln
      ret->items[i].type = 18;
      *prev = 18;
      *ind += 1;
   }
   *ind += 1;
}

void getNextNum(char *s, int *ind, char i, Func *f) {
   double ret = 0;
   char decPlace = 0, neg = 0;
   //negative if previous item was a negative and 
   //second previous was an operator symbol, parenthesis, or nothing
   neg = (i > 1 && f->items[i-1].type == 2 && f->items[i-2].type > 0 &&
         f->items[i-2].type < 6 || f->items[i-2].type == 9);
   neg = neg || (i == 1 && f->items[i-1].type == 2);
   //while characters are digits or a decimal point, keep grabbing 
   //characters to add to number
   while(s[*ind] >= '0' && s[*ind] <= '9' || s[*ind] == '.') {
      if(s[*ind] == '.' || decPlace)
         decPlace++;
      if(decPlace > 1)
         ret += (s[*ind]-'0') * pow(10, -1*(decPlace-1));
      else if(decPlace < 1) {
         ret *= 10;
         ret += s[*ind] - '0';
      }
      *ind += 1;
   }
   f->items[i].type = 0;
   f->items[i].value = ret;
   if(neg) {
      f->items[i].value *= -1;
      f->items[i-1].type = -1;
   }
   *ind -= 1;
}

/* void main() {
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
} */
