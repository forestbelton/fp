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

static fp_t QUOT_NUMERATOR[6] = {
  {0, 0x80, {0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {0, 0x82, {0x22, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {0, 0x82, {0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {1, 0x82, {0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {1, 0x82, {0x22, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {1, 0x80, {0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}} 
};

static fp_t QUOT_DENOMINATOR[5] = {
  {0, 0x81, {0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {0, 0x82, {0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {0, 0x82, {0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {0, 0x81, {0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {0, 0x81, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
};

/* Computes log(x) and stores the result in out.
 * The current method of computation is as follows:
 * 1) Separate x into the form y * 10^n, where 1 <= y < 10.
 * 2) Approximate log(y) using Boole's rule to compute \int_1^y 1/x dx.
 * 3) Compute log(10^n) via n * log(10).
 * 4) Since log(ab) = log(a) + log(b), compute final result by:
 *    log(y) + n log(10).
 */
void fp_log(fp_t *x, fp_t *out) {
  fp_t num, div, tmp;
  
  /* Extract the fractional part of x. */
  tmp      = *x;
  tmp.expt = 0x80;
  
  /* Compute the quotient approximation of frac(x) */
  fp_poly(QUOT_NUMERATOR, sizeof QUOT_NUMERATOR / sizeof QUOT_NUMERATOR[0], &tmp, &num);
  fp_poly(QUOT_DENOMINATOR, sizeof QUOT_DENOMINATOR / sizeof QUOT_DENOMINATOR[0], &tmp, &div);
  
  /* Compute the quotient. */
  fp_div(&num, &div, &tmp);
  
  /* TODO: Rest. */
}

