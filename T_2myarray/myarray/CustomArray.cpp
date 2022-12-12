#include "CustomArray.h"


//template<typename T>
//CustomArray<T>::CustomArray(size_t size) : size_(size), data_(new T[size]) {}

//template<typename T>
//CustomArray<T>::~CustomArray() {
//	delete[] data_;
//}
//
//template<typename T>
//size_t CustomArray<T>::size() {
//	return size_;
//}
//
//template<typename T>
//T CustomArray<T>::get(size_t i) {
//	return data_[i];
//}
//
//template<typename T>
//size_t CustomArray<T>::length() {
//	for (int i = 0; i < size_; i++) {
//		if (!data_[i]) {
//			return i + i;
//		}
//	}
//	return size_;
//}
//
//template<typename T>
//int CustomArray<T>::insert(const T& value) {
//	size_t length = length();
//	if (length == size_) {
//		T* t_data = new T[++size_];
//		for (int i = 0; i < length; i++) {
//			t_data[i] = data_[i];
//		}
//		delete[] data_;
//		data_ = t_data;
//
//	}
//	data_[length] = value;
//
//	return length;
//}
//
////template<typename T>
////int CustomArray<T>::insert(int index, const T& value) {
////	size_t length = length();
////	if (length == size_) {
////		T* t_data = new T[++size_];
////		for (int i = 0; i < length; i++) {
////			t_data[i] = data_[i];
////		}
////		delete[] data_;
////		data_ = t_data;
////
////	}
////	data_[length] = value;
////
////	return length;
////}