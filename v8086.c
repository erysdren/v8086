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
 * globals
 */

/* main runtime struct */
v8086_t *v8086;

/*
 * v8086_init
 */

int v8086_init()
{
	/* allocate runtime struct */
	v8086 = malloc(sizeof(v8086_t));
	if (v8086 == NULL) return -1;

	/* set program address */
	v8086->program = (u8 *)&v8086->memory[0x0100];

	/* return success */
	return 1;
}

/*
 * v8086_shutdown
 */

void v8086_shutdown()
{
	if (v8086) free(v8086);
}

/*
 * v8086_init
 */

int v8086_load(char *filename)
{
	/* variables */
	void *file;
	int len;

	/* load file */
	file = load(filename, &len);
	if (!file) return -1;

	/* copy to program area */
	memcpy(v8086->program, file, len);

	/* return success */
	return 1;
}

/*
 * v8086_execute
 */

int v8086_execute()
{
	/* variables */
	u8 *pointer;
	u8 opcode;
	u8 interrupt;
	int i;

	/* set values */
	i = 0;
	pointer = v8086->program;

	/* parse loop */
	while (i < V8086_MEMORY)
	{
		/* read opcode */
		READ8(opcode, pointer);

		/* parse opcode */
		switch (opcode)
		{
			/* store value in ah register */
			case OP_MOV_AH:
			{
				READ8(v8086->regs.b.ah, pointer);
				break;
			}

			/* store value in dx register */
			case OP_MOV_DX:
			{
				READ16(v8086->regs.x.dx, pointer);
				break;
			}

			/* hardware interrupt */
			case OP_INT:
			{
				READ8(interrupt, pointer);

				/* parse interrupt*/
				switch (interrupt)
				{
					case INT_DOS:
					{
						switch (v8086->regs.b.ah)
						{
							case INT_DOS_PRINT:
							{
								print((char *)&v8086->memory[v8086->regs.x.dx], '$', stdout);
								break;
							}

							case INT_DOS_EXIT:
							{
								return 1;
							}

							default:
							{
								error("unknown dos interrupt function");
								break;
							}
						}

						break;
					}

					default:
					{
						error("unknown hardware interrupt");
						break;
					}
				}

				break;
			}

			/* unknown opcode */
			default:
			{
				error("unknown opcode");
				break;
			}
		}

		/* advance runaway counter */
		i++;
	}

	/* return success */
	return 1;
}
