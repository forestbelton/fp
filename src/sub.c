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

fp_t fp_sub(fp_t a, fp_t b) {
  int     i, j;
  uint8_t minuend[sizeof a.data * 2];
  uint8_t offset[2];
  fp_t    out;
  
  /* TODO: Examine sign. */
  
  /* Compute displacement offsets. */
  out.expt  = a.expt > b.expt ? a.expt : b.expt;
  offset[0] = out.expt - a.expt;
  offset[1] = out.expt - b.expt;

  /* If b > a, flip the sign. */
  out.sgn = 0;
  for(i = 0; i < (int)(sizeof a.data * 2); ++i) {
    uint8_t digit[2];

    digit[0] = fp_getdigit(&a, i - offset[0]);
    digit[1] = fp_getdigit(&b, i - offset[1]);
    
    /* The first operand is larger than the second. */
    if(digit[0] > digit[1])
      break;
    
    /* The second operand is larger than the first. */
    else if(digit[0] < digit[1]) {
      out.sgn = 1;
      break;
    }
  }
  
  /* Switch the operands to ensure a > b. This just relies on the fact that
   * a - b = -(b - a). */
  if(out.sgn == 1) {
    fp_t    t;
    uint8_t off;

    t = a;
    a = b;
    b = t;

    off       = offset[0];
    offset[0] = offset[1];
    offset[1] = off;
  }

  /* Compute extended minuend. */
  for(i = sizeof a.data * 2 - 1; i >= 0; --i)
    minuend[i] = fp_getdigit(&a, i - offset[0]);
  
  /* Adjust for borrow. */
  for(i = sizeof a.data * 2 - 1; i >= 0; --i) {
    uint8_t subtrahend = fp_getdigit(&b, i - offset[1]);
    j = i - 1;
    
    while(minuend[i] < subtrahend) {
      if(minuend[j] > 0) {
        minuend[j]     -= 1;
        minuend[j + 1] += 10;
        j = j + 1;
      }
      else
      	j = j - 1;
    }
  }

  /* Perform computation. */
  for(i = sizeof a.data * 2 - 1; i >= 0; --i)
    fp_setdigit(&out, i, minuend[i] - fp_getdigit(&b, i - offset[1]));
  
  /* Normalize the difference. */
  for(i = 0; i < (int)(sizeof out.data * 2); ++i) {
    if(out.data[0] >> 4) break;
    fp_lshift(&out, 1);
  }

  return out;
}

