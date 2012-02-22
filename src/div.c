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

/* This is an INTERNAL function which computes an approximation to the
 * reciprocal. This function will likely change over time, though it need not
 * be exposed elsewhere. A description of the current implementation is as
 * follows:
 * 
 * A 7th-order polynomial approximation to 1/x on [0.1, 1]. The following
 * function was used:
 * 
 * 25.1957 - 251.291 x + 1303.97 x^2 - 3887 x^3 + 6885.23 x^4 - 7145.18 x^5 +
 * 4005.3 x^6 - 935.265 x^7
 * 
 * Using the Horner scheme, we convert the polynomial to the following form:
 *
 * 25.1957 + (-251.291 + (1303.97 + (-3887 + (6885.23 + (-7145.18 + (4005.3 -
 * 935.265 * x) * x) * x) * x) * x) * x) * x
 *
 * Which only uses 7 multiplies and 7 additions. The naive approach would use
 * 36 multiplies and 7 additions. */
static void fp_recip(fp_t *a, fp_t *b) {
  
}

void fp_div(fp_t *a, fp_t *b, fp_t *c) {
  fp_t a1 = *a;
  fp_t b1 = *b;
  
  /* Scale quotient. */
  a1.expt = a->expt - b->expt + 0x80 - 1;
  
  /* Compute guess. */
  fp_recip(&b1, c);
  
  /* Do a few steps of Newton-Raphson iteration. */
  
}

/*
 * Testing algorithm using regular 32-bit floating types.
 * This will be deleted after fp_div is complete and tested.
 */

/*
#include <stdio.h>
#include <stdint.h>

#define GET_EXP(x) ((x >> 23) & 0xff)

#define SET_EXP(x, n) do {  \
  x &= 0x807fffff;          \
  x |= (n & 0xff) << 23;    \
} while(0)

#define FLT(x) (*(float*)&(x))

float fp_div(float a, float b) {
  float x;
  uint32_t au = *(uint32_t*)&a;
  uint32_t bu = *(uint32_t*)&b;
  
  // compute scale factor for numerator.
  int disp    = -(GET_EXP(bu) - 127) - 1;
  uint8_t tmp = GET_EXP(au) + disp;
  
  // scale quotient.
  SET_EXP(au, tmp); a = FLT(au);
  SET_EXP(bu, 126); b = FLT(bu);
  
  // compute guess.
  x = (48.0 / 17.0) - (32.0 / 17.0) * b;
  
  // do a few steps of newton-raphson.
  x *= 2 - b * x;
  x *= 2 - b * x;
  x *= 2 - b * x;
  x *= 2 - b * x;
  
  return x * a;
}

int main() {
  printf("%f %f\n", fp_div(1.5, 500), 1.5 / 500);
  return 0;
} */
