#ifndef TronBike_h
#define TronBike_h

#include "Arduino.h"

class TronBike
{
public:
	TronBike();
	TronBike(String upString, String rightString, String downString, String leftString, int bikeRow, int bikeCol, int initialDirection, uint32_t c);

	int direction; //0 is right, 1 is up, 2 is left, 3 is down
	int row;
	int col;
	uint32_t color;

	void inputDirection(String input);
	void updateDirection();
	void updatePosition();

private:
	String _right;
	String _up;
	String _left;
	String _down;
	bool right;
	bool up;
	bool left;
	bool down;
	const byte maxRow = 19;
	const byte maxCol = 13;
};

#endif

