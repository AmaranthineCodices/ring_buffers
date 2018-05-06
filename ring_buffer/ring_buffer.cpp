#include <optional>
#include <iostream>

#include "ring_buffer.h"

template<class T>
bool RingBuffer<T>::is_empty() {
	return _count == 0;
}

template<class T>
std::optional<T> RingBuffer<T>::pop() {
	if (is_empty()) {
		return std::nullopt;
	}
	else {
		T item = _items[_read_index];

		_read_index = clamp_index(_read_index + 1);
		_count -= 1;

		return std::optional<T>(item);
	}
}

template<class T>
void RingBuffer<T>::push(T item)
{
	_items[_write_index] = item;
	_write_index = clamp_index(_write_index + 1);
	
	if (_count != _capacity) {
		count += 1;
	}
}

template<class T>
unsigned int RingBuffer<T>::capacity() {
	return _capacity;
}

template<class T>
RingBuffer<T>::RingBuffer(unsigned int buffer_capacity)
{
	_items = new T[buffer_capacity];
	_capacity = buffer_capacity;
	_read_index = 0;
	_write_index = 0;
	_count = 0;
}

template<class T>
RingBuffer<T>::~RingBuffer() {
	delete[] _items;
}

template<class T>
unsigned int RingBuffer<T>::clamp_index(unsigned int index)
{
	if (index >= _capacity) {
		return 0;
	}
	else {
		return index;
	}
}

int main(int argc, char** argv) {
	RingBuffer<int> buffer(3);
	buffer.push(1);
	buffer.push(2);
	buffer.push(3);
	buffer.push(4);
	buffer.push(5);

	while (!buffer.is_empty()) {
		std::optional<int> result = buffer.pop();

		if (result) {
			int value = result.value();
			std::cout << "value: " << value << std::endl;
		}
	}

	system("pause");
}