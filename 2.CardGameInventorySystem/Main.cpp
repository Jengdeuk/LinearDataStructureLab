#include "Core/Input.h"
#include "Container/Vector.h"

#include <windows.h>
#include <iostream>
#include <string>

struct CardInfo
{
	int id = 0;
	std::string name;
	std::string type;
	int cost = 0;
	int rarity = 0;
};

Vector<CardInfo> cardList;
Iterator<Vector<CardInfo>> iter;

void LoadCardList(const char* filename)
{
	FILE* file = nullptr;
	fopen_s(&file, filename, "rt");
	if (file == nullptr)
	{
		return;
	}

	char buffer[4096] = {};
	size_t readSize = fread(buffer, sizeof(char), 4096, file);
	buffer[readSize] = '\0';

	char* lineCtx = nullptr;
	char* line = nullptr;

	line = strtok_s(buffer, "\n", &lineCtx);
	while (line)
	{
		CardInfo newCard;

		char* colCtx = nullptr;
		char* token = nullptr;

		token = strtok_s(line, ",", &colCtx);
		sscanf_s(token, "%d", &newCard.id);

		token = strtok_s(nullptr, ",", &colCtx);
		newCard.name = token;

		token = strtok_s(nullptr, ",", &colCtx);
		newCard.type = token;

		token = strtok_s(nullptr, ",", &colCtx);
		sscanf_s(token, "%d", &newCard.cost);

		token = strtok_s(nullptr, "\0", &colCtx);
		sscanf_s(token, "%d", &newCard.rarity);

		cardList.PushBack(newCard);

		line = strtok_s(nullptr, "\n", &lineCtx);
	}

	fclose(file);
}

void Print()
{
	system("cls");

	std::cout << "> Card Game Inventory System\n\n";

	std::cout << iter->id << ". " << iter->name << '\n';
	std::cout << "Type. " << iter->type << '\n';
	std::cout << "Cost. " << iter->cost << '\n';
	std::cout << "Rarity. " << iter->rarity << "\n\n\n";

	std::cout << "CardChange: { <-, -> }\n";
	std::cout << "Quit: { Q }\n\n";
}

bool Run()
{
	Input::Instance().ProcessInput();

	if (Input::Instance().GetKeyDown('Q'))
	{
		return false;
	}

	bool hasCommandInput = false;

	if (Input::Instance().GetKeyDown(VK_LEFT))
	{
		hasCommandInput = true;
		if (iter == cardList.begin())
		{
			iter = cardList.end() - 1;
		}
		else
		{
			--iter;
		}
	}
	else if (Input::Instance().GetKeyDown(VK_RIGHT))
	{
		hasCommandInput = true;
		if (iter == cardList.end() - 1)
		{
			iter = cardList.begin();
		}
		else
		{
			++iter;
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
	LoadCardList("CardList.txt");
	iter = cardList.begin();
	Print();
	while (Run())
	{
	}
}
