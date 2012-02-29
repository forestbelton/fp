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
#include <stddef.h>

/* A 7th-order polynomial approximation to 1/x on [0.1, 1]. The following
 * function was used, a result of Remez' algorithm used with Chebyshev points
 * along the desired interval.
 * 
 * 27.6372 - 299.449 x + 1664.01 x^2 - 5234.2 x^3 + 9658.57 x^4 - 10332.7 x^5 +
 * 5921.74 x^6 - 1404.62 x^7 */

static fp_t SEPTIC_COEFFICIENTS[8] = {
  {1, 0x83, {0x14, 0x04, 0x62, 0x00, 0x00, 0x00, 0x00}},
  {0, 0x83, {0x59, 0x21, 0x74, 0x00, 0x00, 0x00, 0x00}},
  {1, 0x84, {0x10, 0x33, 0x27, 0x00, 0x00, 0x00, 0x00}},
  {0, 0x83, {0x96, 0x58, 0x57, 0x00, 0x00, 0x00, 0x00}},
  {1, 0x83, {0x52, 0x34, 0x20, 0x00, 0x00, 0x00, 0x00}},
  {0, 0x83, {0x16, 0x64, 0x01, 0x00, 0x00, 0x00, 0x00}},
  {1, 0x82, {0x29, 0x94, 0x49, 0x00, 0x00, 0x00, 0x00}},
  {0, 0x81, {0x27, 0x63, 0x72, 0x00, 0x00, 0x00, 0x00}}
};

void fp_div(fp_t *a, fp_t *b, fp_t *c) {
  fp_t a1 = *a;
  fp_t b1 = *b;
  fp_t tmp, out;
  size_t i;
  
  /* Scale quotient. */
  a1.expt = a->expt - b->expt + 0x80 - 1;
  b1.expt = 0x7f;
  
  /* Compute guess. out ~= 1 / b*/
  fp_poly(SEPTIC_COEFFICIENTS, sizeof SEPTIC_COEFFICIENTS / sizeof SEPTIC_COEFFICIENTS[0], &b1, &out);
  
  /* Do a few steps of Newton-Raphson iteration. */
  for(i = 0; i < 5; ++i) {
    /* out = out * (2 - b * out); */
    fp_mul(&b1, &out, &tmp);
    fp_sub(&FP_TWO, &tmp, &tmp);
    fp_mul(&tmp, &out, &out);
  }
  
  /* Compute quotient based on (hopefully) good reciprocal approximation. */
  fp_mul(&out, &a1, &out);
  *c = out;
}
