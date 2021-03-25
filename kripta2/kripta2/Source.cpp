#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <iostream>
#include "subroutine.h"


using namespace std;


int main() {
	uint32_t p, g, y, x, f=1, a, b, M;
	//uint64_t a, b, M;
	while (f) {
		cout << "enter p, g\n";
		cin >> p >> g;
		//cout << modpow( g, p-1, p);
		if ((PrimeN(p)) && (root(p, g))) {
			f = 0;
			keys(p, g, y, x);
			cout << "keys x,y " << x << " " << y << "\n";
		}
		else printf("\nwrong p or g\n");
	}

	cout << "enter M (M<p) " ;
	cin >> M;

	cout << "enter p g y ";
	cin >> p >> g >> y;

	encrypt(M, p, g, y, a, b);
	cout << "a,b " << a << " " << b << "\n";

	cout << "enter p g x a b" << "\n";
	cin >> p, g, x, a, b;
	decrypt(p, g, x, a, b, M);
	cout << M << "\n";
}