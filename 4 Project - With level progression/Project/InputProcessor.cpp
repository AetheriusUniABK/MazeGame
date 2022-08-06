#include "InputProcessor.h"
#include <windows.h>
#include <conio.h>

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

/*
	TODO: Make this a singleton, and update it so that all screens and states can use this.
*/

InputProcessor::InputProcessor()
	: m_CapturedEvent(InputEvent::None)
	, m_InputThread(nullptr)
{
}

InputProcessor::~InputProcessor()
{

}

void InputProcessor::Run() {
	m_ThreadShouldRun.store(true);
	m_InputThread = new std::thread(&InputProcessor::ListenForKeyPress, this);
}

void InputProcessor::Stop() {
	m_ThreadShouldRun.store(false);
	m_InputThread->join();
}

InputEvent InputProcessor::GetInput() {
	return m_CapturedEvent.exchange(InputEvent::None);
}

void InputProcessor::ListenForKeyPress() {
	while (m_ThreadShouldRun.load()) {
		
		int input = _getch();
		int arrowInput = 0;

		// One of the arrow keys were pressed
		if (input == kArrowInput)
		{
			arrowInput = _getch();
		}

		if ((input == kArrowInput && arrowInput == kLeftArrow) ||
			(char)input == 'A' || (char)input == 'a')
		{
			m_CapturedEvent.store(InputEvent::MoveLeft);
		}
		else if ((input == kArrowInput && arrowInput == kRightArrow) ||
			(char)input == 'D' || (char)input == 'd')
		{
			m_CapturedEvent.store(InputEvent::MoveRight);
		}
		else if ((input == kArrowInput && arrowInput == kUpArrow) ||
			(char)input == 'W' || (char)input == 'w')
		{
			m_CapturedEvent.store(InputEvent::MoveUp);
		}
		else if ((input == kArrowInput && arrowInput == kDownArrow) ||
			(char)input == 'S' || (char)input == 's')
		{
			m_CapturedEvent.store(InputEvent::MoveDown);
		}
		else if (input == kEscapeKey)
		{
			m_CapturedEvent.store(InputEvent::ExitGame);
		}
		else if ((char)input == 'Z' || (char)input == 'z')
		{
			m_CapturedEvent.store(InputEvent::DropKey);
		}
	}
}