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
#include "fp/util.h"
#include <stddef.h>

/* A 7th-order polynomial approximation to 1/x on [0.1, 1]. The following
 * function was used, a result of Remez' algorithm used with Chebyshev points
 * along the desired interval.
 * 
 * 27.6372 - 299.449 x + 1664.01 x^2 - 5234.2 x^3 + 9658.57 x^4 - 10332.7 x^5 +
 * 5921.74 x^6 - 1404.62 x^7 */

static fp_t SEPTIC_COEFFICIENTS[8] = {
  %FP_CONST(-1404.62),
  %FP_CONST(5921.74),
  %FP_CONST(-10332.7),
  %FP_CONST(9658.57),
  %FP_CONST(-5234.2),
  %FP_CONST(1664.01),
  %FP_CONST(-299.449),
  %FP_CONST(27.6372)
};

fp_t fp_div(fp_t a, fp_t b) {
  fp_t tmp, out, old;
  
  /* Scale quotient. */
  a.expt = a.expt - b.expt + 0x80 - 1;
  b.expt = 0x7f;
  
  /* Compute guess. out ~= 1 / b*/
  out = fp_poly(SEPTIC_COEFFICIENTS, sizeof SEPTIC_COEFFICIENTS / sizeof SEPTIC_COEFFICIENTS[0], b);
  
  /* Do a few steps of Newton-Raphson iteration. */
  do {
    old = out;
    tmp = fp_mul(b, out);
    tmp = fp_sub(%FP(2.0), tmp);
    out = fp_mul(tmp, out);
  } while(out.data != old.data);
  
  /* Compute quotient based on (hopefully) good reciprocal approximation. */
  out = fp_mul(out, a);
  return out;
}
