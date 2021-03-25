#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <locale.h>
#include <algorithm>
#include <cctype>
#include "windows.h"

using namespace std;

void letters(int* alph, int length, string al, string str) {
	for (int i = 0; i < 33; i++)
		alph[i] = 0;
	char c;
	for (int i = 0; i < length; i++) {
		c = str[i];
		for (int j = 0; j < 33; j++)
			if (c == al[j])
				alph[j]++;
	}
	for (int i = 0; i < 33; i++)
		cout << al[i] << " " << alph[i] << endl;
	cout << endl;
}

void swapkey(int length, string& str, string al1, string al2) {
	char c;
	for (int i = 0; i < length; i++) {
		c = str[i];
		int ch = 0;
		for (int j = 0; j < 33; j++)
			if (c == al1[j]) {
				str[i] = al2[j];
				ch++;
			}
		//if (ch != 1) str[i] = '*'; äëÿ óäîáñòâà âî âòîðîì çàäàíèèè
	}
}

void check(string& str, string al1) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
		//cout << (int)str[i] << endl;
		if (!(((int)str[i] >= -32 && (int)str[i] <= -1) || ((int)str[i] == -72))) {      //äëÿ ANSI
			str.erase(i, 1);
			i--;
		}
	}
}

//void fisher_yates(int length, string &al2) {
//	for (int i = 0; i < length; i++) {
//		int j = rand() %(i+1);
//		swap(al2[j], al2[i]);
//
//	}
//}

void main() {
	setlocale(LC_ALL, "Russian");
	ifstream in("in1.txt");
	//ifstream in("in2.txt");
	/*ifstream in("in11.txt");*/
	ofstream out("out.txt");
	//ofstream out("out2.txt");
	//ofstream out("out11.txt");
	ofstream key("key.txt");
	string str;
	string al1, al2;


	//al1 = "ö*é*âüà**ð**÷æ*á*úî**ñ*óý***ì***þ";   // ïåðâàÿ ïîïûòêà ðàñøèôðîâêè    //äëÿ ðàñøèôðîâêè îòêëþ÷àåì ïåðåñòàíîâêó
	//al1 = "öõéíâüàè*ðòç÷æëáùúî¸ÿñåóýä**ìã*êþ";   // âòîðàÿ ïîïûòêà ïîíÿòü ñìûñë êîòîïñà 
	//al1 = "öõéíâüàèôðòç÷æëáùúî¸ÿñåóýäûøìãïêþ"; // èòîãîâûé øèôð
	//al2 = "àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ";

	al1 = "àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ";
	al2 = "àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ";  // 1
	//al2 = "ëáè÷àúøþüîñûÿìöïùãóðçòõéýæ¸êåäâôí";  //2

	getline(in, str);
	check(str, al1);

	cout << "ñòðîêà" << endl << str << endl;
	int length = str.length();
	cout << "äëèíà ñòðîêè" << endl << length << endl;
	int alph1[33], alph2[33];
	letters(alph1, length, al1, str);

	random_shuffle(al2.begin(), al2.end());
	//fisher_yates(length, al2);
	key << al1 << endl;
	key << al2 << endl;
	cout << al1 << endl;
	cout << al2 << endl;

	swapkey(length, str, al1, al2);

	cout << "ñòðîêà" << endl << str << endl;
	out << str;
	letters(alph2, length, al2, str);
	in.close();
	out.close();
	key.close();
	_getch();
}