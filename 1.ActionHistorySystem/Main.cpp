#include "Container/Queue.h"
#include "Container/Stack.h"

#include "Core/Input.h"

#include <iostream>

static const int commandCount = 5;
static const char commandKey[commandCount] = { 'A', 'B', 'C', 'D', 'E' };

int main()
{
	Queue<char> commandQueue;
	Stack<char> undoStack;
	Stack<char> redoStack;

	char inputBuffer[10] = {};
	while (true)
	{
		Input::Instance().ProcessInput();

		bool hasCommandInput = false;
		for (int i = 0; i < commandCount; ++i)
		{
			if (Input::Instance().GetKeyDown(commandKey[i]))
			{
				hasCommandInput = true;

				commandQueue.Push(commandKey[i]);
				undoStack.Push(commandQueue.Front());
				commandQueue.Pop();

				redoStack.Clear();
			}
		}
		
		if (!hasCommandInput)
		{
			if (!undoStack.IsEmpty() && Input::Instance().GetKeyDown('U'))
			{
				hasCommandInput = true;
				redoStack.Push(undoStack.Top());
				undoStack.Pop();
			}
			else if (!redoStack.IsEmpty() && Input::Instance().GetKeyDown('R'))
			{
				hasCommandInput = true;
				undoStack.Push(redoStack.Top());
				redoStack.Pop();
			}
		}

		Input::Instance().SavePreviousInputStates();

		if (hasCommandInput)
		{
			system("cls");
			std::cout << "Undo=";
			undoStack.Show();
			std::cout << ", Redo=";
			redoStack.Show();
			std::cout << '\n';
		}
	}
}