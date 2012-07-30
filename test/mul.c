#include <stdio.h>
#include "fp/fp.h"

int main() {
  fp_t a = fp_fromstr("193.052");
  fp_t b = fp_fromstr("38345.29");
  
  fp_t c = fp_mul(a, b);
  printf("{0x%02x, 0x%02x, 0x%08x%08x}\n", a.sgn, a.expt, (uint32_t)(a.data >> 32), (uint32_t)a.data);
  printf("{0x%02x, 0x%02x, 0x%08x%08x}\n", b.sgn, b.expt, (uint32_t)(b.data >> 32), (uint32_t)b.data);
  printf("{0x%02x, 0x%02x, 0x%08x%08x}\n", c.sgn, c.expt, (uint32_t)(c.data >> 32), (uint32_t)c.data);

  return 0;
}

