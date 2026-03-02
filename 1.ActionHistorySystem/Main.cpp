#include "Container/Queue.h"
#include "Container/Stack.h"

#include "Core/Input.h"

#include <iostream>

static const int commandCount = 5;
static const char commandKey[commandCount] = { 'A', 'B', 'C', 'D', 'E' };

Queue<char> commandQueue;
Stack<char, 30> undoStack;
Stack<char, 30> redoStack;

void Print()
{
	system("cls");

	std::cout << "> Action Histroy System\n\n";
	
	std::cout << "Undo=";
	undoStack.Show();
	std::cout << ", Redo=";
	redoStack.Show();
	std::cout << "\n\n";

	std::cout << "Command: { A, B, C, D, E }\n";
	std::cout << "Undo: { U }, Redo: { R }\n";
	std::cout << "Quit: { Q }\n\n";
	// 새로운 커멘드 입력시 Redo 스택 초기화
}

bool Run()
{
	Input::Instance().ProcessInput();

	if (Input::Instance().GetKeyDown('Q'))
	{
		return false;
	}

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

	if (hasCommandInput)
	{
		Print();
	}

	Input::Instance().SavePreviousInputStates();

	return true;
}

int main()
{
	Print();
	while (Run())
	{
	}
}