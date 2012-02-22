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
#include "fp.h"
#include "util.h"

void fp_mul(fp_t *a, fp_t *b, fp_t *c) {
  int i, j, p;
  uint8_t prod[FP_DIGITS * 2] = {0};
  
  /* compute intermediary product */
  for(i = sizeof a->data * 2 - 1; i >= 0; --i) {
    for(j = sizeof a->data * 2 - 1; j >= 0; --j) {
      /* compute digit product */
      p = fp_getdigit(a, i) * fp_getdigit(b, j);
      
      /* skip if the product is zero */
      if(!p)
        continue;
      
      /* add it to partial product sum */
      prod[i + j + 1] += p % 10;
      prod[i + j]     += p / 10;
    }
  }
  
  /* fix carry */
  for(i = sizeof prod - 1; i > 0; --i) {
    while(prod[i] > 9) {
      prod[i] -= 10;
      ++prod[i - 1];
    }
  }
  
  /* compute sign */
  c->sgn = a->sgn ^ b->sgn;
  
  /* compute exponent */
  i = prod[0] == 0;
  c->expt = a->expt + b->expt - 0x80 + !i;
  
  /* copy shifted fractional part */
  for(j = 0; j < (int)(sizeof a->data * 2); ++j)
    fp_setdigit(c, j, prod[i++]);
}
