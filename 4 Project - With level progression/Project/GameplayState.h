#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"

#include <windows.h>
#include <vector>
#include <string>

class StateMachineExampleGame;
class InputProcessor;

class GameplayState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	// for multithreading
	InputProcessor* m_pInputProcessor;
	
	Player m_player;
	Level* m_pLevel;

	bool m_DidBeatLevel;
	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 2;

	int m_currentLevel;

	std::vector<std::string> m_LevelNames;

public:
	GameplayState(StateMachineExampleGame* pOwner);
	~GameplayState();

	virtual void Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;

	// allows world to update independent of the player
	//virtual void UpdateWorld();

protected:
	void ProcessInput() override;
	void CheckBeatLevel();

private:
	void HandleCollision(int newPlayerX, int newPlayerY);
	bool Load();
	void DrawHUD(const HANDLE& console);
};
