#ifndef TronBike_h
#define TronBike_h

#include "Arduino.h"

class TronBike
{
public:
	TronBike(int rightPin, int upPin, int leftPin, int downPin, int bikeRow, int bikeCol, int initialDirection, uint32_t c);

	int direction; //0 is right, 1 is up, 2 is left, 3 is down
	int row;
	int col;
	uint32_t color;

	void inputDirection();
	void updateDirection();
	void updatePosition();

private:
	int _right;
	int _up;
	int _left;
	int _down;
	bool right;
	bool up;
	bool left;
	bool down;
	const byte maxRow = 19;
	const byte maxCol = 13;
};

#endif

