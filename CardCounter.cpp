// CardCounter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>

#include <windows.h>

static double truecount(int cardscounted, int running, double decks) {
    return double(running) / (((decks*52)-cardscounted)/52);
}

static void printCardsOut(const std::map<char, int> &cardsOut, int decks) {
	for (std::map<char, int>::const_iterator iter = cardsOut.cbegin(); iter != cardsOut.end(); ++iter) {
		std::cout << "[" << iter->first << "-" << (4 * decks) - iter->second << "]  ";
	}
    std::cout << "\n";
}

static void printCount(int count, int cardscounted, int decks) {
	std::cout << "Count: " << count << "\n" << "True: " << truecount(cardscounted, count, decks) << "\n";
}

int main()
{
    std::string output = "";

    double decks = 1;
    std::cout << "Number of decks: ";
    std::cin >> decks;
    if (decks == 0) {
        decks = 1;
    }
    output += "Decks:" + std::to_string(decks);

    boolean doOutput = false;
    {
        std::cout << "Write result to output file? (y/n): ";
        char temp;
        std::cin >> temp;
        (temp == 'y') ? doOutput = true : doOutput = false;
    }

    int count = -2*decks;
    int cardscounted = 0;
    bool run = true;

    const std::set<char> symbols = {'a', 'k', 'q', 'j', 't', '9', '8', '7', '6', '5', '4', '3', '2'};

    std::map<char, short> values;
    for (std::set<char>::iterator iter = symbols.begin(); iter != symbols.end(); ++iter) {
        int val = int(*iter)-int('0');
        
        if (val >= 2 && val <= 6) {
            values[*iter] = 1;
        }
        else if (val >= 7 && val <= 9) {
            values[*iter] = 0;
        }
        else {
            values[*iter] = -1;
        }
    }

    std::map<char, char> keymap;
    keymap['+'] = 'a';
    keymap['-'] = 'k';
    keymap['*'] = 'q';
    keymap['/'] = 'j';
    keymap['0'] = 't';
    keymap['9'] = '9';
    keymap['8'] = '8';
    keymap['7'] = '7';
    keymap['6'] = '6';
    keymap['5'] = '5';
    keymap['4'] = '4';
    keymap['3'] = '3';
    keymap['2'] = '2';

    const char seperator = ',';
    const char promptMessage[] = "Input card(s): ";

	std::map<char, int> cardsOut;
    //std::vector<int> cardsOut(13);
    for (std::map<char,short>::iterator iter = values.begin(); iter != values.end(); ++iter) {
        cardsOut[iter->first] = 0;
    }
    //Position coding A = 0, 2-K = 2-12

    printCount(count, cardscounted, decks);
	std::cout << promptMessage;

    while (run) {
        boolean print = false;
        char symbol;
        std::cin >> symbol;
		std::cout << symbol << "\n";

        if (symbol == seperator) {
            print = true;
        }
        if (symbol == 'e') {
            break;
        }

        if (print) {
            output += "\n";
        }
        else if (symbols.count(keymap[symbol])) {
			cardscounted++;
            count += values[keymap[symbol]];
            cardsOut[keymap[symbol]]++;
            output += symbol;
        }


        printCardsOut(cardsOut, decks);

        if (print) {
            printCount(count, cardscounted, decks);
            std::cout << promptMessage;
        }
		//std::cout << "True: " << truecount(cardscounted, count, decks) << "\n";

    }
    if (doOutput) {
        FILE* output_file;

        if (fopen_s(&output_file, (std::to_string(static_cast<long int> (time(NULL))) + ".data").c_str(), "w") == 0) {
            fwrite(output.c_str(), sizeof(char), output.length(), output_file);
        }
        else {
            std::cout << "Error opening file for writing...";
        }
    }
    {
        char temp;
        std::cout << "Any key to exit: ";
        std::cin >> temp;
    }
    _fcloseall();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
