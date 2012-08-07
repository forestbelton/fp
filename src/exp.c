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
#include "fp/fp.h"

/* This function uses Newton's method to compute exp(x). Since
 * f(x) = log(x) - a has a zero at exp(a), we obtain
 * x_{n+1} = x_n (1 + a - log(x_n)). 1 + a is precomputed, reducing the
 * iterative step to x_{n+1} = x_n (b - log(x_n)).
 */
fp_t fp_exp(fp_t x) {
  fp_t guess, new;
  
  /* TODO: Use a better guess. */
  x = fp_add(%FP(1.0), x);
  new = %FP(1.0);

  do {
    guess = new;
    new   = fp_mul(new, fp_sub(x, fp_log(new)));
  } while(guess.data != new.data);

  return guess;
}

