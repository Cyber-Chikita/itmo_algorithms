#pragma once
#include <iostream>

template <typename T>
class CustomArray {
private:
	const size_t default_size_ = 8;
	size_t size_;
	size_t capacity_;
	T* data_;

	void addMemory() {
		T* t_data = new T[++capacity_];
		for (int i = 0; i < size_; i++) {
			t_data[i] = data_[i];
		}
		delete[] data_;
		data_ = t_data;
	}

	void releaseMemory() {
		for (size_t i = 0; i < size_; i++)
		{
			data_[i].~T();
		}

		delete[] data_;
	}
public:

	class Iterator {
	protected:
		T* current_item_;
		size_t* array_size_;
		T* head_item_;
		bool is_reverced_;
	public:
		Iterator(T* current_item, size_t* array_size, bool is_reverced)
			: current_item_(current_item), head_item_(current_item), array_size_(array_size), is_reverced_(is_reverced)
		{
		};

		const T& get() {
			return *current_item_;
		}
		void next() {
			if (is_reverced_) {
				current_item_ -= 1;
			}
			else {
				current_item_ += 1;
			}
		}
		bool hasNext() const {
			if (is_reverced_) {
				return head_item_ - *array_size_ + 1 != current_item_;
			}
			else {
				return head_item_ + *array_size_ - 1 != current_item_;
			}
		}
		void set(const T& value) {
			*current_item_ = value;
		};
	};

	class ConstIterator : public Iterator {
	public:
		ConstIterator(T* current_item, size_t* array_size, bool is_reverced)
			: Iterator(current_item, array_size, is_reverced)
		{
		};
		
		void set(const T& value) = delete;
	};

	Iterator iterator() { return Iterator(data_, &size_, false); }
	ConstIterator const_iterator() { return ConstIterator(data_, &size_, false); }
	Iterator reversed_iterator() { return Iterator(&data_[size_ - 1], &size_, true); }
	ConstIterator const_reverced_iterator() { return ConstIterator(&data_[size_ - 1], &size_, true); }

	CustomArray() : capacity_(default_size_), size_(0), data_(new T[default_size_]) {}

	CustomArray(size_t capacity) : capacity_(capacity), size_(0), data_(new T[capacity]) {}

	~CustomArray() {
		delete[] data_;
	}

	T& operator[](int index) {
		if (index >= 0 && index < size_)
		{
			return data_[index];
		}
		else {
			throw "Index out of range";
		}
	}

	size_t length() {
		return size_;
	}

	size_t capacity() {
		return capacity_;
	}


	T get(size_t i) {
		return data_[i];
	}


	size_t insert(const T& value) {

		if (size_ == capacity_) {
			addMemory();
		}
		data_[size_] = value;

		size_++;

		return size_;
	}


	size_t insert(size_t index, const T& value) {

		if (index >= size_) {
			return -1;
		}
		else if (size_ == capacity_) {
			addMemory();
		}

		size_++;

		for (size_t i = size_ - 1; i > index; i--) {
			data_[i] = std::move(data_[i - 1]);
			data_[i - 1].~T();
		}

		data_[index] = value;

		return size_;
	}

	size_t remove(size_t index) {
		if (index >= size_) {
			return -1;
		}
		else {

			for (size_t i = index; i != size_ - 1; ++i)
			{
				data_[i] = std::move(data_[i + 1]);
				data_[i + 1].~T();
			}

			return --size_;
		}
	}
};
