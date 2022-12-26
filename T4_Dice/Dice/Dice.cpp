
#include <iostream>
#include "Dice.h"


int main()
{

	char cs[] = "1d20,1d6+2,5d8+4";
	std::cout << Dice::throwsDices(cs) << std::endl;

	//const int range = 18;

	//char c[] = "3d6";

	//Dice dice = Dice(c);

	//int a[range];


	//for (int i = 0; i < range; i++)
	//{
	//	a[i] = 0;
	//}

	//for (int i = 0; i < 1000; i++)
	//{
	//	a[dice.throwDice() - 1]++;
	//}

	//for (int i = 0; i < range; i++)
	//{
	//	std::cout << i + 1 << "|" << a[i] << std::endl;
	//}

	//return 1;
}

