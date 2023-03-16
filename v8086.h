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
 * types
 */

/* base integer types */
#if __SIZEOF_POINTER__ == 8

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#elif __SIZEOF_POINTER__ == 4

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#else

#error unable to determine system architecture, sorry

#endif

/*
 * macros
 */

/* 640k ought to be enough for anybody */
#define V8086_MEMORY 0xA0000

/* read from and advance ptr */
#define READ8(v, p) {v = *(u8 *)p; p += sizeof(u8);}
#define READ16(v, p) {v = *(u16 *)p; p += sizeof(u16);}
#define READ32(v, p) {v = *(u32 *)p; p += sizeof(u32);}

/* runtime struct */
typedef struct v8086_t
{

	/* memory buffer */
	u8 memory[V8086_MEMORY];

	/* program (offset 0x0100)*/
	u8 *program;

	/* regs */
	union
	{
		/* 8-bit regs */
		struct
		{
			u8 ah;
			u8 al;
			u8 bh;
			u8 bl;
			u8 ch;
			u8 cl;
			u8 dh;
			u8 dl;
		} b;

		/* 16-bit regs */
		struct
		{
			u16 ax;
			u16 bx;
			u16 cx;
			u16 dx;

			u16 si;
			u16 di;
			u16 bp;
			u16 sp;
			u16 ip;
			u16 cs;
			u16 ds;
			u16 es;
			u16 ss;
			u16 flags;
		} x;

	} regs;

} v8086_t;

/*
 * instruction opcodes
 */

enum
{
	OP_MOV_AH = 0xB4,
	OP_MOV_DX = 0xBA,
	OP_INT = 0xCD
};

/*
 * hardware interrupt codes
 */

enum
{
	INT_DOS = 0x21
};

/*
 * dos interrupt functions
 */

enum
{
	INT_DOS_PRINT = 0x09,
	INT_DOS_EXIT = 0x4C
};

/*
 * forward definitions
 */

int v8086_init();
void v8086_shutdown();
int v8086_load(char *filename);
int v8086_execute();
