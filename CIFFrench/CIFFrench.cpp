// CIFFrench.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <locale>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cstring>

using namespace std;

map<int, string> DICT {
	    { 0, "zero"},
		{ 1, "un" },
		{ 2, "deux" },
		{ 3, "trois" },
		{ 4, "quatre" },
		{ 5, "cinq" },
		{ 6, "six" },
		{ 7, "sept" },
		{ 8, "huit" },
		{ 9, "neuf" },
		{ 10, "dix" },
		{ 11, "onze" },
		{ 12, "douze" },
		{ 13, "treize" },
		{ 14, "quatorze" },
		{ 15, "quinze" },
		{ 16, "seize" },
		{ 17, "dix-sept" },
		{ 18, "dix-huit" },
		{ 19, "dix-neuf" },
		{ 20, "vingt" },
		{ 30, "trente" },
		{ 40, "quarante" },
		{ 50, "cinquante" },
		{ 60, "soixante" },
		{ 80, "quatre-vingt" },
		{ 100, "cent" },
		{ 1000, "mille" },
		{ 1000000, "million" },
	};

const string INVALID_NUMBER = "Invalid Number!";
const int INVALID_WORDS = -11;

int getDictKey(string word) {
	for (map<int, string>::iterator it = DICT.begin(); it != DICT.end(); ++it) {
		if (it->second == word) {
			return it->first;
		}
	}
	return -1;
}

bool is_number(string so_called_number) {
	if (so_called_number.empty()) return false;
	for (int i = 0; i < so_called_number.length(); i++) {
		if (!isdigit(so_called_number[i])) {
			return false;
		}
	}
	return true;
}

void convert2DigitsToWords(string number, string& words) {
	int actual_number = stoi(number);

	if (DICT[actual_number] != "") {
		if (number.length() == 2 && actual_number == 0) {
			return;
		}
		words += DICT[actual_number];
	}
	else {
		switch (actual_number / 10) {
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 8:
			words += DICT[(actual_number / 10) * 10];
			if (number[1] == '1' && number[0] != '8') {
				words += " et un";
			}
			else if (actual_number == 80) {
				words += "s";
			}
			else {
				words += "-" + DICT[actual_number % 10];
			}
			break;
		case 7:
		case 9:
			words += DICT[(actual_number / 10 - 1) * 10];
			if (actual_number == 71) {
				words += " et ";
			}
			else {
				words += "-";
			}

			words += DICT[(actual_number % 10) + 10];
			break;
		default:
			words += "oops, unknown";
		}
	}
}

void convert3DigitsToWords(string number, string& words) {
	int actual_number = stoi(number);

	if (actual_number == 0) {
		return;
	}

	if (number[0] == '1') {
		words += DICT[100];
	}
	else if (number[0] == '0') {
		convert2DigitsToWords(number.substr(1), words);
		return;
	}
	else {
		words += DICT[actual_number / 100] + " " + DICT[100];
	}
	if (number[1] == '0' && number[2] == '0' && number[0] != '1') {
		words += "s";
	}
	else if (number[1] != '0' || number[2] != '0') {
		words += " ";
		convert2DigitsToWords(number.substr(1), words);
	}
}

void convert6DigitsToWords(string number, string& words) {
	int actual_number = stoi(number);

	if (actual_number == 0) {
		return;
	}
	if (DICT[actual_number] != "") {
		words += DICT[actual_number];
	}
	else {
		if (number.substr(0, number.length() - 3) != "1") {
			if (number.length() == 6) {
				convert3DigitsToWords(number.substr(0, number.length() - 3), words);
			}
			else {
				convert2DigitsToWords(number.substr(0, number.length() - 3), words);
			}
			words += " ";
		}
		if (stoi(number.substr(0, number.length() - 3)) != 0) {
			words += "mille ";
		}
		if (actual_number % 1000 != 0) {
			convert3DigitsToWords(number.substr(number.length() - 3), words);
		}
	}
}

void convert7DigitsToNumber(string number, string& words) {
	int actual_number = stoi(number);

	convert2DigitsToWords(number.substr(0, 1), words);
	words += " " + DICT[1000000];
	if (number[0] != '1') {
		words += "s ";
	}
	convert6DigitsToWords(number.substr(1), words);
}

string convertNumberToWords(string number) {
	string words = "";

	if (number[0] == '-') {
		words += "minus ";
		number.erase(0, 1);
	}

	if (!is_number(number)) {
		return INVALID_NUMBER;
	}

	switch (number.length()) {
		case 1:
		case 2:
			convert2DigitsToWords(number, words);
			break;
		case 3:
			convert3DigitsToWords(number, words);
			break;
		case 4:
		case 5:
		case 6:
			convert6DigitsToWords(number, words);
			break;
		case 7:
			convert7DigitsToNumber(number, words);
			break;
		case 8:
			if (number == "10000000") {
				convert2DigitsToWords(number.substr(0, 2), words);
				words += " " + DICT[1000000] + "s";
			}
			else {
				return INVALID_NUMBER;
			}
			break;
		default:
			return INVALID_NUMBER;
	}

	return words;
}


int convertWordsTo2Digits(vector<string> words) {

	if (empty(words)) {
		return 0;
	}
	if (getDictKey(words[0]) != -1) {
		if (words.size() == 1) {
			return getDictKey(words[0]);
		}
		else {
			if (words[2] == "un") {
				return getDictKey(words[0]) + 1;
			}
			else {
				return getDictKey(words[0]) + 11;
			}
		}
	}
	else if (words[0] == DICT[80] + "s") {
		return getDictKey(DICT[80]);
	}
	else {
		int delim = words[0].find("-");
		if (words[0].substr(0, delim) == "quatre") {
			delim = words[0].find("-", delim + 1);
		}
		if (getDictKey(words[0].substr(0, delim)) != -1) {
			if (getDictKey(words[0].substr(delim + 1)) != -1) {
				return getDictKey(words[0].substr(0, delim)) + getDictKey(words[0].substr(delim + 1));
			}
		}
	}
	return INVALID_WORDS;
}

int convertWordsTo3Digits(vector<string> words) {
	int number = 0;
	int i = 0;
	vector<string> temp_words;

	while (i < words.size() && words[i] != "cent" && words[i] != "cents") {
		i++;
	}

	if (i < words.size()) {
		if (i > 0) {
			for (int j = 0; j < i; j++) {
				temp_words.push_back(words[j]);
			}

			int result = convertWordsTo2Digits(temp_words) * 100;
			if (result < 0) {
				return INVALID_WORDS;
			}
			number = result;
		}
		else {
			number = 100;
		}

		if (words[i] == "cent") {
			temp_words.clear();
			for (int j = i + 1; j < words.size(); j++) {
				temp_words.push_back(words[j]);
			}

			int result = convertWordsTo2Digits(temp_words);
			if (result < 0) {
				return INVALID_WORDS;
			}
			number += result;
		}
	}
	else {
		int result = convertWordsTo2Digits(words);
		if (result < 0) {
			return INVALID_WORDS;
		}
		number = result;
	}

	return number;
}

int convertWordsToNumber(vector<string> words) {
	int number = 0;
	int i = 0;
	vector<string> temp_words;
	bool negative = false;

	if (words[0] == "minus") {
		negative = true;
		words.erase(words.begin());
	}
	
	while (i < words.size() && words[i] != "million" && words[i] != "millions") {
		i++;
	}
	if (i < words.size()) {
		int j = 0;
		for (int j = 0; j < i; j++) {
			temp_words.push_back(words[j]);
		}
		auto it = next(words.begin(), i+1);
		words.erase(words.begin(), it);

		int result = convertWordsTo2Digits(temp_words) * 1000000;
		if (result < 0) {
			return INVALID_WORDS;
		}
		number = result;
	}

	i = 0;
	while (i < words.size() && words[i] != "mille") {
		i++;
	}
	if (i < words.size()) {
		if (i > 0) {
			int j = 0;
			temp_words.clear();
			for (int j = 0; j < i; j++) {
				temp_words.push_back(words[j]);
			}
			int result = convertWordsTo3Digits(temp_words) * 1000;
			if (result < 0) {
				return INVALID_WORDS;
			}
			number += result;
		}
		else {
			number += 1000;
		}

		temp_words.clear();
		for (int j = i + 1; j < words.size(); j++) {
			temp_words.push_back(words[j]);
		}

		int result = convertWordsTo3Digits(temp_words);
		if (result < 0) {
			return INVALID_WORDS;
		}
		number += result;
	}
	else {
		int result = convertWordsTo3Digits(words);
		if (result < 0) {
			return INVALID_WORDS;
		}
		number += result;
	}
	 
	if (number < 0) {
		return INVALID_WORDS;
	}
	if (negative) {
		return number * -1;
	}
	return number;
}

int main()
{
	char *locale;
	locale = setlocale(LC_ALL, "");
	int stop = 0;
	string sir;

	while (stop == 0) {
		cout << "\n\nIntrodu numarul sau cuvintele pe care le doresti convertite. 'stop' pentru iesire." << endl;
		getline(std::cin, sir);

		if (isdigit(sir[0]) || sir[0] == '-') {
			cout << "Nrul ca sir de caractere: " + convertNumberToWords(sir);
		} else if (sir == "stop" || sir == "") {
			stop = 1;
		} else {
			stringstream iss(sir);
			vector<string> tokens{ istream_iterator<string>{iss},
				istream_iterator<string>{} };
			int result = convertWordsToNumber(tokens);
			if (result == INVALID_WORDS) {
				cout << INVALID_NUMBER;
			}
			else {
				cout << "Nrul ca sir de cifre: ";
				cout << result;
			}
		}

	}
	return 0;
}

