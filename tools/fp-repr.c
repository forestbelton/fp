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
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  fp_t   f;
  size_t i;
  
  if(argc != 2) {
    fprintf(stderr, "usage: fp-repr [num]\n");
    fprintf(stderr, "[num]  A floating point number to convert.\n");
    exit(EXIT_FAILURE);
  }
  
  /* Convert to internal format. */
  fp_fromstr(&f, argv[1]);
  
  /* Print representation. */
  printf("{%u, 0x%02x, {", f.sgn, f.expt);
  for(i = 0; i < sizeof f.data - 1; ++i)
    printf("0x%02x, ", f.data[i]);
  printf("0x%02x}}\n", f.data[sizeof f.data - 1]);
  
  return 0;
}
