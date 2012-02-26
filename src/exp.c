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

static fp_t SEPTIC_COEFFICIENTS[8] = {
  {0, 0x7c, {0x19, 0x84, 0x12, 0x69, 0x84, 0x12, 0x69}},
  {0, 0x7d, {0x13, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88}},
  {0, 0x7d, {0x83, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33}},
  {0, 0x7e, {0x41, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66}},
  {0, 0x7f, {0x16, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66}},
  {0, 0x7f, {0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {0, 0x80, {0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {0, 0x80, {0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
};

/* Computes exp(x) where ||x|| <= 1. */
static void fp_exp_frac(fp_t *x, fp_t *out) {
  fp_poly(SEPTIC_COEFFICIENTS, sizeof SEPTIC_COEFFICIENTS / sizeof SEPTIC_COEFFICIENTS[0], x, out);
}

/* Computes exp(x) and stores the result in out. */
void fp_exp(fp_t *x, fp_t *out) {
  fp_t whole, frac;
  
  /* If there is no whole part, simply compute and return the fractional part. */
  if(x->expt < 0x80) {
    fp_exp_frac(x, out);
    return;
  }
  
  /* Separate the whole and fractional parts. Then compute each separately, and
   * combine them to form the result. This relies on the fact that
   * exp(a + b) = exp(a) exp(b) */
  
  /* Multiply them together and return. */
  fp_mul(&whole, &frac, out);
}
