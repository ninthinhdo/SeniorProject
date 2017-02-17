#include "Arduino.h"
#include "Snake.h"

#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include "avr/power.h"
#endif
#include "avr/pgmspace.h"

#define PIN 44
Adafruit_NeoPixel snake_strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);

#include "PixelResource.h"

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


Snake::Snake()
{
	// Play Tetris Theme
	Serial2.print("GAME.ARCADE2.");

	//Initialize logicMatrice to zeros;
	clearLogicMatrice();

	//Initialize LED strip
	snake_strip.begin();
	snake_strip.setBrightness(32);

	//Initialize Snake
	initializeSnake();

	delay(100);
	//digitalWrite(resetSoundPin, HIGH);

	//Start Countdown
	countDown();

	//Generate Food
	genFood();
}


void Snake::Update()
{
	/*
	String pauseBtn = Serial1.readStringUntil('.');
	if(pauseBtn.equals("BReset")){
	pauseGame();
	}
	*/

	//200ms delay
	//waitForInput(100);

	delay(200);
	inputDirection();

	updateFrame();
}


void Snake::waitForInput(int wait)
{
	for (int i = 0; i < wait; i++){
		inputDirection();
		delay(1);
	}
}


void Snake::updateFrame()
{
	updateDirection();
	updatePosition();

	//Erase Tail
	snake_strip.setPixelColor(PixelMatrice[posRow[tail]][posCol[tail]], 0);
	logicMatrice[posRow[tail]][posCol[tail]] = 0;
	tail++;
	if (tail == 100) tail = 0;

	//Assign Head
	head++;
	if (head == 100) head = 0;
	posRow[head] = row;
	posCol[head] = col;
	snake_strip.setPixelColor(PixelMatrice[row][col], snakeColor);
	snake_strip.show();

	//Food Eaten
	if ((row == foodRow) && (col == foodCol)){
		blinkTail(100);
		tail--;
		//Generate new food
		genFood();
	}

	if (logicMatrice[row][col] == 1){
		crash = true;
	}
	else{
		logicMatrice[row][col] = 1;
	}

	if (crash){
		blinkHead(190);
		snake_strip.clear();
		resetGame();
	}
}


void Snake::inputDirection()
{
	if (Serial1.available() > 0){
		//Read INPUTS
		String inputCommand = Serial1.readStringUntil('.');

		if (inputCommand.equals("BUp")){
			right = false;
			up = true;
			left = false;
			down = false;
		}
		else if (inputCommand.equals("BRight")){
			right = true;
			up = false;
			left = false;
			down = false;
		}
		else if (inputCommand.equals("BDown")){
			right = false;
			up = false;
			left = false;
			down = true;
		}
		else if (inputCommand.equals("BLeft")){
			right = false;
			up = false;
			left = true;
			down = false;
		}

	}
}


void Snake::updateDirection()
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


void Snake::updatePosition()
{
	//Update new position
	switch (direction){
	case 0:
		if (col == MAX_COL){
			crash = true;
		}
		else{
			col++;
		}
		break;

	case 1:
		if (row == 0){
			crash = true;
		}
		else{
			row--;
		}
		break;

	case 2:
		if (col == 0){
			crash = true;
		}
		else{
			col--;
		}
		break;

	case 3:
		if (row == MAX_ROW){
			crash = true;
		}
		else{
			row++;
		}
		break;

	default:
		break;
	}
}


void Snake::blinkHead(uint16_t wait)
{
	Serial2.print("DEATH2.");

	for (int i = 0; i < 4; i++){
		snake_strip.setPixelColor(PixelMatrice[row][col], white);
		snake_strip.show();
		delay(wait);
		snake_strip.setPixelColor(PixelMatrice[row][col], snakeColor);
		snake_strip.show();
		delay(wait);
	}
}


void Snake::blinkTail(uint16_t wait)
{
	Serial2.print("ONEUP.");

	for (int i = 0; i < 4; i++){
		snake_strip.setPixelColor(PixelMatrice[posRow[tail - 1]][posCol[tail - 1]], 0);
		snake_strip.show();
		delay(wait);
		snake_strip.setPixelColor(PixelMatrice[posRow[tail - 1]][posCol[tail - 1]], snakeColor);
		snake_strip.show();
		delay(wait);
	}

	logicMatrice[posRow[tail - 1]][posCol[tail - 1]] = 1;
}


void Snake::initializeSnake()
{
	right = false;
	up = false;
	left = false;
	down = false;

	direction = 0; //goes right
	crash = false;

	row = 10;
	col = 7;

	tail = 0;
	head = 0;

	//Erase snake positions
	for (int i = 0; i < MAX_LENGTH; i++){
		posRow[i] = 0;
		posCol[i] = 0;
	}

	//Setup Random Generator
	randomSeed(analogRead(0));
	delay(20);
	int varRandom;
	for (int i = 0; i < (analogRead(0) % 10); i++) varRandom = random(0, sizeof(ColorPick) / 4);

	//Initialize Snake
	posRow[0] = row;
	posCol[0] = col;
	snakeColor = ColorPick[varRandom];
	snake_strip.setPixelColor(PixelMatrice[row][col], snakeColor);
	logicMatrice[row][col] = 1;
	snake_strip.show();

	foodColor = ColorPick[random(0, sizeof(ColorPick) / 4)];
	while (foodColor == snakeColor) foodColor = ColorPick[random(0, sizeof(ColorPick) / 4)];
}


void Snake::genFood()
{
	foodRow = random(0, MAX_ROW);
	foodCol = random(0, MAX_COL);

	foodColor = ColorPick[random(0, sizeof(ColorPick) / 4)];
	while (foodColor == snakeColor) foodColor = ColorPick[random(0, sizeof(ColorPick) / 4)];

	while (logicMatrice[foodRow][foodCol]){
		foodRow = random(0, MAX_ROW);
		foodCol = random(0, MAX_COL);
	}

	snake_strip.setPixelColor(PixelMatrice[foodRow][foodCol], foodColor);
}


void Snake::pauseGame()
{
	delay(3000);
	String tempPause = Serial1.readStringUntil('.');
	while (!tempPause.equals("BReset")) tempPause = Serial1.readStringUntil('.');
	delay(200);
}


void Snake::resetGame()
{
	clearLogicMatrice();
	initializeSnake();
	countDown();
	genFood();
}


void Snake::clearLogicMatrice()
{
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 14; j++) logicMatrice[i][j] = 0;
	}
}


void Snake::countDown()
{
	Serial2.print("CNTDOWN.");
	delay(10);
	for (int i = 3; i >= 0; i--){
		printNum(i, 1, 6, cyan);
		delay(1000);
		clearStrip(1);
	}
}


void Snake::printNum(byte index, int rowPos, int colPos, uint32_t textColor)
{
	for (int c = 0; c < 3; c++){
		if (((colPos + (2 - c)) < 14) && ((colPos + (2 - c)) >= 0)){
			if (bitRead(Numbers[index]->line1, c)) snake_strip.setPixelColor(PixelMatrice[rowPos][colPos + (2 - c)], textColor);
			if (bitRead(Numbers[index]->line2, c)) snake_strip.setPixelColor(PixelMatrice[rowPos + 1][colPos + (2 - c)], textColor);
			if (bitRead(Numbers[index]->line3, c)) snake_strip.setPixelColor(PixelMatrice[rowPos + 2][colPos + (2 - c)], textColor);
			if (bitRead(Numbers[index]->line4, c)) snake_strip.setPixelColor(PixelMatrice[rowPos + 3][colPos + (2 - c)], textColor);
			if (bitRead(Numbers[index]->line5, c)) snake_strip.setPixelColor(PixelMatrice[rowPos + 4][colPos + (2 - c)], textColor);
		}
	}
	snake_strip.show();
}


void Snake::clearStrip(int initialRow)
{
	for (int c = 0; c < 14; c++){
		for (int r = 0; r < 5; r++){
			snake_strip.setPixelColor(PixelMatrice[initialRow + r][c], 0);
		}
	}
}