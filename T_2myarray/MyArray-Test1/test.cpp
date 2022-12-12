#include "pch.h"
#include "../myarray/CustomArray.h"

TEST(MyArrayTest, TestEqualCapability) {
	int capacity = 10;
	CustomArray<int> ar = CustomArray<int>(capacity);
	EXPECT_EQ(ar.capacity(), capacity);
}

TEST(MyArrayTest, TestInsert) {
	CustomArray<int> ar = CustomArray<int>();
	ar.insert(1);
	EXPECT_EQ(ar[0], 1);
}

TEST(MyArrayTest, TestInsertIndex) {
	CustomArray<int> ar = CustomArray<int>();
	ar.insert(3);
	ar.insert(23);
	ar.insert(1, 1);
	EXPECT_EQ(ar[1], 1);
	EXPECT_EQ(ar[2], 23);
}

TEST(MyArrayTest, TestLengthInsert) {
	CustomArray<int> ar = CustomArray<int>();
	ar.insert(3);
	ar.insert(23);
	ar.insert(1, 1);
	EXPECT_EQ(ar.length(), 3);
}

TEST(MyArrayTest, TestLengthRemove) {
	CustomArray<int> ar = CustomArray<int>();
	ar.insert(3);
	ar.insert(23);
	ar.remove(1);
	EXPECT_EQ(ar.length(), 1);
}

TEST(MyArrayTest, TestIterator) {
	CustomArray<int> ar = CustomArray<int>();
	ar.insert(3);
	ar.insert(23);
	auto b = ar.iterator();
	b.set(1);
	EXPECT_EQ(b.get(), 1);
	EXPECT_EQ(ar[0], 1);
	b.next();
	EXPECT_TRUE(!b.hasNext());
}

TEST(MyArrayTest, TestRevercedIterator) {
	CustomArray<int> ar = CustomArray<int>();
	ar.insert(3);
	ar.insert(23);
	auto b = ar.reversed_iterator();
	b.set(1);
	EXPECT_EQ(b.get(), 1);
	EXPECT_EQ(ar[1], 1);
	b.next();
	EXPECT_TRUE(!b.hasNext());
}