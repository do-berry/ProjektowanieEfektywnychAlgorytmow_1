#include "BruteForce.h"
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

/*
	wyznaczanie sumy kosztow
*/
int sumCosts(int *arr, int **costs, int size)
{
	int sum = 0;
	for (int i = 1; i < size; i++)
	{
		sum += costs[arr[i - 1]][arr[i]];
	}
	sum += costs[arr[size - 1]][arr[0]];
	return sum;
}

/*
	kopiowanie tablicy
*/
void copyArray(int *from, int *to, int size)
{
	for (int i = 0; i < size; i++)
	{
		from[i] = to[i];
	}
}

/*
	zamiana wartosci
*/
void swapValues(int &first, int &second)
{
	int copy = first;
	first = second;
	second = copy;
}

/*
	permutowanie  tablicy arr i wyznaczanie kosztu permutacji
*/
void permute(Path *result, int counter, int *arr, int size, int **costs)
{
	if (counter == 0)
	{
		if (result->cost > sumCosts(arr, costs, size))
		{
			result->cost = sumCosts(arr, costs, size);
			copyArray(result->shortestPath, arr, size);
		}
	}
	else {
		for (int i = counter - 1; i >= 0; i--)
		{
			swapValues(arr[i], arr[counter - 1]);
			permute(result, counter - 1, arr, size, costs);
			swapValues(arr[i], arr[counter - 1]);
		}
	}
}

/*
	sortowanie tablicy + permutowanie i znajdowanie
	najlepszego rozwiazania
	: zwraca strukture Path (-> BruteForce.h)
*/
Path *bruteForce(int *arr, int **costs, int size)
{
	Path *result = new Path();
	
	// wartosci poczatkowe: zeby bylo do czego porownywac
	result->cost = sumCosts(arr, costs, size);
	result->shortestPath = new int[size];
	for (int i = 0; i < size; i++) {
		result->shortestPath[i] = i;
	}

	sort(arr, arr + size);

	permute(result, size, arr, size, costs);

	return result;
}

/*
	wypisywanie wyniku
*/
void printResult(Path *p, int size)
{
	cout << "Koszt: " << p->cost << ", sciezka: ";
	for (int i = 0; i < size; i++)
	{
		cout << p->shortestPath[i] << "->";
	}
	cout << p->shortestPath[0] << endl;
}
