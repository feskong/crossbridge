//===-- paritysi2_test.c - Test __paritysi2 -------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file tests __paritysi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#include "int_lib.h"
#include <stdio.h>
#include <stdlib.h>

// Returns: 1 if number of bits is odd else returns 0

si_int __paritysi2(si_int a);

int naive_parity(si_int a)
{
    int r = 0;
    for (; a; a = a & (a - 1))
        r = ~r;
    return r & 1;
}

int test__paritysi2(si_int a)
{
    si_int x = __paritysi2(a);
    si_int expected = naive_parity(a);
    if (x != expected)
        printf("error in __paritysi2(0x%X) = %d, expected %d\n",
               a, x, expected);
    return x != expected;
}

char assumption_2[sizeof(si_int)*CHAR_BIT == 32] = {0};

int main()
{
    int i;
    for (i = 0; i < 10000; ++i)
        if (test__paritysi2(rand()))
            return 1;

   printf("PASS\n");
    return 0;
}
