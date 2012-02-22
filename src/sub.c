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

/* This is an INTERNAL function that subtracts two numbers. It ignores the sign
 * of both operands and subtracts the unsigned value of the second from the
 * unsigned value of the first. Actual subtraction should be performed by
 * calling fp_add with an inverted sign. */
void fp_sub(fp_t *a, fp_t *b, fp_t *c, uint8_t offset[2]) {
  int i, borrow;
  int digit[2];
  
  /* NOTE: The exponent has already been set in fp_add, as well as
   *       each operand's distance relative to it computed. This is received as
   *       the parameter "offset". */
  
  /* TODO: Implement a fp_cmp function and abstract this area of code out. */
  
  /* Compare the two operands. */
  c->sgn = 0;
  for(i = 0; i < (int)(sizeof a->data * 2); ++i) {
    digit[0] = fp_getdigit(a, i - offset[0]);
    digit[1] = fp_getdigit(b, i - offset[1]);
    
    /* The first operand is larger than the second. */
    if(digit[0] > digit[1])
      break;
    
    /* The second operand is larger than the first. */
    else if(digit[0] < digit[1]) {
      c->sgn = 1;
      break;
    }
  }
  
  /* If the second operand is larger, then swap the operands to cleanly ensure
   * that there is no final borrow. Make sure to also swap the associated
   * offsets. */
  if(c->sgn) {
    uint8_t  off;
    fp_t    *f;
    
    f = b;
    b = a;
    a = f;
    
    off       = offset[0];
    offset[0] = offset[1];
    offset[1] = off;
  }
  
  /* Perform a digit-by-digit subtraction. */
  borrow = 0;
  for(i = (sizeof a->data * 2) - 1; i >= 0; --i) {
    /* Compute the digits, subtracting current borrow. */
    digit[0] = fp_getdigit(a, i - offset[0]) - borrow;
    digit[1] = fp_getdigit(b, i - offset[1]);
    
    /* If we need to borrow, do so. */
    if(digit[0] < digit[1]) {
      ++borrow;
      digit[0] += 10;
    }
    
    /* Otherwise, reset borrow. */
    else
      borrow = 0;
    
    /* Perform subtraction and set digit. */
    fp_setdigit(c, i, digit[0] - digit[1]);
  }
  
  /* Since a > b, borrow should always be zero here. */
}