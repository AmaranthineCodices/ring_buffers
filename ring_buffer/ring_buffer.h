#pragma once

#include <optional>

template<class T>
class RingBuffer {
public:
	std::optional<T> pop();
	void push(T);
	unsigned int capacity();
	bool is_empty();

	RingBuffer(unsigned int);
	~RingBuffer();
private:
	unsigned int clamp_index(unsigned int);

	T * _items;
	unsigned int _capacity;
	unsigned int _write_index;
	unsigned int _read_index;
	unsigned int _count;
};