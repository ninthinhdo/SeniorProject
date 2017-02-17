#ifndef PixelStruct_h
#define PixelStruct_h

#include "Arduino.h"


typedef struct Block_4x4 {
	unsigned line1 : 4;
	unsigned line2 : 4;
	unsigned line3 : 4;
	unsigned line4 : 4;
	unsigned : 0;
};
typedef struct Block_4x4 Block_4x4;

typedef struct Block_3x3 {
	unsigned line1 : 3;
	unsigned line2 : 3;
	unsigned line3 : 3;
	unsigned : 0;
};
typedef struct Block_3x3 Block_3x3;

Block_4x4 IBlock{
	B0000,
	B1111,
	B0000,
	B0000
};

Block_4x4 OBlock{
	B0000,
	B0110,
	B0110,
	B0000
};

Block_3x3 TBlock{
	B000,
	B111,
	B010
};

Block_3x3 SBlock{
	B000,
	B011,
	B110
};

Block_3x3 ZBlock{
	B000,
	B110,
	B011
};

Block_3x3 JBlock{
	B000,
	B100,
	B111
};

Block_3x3 LBlock{
	B000,
	B001,
	B111
};

Block_4x4 *BlockList_4x4[] = { &IBlock, &OBlock };
Block_3x3 *BlockList_3x3[] = { 0, 0, &TBlock, &SBlock, &ZBlock, &JBlock, &LBlock };


struct Number {
	unsigned line1 : 3;
	unsigned line2 : 3;
	unsigned line3 : 3;
	unsigned line4 : 3;
	unsigned line5 : 3;
	unsigned : 0;
};
typedef struct Number Number;

Number zero = {
	B111,
	B101,
	B101,
	B101,
	B111
};

Number one = {
	B010,
	B110,
	B010,
	B010,
	B111
};

Number two = {
	B111,
	B001,
	B111,
	B100,
	B111
};

Number three = {
	B111,
	B001,
	B111,
	B001,
	B111
};

Number four = {
	B101,
	B101,
	B111,
	B001,
	B001
};

Number five = {
	B111,
	B100,
	B111,
	B001,
	B111
};

Number six = {
	B111,
	B100,
	B111,
	B101,
	B111
};

Number seven = {
	B111,
	B001,
	B001,
	B001,
	B001
};

Number eight = {
	B111,
	B101,
	B111,
	B101,
	B111
};

Number nine = {
	B111,
	B101,
	B111,
	B001,
	B001
};

Number dash = {
	B000,
	B000,
	B111,
	B000,
	B000
};

Number *Numbers[] = { &zero, &one, &two, &three, &four, &five, &six, &seven, &eight, &nine, &dash };


#endif