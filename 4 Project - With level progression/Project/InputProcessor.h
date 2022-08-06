#pragma once
#include <atomic>
#include <thread>

enum class InputEvent {
	None,
	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight,
	DropKey,
	ExitGame
};

class InputProcessor
{
	std::atomic<bool> m_ThreadShouldRun;
	std::atomic<InputEvent> m_CapturedEvent;
	std::thread* m_InputThread;

public:
	InputProcessor();
	~InputProcessor();
	void Run();
	void Stop();
	InputEvent GetInput();
private:
	void ListenForKeyPress();
};
