#ifndef Tron_h
#define Tron_h

#include "Arduino.h"
#include "TronBike.h"


class Tron
{
public:
	Tron();
	void Update();

private:
	byte logicMatrice[20][14];
	int score1;
	int score2;
	char scoreDisplay[3];
	byte setWinScore = 5;
	String command;

	void waitForInput(int wait);
	void updateFrame();
	void blinkBike(TronBike &bike, bool both, uint16_t wait);
	void initializeBike(TronBike &bike);
	void printScore(int wait);
	void printWord(char charArray[], byte len, int rowPos, int colPos);
	void printNum(byte index, int rowPos, int colPos, uint32_t textColor);
	void pauseGame();
	void resetGame();
	void countDown();
	void clearStrip(int initialRow);
	void clearLogicMatrice();
	void winnerCircle(uint32_t color1, uint8_t wait);
	uint32_t Wheel(byte WheelPos);
};

#endif

