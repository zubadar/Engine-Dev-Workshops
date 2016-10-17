#include "Engine.h"
#include "GameState.h"
#include <cstdio>

Engine::Engine() { }

void Engine::Go() {
	Init();
	SetupGame();
	GameLoop();
	CleanUp();
}

void Engine::Init() {
	_window.create(sf::VideoMode(800, 600), "Game", sf::Style::Close);
}

void Engine::SetupGame() {
	_currentState = new GameState(&_window);
}

void Engine::GameLoop() {
	while (_currentState != nullptr) {
		_currentState = _currentState->Run();
	}
}

void Engine::CleanUp() {
	_window.close();
}