#include "Arduino.h"
#include "TronBike.h"

TronBike::TronBike(int rightPin, int upPin, int leftPin, int downPin, int bikeRow, int bikeCol, int initialDirection, uint32_t c)
{
	//Initialize input pins
	pinMode(rightPin, INPUT);
	pinMode(upPin, INPUT);
	pinMode(leftPin, INPUT);
	pinMode(downPin, INPUT);
	digitalWrite(rightPin, HIGH);
	digitalWrite(upPin, HIGH);
	digitalWrite(downPin, HIGH);
	digitalWrite(leftPin, HIGH);

	//Assign pins to private variables
	_right = rightPin;
	_up = upPin;
	_left = leftPin;
	_down = downPin;
	

	//Initialize private varialbes
	row = bikeRow;
	col = bikeCol;
	direction = initialDirection;
	color = c;
	//directions
	right = false;
	up = false;
	left = false;
	down = false;
}

void TronBike::inputDirection(){
	//Read INPUTS
	byte rightBtn = digitalRead(_right);
	byte upBtn = digitalRead(_up);
	byte leftBtn = digitalRead(_left);
	byte downBtn = digitalRead(_down);

	if (rightBtn == LOW){
		right = true;
		up = false;
		left = false;
		down = false;
	} else if (upBtn == LOW){
		right = false;
		up = true;
		left = false;
		down = false;
	} else if (leftBtn == LOW){
		right = false;
		up = false;
		left = true;
		down = false;
	} else if (downBtn == LOW){
		right = false;
		up = false;
		left = false;
		down = true;
	}
}

void TronBike::updateDirection()
{

	//Change direction
	switch (direction){
	case 0:
		if (down == true){
			direction = 3;
		}
		else if (up == true){
			direction = 1;
		}
		break;
	case 1:
		if (left == true){
			direction = 2;
		}
		else if (right == true){
			direction = 0;
		}
		break;
	case 2:
		if (down == true){
			direction = 3;
		}
		else if (up == true){
			direction = 1;
		}
		break;
	case 3:
		if (left == true){
			direction = 2;
		}
		else if (right == true){
			direction = 0;
		}
		break;
	default:
		break;
	}

	right = false;
	up = false;
	left = false;
	down = false;
}

void TronBike::updatePosition()
{
	//Update new position
	switch (direction){
	case 0:
		if (col == maxCol){
			col = 0;
		}
		else{
			col++;
		}
		break;

	case 1:
		if (row == 0){
			row = maxRow;
		}
		else{
			row--;
		}
		break;

	case 2:
		if (col == 0){
			col = maxCol;
		}
		else{
			col--;
		}
		break;

	case 3:
		if (row == maxRow){
			row = 0;
		}
		else{
			row++;
		}
		break;

	default:
		break;
	}
}

