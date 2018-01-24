// CIFFrench.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <locale>

using namespace std;

map<int, string> initMap() {
	static pair<int, string> data[] = {
		pair<int, string>(0, "z\u00E8ro"),
		pair<int, string>(1, "un"),
		pair<int, string>(2, "deux"),
		pair<int, string>(3, "trois"),
		pair<int, string>(4, "quatre"),
		pair<int, string>(5, "cinq"),
		pair<int, string>(6, "six"),
		pair<int, string>(7, "sept"),
		pair<int, string>(8, "huit"),
		pair<int, string>(9, "neuf"),
		pair<int, string>(10, "dix"),
		pair<int, string>(11, "onze"),
		pair<int, string>(12, "douze"),
		pair<int, string>(13, "treize"),
		pair<int, string>(14, "quatorze"),
		pair<int, string>(15, "quinze"),
		pair<int, string>(16, "seize"),
		pair<int, string>(17, "dix-sept"),
		pair<int, string>(18, "dix-huit"),
		pair<int, string>(19, "dix-neuf"),
		pair<int, string>(20, "vingt"),
		pair<int, string>(30, "trente"),
		pair<int, string>(40, "quarante"),
		pair<int, string>(50, "cinquante"),
		pair<int, string>(60, "soixante"),
		pair<int, string>(100, "cent"),
		pair<int, string>(1000, "mille"),
		pair<int, string>(1000000, "million"),
	};

	return map<int, string>(data, data + sizeof(data) / sizeof(*data));
}

int main()
{
	char *locale;
	locale = setlocale(LC_ALL, "");

	map<int, string> DICT = initMap();
	cout << DICT[999] << endl;
	return 0;
}

