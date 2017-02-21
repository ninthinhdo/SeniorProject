#include "Arduino.h"
#include "TronBike.h"

TronBike::TronBike()
{

}

TronBike::TronBike(String rightString, String upString, String leftString, String downString, int bikeRow, int bikeCol, int initialDirection, uint32_t c)
{
	//Assign pins to private variables
	_right = rightString;
	_up = upString;
	_left = leftString;
	_down = downString;
	

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

void TronBike::inputDirection(String input){

	if (input.equals(_right)){
		right = true;
		up = false;
		left = false;
		down = false;
	}
	else if (input.equals(_up)){
		right = false;
		up = true;
		left = false;
		down = false;
	}
	else if (input.equals(_left)){
		right = false;
		up = false;
		left = true;
		down = false;
	}
	else if (input.equals(_down)){
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

