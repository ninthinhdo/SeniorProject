#include "Arduino.h"
#include "TextDisplay.h"

TextDisplay::TextDisplay()
{

	//Letters
	Letter A = {
	B010,
	B101,
	B111,
	B101,
	B101
	};

	Letter B = {
		B110,
		B101,
		B110,
		B101,
		B110
	};

	Letter C = {
		B111,
		B100,
		B100,
		B100,
		B111
	};

	Letter D = {
		B110,
		B101,
		B101,
		B101,
		B110
	};

	Letter E = {
		B111,
		B100,
		B111,
		B100,
		B111
	};

	Letter F = {
		B111,
		B100,
		B111,
		B100,
		B100
	};

	Letter G = {
		B111,
		B100,
		B100,
		B101,
		B111
	};

	Letter H = {
		B101,
		B101,
		B111,
		B101,
		B101
	};

	Letter I = {
		B111,
		B010,
		B010,
		B010,
		B111
	};

	Letter J = {
		B111,
		B010,
		B010,
		B010,
		B110
	};

	Letter K = {
		B101,
		B110,
		B100,
		B110,
		B101
	};

	Letter L = {
		B100,
		B100,
		B100,
		B100,
		B111
	};

	Letter M = {
		B101,
		B111,
		B101,
		B101,
		B101
	};

	Letter N = {
		B111,
		B101,
		B101,
		B101,
		B101
	};

	Letter O = {
		B111,
		B101,
		B101,
		B101,
		B111
	};

	Letter P = {
		B111,
		B101,
		B111,
		B100,
		B100
	};

	Letter Q = {
		B111,
		B101,
		B101,
		B111,
		B001
	};

	Letter R = {
		B110,
		B101,
		B110,
		B110,
		B101
	};

	Letter S = {
		B111,
		B100,
		B111,
		B001,
		B111
	};

	Letter T = {
		B111,
		B010,
		B010,
		B010,
		B010
	};

	Letter U = {
		B101,
		B101,
		B101,
		B101,
		B111
	};

	Letter V = {
		B101,
		B101,
		B101,
		B101,
		B010
	};

	Letter W = {
		B101,
		B101,
		B101,
		B111,
		B101
	};

	Letter X = {
		B101,
		B101,
		B010,
		B101,
		B101
	};

	Letter Y = {
		B101,
		B101,
		B010,
		B010,
		B010
	};

	Letter Z = {
		B111,
		B001,
		B010,
		B100,
		B111
	};

	Letter s = {
		B000,
		B000,
		B000,
		B000,
		B000
	};

	Alphabet[0] = A;
	Alphabet[1] = B;
	Alphabet[2] = C;
	Alphabet[3] = D;
	Alphabet[4] = E;
	Alphabet[5] = F;
	Alphabet[6] = G;
	Alphabet[7] = H;
	Alphabet[8] = I;
	Alphabet[9] = J;
	Alphabet[10] = K;
	Alphabet[11] = L;
	Alphabet[12] = M;
	Alphabet[13] = N;
	Alphabet[14] = O;
	Alphabet[15] = P;
	Alphabet[16] = Q;
	Alphabet[17] = R;
	Alphabet[18] = S;
	Alphabet[19] = T;
	Alphabet[20] = U;
	Alphabet[21] = V;
	Alphabet[22] = W;
	Alphabet[23] = X;
	Alphabet[24] = Y;
	Alphabet[25] = Z;
	Alphabet[26] = s;
	

	//Alphabet[26] = { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z };
	//Letter *Alphabet[] = { &A, &B, &C, &D, &E, &F, &G, &H, &I, &J, &K, &L, &M, &N, &O, &P, &Q, &R, &S, &T, &U, &V, &W, &X, &Y, &Z };

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

	Numbers[0] = zero;
	Numbers[1] = one;
	Numbers[2] = two;
	Numbers[3] = three;
	Numbers[4] = four;
	Numbers[5] = five;
	Numbers[6] = six;
	Numbers[7] = seven;
	Numbers[8] = eight;
	Numbers[9] = nine;
	Numbers[10] = dash;
}

