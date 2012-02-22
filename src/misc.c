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

void fp_fromstr(fp_t *out, const char *str) {
  unsigned i, done = 0;
  
  /* Parse sign, if it exists. */
  switch(*str) {
    case '-': ++str; out->sgn = 1; break;
    case '+': ++str;
    default:  out->sgn = 0;
  }
  
  /* Initialize output to zero. */
  out->expt = 0x80 - 1;
  for(i = 0; i < sizeof out->data; ++i)
    out->data[i] = 0;
  
  /* Ignore leading zeros. If there are no leading nonzero digits, start
   * reducing the exponent until one is found. */
  while(*str == '0') ++str;
  if(*str == '.') {
    ++str;
    while(*str == '0') {
      --out->expt;
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
      ++out->expt;
    
    /* The decimal point has been encountered and the floating-point value has
     * been filled with digits. Any further iteration would be needless. */
    if(done && i == sizeof out->data)
      break;
    
    /* Add the digit if there is any room left and continue iteration. */
    if(i < sizeof out->data)
      fp_setdigit(out, i++, *str - '0');
    ++str;
  }
}

/* TODO: Comment and clean up (and fix). */
void fp_tostr(fp_t *f, char *out) {
  unsigned i;
  int expt;
  char expc[5] = {0};
  
  if(f->sgn)
    *out++ = '-';
  
  *out++ = fp_getdigit(f, 0) + '0';
  *out++ = '.';
  
  for(i = 1; i < sizeof f->data * 2; ++i)
    *out++ = fp_getdigit(f, i) + '0';
  
  *out++ = 'e';
  expt = f->expt - 0x80;
  
  if(expt < 0)
    *out++ = '-';
  
  i = sizeof expc - 1;
  do {
    expc[i--] = expt % 10 + '0';
    expt /= 10;
  } while(expt != 0);
  
  while(i < sizeof expc)
    *out++ = expc[++i];
  
  *out = 0;
}