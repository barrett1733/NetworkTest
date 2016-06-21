#pragma once
#include <mutex>

template <typename T>
class Buffer
{
	struct Wrapper
	{
		bool bad = true;
		T pck;
		std::mutex mutex;
	};

	Wrapper* buffer;
	int bufferSize;
	int bufferAlloc;
	void set(int i, T pck);

public:
	Buffer();
	Buffer(int size);
	~Buffer();
	bool push(T);
	void invalidate(int i);
	int size();
	bool empty();
	bool full();
	// -?- Maybe make pointer and add packet factory here
	T get(int i);
};

template <typename T>
Buffer<T>::Buffer() : Buffer(100)
{}

template <typename T>
Buffer<T>::Buffer(int _size)
{
	bufferSize = _size;
	bufferAlloc = 0;
	buffer = new Wrapper[bufferSize];
}

template <typename T>
Buffer<T>::~Buffer()
{
	delete[] buffer;
	buffer = NULL;
}

template <typename T>
bool Buffer<T>::push(T pck)
{
	if (!full())
	{
		for (int i = 0; i < bufferSize; i++)
		{
			if (buffer[i].bad)
			{
				set(i, pck);
				buffer[i].bad = false;
				bufferAlloc++;
				return true;
			}
		}
	}
	return false;
}

template <typename T>
void Buffer<T>::invalidate(int loc)
{
	buffer[loc].mutex.lock();
	buffer[loc].bad = true;
	buffer[loc].mutex.unlock();
	bufferAlloc--;
}

template <typename T>
int Buffer<T>::size()
{
	return bufferAlloc;
}

template <typename T>
T Buffer<T>::get(int loc)
{
	return buffer[loc].pck;
}

template <typename T>
void Buffer<T>::set(int loc, T pck)
{
	buffer[loc].mutex.lock();
	buffer[loc].pck = pck;
	buffer[loc].mutex.unlock();
}

template <typename T>
bool Buffer<T>::empty()
{
	return bufferSize == 0 ? true : false;
}

template <typename T>
bool Buffer<T>::full()
{
	return bufferSize == bufferAlloc ? true : false;
}
