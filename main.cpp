#include <iostream>
#include <climits>
#include <windows.h>
#include "Reader.h"
#include "BruteForce.h"
#include "DynamicProgramming.h"
#include <chrono> 
using namespace std::chrono;

using namespace std;

int main()
{
	char choice;
	Reader * reader;
	Path * p = new Path();
	char name[] = "tsp_10c.txt";
	boolean isRead = false;					// czy graf jest wczytany

	cout << "Menu:" << endl;
	cout << "1. Wczytaj graf" << endl
		 << "2. Wyswietl graf" << endl 
		 << "3. Algorytm Brute Force" << endl 
		 << "4. Programowanie dynamiczne" << endl 
		 << "0. Wyjscie" << endl;

	do {
		cout << "Twoj wybor: ";
		cin >> choice;
		switch (choice)
		{
		case '1':
			reader = new Reader(name);
			isRead = true;
			break;
		case '2':
			if (!isRead) {
				cout << "Graf nie zostal wczytany." << endl;
			}
			else {
				reader->printTab();
			}
			break;
		case '3':
			if (!isRead) {
				cout << "Graf nie zostal wczytany." << endl;
			}
			else {
				p = bruteForce(reader->vertices, reader->tab, reader->elementsNumber);
				printResult(p, reader->elementsNumber);
			}
			break;
		case '4':
			if (!isRead) {
				cout << "Graf nie zostal wczytany." << endl;
			}
			else {
				p = dynamicProgramming(reader->vertices, reader->tab, reader->elementsNumber);
				printResult(p, reader->elementsNumber);
			}
			break;
		case '0':
			break;
		default:
			cout << "Bledny wybor." << endl;
		}
	} while (choice != '0');

    delete reader, p;
    return 0;
}