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
		// _count is never 0 because of the is_empty guard above
		_count -= 1;

		return std::optional<T>(item);
	}
}

template<class T>
void RingBuffer<T>::push(T item)
{
	_items[_write_index] = item;
	_write_index = clamp_index(_write_index + 1);
	
	// Only increment _count if the buffer isn't already full.
	// If it's full we've just overwritten data, not expanded the buffer!
	if (_count != _capacity) {
		_count += 1;
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
	// everything else is an int, but this is a heap-allocated array.
	delete[] _items;
}

template<class T>
unsigned int RingBuffer<T>::clamp_index(unsigned int index)
{
	// stops out-of-bounds indexing
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
	// add some extra values that will overflow the buffer, oh no :(
	buffer.push(4);
	buffer.push(5);

	while (!buffer.is_empty()) {
		std::optional<int> result = buffer.pop();
		
		// result will never be nullopt if is_empty returned true, so this is safe.
		int value = result.value();
		std::cout << value << std::endl;
	}
}