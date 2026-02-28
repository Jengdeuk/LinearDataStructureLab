#include "Container/Queue.h"
#include "Container/Stack.h"

#include "Core/Input.h"

#include <iostream>

static const int commandCount = 5;
static const char commandKey[commandCount] = { 'A', 'B', 'C', 'D', 'E' };

Queue<char> commandQueue;
Stack<char> undoStack;
Stack<char> redoStack;

void Print()
{
	system("cls");

	std::cout << "KeyInfo: Quit{ Q }, Command{ A, B, C, D, E }, Undo{ U }, Redo{ R }\n\n";
	// 새로운 커멘드 입력시 Redo 스택 초기화
	
	std::cout << "Undo=";
	undoStack.Show();
	std::cout << ", Redo=";
	redoStack.Show();
	std::cout << '\n';
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