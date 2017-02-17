#ifndef PixelResource_h
#define PixelResource_h

#include "Arduino.h"

const int PixelMatrice[][14] =
	//    [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]  [8]  [9] [10] [11] [12] [13]
	{ { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 },   //[0]
	{ 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14 },   //[1]
	{ 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41 },   //[2]
	{ 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42 },   //[3]
	{ 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69 },   //[4]
	{ 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70 },   //[5]
	{ 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97 },   //[6]
	{ 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98 },   //[7]
	{ 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125 },   //[8]
	{ 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128, 127, 126 },   //[9]
	{ 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153 },   //[10]
	{ 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154 },   //[11]
	{ 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181 },   //[12]
	{ 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182 },   //[13]
	{ 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209 },   //[14]
	{ 223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210 },   //[15]
	{ 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237 },   //[16]
	{ 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, 238 },   //[17]
	{ 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265 },   //[18]
	{ 279, 278, 277, 276, 275, 274, 273, 272, 271, 270, 269, 268, 267, 266 }    //[19]
	};


// Colors
//((uint32_t)r << 16) | ((uint32_t)g << 8) | b
const uint32_t red = ((uint32_t)255 << 16) | ((uint32_t)0 << 8) | 0;
const uint32_t green = ((uint32_t)0 << 16) | ((uint32_t)255 << 8) | 0;
const uint32_t blue = ((uint32_t)0 << 16) | ((uint32_t)0 << 8) | 255;
const uint32_t yellow = ((uint32_t)255 << 16) | ((uint32_t)255 << 8) | 0;
const uint32_t cyan = ((uint32_t)0 << 16) | ((uint32_t)255 << 8) | 255;
const uint32_t magenta = ((uint32_t)255 << 16) | ((uint32_t)0 << 8) | 255;
const uint32_t chocolate = ((uint32_t)210 << 16) | ((uint32_t)105 << 8) | 30;
const uint32_t orange = ((uint32_t)255 << 16) | ((uint32_t)165 << 8) | 0;
const uint32_t seaGreen = ((uint32_t)60 << 16) | ((uint32_t)179 << 8) | 113;
const uint32_t hotPink = ((uint32_t)255 << 16) | ((uint32_t)20 << 8) | 147;
const uint32_t white = ((uint32_t)255 << 16) | ((uint32_t)255 << 8) | 255;
/*
const uint32_t red = strip.Color(255, 0, 0);
const uint32_t green = strip.Color(0, 255, 0);
const uint32_t blue = strip.Color(0, 0, 255);
const uint32_t yellow = strip.Color(255, 255, 0);
const uint32_t cyan = strip.Color(0, 255, 255);
const uint32_t magenta = strip.Color(255, 0, 255);
const uint32_t chocolate = strip.Color(210, 105, 30);
const uint32_t orange = strip.Color(255, 165, 0);
const uint32_t seaGreen = strip.Color(60, 179, 113);
const uint32_t hotPink = strip.Color(255, 20, 147);
const uint32_t white = strip.Color(255, 255, 255);
*/

const uint32_t ColorPick[] = { red, green, blue, green, cyan, magenta, chocolate, orange, seaGreen, hotPink };

const uint32_t BlockListColor[] = { cyan, yellow, magenta, green, red, blue, orange };

#define MAX_ROW 19
#define MAX_COL 13

#endif