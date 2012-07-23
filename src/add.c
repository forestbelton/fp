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
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include "fp.h"
#include "util.h"

/*
 * This function takes two normalized floating-point values and adds them
 * together to produce a normalized result and store it in the parameter c.
 * If this "addition" is actually a subtraction, it internally calls fp_sub.
 * 
 * NOTE: Eventually this function will be extended to return a result
 *       indicating the success of this function to include overflow
 *       notification, etc. */
fp_t fp_add(fp_t a, fp_t b) {
  int  i, carry;
  fp_t out;
  
  /* Determine sign of result. */
  switch((a.sgn << 1) | b.sgn) {
    /* c <- a + b = a + b    */
    case 0:
      out.sgn = 0;
    break;
    
    /* c <- a + (-b) = a - b    */
    case 1:
      b.sgn = 0;
      return fp_sub(a, b);
    break;
    
    /* c <- (-a) + b = b - a    */
    case 2:
      a.sgn = 0;
      return fp_sub(b, a);
    break;

    /* c <- (-a) + (-b) = -(a + b) */
    case 3:
      out.sgn = 1;
    break;  
  }

  /* Align (and denormalize) a and b. */
  out.expt = a.expt > b.expt ? a.expt : b.expt;
  fp_rshift(&a, out.expt - a.expt);
  fp_rshift(&b, out.expt - b.expt);
  
  /* Perform addition and adjust for carry. */
  out.data = a.data + b.data;

  carry = 0;
  for(i = FP_DIGITS - 1; i >= 0; --i) {
    uint8_t digit = fp_getdigit(&out, i) + carry;
    
    if(digit > 9) {
      digit -= 10;
      carry  = 1;
    }
    else
      carry = 0;

    fp_setdigit(&out, i, digit);
  }

  if(carry) {
    fp_rshift(&out, 1);
    fp_setdigit(&out, 0, 1);
  }

  /* Normalize sum. */
  while(!(out.data == 0 || fp_getdigit(&out, 0) != 0))
    fp_lshift(&out, 1);

  return out;
}

