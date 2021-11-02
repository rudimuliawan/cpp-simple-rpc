//
// Created by rudi on 02/11/21.
//

#include <simple-buffer.hpp>

#include <cstring>

using SimpleRPC::SimpleBuffer;

// Public methods

SimpleBuffer::SimpleBuffer(
) : next_ {0}, size_ {SIMPLE_BUFFER_DEFAULT_SIZE}
{
	start_ = (char *) calloc(1, SIMPLE_BUFFER_DEFAULT_SIZE);
}

SimpleBuffer::~SimpleBuffer()
{
	free(start_);
};

void SimpleBuffer::Serialize(char *data, size_t nbytes)
{
	auto availableSize = size_ - next_;
	auto needToResize = false;

	while (availableSize < nbytes)
	{
		size_ = size_ * 2;
		availableSize = size_ - next_;
		needToResize = true;
	}

	if (!needToResize)
	{
		std::memcpy((char *) start_ + next_, data, nbytes);
		next_ += nbytes;
		return;
	}

	start_ = (char *)std::realloc(start_, size_);
	std::memcpy((char *)start_ + next_, data, nbytes);
	next_ += nbytes;
}

void SimpleBuffer::Deserialize(char *dest, size_t size)
{
	std::memcpy(dest, start_ + next_, size);
	next_ += size;
}

void SimpleBuffer::Skip(size_t skipSize)
{
	if (next_ + skipSize > 0 &&
		next_ + skipSize < size_)
	{
		next_ += skipSize;
	}
}

void SimpleBuffer::SeekToZero()
{
	next_ = 0;
}

void SimpleBuffer::Clear()
{
	free(start_);

	start_ = (char *) calloc(1, SIMPLE_BUFFER_DEFAULT_SIZE);
	next_ = 0;
	size_ = 0;
}


