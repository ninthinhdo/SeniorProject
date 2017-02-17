#ifndef Tetris_h
#define Tetris_h

#include "Arduino.h"

class Tetris
{
public:
	Tetris();
	void Update();

private:
	int currentBlock;
	int rowPos;
	int colPos;
	byte rotation;
	bool allowPlacement = false;
	int blockShiftCounter = 0;
	String previousCommand;
	int blockSpeed = 50;
	uint32_t randomBlockColor;
	//0 is off, 1 is on for LEDs
	byte logicMatrice[20][14];

	void waitForInput(int wait, int blockDelay);
	void updateFrame();
	void clearLines();
	void generateNewBlock();
	void clearStrip(int initialRow, int length);
	void clearLogicMatrice();
};

#endif

