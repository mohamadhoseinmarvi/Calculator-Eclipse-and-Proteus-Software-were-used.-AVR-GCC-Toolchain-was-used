#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#define ZERO 0x00
#define NULL ((void*)0)
#define SUPER_LOOP (u8)1

#ifndef PROCESSOR_FREQ
# define PROCESSOR_FREQ 	8000000UL
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long int u32;
typedef char s8;
typedef short s16;
typedef long int s32;
typedef float f32;
typedef double f64;

typedef void (*ptr_2func)(void);

typedef union {
	struct {
		u8 B0 : 1;
		u8 B1 : 1;
		u8 B2 : 1;
		u8 B3 : 1;
		u8 B4 : 1;
		u8 B5 : 1;
		u8 B6 : 1;
		u8 B7 : 1;
	}Bit;
	u8 byte;
} Register;

typedef enum {
	OK = 0,
	NOT_OK
}STD_ERROR;

#endif 
