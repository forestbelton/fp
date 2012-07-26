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
#include <stdio.h>
#include <string.h>

fp_t fp_fromint(int n) {
  fp_t     out;
  unsigned i = 0, j = 0;
  unsigned digits[FP_DIGITS * 2];
  
  /* Initialize out variable. */
  out.sgn  = 0;
  out.expt = 0x7f;
  out.data = 0;
  
  /* Compute sign. */
  if(n < 0) {
    ++out.sgn;
    n = -n;
  }
  
  /* Record digits (in reverse order). */
  while(n) {
    ++out.expt;
    digits[i++] = n % 10;
    n /= 10;
  }
  
  /* Set them in the float in the proper order. */
  while(i--)
    fp_setdigit(&out, j++, digits[i]);
  
  return out;
}

fp_t fp_fromstr(const char *str) {
  fp_t     out;
  unsigned i, done = 0;
  
  /* Parse sign, if it exists. */
  switch(*str) {
    case '-': ++str; out.sgn = 1; break;
    case '+': ++str;
    default:  out.sgn = 0;
  }
  
  /* Initialize output to zero. */
  out.expt = 0x7f;
  out.data = 0;
  
  /* Ignore leading zeros. If there are no leading nonzero digits, start
   * reducing the exponent until one is found. */
  while(*str == '0') ++str;
  if(*str == '.') {
    --out.expt;
    ++str;
    while(*str == '0') {
      --out.expt;
      ++str;
    }
    done = 1;
  }
  
  /* Scan over each character, adding it to the number if there is enough
   * space left. */
  i = 0;
  while(*str) {
    /* Note if the decimal point has been encountered. */
    if(*str == '.') {
      done = 1;
      ++str;
      continue;
    }
    
    /* Increase the exponent if the decimal point still has not yet been
     * found. */
    else if(!done)
      ++out.expt;
    
    /* The decimal point has been encountered and the floating-point value has
     * been filled with digits. Any further iteration would be needless. */
    if(done && i == sizeof out.data * 2)
      break;
    
    /* Add the digit if there is any room left and continue iteration. */
    if(i < sizeof out.data * 2)
      fp_setdigit(&out, i++, *str - '0');
    ++str;
  }

  return out;
}

/* TODO: Comment and clean up (and fix). */
void fp_tostr(fp_t f, char *out) {
  int      expt = f.expt - 0x80;
  uint64_t tmp  = f.data;
  
  if(f.sgn)
    *out++ = '-';

  /* reasonably small, 10^-14 < |f| < 1 */
  if(expt < 0 && expt > -14) {

    *out++ = '0';
    *out++ = '.';
    
    while(expt < -1) {
      *out++ = '0';
      ++expt;
    }

    while(tmp) {
      *out++ = '0' + ((tmp >> 52) & 0xf);
      tmp <<= 4;
      tmp &= ~(0xffULL << 56);
    }
  }
  
  /* reasonably large, 1 < |f| < 10^14 */
  else if(expt >= 0 && expt < 14) {
    while(tmp && expt > -1) {
      *out++ = '0' + ((tmp >> 52) & 0xf);
      tmp <<= 4;
      tmp &= ~(0xffULL << 56);
      --expt;
    }

    *out++ = '.';
    if(!tmp)
      *out++ = '0';
    else while(tmp) {
      *out++ = '0' + ((tmp >> 52) & 0xf);
      tmp <<= 4;
      tmp &= ~(0xffULL << 56);
    }
  }

  /* crazy big/small!! */
  else {
    /* first digit */
    *out++ = '0' + ((tmp >> 52) & 0xf);
    tmp <<= 4;
    tmp &= ~(0xffULL << 56);

    *out++ = '.';
    /* the rest */
    while(tmp) {
      *out++ = '0' + ((tmp >> 52) & 0xf);
      tmp <<= 4;
      tmp &= ~(0xffULL << 56);
    }

    sprintf(out, "e%d", expt);
    return;
  }
  
  *out++ = 0;
}
