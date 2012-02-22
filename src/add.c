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
#include <stdint.h>
#include "fp.h"
#include "util.h"

/* Prototype for the internal fp_sub function. */
void fp_sub(fp_t *a, fp_t *b, fp_t *c, uint8_t offset[2]);

/*
 * This function takes two normalized floating-point values and adds them
 * together to produce a normalized result and store it in the parameter c.
 * If this "addition" is actually a subtraction, it internally calls fp_sub.
 * 
 * NOTE: Eventually this function will be extended to return a result
 *       indicating the success of this function to include overflow
 *       notification, etc. */
void fp_add(fp_t *a, fp_t *b, fp_t *c) {
  int     i;
  uint8_t tmp, carry;
  uint8_t offset[2];
  
  /* Use the larger of the two exponents and compute the distance between
   * it and a->expt, b->expt. These offsets are used to simulate the adjustment
   * of a and b to have the same exponent without performing the actual
   * operation. This means that a and b don't have to be clobbered, duplicated
   * on the stack, etc. and generally saves having to iterate through the
   * fractional component of their data. */
  c->expt   = a->expt > b->expt ? a->expt : b->expt;
  offset[0] = c->expt - a->expt;
  offset[1] = c->expt - b->expt;
  
  /* Determine sign of result. */
  switch((a->sgn << 1) | b->sgn) {
    /* c <- a + b = a + b    */
    case 0:
      c->sgn = 0;
    break;
    
    /* c <- a + (-b) = a - b    */
    case 1:
      fp_sub(a, b, c, offset);
    return;
    
    /* c <- (-a) + b = b - a    */
    case 2:
      tmp       = offset[0];
      offset[0] = offset[1];
      offset[1] = tmp;
      fp_sub(b, a, c, offset);
    return;
    
    /* c <- (-a) + (-b) = -(a + b) */
    case 3:
      c->sgn = 1;
    break;  
  }
  
  carry = 0;
  for(i = (sizeof a->data * 2) - 1; i >= 0; --i) {
    /* Compute digit sum using the simulated shifting. */
    tmp = fp_getdigit(a, i - offset[0]) + fp_getdigit(b, i - offset[1]) + carry;
    
    /* Compute new carry and optionally adjust the sum digit. */
    carry = tmp > 9;
    if(carry)
      tmp -= 10;
    
    /* Update c with result. */
    fp_setdigit(c, i, tmp);
  }
  
  /* If we still have carry, then this means that we are done performing
   * normalization after done shifting once. Then set the topmost digit to
   * 1, the carry value. */
  if(carry) {
    fp_rshift(c, 1);
    fp_setdigit(c, 0, 1);
  }
  
  /* Shift to the left until we have a leading nonzero digit. The value
   * will then be normalized. Make sure shifting does not continue on
   * forever due to a sum of zero. */
  else {
    for(i = 0; i < (int)(sizeof a->data * 2); ++i) {
      if(a->data[0] >> 4) break;
      fp_lshift(c, 1);
    }
  }
}
