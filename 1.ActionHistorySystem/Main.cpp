#include "Container/Queue.h"
#include "Container/Stack.h"

#include <iostream>

int main()
{
	Queue<int, 5> commandQueue;

	commandQueue.Push(1);
	commandQueue.Push(2);
	commandQueue.Push(3);
	commandQueue.Push(4);
	commandQueue.Push(5);
	commandQueue.Push(6);

	commandQueue.Pop();
	commandQueue.Pop();

	commandQueue.Push(6);
	commandQueue.Push(6);

	//char inputBuffer[10] = {};
	//while (true)
	//{
	//	std::cin >> inputBuffer;
	//	if (strlen(inputBuffer) == 1)
	//	{
	//		commandQueue.Push(inputBuffer[0]);
	//	}
	//	else if (strcmp(inputBuffer, "undo") == 0)
	//	{

	//	}
	//	else if (strcmp(inputBuffer, "redo") == 0)
	//	{

	//	}
	//	else if (strcmp(inputBuffer, "show") == 0)
	//	{

	//	}
	//}
}