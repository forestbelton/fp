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

fp_t FP_ZERO = {0, 0x7f, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
fp_t FP_ONE  = {0, 0x80, {0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
fp_t FP_TWO  = {0, 0x80, {0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
fp_t FP_PI   = {0, 0x80, {0x31, 0x41, 0x59, 0x26, 0x53, 0x58, 0x97}};
fp_t FP_E    = {0, 0x80, {0x27, 0x18, 0x28, 0x18, 0x28, 0x45, 0x90}};
