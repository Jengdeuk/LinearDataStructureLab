#pragma once

template <typename T, int capacity = 10>
class Queue
{
public:
	void Push(const T& value)
	{
		if (IsFull())
		{
			return;
		}

		data[rear] = value;

		rear = (rear + 1) % (capacity + 1);
	}

	void Pop()
	{
		if (IsEmpty())
		{
			return;
		}

		front = (front + 1) % (capacity + 1);
	}

	const T& Front()
	{
		if (IsEmpty())
		{
			return T{};
		}

		return data[front];
	}

public:
	bool IsEmpty()
	{
		return front == rear;
	}

	bool IsFull()
	{
		return Size() == capacity;
	}

	int Size()
	{
		if (IsEmpty())
		{
			return 0;
		}

		return (front < rear) ? rear - front : rear + (capacity + 1) - front;
	}

	void Clear()
	{
		front = 0;
		rear = 0;
	}

private:
	int front = 0;
	int rear = 0;
	T data[capacity + 1]{};
};