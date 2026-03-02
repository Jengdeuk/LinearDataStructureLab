#pragma once

#include <utility>
#include <cstring>
#include <cassert>

template <typename ContainerType>
class Iterator
{
public:
	using T = typename ContainerType::ValueType;

public:
	Iterator() = default;
	Iterator(T* ptr)
		: ptr(ptr)
	{
	}

	Iterator& operator++()
	{
		++ptr;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator iter = *this;
		++ptr;
		return iter;
	}

	Iterator& operator--()
	{
		--ptr;
		return *this;
	}

	Iterator operator--(int)
	{
		Iterator iter = *this;
		--ptr;
		return iter;
	}

	Iterator operator+(int num)
	{
		return Iterator(ptr + num);
	}

	Iterator operator-(int num)
	{
		return Iterator(ptr - num);
	}

	T* operator->()
	{
		return ptr;
	}

	T& operator*()
	{
		return *ptr;
	}

	bool operator==(const Iterator& other) const
	{
		return ptr == other.ptr;
	}

	bool operator!=(const Iterator& other) const
	{
		return !(*this == other);
	}

private:
	T* ptr = nullptr;
};

template <typename T>
class Vector
{
public:
	using Iter = Iterator<Vector<T>>;
	using ValueType = T;

public:
	Vector()
	{
		Reserve(capacity);
	}

	~Vector()
	{
		if (data)
		{
			delete[] data;
		}
	}

public:
	void PushBack(const T& value)
	{
		if (IsFull())
		{
			Reserve(capacity * 2);
		}

		data[size++] = value;
	}

	void PushBack(T&& value)
	{
		if (IsFull())
		{
			Reserve(capacity * 2);
		}

		data[size++] = std::move(value);
	}

	void PopBack()
	{
		if (IsEmpty)
		{
			return;
		}

		--size;
	}

	Iter Erase(const Iter& iter)
	{
		Iter temp = iter;
		while (iter + 1 != this->end())
		{
			*iter = *(iter + 1);
			++iter;
		}

		return temp;
	}

	const T& Back()
	{
		if (IsEmpty())
		{
			return T{};
		}

		return data[size - 1];
	}

	T& operator[](int index)
	{
		assert(index >= 0 && index < size);
		return data[index];
	}

	Iter begin()
	{
		return Iter(data);
	}

	Iter end()
	{
		return Iter(data + size);
	}

public:
	bool IsEmpty()
	{
		return size == 0;
	}

	bool IsFull()
	{
		return size == capacity;
	}

	void Clear()
	{
		size = 0;
	}

	void Reserve(int newCapacity)
	{
		T* newBlock = new T[newCapacity];
		for (int i = 0; i < size; ++i)
			newBlock[i] = std::move(data[i]);

		delete[] data;
		data = newBlock;
		capacity = newCapacity;
	}

public:
	inline int Size() const { return size; }
	inline int Capacity() const { return capacity; }

private:
	int size = 0;
	int capacity = 2;
	T* data = nullptr;
};
