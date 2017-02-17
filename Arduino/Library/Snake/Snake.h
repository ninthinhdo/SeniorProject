#ifndef Snake_h
#define Snake_h

#include "Arduino.h"

#define MAX_LENGTH 100

class Snake
{
public:
	Snake();
	void Update();

private:
	byte logicMatrice[20][14];
	byte direction; //0 is right, 1 is up, 2 is left, 3 is down
	byte row, col;
	bool right, up, left, down;
	bool crash;
	uint32_t snakeColor;
	byte tail, head;
	byte posRow[MAX_LENGTH];
	byte posCol[MAX_LENGTH];
	byte foodRow, foodCol;
	uint32_t foodColor;

	void waitForInput(int wait);
	void updateFrame();
	void inputDirection();
	void updateDirection();
	void updatePosition();
	void blinkHead(uint16_t wait);
	void blinkTail(uint16_t wait);
	void initializeSnake();
	void genFood();
	void pauseGame();
	void resetGame();
	void clearLogicMatrice();
	void countDown();
	void printNum(byte index, int rowPos, int colPos, uint32_t textColor);
	void clearStrip(int initialRow);

};

#endif

