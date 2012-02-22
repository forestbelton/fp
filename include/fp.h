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
#ifndef FP_H_
#define FP_H_

#include <stdint.h>

/* Must be an even number. */
#define FP_DIGITS 14

/* Floating-point format. */
typedef struct {
  uint8_t sgn;
  uint8_t expt;
  uint8_t data[FP_DIGITS / 2];
} fp_t;

/* Floating-point API. */
void fp_add(fp_t *a, fp_t *b, fp_t *c); /* C <- A + B */
void fp_mul(fp_t *a, fp_t *b, fp_t *c); /* C <- A * B */
void fp_div(fp_t *a, fp_t *b, fp_t *c); /* C <- A / B */

void fp_fromstr(fp_t *out, const char *value);
void fp_tostr  (fp_t *f, char *out);

#endif
