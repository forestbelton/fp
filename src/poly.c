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
#include <stddef.h>

/* Evaluates the following polynomial at x = a:
 * 
 * coefs[0] x^(n-1) + coefs[1] x^(n-1) + ... + coefs[n-1]
 * 
 * using the Horner scheme. This changes the order of evaluation to:
 * 
 * coefs[n-1] + (coefs[n-2] + (... + coefs[n-1] * x) * x) * x
 * 
 * which greatly reduces the number of required multiplies. */
void fp_poly(fp_t coefs[], size_t n, fp_t *a, fp_t *out) {
  size_t i;
  fp_t tmp;
  
  tmp = coefs[0];
  for(i = 1; i < n; ++i) {
    fp_mul(a, &tmp, &tmp);
    fp_add(&coefs[i], &tmp, &tmp);
  }
  
  *out = tmp;
}
