#ifndef TextDisplay_h
#define TextDisplay_h

#include "Arduino.h"

struct Letter {
	unsigned line1 : 3;
	unsigned line2 : 3;
	unsigned line3 : 3;
	unsigned line4 : 3;
	unsigned line5 : 3;
	unsigned : 0;
};
typedef struct Letter Letter;

struct Number {
	unsigned line1 : 3;
	unsigned line2 : 3;
	unsigned line3 : 3;
	unsigned line4 : 3;
	unsigned line5 : 3;
	unsigned : 0;
};
typedef struct Number Number;


class TextDisplay
{
	public:
	TextDisplay();
	Letter Alphabet[];
	Number Numbers[];

	private:
};

#endif

