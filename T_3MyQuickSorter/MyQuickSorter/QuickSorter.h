#pragma once

#include <iostream>

template<typename T, typename Compare>
void quick_sort(T* first, T* last, Compare comp, int& comparations) {

	T* left = first;
	T* right = last;

	while (left < right) {
		if (right - left < 15) {
			insert_sort(first, last, comp, comparations);
			return;
		}

		const T mid_value = find_mediana(left, right, comp);

		comparations += 3;

		T* p = divide_on_parts(left, right, mid_value, comp, comparations);

		if (right - p > p - left)
		{
			quick_sort(left, p, comp, comparations);
			left = p + 1;
		}
		else
		{
			quick_sort(p + 1, right, comp, comparations);
			right = p;
		}
	}
};

template<typename T, typename Compare>
T find_mediana(T* first, T* last, Compare comp) {
	T* mid = first + (last - first) / 2;
	if (comp(*mid, *first)) std::swap(*mid, *first);
	if (comp(*last, *first)) std::swap(*last, *first);
	if (comp(*last, *mid)) std::swap(*last, *mid);

	return *mid;
}

template<typename T, typename Compare>
T* divide_on_parts(T* first, T* last, T mid_value, Compare comp, int& comparations) {
	T* i = first;
	T* j = last;

	while (true) {
		while (comp(*i, mid_value)) {
			i++;
			comparations++;
		}
		while (comp(mid_value, *j)) {
			j--;
			comparations++;
		}
		comparations++;
		comparations++;

		if (i >= j) {
			break;
		}
		std::swap(*i, *j);
		i++;
		j--;
	}

	return j;
}

template<typename T, typename Compare>
void insert_sort(T* first, T* last, Compare comp, int& comparations) {
	if (!first || !last) throw std::exception("Nullptr in args!");

	if (first == last) return;

	T tmp;
	T* j;

	for (auto i = first + 1; i <= last; i++)
	{
		tmp = (*i);
		j = i;

		for (j; j > first && comp(tmp, *(j - 1)); j--)
		{
			*j = std::move(*(j - 1));
			comparations += 2;
		}

		*j = std::move(tmp);
	}
}


