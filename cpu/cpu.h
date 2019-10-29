/*
 * cpu.h
 * Copyright (C) 2019 martian <martian@Martian-sys>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CPU_H
#define CPU_H

#include <stdint.h>

struct gb_regs {
	uint16_t af;
	uint16_t bc;
	uint16_t de;
	uint16_t hl;
	uint16_t sp;
	uint16_t pc;
};

struct gb_cpu {
	struct gb_regs regs;
	uint8_t memory[0x5eff];
};

#define __GB_READ_REGH(reg) ((reg >> 8) & 0xff)
#define __GB_READ_REGL(reg) (reg & 0xff)

#define GB_READ_A(gb_cpu) __GB_READ_REGH((gb_cpu->regs.af))
#define GB_READ_F(gb_cpu) __GB_READ_REGL((gb_cpu->regs.af))
#define GB_READ_B(gb_cpu) __GB_READ_REGH((gb_cpu->regs.bc))
#define GB_READ_C(gb_cpu) __GB_READ_REGL((gb_cpu->regs.bc))
#define GB_READ_D(gb_cpu) __GB_READ_REGH((gb_cpu->regs.de))
#define GB_READ_E(gb_cpu) __GB_READ_REGL((gb_cpu->regs.de))
#define GB_READ_H(gb_cpu) __GB_READ_REGH((gb_cpu->regs.hl))
#define GB_READ_L(gb_cpu) __GB_READ_REGL((gb_cpu->regs.hl))
#define GB_READ_BC(gb_cpu) (gb_cpu->reg.bc)
#define GB_READ_DE(gb_cpu) (gb_cpu->reg.de)
#define GB_READ_HL(gb_cpu) (gb_cpu->reg.hl)
#define GB_READ_SP(gb_cpu) (gb_cpu->reg.sp)
#define GB_READ_PC(gb_cpu) (gb_cpu->reg.pc)

#define __GB_WRITE_REGH(reg, val) {reg = (((val & 0xff) << 8) | (reg & (0xff << 8)));}
#define __GB_WRITE_REGL(reg, val) {reg = ((reg & 0xff) | (reg & 0xff));}

#define GB_WRITE_A(gb_cpu, val) __GB_WRITE_REGH((gb_cpu->regs.af), val)
#define GB_WRITE_F(gb_cpu, val) __GB_WRITE_REGL((gb_cpu->regs.af), val)
#define GB_WRITE_B(gb_cpu, val) __GB_WRITE_REGH((gb_cpu->regs.bc), val)
#define GB_WRITE_C(gb_cpu, val) __GB_WRITE_REGL((gb_cpu->regs.bc), val)
#define GB_WRITE_D(gb_cpu, val) __GB_WRITE_REGH((gb_cpu->regs.de), val)
#define GB_WRITE_E(gb_cpu, val) __GB_WRITE_REGL((gb_cpu->regs.de), val)
#define GB_WRITE_H(gb_cpu, val) __GB_WRITE_REGH((gb_cpu->regs.hl), val)
#define GB_WRITE_L(gb_cpu, val) __GB_WRITE_REGL((gb_cpu->regs.hl), val)
#define GB_WRITE_BC(gb_cpu, val) {gb_cpu->reg.bc = val;}
#define GB_WRITE_DE(gb_cpu, val) {gb_cpu->reg.de = val;}
#define GB_WRITE_HL(gb_cpu, val) {gb_cpu->reg.hl = val;}
#define GB_WRITE_SP(gb_cpu, val) {gb_cpu->reg.sp = val;}
#define GB_WRITE_PC(gb_cpu, val) {gb_cpu->reg.pc = val;}

#endif /* !CPU_H */
