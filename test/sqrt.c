/* Copyright (c) 2012 Forest Belton (apples)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <math.h>
#undef FP_ZERO
#include <stdio.h>
#include <stdlib.h>

#include "fp.h"

float mkfloat(void) {
  float f = (float)rand() / RAND_MAX;
  return f * 1000;
}

void do_test(void) {
  fp_t  x;
  float f = mkfloat();
  char  buf[20];

  sprintf(buf, "%f", f);
  x = fp_fromstr(buf);

  printf("float: sqrt(%f) = %f\n", f, sqrt(f));

  fp_tostr(x, buf);
  printf("fp_t:  sqrt(%s) = ", buf);
  x = fp_sqrt(x);
  fp_tostr(x, buf);
  printf("%s\n", buf);
}

int main() {
  int i;

  for(i = 0; i < 10; ++i)
    do_test();

  return 0;
}
