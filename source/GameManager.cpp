//
// Created by Saul Moreno Abril on 18/02/2018.
//

#include "GameManager.h"

void GameManager::setPause(bool pause) {
    _pause = pause;
}

bool GameManager::getPause(){
    return _pause;
}

void GameManager::setGameState(GameManager::GameState state) {
    _gameState = state;
}

GameManager::GameState GameManager::getGameState() {
    return _gameState;
}

void GameManager::setLives(unsigned int lives) {
    _lives = lives;
}

unsigned int GameManager::getLives() {
    return _lives;
}

void GameManager::setPoints(unsigned int points) {
    _points = points;
}

unsigned int GameManager::getPoints() {
    return _points;
}

void GameManager::resetGame() {
    _pause = false;
    _gameState = GameManager::GameState::Game;
    _lives = maxLives;
    _points = 0;
}