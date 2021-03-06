#ifndef __OPCODES_H
#define __OPCODES_H
enum opcodes {
	NOP,
	PUSH,
	ADD,
	SUB,
	MUL,
	DIV,
	ADDC,
	SUBC,
	INC,
	DEC,
	SWAP,
	XOR,
	AND,
	OR,
	NOT,
	CALL,
	PUSHPC,
	JMP,
	RET,
	REF,
	DUP,
	MOD,
	CMP,
	JMPEQ,
	JMPLT,
	JMPGT,
	JMPLE,
	JMPGE,
	JMPAB,
	JMPBL,
	JMPAE,
	JMPBE,
	JMPNE,
	DIVMOD,
	ADDSP,
	SUBSP,
	INCSP,
	DECSP,
	UNREF,
	PUSHBP,
	POPBP,
	PUSHALL,
	POPALL,
	HALT,
	PUSHFLAGS,
	POPFLAGS,
	REFBP,
	UNREFBP
};
#endif
