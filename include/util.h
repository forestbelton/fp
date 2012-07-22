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
#ifndef FP_UTIL_H_
#define FP_UTIL_H_

/* Extracts a single digit at the index n. If the index is
 * out of bounds, return 0. */
static inline uint8_t fp_getdigit(fp_t *f, int n) {
  if(n < 0 || n > (int)(sizeof f->data - 1) * 2)
    return 0;
  else
    return (f->data >> (4 * n)) & 0x0f;
}

/* Sets a single digit at the index n. */
static inline void fp_setdigit(fp_t *f, uint8_t n, uint8_t value) {
  f->data &= ~(0xf << (4 * n));
  f->data |= (value & 0xf) << (4 * n);
}

/* Shifts the floating point value n digits to the right, automatically
 * adjusting the exponent. If the exponent were not adjusted, this operation
 * would be equivalent to dividing by 10^n. */
static inline void fp_rshift(fp_t *f, uint8_t n) {
  f->data >>= n;
  f->expt  += n;
}

static inline void fp_lshift(fp_t *f, uint8_t n) {
  f->data <<= n;
  f->data  &= ~(0xffULL << 56);
  f->expt  -= n;
}

#endif

