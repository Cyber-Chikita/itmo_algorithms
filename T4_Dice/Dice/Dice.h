#pragma once
#include <iostream>


class Dice
{
private:
	int range_;
	int throws_count_;
	int modifier_;

	int my_rand() {
		return rand() % range_ + 1;
	}
public:
	Dice(int range, int throws_count, int modifier = 0) : range_(range), throws_count_(throws_count), modifier_(modifier) {}

	Dice(const char* dice) {
		int range = 0;
		int throws_count = 0;
		int modifier = 0;

		int item_index = 0;

		while (*dice) {
			if (isdigit(*dice)) {
				switch (item_index)
				{
				case 0:
					throws_count += throws_count * 9 + (int)*dice - 48;
					break;
				case 1:
					range += range * 9 + (int)*dice - 48;
					break;
				case 2:
					modifier += modifier * 9 + (int)*dice - 48;
					break;
				default:
					break;
				}
			}
			else {
				item_index++;
			}
			dice++;
		}

		range_ = range;
		throws_count_ = throws_count;
		modifier_ = modifier;
	}


	int throwDice() {
		int amount = 0;

		for (int i = 0; i < throws_count_; i++)
		{
			amount += my_rand();
		}

		return amount + modifier_;
	}

	static int throwsDices(Dice* dices, int size) {
		int amount = 0;
		for (int i = 0; i < size; i++)
		{
			(dices + i)->throwDice();
		}

		return amount;
	}


	static int throwsDices(char* dices) {
		int amount = 0;

		int index = 0;
		int l_index = 0;

		while (*dices)
		{
			if (*dices == ',') {
				int t_index = index - l_index;
				char* d = new char[t_index+1];
				strncpy_s(d, t_index+1, dices - t_index, t_index);
				amount += Dice(d).throwDice();
				l_index = index + 1;
				delete[] d;
			}
			index++;
			dices++;
		}

		int t_index = index - l_index;
		char* d = new char[t_index+1];
		strncpy_s(d, t_index + 1, dices - t_index, t_index);
		amount += Dice(d).throwDice();

		delete[] d;

		return amount;
	}
};

