#include "DynamicProgramming.h"
#include "BruteForce.h"
#include <nmmintrin.h>
#include <algorithm>
#include <math.h>
#include <iostream>
using namespace std;
/*
	funkcje polegaj¹ na operacjach bitowych
*/

/*
	ustawienie bitu == dodanie do setu
*/
unsigned int addToSet(unsigned int set, int vertex)
{
	return set | 1 << vertex;
}

/*
	wyzerowanie bitu == usuniecie z setu
*/
unsigned int removeFromSet(unsigned int set, int vertex)
{
	return set & ~(1 << vertex);
}

/*
	sprawdzenie, czy bit jest ustawiony
	== czy miasto zostalo odwiedzone
*/
bool isInSet(unsigned int set, int vertex)
{
	if ((set & (1 << vertex)) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/*
	zwraca liczbe zapalonych bitow == ile wierzcholkow zostalo odwiedzonych
	max 32b
*/
int howManyElementsInSet(unsigned int set)
{
	return _mm_popcnt_u32(set);
}

int count(int **lookupCosts, int **lookupPath, int vertex, unsigned int set, int *arr, int **costs, int size) {
	// jak odwiedzone to zwraca mi wage krawedzi
	if (lookupCosts[vertex][set] != INT_MAX) {
		return lookupCosts[vertex][set];
	}

	// sprawdzamy czy jest odwiedzony wierzcholek
	// jak tak to usuwamy go z setu
	if (isInSet(set, vertex)) {
		set = removeFromSet(set, vertex);
	}

	// sprawdzamy ile jest w secie
	// jak jest 0 (== wszystkie sa odwiedzone)
	// to zwracamy wage ostatniej krawedzi
	if (howManyElementsInSet(set) == 0) {
		return costs[vertex][0];
	}
	// w przeciwnym razie
	else {
		int min = INT_MAX;
		int minVertex = INT_MAX;
		for (int i = 0; i < size; i++) {
			// liczy wagi galezi wychodzacych z galezi
			if (isInSet(set, i)) {
				// sprawdza te inne co nie byly odwiedzone
				int tmp = count(lookupCosts, lookupPath, i, removeFromSet(set, i), arr, costs, size) + costs[vertex][i];
				if (tmp < min) {
					// jak mniejsze to podmieniamy
					min = tmp;
					minVertex = i;
				}
			}
		}

		// dajemy znalezione minimum
		lookupCosts[vertex][set] = min;
		lookupPath[vertex][set] = minVertex;

		// zwracamy minimum
		return min;
	}
}

Path * dynamicProgramming(int *arr, int **costs, int size)
{
	Path * result = new Path();
	result->shortestPath = new int[size];

	// n x 2^n i wszystko jako INT_MAX
	// INT_MAX -> nie bylo odwiedzone
	int x = int(pow(2, size) + 0.25);
	int ** myarr = new int *[size];
	for (int i = 0; i < size; i++) {
		myarr[i] = new int[x];
		for (int j = 0; j < x; j++) {
			myarr[i][j] = INT_MAX;
		}
	}

	// uzupelniane razem z myarr
	// do pozniejszego odczytania sciezki
	int ** path = new int *[size];
	for (int i = 0; i < size; i++) {
		path[i] = new int[x];
		for (int j = 0; j < x; j++) {
			path[i][j] = INT_MAX;
		}
	}

	unsigned int set = 0; // 0000...
	for (int i = 1; i < size; i++) {
		set = addToSet(set, i);
	}
	// start: 0
	// wszystkie poza startowym na 1
	// 111...110

	result->cost = count(myarr, path, 0, set, arr, costs, size);
	
	// odczyt sciezki
	result->shortestPath[0] = 0;
	for (int i = 1; howManyElementsInSet(set) > 0; i++) {
		int min = 0;
		for (int j = 0; j < size; j++) {
			if (path[min][set] > path[j][set]) {
				min = j;
			}
		}
		result->shortestPath[i] = path[min][set];
		set = removeFromSet(set, path[min][set]);
	}

	return result;
}
