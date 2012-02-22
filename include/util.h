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
  if(n < 0 || n > (int)(sizeof f->data * 2)) return 0;
  return (f->data[n / 2] >> (!(n % 2) * 4)) & 0x0f;
}

/* Sets a single digit at the index n. */
static inline void fp_setdigit(fp_t *f, uint8_t n, uint8_t value) {
  f->data[n / 2] &= 0xf   << (4 * (n % 2));  /* Clear previous digit. */
  f->data[n / 2] |= value << (4 * !(n % 2)); /* Set new value. */
}

/* Shifts the floating point value n digits to the right, automatically
 * adjusting the exponent. If the exponent were not adjusted, this operation
 * would be equivalent to dividing by 10^n. */
static inline void fp_rshift(fp_t *f, uint8_t n) {
  unsigned i   = 0;
  uint8_t last = 0;
  uint8_t tmp;
  
  /* Copy data in bytes as much as we can. This saves a great deal of
   * complexity, since separate digits don't need to be extracted and then
   * shifted. */
  while(n > 1) {
    last = 0;
    for(i = 0; i < sizeof f->data; ++i) {
      tmp        = f->data[i];
      f->data[i] = last;
      last       = tmp;
    }
    n -= 2;
    f->expt += 2;
  }
  
  /* If there is a single shift left, copy it nibble by nibble. */
  if(n != 0) { 
    last = 0;
    for(i = 0; i < sizeof f->data; ++i) { 
      tmp        = (f->data[i] & 0x0f) << 4;
      f->data[i] = last | (f->data[i] >> 4);
      last       = tmp;
    }
    f->expt++;
  }
}

static inline void fp_lshift(fp_t *f, uint8_t n) {
  unsigned i = 0;
  
  /* Copy data in bytes as much as we can. This saves a great deal of
   * complexity, since separate digits don't need to be extracted and then
   * shifted. */
  while(n > 1) {
    for(i = 0; i < sizeof f->data - 1; ++i)
      f->data[i] = f->data[i + 1];
    f->data[sizeof f->data - 1] = 0;
    n -= 2;
    f->expt -= 2;
  }
  
  /* If there is a single shift left, copy it nibble by nibble. */
  if(n != 0) { 
    for(i = 0; i < sizeof f->data - 1; ++i) {
      f->data[i] <<= 4;
      f->data[i]  |= f->data[i + 1] >> 4;
    }
    f->data[sizeof f->data - 1] <<= 4;
    f->expt--;
  }
}

#endif
