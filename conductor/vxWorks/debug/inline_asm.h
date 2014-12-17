/*
* inline assembly helper routines
* william.pan@kontron.cn,aug07
*/

#if !defined(INLNE_ASM_H_)
#define INLNE_ASM_H_

#define STRINGFY(v) #v
#define VALUE_OF(v) STRINGFY(v)

#if __VXWORKS__ > 0x540
#define FUNC_NAME(n) n
#define FUNC_NAME_STR(n) #n
#else
#define FUNC_NAME(n) _##n
#define FUNC_NAME_STR(n) "_" #n
#endif

/* helper to define 16-bit code */
#define begin_assembly(name)\
	__asm__ (\
	".globl " FUNC_NAME_STR(name) "\n" \
	".globl " FUNC_NAME_STR(name) "_size\n" \
	FUNC_NAME_STR(name) ":\n"

#define begin_assembly_16bit(name)\
	__asm__ (\
	".globl " FUNC_NAME_STR(name) "\n" \
	".globl " FUNC_NAME_STR(name) "_size \n" \
	FUNC_NAME_STR(name) ":\n"\
	".code16\n"
	
#define end_assembly(name) \
	FUNC_NAME_STR(name) ":\n" \
	".long . - " FUNC_NAME_STR(name) "\n" \
	);\
	extern uint8_t name[];\
	extern uint_t name##_size;

#define end_assembly_16bit(name) \
FUNC_NAME_STR(name) "_size:\n" \
	".long . - " FUNC_NAME_STR(name) "\n" \
	".code32\n" \
	);\
	extern uint8_t name[];\
	extern uint_t name##_size;

/* 16bit assembly support */
#define MK_LP(s,o) ((void*)((s)<<4)+o)
#define ptr32(x) ((((uint32_t)(x)>>16)<<4) + ((uint32_t)(x) & 0xffff))

#endif

