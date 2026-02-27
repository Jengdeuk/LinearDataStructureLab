#pragma once

#include <iostream>

template <typename T, int capacity = 10>
class Stack
{
public:
	void Push(const T& value)
	{
		if (IsFull())
		{
			return;
		}

		data[++top] = value;
	}

	void Pop()
	{
		if (IsEmpty())
		{
			return;
		}

		--top;
	}

	const T& Top()
	{
		if (IsEmpty())
		{
			return T{};
		}

		return data[top];
	}

public:
	bool IsEmpty()
	{
		return Size() == 0;
	}

	bool IsFull()
	{
		return top == capacity - 1;
	}

	int Size()
	{
		return top + 1;
	}

	void Clear()
	{
		top = -1;
	}

public:
	void Show()
	{
		if (IsEmpty())
		{
			std::cout << "[]";
			return;
		}

		std::cout << '[';
		for (int i = 0; i < top; ++i)
		{
			std::cout << data[i] << ", ";
		}
		std::cout << data[top];
		std::cout << ']';
	}

private:
	int top = -1;
	T data[capacity]{};
};