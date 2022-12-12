#include <iostream>
#include "QuickSorter.h"
#include <algorithm> 

using namespace std;


int main()
{
	const int size = 300;

	int a[size];
	int b[size];

	for (int i = 0; i < size; i++)
	{
		int r = rand() % 100;
		a[i] = r;
		b[i] = r;
	}

	for (int j = 3; j <= size; j += 3)

	{
		int q_transposition = 0;
		int i_transposition = 0;
		int q_amountTransposition = 0;
		int i_amountTransposition = 0;
		for (size_t x = 0; x < 30; x++)
		{
			for (int i = 0; i < j; i++)
			{
				int r = rand() % 100;
				a[i] = r;
			}

			quick_sort<int>(a, a + j - 1, [](int x, int y) { return x < y; }, q_transposition);
			q_amountTransposition += q_transposition;
			q_transposition = 0;

			for (int i = 0; i < j; i++)
			{
				int r = rand() % 100;
				a[i] = r;
			}

			insert_sort<int>(a, a + j - 1, [](int x, int y) { return x < y; }, i_transposition);
			i_amountTransposition += i_transposition;
			i_transposition = 0;
		}

		cout << j << "|" << q_amountTransposition / 30 << "|" << i_amountTransposition / 30 << endl;
	}
}

