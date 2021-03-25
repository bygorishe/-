#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include <random>

using namespace std;

uint64_t modpow(uint64_t a, uint32_t b, uint32_t c) 
{
	uint64_t t = 1;
	while (b) {
		if (b % 2 == 0) {
			b /= 2;
			a = (a * a) % c;
		}
		else {
			b--;
			t = (t * a) % c;
		}
	}
	return t;
}

bool PrimeN(uint32_t p) {
	uint64_t t = 2;
	while ((t*t <= p) && (p % t != 0)) t++;
	if (t*t > p) return true;
	else return false;
}

uint32_t random(uint32_t p, uint32_t &a){
	random_device rd;   
	mt19937 gen(rd());  
	uniform_int_distribution<uint32_t> dist(2, p-2); // тк 1 < x < p-1
	a = dist(gen);
	return a;
}

vector<uint32_t> factorize(uint32_t x) {
	vector<uint32_t> factors;
	for (int i = 2; i <= x; i++) {
		if ((x % i == 0) && (PrimeN(i))) {
			factors.push_back(i);
			x /= i;
		}
	}
	return factors;
}

bool root(uint32_t p, uint32_t g) {
	if (modpow(g, p - 1, p) == 1) {
		vector<uint32_t> dividers;
		dividers = factorize(p - 1);
		for (int j : dividers) {
			cout << j << "\n";
			if(modpow(g, (p-1)/j, p)==1)
				return false;
		}
		return true; 
	}
	else return false;
}

uint32_t NOD(uint32_t a, uint32_t b) {
	return b ? NOD(b, a % b) : a;
}

void keys(uint32_t p, uint32_t g, uint32_t &y, uint32_t &x) {
	x = 0;
	while (NOD(x, p - 1) != 1)
		x = random(p, x);
	y = modpow(g, x, p);
}

void encrypt(uint32_t  M, uint32_t p, uint32_t g, uint32_t y, uint32_t &a, uint32_t &b) {
	uint32_t k = 0;
	while (NOD(k, p - 1) != 1)
		k = random(p, k);
	a = modpow(g, k,p);
	b = (modpow(y, k, p) * M) %p ;
}

void decrypt(uint32_t p, uint32_t g, uint32_t x, uint32_t a, uint32_t b, uint32_t&M) {
	M = (modpow(a, (p - 1 - x), p) * b) % p;
}


