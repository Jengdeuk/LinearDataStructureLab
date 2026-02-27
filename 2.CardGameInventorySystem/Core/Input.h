#pragma once

class Input
{
	struct KeyState
	{
		bool isKeyDown = false;
		bool wasKeyDown = false;
	};

private:
	Input();
	~Input();

	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

public:
	static Input& Instance();

public:
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);
	bool GetKey(int keyCode);

public:
	void ProcessInput();
	void SavePreviousInputStates();

private:
	KeyState keyState[255] = {};
};
