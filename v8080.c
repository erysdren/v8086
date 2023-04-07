
/*
 *
 * headers
 *
 */

/* std */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 *
 * macros
 *
 */

#define REG_A (v8080.registers.af & 0xFF00)
#define REG_F (v8080.registers.af & 0x00FF)
#define REG_B (v8080.registers.bc & 0xFF00)
#define REG_C (v8080.registers.bc & 0x00FF)
#define REG_D (v8080.registers.de & 0xFF00)
#define REG_E (v8080.registers.de & 0x00FF)
#define REG_H (v8080.registers.hl & 0xFF00)
#define REG_L (v8080.registers.hl & 0x00FF)

#define REG_AF (v8080.registers.af)
#define REG_BC (v8080.registers.bc)
#define REG_DE (v8080.registers.de)
#define REG_HL (v8080.registers.de)
#define REG_SP (v8080.registers.sp)
#define REG_PC (v8080.registers.pc)
#define REG_FLAGS (v8080.registers.flags)

/*
 *
 * types
 *
 */

/* opcode function */
typedef void (*v8080_opcode_func_t)();

/*
 *
 * globals
 *
 */

/*
 * virtual cpu
 */

struct
{
	/* memory */
	uint8_t memory[0x10000];

	/* registers */
	struct
	{

		uint16_t af;
		uint16_t bc;
		uint16_t de;
		uint16_t hl;
		uint16_t sp;
		uint16_t pc;
		uint16_t flags;

	} registers;

} v8080;

/*
 * opcode functions
 */

void nop() { return; }
void lxibd16() { printf("oopsie"); }
void staxb() { REG_BC = REG_A; }
void inxb() { REG_BC += 1; }
void inrb() { REG_BC | ((((uint8_t)1) << 8) & 0xFF00); }

/*
 * opcode functions table
 */

v8080_opcode_func_t opcode_funcs[256] =
{
	nop,
	lxibd16,
	staxb,
	inxb,
	inrb
};

/*
 *
 * functions
 *
 */

/* main */
int main(int argc, char **argv)
{
	return 0;
}
