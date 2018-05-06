#pragma once

#include <optional>

template<class T>
class RingBuffer {
public:
	// Pops an item off of the queue
	std::optional<T> pop();
	// Pushes an item onto the queue, overwriting an old item if necessary
	void push(T);
	// The capacity of the queue
	unsigned int capacity();
	// Whether the queue is empty or not
	bool is_empty();

	// Creates a new RingBuffer with a given capacity
	RingBuffer(unsigned int);
	~RingBuffer();
private:
	// Clamps an index between 0 and _capacity - 1
	unsigned int clamp_index(unsigned int);

	// The items in the buffer
	T * _items;
	// How big the allocated array is
	unsigned int _capacity;
	// Where we're writing items to
	unsigned int _write_index;
	// Where we're reading items from
	unsigned int _read_index;
	// The number of items we currently have in the buffer
	unsigned int _count;
};