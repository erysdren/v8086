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

/* get register */
#define REGS(i) v8086.regs[i]

/* main registers */
#define REG_AX REGS(0)
#define REG_BX REGS(1)
#define REG_CX REGS(2)
#define REG_DX REGS(3)

/* index registers */
#define REG_SI REGS(4)
#define REG_DI REGS(5)
#define REG_BP REGS(6)
#define REG_SP REGS(7)

/* program counter */
#define REG_IP REGS(8)

/* segment registers */
#define REG_CS REGS(9)
#define REG_DS REGS(10)
#define REG_ES REGS(11)
#define REG_SS REGS(12)

/* status register */
#define FLAGS REGS(13)

/* flags */
#define FLAG_C BIT(FLAGS, 0)
#define FLAG_P BIT(FLAGS, 2)
#define FLAG_A BIT(FLAGS, 4)
#define FLAG_Z BIT(FLAGS, 6)
#define FLAG_S BIT(FLAGS, 7)
#define FLAG_T BIT(FLAGS, 8)
#define FLAG_I BIT(FLAGS, 9)
#define FLAG_D BIT(FLAGS, 10)
#define FLAG_O BIT(FLAGS, 11)

/*
 * memory
 */

struct
{

	/* 640k ought to be enough for anybody */
	u8 mem[0xA0000];

	/* registers */
	u16 regs[14];

} v8086;

