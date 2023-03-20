/*
ANTI-CAPITALIST SOFTWARE LICENSE (v 1.4)

Copyright © 2023 erysdren (it/they/she)

This is anti-capitalist software, released for free use by individuals
and organizations that do not operate by capitalist principles.

Permission is hereby granted, free of charge, to any person or
organization (the "User") obtaining a copy of this software and
associated documentation files (the "Software"), to use, copy, modify,
merge, distribute, and/or sell copies of the Software, subject to the
following conditions:

  1. The above copyright notice and this permission notice shall be
  included in all copies or modified versions of the Software.

  2. The User is one of the following:
    a. An individual person, laboring for themselves
    b. A non-profit organization
    c. An educational institution
    d. An organization that seeks shared profit for all of its members,
    and allows non-members to set the cost of their labor

  3. If the User is an organization with owners, then all owners are
  workers and all workers are owners with equal equity and/or equal vote.

  4. If the User is an organization, then the User is not law enforcement
  or military, or working for or under either.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT EXPRESS OR IMPLIED WARRANTY OF
ANY KIND, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
 * headers
 */

/* std */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* v8086 */
#include "utils.h"
#include "v8086.h"

/*
 * macros
 */

/* get 8-bit register */
#define REG8(i) v8086.regs[i]

/* get 16-bit register */
#define REG16(i) *(u16 *)&v8086.regs[i]

/* main registers */
#define REG_AX REG16(0)
#define REG_AH REG8(0)
#define REG_AL REG8(1)
#define REG_BX REG16(2)
#define REG_BH REG8(2)
#define REG_BL REG8(3)
#define REG_CX REG16(4)
#define REG_CH REG8(4)
#define REG_CL REG8(5)
#define REG_DX REG16(6)
#define REG_DH REG8(6)
#define REG_DL REG8(7)

/* index registers */
#define REG_SI REG16(8)
#define REG_DI REG16(10)
#define REG_BP REG16(12)
#define REG_SP REG16(14)

/* program counter */
#define REG_IP REG16(16)

/* segment registers */
#define REG_CS REG16(18)
#define REG_DS REG16(20)
#define REG_ES REG16(22)
#define REG_SS REG16(24)

/* status register */
#define FLAGS REG16(26)

/* flags */
#define FLAG_C GETBIT(FLAGS, 0)
#define FLAG_P GETBIT(FLAGS, 2)
#define FLAG_A GETBIT(FLAGS, 4)
#define FLAG_Z GETBIT(FLAGS, 6)
#define FLAG_S GETBIT(FLAGS, 7)
#define FLAG_T GETBIT(FLAGS, 8)
#define FLAG_I GETBIT(FLAGS, 9)
#define FLAG_D GETBIT(FLAGS, 10)
#define FLAG_O GETBIT(FLAGS, 11)

/*
 * memory
 */

struct
{

	/* 640k ought to be enough for anybody */
	u8 mem[0xA0000];

	/* registers */
	u8 regs[28];

} v8086;

/*
 * main
 */

int main(int argc, char **argv)
{
	memset(&v8086, 0, sizeof(v8086));
	REG_DX = 16;
	printf("dx: %d\n", REG_DX);
	REG_DH = 19;
	REG_DL = 8;
	printf("dh: %d\ndl: %d\n", REG_DH, REG_DL);
	return 0;
}
