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
#include <inttypes.h>
#include <stdio.h>

int main() {
  fp_t a, b, c;
  
  a = fp_fromstr("301.2");
  b = fp_fromstr("902.7");
  c = fp_add(a, b);

  printf("a: {%u, 0x%02x, 0x%08x%08xULL}\n", a.sgn, a.expt, (uint32_t)(a.data >> 32), (uint32_t)a.data);
  printf("b: {%u, 0x%02x, 0x%08x%08xULL}\n", b.sgn, b.expt, (uint32_t)(b.data >> 32), (uint32_t)b.data);
  printf("a + b: {%u, 0x%02x, 0x%08x%08xULL}\n", c.sgn, c.expt, (uint32_t)(c.data >> 32), (uint32_t)c.data);

  return 0;
}
