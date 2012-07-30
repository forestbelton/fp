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

static fp_t QUOT_NUMERATOR[6] = {
  %FP(137.0),
  %FP(1625.0),
  %FP(2000.0),
  %FP(-2000.0),
  %FP(-1625.0),
  %FP(-137.0)
};

static fp_t QUOT_DENOMINATOR[6] = {
  %FP(30.0),
  %FP(750.0),
  %FP(3000.0),
  %FP(3000.0),
  %FP(750.0),
  %FP(30.0)
};

/* Computes log(x) and stores the result in out.
 * The current method of computation is as follows:
 * 1) Separate x into the form y * 10^n, where 1 <= y < 10.
 * 2) Approximate log(y) using a 5/5 Pade approximant.
 * 3) Compute log(10^n) via n * log(10).
 * 4) Since log(ab) = log(a) + log(b), compute final result by:
 *    log(y) + n log(10).
 */
fp_t fp_log(fp_t x) {
  fp_t num, div, tmp, p10;
  
  /* Extract the fractional part of x. */
  tmp      = x;
  tmp.expt = 0x7f;
  
  /* Compute the quotient approximation of frac(x) */
  num = fp_poly(QUOT_NUMERATOR, sizeof QUOT_NUMERATOR / sizeof QUOT_NUMERATOR[0], tmp);
  div = fp_poly(QUOT_DENOMINATOR, sizeof QUOT_DENOMINATOR / sizeof QUOT_DENOMINATOR[0], tmp);
  
  /* Compute the quotient. */
  tmp = fp_div(num, div);
  
  p10 = fp_fromint(x.expt - 0x7f);
  p10 = fp_mul(p10, FP_LOG10);
  
  tmp = fp_add(tmp, p10);
  return tmp;
}

