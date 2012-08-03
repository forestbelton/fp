#include <fp/fp.h>
#include <stdio.h>

fp_t fp_fac(unsigned int n) {
  fp_t x = %FP(1.0);
  
  while(n > 0) {
    x = fp_mul(fp_fromint(n), x);
    --n;
  }
  
  return x;
}

int main() {
  int  i;
  fp_t x;
  char buf[20];
  
  for(i = 0; i <= 10; ++i) {
    x = fp_fac(i);
    fp_tostr(x, buf);
    
    printf("10! = %s\n", buf);
  }
  
  return 0;
}

