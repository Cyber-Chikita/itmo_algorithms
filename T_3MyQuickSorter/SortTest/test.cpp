#include "pch.h"
#include <algorithm> 
#include "../MyQuickSorter/QuickSorter.h"

TEST(TestQSort, Size10) {
	const int size = 10;

	int a[size];
	int b[size];

	for (int i = 0; i < size; i++)
	{
		int r = rand() % 100;
		a[i] = r;
		b[i] = r;
	}

	int t = 0;

	std::sort(b, b + size);
	quick_sort(a, a + size - 1, [](int x, int y) { return x < y; }, t);

	bool is_right = true;

	for (int i = 0; i < size; i++)
	{
		if (a[i] != b[i]) {
			is_right = false;
			break;
		}
	}

	EXPECT_TRUE(is_right);
}

TEST(TestQSort, Size50) {
	const int size = 50;

	int a[size];
	int b[size];

	for (int i = 0; i < size; i++)
	{
		int r = rand() % 100;
		a[i] = r;
		b[i] = r;
	}

	int t = 0;

	std::sort(b, b + size);
	quick_sort(a, a + size - 1, [](int x, int y) { return x < y; }, t);

	bool is_right = true;

	for (int i = 0; i < size; i++)
	{
		if (a[i] != b[i]) {
			is_right = false;
			break;
		}
	}

	EXPECT_TRUE(is_right);
}

TEST(TestQSort, Size100) {
	const int size = 100;

	int a[size];
	int b[size];

	for (int i = 0; i < size; i++)
	{
		int r = rand() % 100;
		a[i] = r;
		b[i] = r;
	}

	int t = 0;

	std::sort(b, b + size);
	quick_sort(a, a + size - 1, [](int x, int y) { return x < y; }, t);

	bool is_right = true;

	for (int i = 0; i < size; i++)
	{
		if (a[i] != b[i]) {
			is_right = false;
			break;
		}
	}

	EXPECT_TRUE(is_right);
}

TEST(TestISort, Size10) {
	const int size = 10;

	int a[size];
	int b[size];

	for (int i = 0; i < size; i++)
	{
		int r = rand() % 100;
		a[i] = r;
		b[i] = r;
	}

	int t = 0;

	std::sort(b, b + size);
	insert_sort(a, a + size - 1, [](int x, int y) { return x < y; }, t);

	bool is_right = true;

	for (int i = 0; i < size; i++)
	{
		if (a[i] != b[i]) {
			is_right = false;
			break;
		}
	}

	EXPECT_TRUE(is_right);
}

TEST(TestISort, Size50) {
	const int size = 50;

	int a[size];
	int b[size];

	for (int i = 0; i < size; i++)
	{
		int r = rand() % 100;
		a[i] = r;
		b[i] = r;
	}

	int t = 0;

	std::sort(b, b + size);
	insert_sort(a, a + size - 1, [](int x, int y) { return x < y; }, t);

	bool is_right = true;

	for (int i = 0; i < size; i++)
	{
		if (a[i] != b[i]) {
			is_right = false;
			break;
		}
	}

	EXPECT_TRUE(is_right);
}

TEST(TestISort, Size100) {
	const int size = 100;

	int a[size];
	int b[size];

	for (int i = 0; i < size; i++)
	{
		int r = rand() % 100;
		a[i] = r;
		b[i] = r;
	}

	int t = 0;

	std::sort(b, b + size);
	insert_sort(a, a + size - 1, [](int x, int y) { return x < y; }, t);

	bool is_right = true;

	for (int i = 0; i < size; i++)
	{
		if (a[i] != b[i]) {
			is_right = false;
			break;
		}
	}

	EXPECT_TRUE(is_right);
}